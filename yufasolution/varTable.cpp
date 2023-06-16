#include "stdafx.h"

#include <string>
#include <vector>

#include "varTable.h"

using namespace std;

extern int level;

vector<Variable> vTable;
vector<Function> fTable;

int vNumber = 0;
int vAddress = 0;
extern string nowFunc;

int calArrayOffset(int dim, int *d) {
	int offset = 1;
	for (int i = 0; i < dim; i++)
		offset *= d[i];
	offset *= 4;
	if (offset == 0)
		return 4;
	return offset;
}

string addVar(bool old, string rName, int dim, int *d) {
	vNumber++;
	Variable a;
	a.num = vNumber;
	a.rName = old ? rName : "var_" + to_string(vNumber);
	a.fName = "var_" + to_string(vNumber);
	a.dimCount = old ? dim : 0;
	if (dim != 0 && old)
		for (int i = 0; i < dim; i++)
			a.dim[i] = d[i];
	a.level = level;
	a.valid = true;
	a.address = vAddress;
	a.func = nowFunc;
	vTable.push_back(a);
	vAddress += old ? calArrayOffset(dim, d) : 4;
	return a.fName;
}

void checkVarTable() {
	for (int i = vTable.size() - 1; i > 0; i--)
		if (vTable[i].level == level)
			vTable[i].valid = false;
}


