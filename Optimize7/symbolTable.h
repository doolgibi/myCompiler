#pragma once
#include<string>

using namespace std;

enum KindEnum {
	CONST,
	VAR,
	FUNC,
	PARAM
};

enum TypeEnum {
	CHAR,
	INT,
	VOID
};

struct Symbol
{
	string idenfr;
	int kind;
	int type;
	int level;
	int dim;
	string addrOffset;
};

inline string numToType(int type)
{
	switch (type)
	{
	case CHAR: return "CHAR";
	case INT: return "INT";
	case VOID: return "VOID";
	default:
		return "TYPEERR";
	}
}

inline string numToKind(int kind)
{
	switch (kind)
	{
	case CONST: return "CONST";
	case VAR: return "VAR";
	case FUNC: return "FUNC";
	case PARAM: return "PARAM";
	default:
		return "KINDERR";
	}
}