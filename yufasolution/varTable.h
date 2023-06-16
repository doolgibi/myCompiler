#ifndef VTABLE_H
#define VTABLE_H

#include <string>
#include <vector>
#include <map>

using namespace std;

struct Variable {
	int num;
	string rName = "";
	string fName = "";
	int dimCount;
	int dim[2];
	int level;
	bool valid;
	int address;
	string func = "";
	vector<string> value;
};

struct Function {
	string ident;
	int type;
	int length;
	vector<Variable> params;
};

string addVar(bool old, string rName, int dim, int *d = nullptr);
void checkVarTable();
#endif