#ifndef utils_h
#define utils_h
#include <string>
#include "varTable.h"
using namespace std;

enum operation {
	PLUSOP,
	MINUOP,
	MULTOP,
	DIVOP,
	MODOP,
	ANDOP,
	OROP,
	LSSOP,
	LEQOP,
	GREOP,
	GEQOP,
	EQLOP,
	NEQOP,
	NOTOP,
	ASSIGNOP,
	GOTO,
	BZ,
	BNZ,
	LABEL,
	PUSH,
	PUSHADDR,
	CALL,
	RET,
	RETVALUE,
	SCAN,
	PRINTD,
	PRINTS,
	CONST,
	CONSTARRAY,
	ARRAY,
	VAR,
	FUNC,
	PARAM,
	GETARRAY,
	PUTARRAY,
	EXIT,
};

class midCode {
public:
	operation op;
	string z;
	string x;
	string y;
	midCode(operation o, string zz = "", string xx = "", string yy = "") : op(o), z(zz), x(xx), y(yy) {}
};

void splitAssign(int vidx, bool isConstV);
string isContainOffset(string item);
string getVarWithoutOffset(string item);
bool isNumber(string item);
string merge(operation o, string left, string right);

void outputMidCode();

string getString();
string getLabel();

#endif 
