#include <string>
#include "varTable.h"
using namespace std;

bool IsExp();
int UnitBranch();




bool CompUnit();


bool ConstDecl();



bool ConstDef();


bool ConstInitVal(int vidx);


bool VarDecl();


bool VarDef();


bool InitVal(int vidx);


bool FuncDef();


bool MainFuncDef();


bool FuncType();


bool FuncFParams(string ident);


bool FuncFParam(string ident);


bool Block(bool isFuncFollow);


/*语句 Stmt → LeftVal '=' Exp ';'
| [Exp] ';'
| Block
| 'if' '(' Cond ')' Stmt [ 'else' Stmt ]
| 'while' '(' Cond ')' Stmt
| 'break' ';' | 'continue' ';'
| 'return' [Exp] ';'
| LeftVal '=' 'getint''('')'';'
| 'printf''('FormatString{','Exp}')'';'
*/
bool Stmt();


string Exp();


string Cond();


string LeftVal(bool isGet);


string PrimaryExp();


string Number();


string normExp();


string normOperate();


bool FuncRParams(string ident);


string MulExp();


string AddExp();


string RelExp();


string EqExp();


string LAndExp(string andEndLabel);


string LOrExp();


string ConstExp();


bool GrammarAnalysis();
