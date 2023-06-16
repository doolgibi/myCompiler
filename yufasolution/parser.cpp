#include "stdafx.h"

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <vector>

#include "parser.h"
#include "lexer.h"
#include "utils.h"
using namespace std;

extern int symbol;
extern int si;
extern int ci;

extern string nowToken;
extern ofstream outputFile;
extern vector<CompSymbol> symbolTable;
extern vector<Variable> vTable;
extern vector<Function> fTable;

vector<pair<string, string>> strings;
extern int vAddress;
string nowFunc = "";
int level = 0;

bool ConstDecl() {
	if (symbol != CONSTTK)
		return false;
	lexerInfo();
	getP();
	getNP();
	ConstDef();
	while (symbol == COMMA) {
		lexerInfo();
		getNP();
		ConstDef();
	}
	lexerInfo();
	getNP();
	outputFile << "<ConstDecl>" << endl;
	return true;
}

bool ConstDef() {
	lexerInfo();
	int dim = 0;
	int d[2];
	string ident = nowToken;
	getP();
	while (symbol == LBRACK) {
		dim++;
		getNP();
		d[dim - 1] = stoi(ConstExp());
		lexerInfo();
		getP();
	}
	addVar(true, ident, dim, d);
	int vidx = vTable.size() - 1;
	getNP();
	ConstInitVal(vidx);
	splitAssign(vidx, true);
	outputFile << "<ConstDef>" << endl;
	return true;
}

bool ConstInitVal(int vidx) {
	if (symbol != LBRACE) {
		vTable[vidx].value.push_back(ConstExp());
	}
	else {
		lexerInfo();
		getNP();
		if (symbol != RBRACE) {
			ConstInitVal(vidx);
			while (symbol == COMMA) {
				lexerInfo();
				getNP();
				ConstInitVal(vidx);
			}
		}
		lexerInfo();
		getNP();
	}
	outputFile << "<ConstInitVal>" << endl;
	return true;
}

bool VarDecl() {
	lexerInfo();
	getNP();
	VarDef();
	while (symbol == COMMA) {
		lexerInfo();
		getNP();
		VarDef();
	}
	lexerInfo();
	getNP();
	outputFile << "<VarDecl>" << endl;
	return true;
}


bool VarDef() {
	lexerInfo();
	int dim = 0;
	int d[2];
	string ident = nowToken;

	getNP();
	while (symbol == LBRACK) {
		lexerInfo();
		dim++;
		getNP();
		d[dim - 1] = stoi(ConstExp());
		lexerInfo();
		getNP();
	}
	addVar(true, ident, dim, d);
	int vidx = vTable.size() - 1;
	if (symbol == ASSIGN) {
		lexerInfo();
		getNP();
		InitVal(vidx);
		splitAssign(vidx, false);
	}
	outputFile << "<VarDef>" << endl;
	return true;
}

bool InitVal(int vidx) {
	if (symbol != LBRACE) {
		string exp = Exp();
		vTable[vidx].value.push_back(exp);
	}
	else {
		lexerInfo();
		getNP();
		if (symbol != RBRACE) {
			InitVal(vidx);
			while (symbol == COMMA) {
				lexerInfo();
				getNP();
				InitVal(vidx);
			}
		}
		lexerInfo();
		getNP();
	}
	outputFile << "<InitVal>" << endl;
	return true;
}

bool FuncDef() {
	bool isFuncFollow = true;
	vAddress = 0;
	level++;

	Function f;
	f.type = FuncType();
	lexerInfo();
	string ident = nowToken;

	f.ident = ident;
	nowFunc = ident;
	vector<Variable> params;
	f.params = params;
	fTable.push_back(f);

	getP();
	getNP();
	if (symbol != RPARENT)
		FuncFParams(ident);
	lexerInfo();
	getNP();
	Block(isFuncFollow);
	outputFile << "<FuncDef>" << endl;
	level -= 1;
	nowFunc = "";
	fTable[fTable.size() - 1].length = vAddress + 8;
	return true;
}


string Exp() {
	string var = AddExp();
	outputFile << "<Exp>" << endl;
	return var;
}


string Cond() {
	string var = LOrExp();
	outputFile << "<Cond>" << endl;
	return var;
}

bool isAllNumber(vector<string> list) {
	for (int i = 0; i < list.size(); i++)
		if (!isNumber(list[i]))
			return false;
	return true;
}

string LeftValGetValue(string ident, vector<string> indexs) {
	Variable variable;
	for (int i = vTable.size() - 1; i >= 0; i--) {
		if ((vTable[i].rName == ident) && (vTable[i].valid)) {
			variable = vTable[i];
			break;
		}
	}

	if (variable.dimCount == indexs.size()) {
		if ((!variable.value.empty()) && (isAllNumber(indexs)) && (isAllNumber(variable.value))) {
			switch (indexs.size()) {
			case 0: {
				return variable.value[0];
				break;
			}
			case 1: {
				return variable.value[stoi(indexs[0])];
				break;
			}
			case 2: {
				int offset = stoi(indexs[0]) * variable.dim[1] + stoi(indexs[1]);
				return variable.value[offset];
				break;
			}
			}
		}
		else {
			switch (indexs.size()) {
			case 0:
				return variable.fName;
				break;
			case 1: {
				string ne = addVar(false, "", 0, 0);
				return ne;
			}
			case 2: {
				string ne = addVar(false, "", 0, 0);
				return ne;
			}
			}
		}
	}

	else if (variable.dimCount > indexs.size()) {
		if (indexs.size() == 0) {
			return variable.fName + "[" + "0" + "]";
		}
		else if ((indexs.size() == 1) && (variable.dimCount == 2)) {
			string neoV = merge(MULTOP, indexs[0], to_string(variable.dim[1]));
			return variable.fName + "[" + neoV + "]";
		}
	}
	return "";
}

bool MainFuncDef() {

	bool isFuncFollow = true;
	level++;
	vAddress = 0;
	nowFunc = "main";

	lexerInfo();
	getP(); getP(); getP();
	getNP();
	Block(isFuncFollow);
	outputFile << "<MainFuncDef>" << endl;

	level -= 1;
	nowFunc = "";
	vector<Variable> params;
	Function function;
	function.ident = "main";
	function.type = 1;
	function.length = vAddress + 8;
	function.params = params;
	fTable.push_back(function);
	return true;
}


bool FuncType() {
	lexerInfo();
	bool isInt = (symbol == INTTK);
	getNP();
	outputFile << "<FuncType>" << endl;
	return isInt;
}


bool FuncFParams(string ident) {
	FuncFParam(ident);
	while (symbol == COMMA) {
		lexerInfo();
		getNP();
		FuncFParam(ident);
	}
	outputFile << "<FuncFParams>" << endl;
	return true;
}

bool FuncFParam(string ident) {
	lexerInfo();
	getP();
	int dim = 0;
	int d[2];
	string varident = nowToken;
	getNP();
	if (symbol == LBRACK) {
		lexerInfo();
		dim++;
		d[dim - 1] = 0;
		getP();
		getNP();
		while (symbol == LBRACK) {
			lexerInfo();
			dim++;
			getNP();
			d[dim - 1] = stoi(ConstExp());
			lexerInfo();
			getNP();
		}
	}
	addVar(true, varident, dim, d);
	Variable &v = vTable[vTable.size() - 1];
	fTable[fTable.size() - 1].params.push_back(v);

	outputFile << "<FuncFParam>" << endl;
	return true;
}



bool Block(bool isFuncFollow) {
	lexerInfo();
	if (!isFuncFollow)
		level++;
	getNP();
	while (true) {
		if (symbol == RBRACE) {
			lexerInfo();
			break;
		}
		if (ConstDecl()) {}
		else if (symbol == INTTK) {
			VarDecl();
		}
		else {
			Stmt();
		}
	}
	getNP();
	outputFile << "<Block>" << endl;

	checkVarTable();
	if (!isFuncFollow) {
		level -= 1;
	}
	return true;
}

bool Stmt() {
	switch (symbol) {
	case LBRACE: {
		Block(false);
		break;
	}
	case IFTK: {
		lexerInfo();
		getP();
		getNP();
		string op = Cond();
		lexerInfo();
		getNP();
		Stmt();
		if (symbol == ELSETK) {
			lexerInfo();
			getNP();
			Stmt();
		}
		break;
	}
	case WHILETK: {
		lexerInfo();
		getP();
		getNP();
		string op = Cond();
		lexerInfo();
		getNP();
		Stmt();
		break;
	}
	case BREAKTK: {
		lexerInfo();
		getP();
		getNP();
		break;
	}
	case CONTINUETK: {
		lexerInfo();
		getP();
		getNP();
		break;
	}
	case RETURNTK: {
		lexerInfo();
		getNP();
		if (symbol == SEMICN) {
			lexerInfo();
			getNP();

			break;
		}
		string ret = Exp();
		lexerInfo();
		getNP();

		break;

	}
	case PRINTFTK: {
		lexerInfo();
		vector<int> consequence;
		vector<pair<string, string>> strList;
		getP();
		getP();
		string formatstring = nowToken;
		string curString;

		for (int i = 0; i<formatstring.size(); i++) {
			if ((formatstring[i] == '%') && (formatstring[i + 1] == 'd')) {
				if (!curString.empty()) {
					string stringName = getString();
					strings.emplace_back(stringName, curString);
					strList.emplace_back(stringName, curString);
					consequence.push_back(0);
				}
				consequence.push_back(1);
				i++;
				curString = "";
			}
			else {
				curString += formatstring[i];
			}
		}
		if (!curString.empty()) {
			string stringName = getString();
			strings.emplace_back(stringName, curString);
			strList.emplace_back(stringName, curString);
			consequence.push_back(0);
		}
		getNP();
		vector<string> varList;
		while (symbol == COMMA) {
			lexerInfo();
			getNP();
			varList.push_back(Exp());
		}
		lexerInfo();
		getP();
		getNP();

		for (int i = 0; i < consequence.size(); i++) {
			if (consequence[i] == 1) {

				varList.erase(varList.begin());
			}
			else if (consequence[i] == 0) {

				strList.erase(strList.begin());
			}
		}
		break;
	}

	case SEMICN:
		lexerInfo();
		getNP();
		break;
	case IDENFR: {
		if (IsExp()) {
			Exp();
			lexerInfo();
			getNP();
		}
		else {
			string LeftVal1;
			LeftVal1 = LeftVal(false);
			string offset = isContainOffset(LeftVal1);
			lexerInfo();
			getNP();
			if (symbol == GETINTTK) {
				if (offset.size() != 0)
					string newV = addVar(false, "", 0, 0);
				lexerInfo();
				for (int i = 0; i < 3; i++)
					getP();
				getNP();
			}
			else {
				string rval = Exp();
				lexerInfo();
				getNP();
			}
		}
		break;
	}

	default:
		Exp();
		lexerInfo();
		getNP();
	}
	outputFile << "<Stmt>" << endl;
	return true;
}

string LeftValGetLeft(string ident, vector<string> indexs) {
	for (int i = vTable.size() - 1; i >= 0; i--) {
		if ((vTable[i].rName == ident) && (vTable[i].valid)) {
			if (indexs.empty()) {
				return vTable[i].fName;
			}
			else if (indexs.size() == 1) {
				return vTable[i].fName + "[" + indexs[0] + "]";
			}
			else if (indexs.size() == 2) {
				string neoV = merge(MULTOP, indexs[0], to_string(vTable[i].dim[1]));
				string neoVV = merge(PLUSOP, neoV, indexs[1]);
				return vTable[i].fName + "[" + neoVV + "]";
			}
		}
	}
	return "";
}

string LeftVal(bool isGet) {
	lexerInfo();
	string re;
	string ident = nowToken;
	vector<string> indexs;
	getNP();
	while (true) {
		if (symbol == LBRACK) {
			lexerInfo();
			getNP();
			string index = Exp();
			indexs.push_back(index);
			lexerInfo();
			getNP();
		}
		else {
			break;
		}
	}
	if (isGet) {
		re = LeftValGetValue(ident, indexs);
	}
	else {
		re = LeftValGetLeft(ident, indexs);
	}
	outputFile << "<LVal>" << endl;
	return re;
}



string PrimaryExp() {
	string var;
	if (symbol == LPARENT) {
		lexerInfo();
		getNP();
		var = Exp();
		lexerInfo();
		getNP();
	}
	else if (symbol != INTCON) {
		var = LeftVal(true);
	}
	else if (symbol == INTCON) {
		var = Number();
	}
	outputFile << "<PrimaryExp>" << endl;
	return var;
}


string Number() {
	if (symbol == INTCON) {
		lexerInfo();
		string var = nowToken;
		getNP();
		outputFile << "<Number>" << endl;
		return var;
	}
	return "";
}


string normExp() {
	string var;
	if (symbol == PLUS || symbol == MINU || symbol == NOT) {
		string neoOp = normOperate();
		if (neoOp == "+")
			var = normExp();
		else if (neoOp == "-")
			var = merge(MINUOP, "0", normExp());
		else if (neoOp == "!")
			var = merge(NOTOP, normExp(), "");
	}
	else if (symbol == LPARENT || symbol == INTCON) {
		var = PrimaryExp();
	}
	else if (symbol == IDENFR) {
		if (symbolTable[si].symbol == LPARENT) {
			lexerInfo();
			string ident = nowToken;
			getP();
			getNP();
			if (symbol != RPARENT) {
				FuncRParams(ident);
			}
			lexerInfo();
			getNP();
		}
		else {
			var = PrimaryExp();
		}
	}
	outputFile << "<UnaryExp>" << endl;
	return var;
}


string normOperate() {
	if (symbol == PLUS || symbol == MINU || symbol == NOT) {
		string neoOp;
		switch (symbol) {
		case PLUS:
			neoOp = "+";
			break;
		case MINU:
			neoOp = "-";
			break;
		case NOT:
			neoOp = "!";
			break;
		}
		lexerInfo();
		getNP();
		outputFile << "<UnaryOp>" << endl;
		return neoOp;
	}
	return "";
}



void funcParamPush(string ident, int dim, string var) {
	Function function;
	for (int i = fTable.size() - 1; i >= 0; i--) {
		if (fTable[i].ident == ident) {
			function = fTable[i];
		}
	}
	string offset = isContainOffset(var);
}

bool FuncRParams(string ident) {
	string var;
	int dim = 0;
	var = Exp();
	funcParamPush(ident, dim, var);
	while (symbol == COMMA) {
		lexerInfo();
		dim++;
		getNP();
		var = Exp();
		funcParamPush(ident, dim, var);
	}
	outputFile << "<FuncRParams>" << endl;
	return true;
}


string MulExp() {
	string var = normExp();
	outputFile << "<MulExp>" << endl;
	while (symbol == MULT || symbol == DIV || symbol == MOD) {
		lexerInfo();
		if (symbol == MULT) {
			getNP();
			var = merge(MULTOP, var, normExp());
		}
		else if (symbol == DIV) {
			getNP();
			var = merge(DIVOP, var, normExp());
		}
		else if (symbol == MOD) {
			getNP();
			var = merge(MODOP, var, normExp());
		}
		outputFile << "<MulExp>" << endl;
	}
	return var;
}


string AddExp() {
	string var = MulExp();
	outputFile << "<AddExp>" << endl;
	while (symbol == PLUS || symbol == MINU) {
		lexerInfo();
		if (symbol == PLUS) {
			getNP();
			var = merge(PLUSOP, var, MulExp());
		}
		else if (symbol == MINU) {
			getNP();
			var = merge(MINUOP, var, MulExp());
		}
		outputFile << "<AddExp>" << endl;
	}
	return var;
}


string RelExp() {
	string var = AddExp();
	outputFile << "<RelExp>" << endl;
	while (symbol == LSS || symbol == GRE || symbol == LEQ || symbol == GEQ) {
		lexerInfo();
		if (symbol == LSS) {
			getNP();
			var = merge(LSSOP, var, AddExp());
		}
		else if (symbol == GRE) {
			getNP();
			var = merge(GREOP, var, AddExp());
		}
		else if (symbol == LEQ) {
			getNP();
			var = merge(LEQOP, var, AddExp());
		}
		else if (symbol == GEQ) {
			getNP();
			var = merge(GEQOP, var, AddExp());
		}
		outputFile << "<RelExp>" << endl;
	}
	return var;
}


string EqExp() {
	string var = RelExp();
	outputFile << "<EqExp>" << endl;
	while (symbol == EQL || symbol == NEQ) {
		lexerInfo();
		if (symbol == EQL) {
			getNP();
			var = merge(EQLOP, var, RelExp());
		}
		else if (symbol == NEQ) {
			getNP();
			var = merge(NEQOP, var, RelExp());
		}
		outputFile << "<EqExp>" << endl;
	}
	return var;
}


string LAndExp(string andEndLabel) {
	string eqExp = EqExp();
	outputFile << "<LAndExp>" << endl;
	while (symbol == AND) {
		lexerInfo();
		getNP();
		eqExp = EqExp();
		outputFile << "<LAndExp>" << endl;
	}
	return "";
}


string LOrExp() {
	string var = addVar(false, "", 0, 0);
	string andEndLabel = getLabel();
	string orEndLabel = getLabel();
	LAndExp(andEndLabel);
	outputFile << "<LOrExp>" << endl;
	while (symbol == OR) {
		lexerInfo();
		getNP();
		andEndLabel = getLabel();
		LAndExp(andEndLabel);
		outputFile << "<LOrExp>" << endl;
	}
	return var;
}
string ConstExp() {
	string var;
	var = AddExp();
	outputFile << "<ConstExp>" << endl;
	return var;
}

bool IsExp() {
	for (int i = si; i < ci; i++) {
		if (symbolTable[i].symbol == ASSIGN)
			return false;
		else if (symbolTable[i].symbol == SEMICN)
			return true;
	}
	return false;
}

int UnitBranch() {
	int i = si;
	if (symbolTable[i].symbol == MAINTK)
		return 1;
	else if (symbolTable[i + 1].symbol == LPARENT)
		return 0;
	return -1;
}

bool CompUnit() {
	bool exitFlag = false;
	while (1) {
		if (symbol == CONSTTK) {
			ConstDecl();
		}
		else {
			switch (UnitBranch()) {
			case 1:
				MainFuncDef();
				exitFlag = true;
				break;
			case 0:
				FuncDef();
				break;
			case -1:
				VarDecl();
				break;
			default:
				return false;
			}
		}
		if (exitFlag) {
			break;
		}
	}
	outputFile << "<CompUnit>" << endl;
	return true;
}
bool GrammarAnalysis() {
	return CompUnit();
}