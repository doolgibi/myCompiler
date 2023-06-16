#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <string>

#include "lexer.h"

using namespace std;

#define isBlank   (posChar == ' ' || posChar == '\n' || posChar == '\t' || posChar == '\r' || posChar == '\f' || posChar == '\v')
#define isNewLine (posChar == '\n')
#define isLetter  ((posChar >= 'A' && posChar <= 'Z') || (posChar >= 'a' && posChar <= 'z') || (posChar == '_'))
#define isDigit   (posChar >= '0' && posChar <= '9')
#define isPlus    (posChar == '+')
#define isMinu    (posChar == '-')
#define isMult    (posChar == '*')
#define isDiv     (posChar == '/')
#define isMod     (posChar == '%')
#define isAnd     (posChar == '&')
#define isOr      (posChar == '|')
#define isLss     (posChar == '<')
#define isGre     (posChar == '>')
#define isExcla   (posChar == '!')
#define isAssign  (posChar == '=')
#define isSemicn  (posChar == ';')
#define isComma   (posChar == ',')
#define isLparent (posChar == '(')
#define isRparent (posChar == ')')
#define isLbrack  (posChar == '[')
#define isRbrack  (posChar == ']')
#define isLbrace  (posChar == '{')
#define isRbrace  (posChar == '}')
#define isDquo    (posChar == '\"')
#define isEOF     (indexs >= sysc.size())

const char resWord[12][10]{
	"main",
	"const",
	"int",
	"break",
	"continue",
	"if",
	"else",
	"while",
	"getint",
	"printf",
	"return",
	"void"
};

const int resWordNum = 12;

char posChar;
char token[100000];
int tokenI = 0;

vector<CompSymbol> symbolTable;
int si = 0;
int ci = 0;
int curLine;
int lastLine;

int symbol;
string nowToken;
int indexs = 0;
int line = 1;
string sysc;
extern ofstream outputFile;

void clearToken() {
	tokenI = 0;
}

void catchToken() {
	token[tokenI++] = posChar;
}

void getCh() {
	posChar = sysc[indexs++];
	if (isNewLine)
		line++;
}
void retract() {
	if (isNewLine)
		line--;
	indexs--;
}

int isResWord() {
	for (int i = 0; i < resWordNum; i++)
		if (strcmp(resWord[i], token) == 0)
			return i;
	return -1;
}

int tokenAnalysis() {
	clearToken();
	getCh();
	while (isBlank)
		getCh();
	if (isEOF)
		return -1;
	if (isLetter) {
		while (isLetter || isDigit) {
			catchToken();
			getCh();
		}
		retract();
		token[tokenI] = 0;
		int resValue = isResWord();
		if (resValue == -1)
			symbol = IDENFR;
		else
			symbol = (resType)resValue;
		return 1;
	}
	else if (isDigit) {
		while (isDigit) {
			catchToken();
			getCh();
		}
		retract();
		token[tokenI] = 0;
		symbol = INTCON;
		return 1;
	}
	else if (isDquo) {
		getCh();
		while (!isDquo) {
			catchToken();
			getCh();
		}
		symbol = STRCON;
		token[tokenI] = '\0';
		return 1;
	}
	else if (isAnd) {
		getCh();
		if (isAnd) {
			symbol = AND;
			return 1;
		}
		else {
			return -1;
		}
	}
	else if (isOr) {
		getCh();
		if (isOr) {
			symbol = OR;
			return 1;
		}
		else {
			return -1;
		}
	}
	else if (isMinu) {
		symbol = MINU;
		return 1;
	}
	else if (isMult) {
		symbol = MULT;
		return 1;
	}
	else if (isPlus) {
		symbol = PLUS;
		return 1;
	}
	else if (isDiv) {
		getCh();
		if (isDiv) {
			while (!isNewLine)
				getCh();
			symbol = ANNOTATION;
			return 1;
		}
		else if (isMult) {
			while (true) {
				getCh();
				if (isMult) {
					getCh();
					if (isDiv) {
						symbol = ANNOTATION;
						break;
					}
					retract();
				}
			}
			return 1;
		}
		retract();
		symbol = DIV;
		return 1;
	}
	else if (isMod) {
		symbol = MOD;
		return 1;
	}
	else if (isLss) {
		getCh();
		if (isAssign) {
			symbol = LEQ;
		}
		else {
			symbol = LSS;
			retract();
		}
		return 1;
	}
	else if (isGre) {
		getCh();
		if (isAssign) {
			symbol = GEQ;
		}
		else {
			symbol = GRE;
			retract();
		}
		return 1;
	}
	else if (isExcla) {
		getCh();
		if (isAssign) {
			symbol = NEQ;
		}
		else {
			retract();
			symbol = NOT;
		}
		return 1;
	}
	else if (isAssign) {
		getCh();
		if (isAssign) {
			symbol = EQL;
		}
		else {
			symbol = ASSIGN;
			retract();
		}
		return 1;
	}
	else if (isSemicn) {
		symbol = SEMICN;
		return 1;
	}
	else if (isComma) {
		symbol = COMMA;
		return 1;
	}
	else if (isLparent) {
		symbol = LPARENT;
		return 1;
	}
	else if (isRparent) {
		symbol = RPARENT;
		return 1;
	}
	else if (isLbrack) {
		symbol = LBRACK;
		return 1;
	}
	else if (isRbrack) {
		symbol = RBRACK;
		return 1;
	}
	else if (isLbrace) {
		symbol = LBRACE;
		return 1;
	}
	else if (isRbrace) {
		symbol = RBRACE;
		return 1;
	}
	else {
		return -1;
	}
}

int lexerInfo() {
	if (symbol == IDENFR)
		outputFile << "IDENFR " << nowToken << endl;
	else if (symbol == INTCON)
		outputFile << "INTCON " << nowToken << endl;
	else if (symbol == STRCON)
		outputFile << "STRCON " << "\"" << nowToken << "\"" << endl;
	else
		outputFile << resNameStr[symbol] << endl;
	return 0;
}

int LexerAnalysis() {
	while (tokenAnalysis() != -1) {
		if (symbol == ANNOTATION)
			continue;
		CompSymbol compSymbol;
		compSymbol.symbol = symbol;
		compSymbol.stringContent = token;
		compSymbol.line = line;
		symbolTable.push_back(compSymbol);
		si++;
	}
	ci = si;
	si = 0;
	return 0;
}

int getP_error() {
	if (si == ci)
		return 0;
	symbol = symbolTable[si].symbol;
	nowToken = symbolTable[si].stringContent;
	lastLine = curLine;
	curLine = symbolTable[si].line;

	si++;
	return 1;
}

int getNP_error() {
	if (si == ci)
		return 0;
	symbol = symbolTable[si].symbol;
	nowToken = symbolTable[si].stringContent;
	lastLine = curLine;
	curLine = symbolTable[si].line;
	si++;
	return 1;
}

int getP() {
	if (si == ci)
		return 0;
	symbol = symbolTable[si].symbol;
	nowToken = symbolTable[si].stringContent;
	lastLine = curLine;
	curLine = symbolTable[si].line;
	lexerInfo();
	si++;
	return 1;
}

int getNP() {
	if (si == ci)
		return 0;
	symbol = symbolTable[si].symbol;
	nowToken = symbolTable[si].stringContent;
	lastLine = curLine;
	curLine = symbolTable[si].line;
	si++;
	return 1;
}

void resetsymbolTable() {
	si = 0;
}