#pragma once
#ifndef LEXICAL_LEXICAL_H
#define LEXICAL_LEXICAL_H

#define MAXLINE 100000

struct CompSymbol {
	int symbol = 0;
	std::string stringContent;
	int line = 0;
};
enum resType {
	MAINTK,
	CONSTTK,
	INTTK,
	BREAKTK,
	CONTINUETK,
	IFTK,
	ELSETK,
	WHILETK,
	GETINTTK,
	PRINTFTK,
	RETURNTK,
	VOIDTK,
	IDENFR,
	INTCON,
	STRCON,
	NOT,
	AND,
	OR,
	PLUS,
	MINU,
	MULT,
	DIV,
	MOD,
	LSS,
	LEQ,
	GRE,
	GEQ,
	EQL,
	NEQ,
	ASSIGN,
	SEMICN,
	COMMA,
	LPARENT,
	RPARENT,
	LBRACK,
	RBRACK,
	LBRACE,
	RBRACE,
	ANNOTATION
};

const char resNameStr[40][20] = {
	"MAINTK main",
	"CONSTTK const",
	"INTTK int",
	"BREAKTK break",
	"CONTINUETK continue",
	"IFTK if",
	"ELSETK else",
	"WHILETK while",
	"GETINTTK getint",
	"PRINTFTK printf",
	"RETURNTK return",
	"VOIDTK void",
	"IDENFR ",
	"INTCON ",
	"",
	"NOT !",
	"AND &&",
	"OR ||",
	"PLUS +",
	"MINU -",
	"MULT *",
	"DIV /",
	"MOD %",
	"LSS <",
	"LEQ <=",
	"GRE >",
	"GEQ >=",
	"EQL ==",
	"NEQ !=",
	"ASSIGN =",
	"SEMICN ;",
	"COMMA ,",
	"LPARENT (",
	"RPARENT )",
	"LBRACK [",
	"RBRACK ]",
	"LBRACE {",
	"RBRACE }",
	""
};

void clearToken();
void catchToken();
void getCh();
void retract();
int isResWord();

int tokenAnalysis();
int lexerInfo();
int LexerAnalysis();
int getP();
int getNP();
int getP_error();
int getNP_error();
int print();
void resetsymbolTable();

#endif 
