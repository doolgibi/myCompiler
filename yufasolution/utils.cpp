#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "utils.h"
#include "varTable.h"
using namespace std;


extern vector<Variable> vTable;

int label = 0;

int stringCount = 0;

string getLabel() {
	label++;
	return "label_" + to_string(label);
}

string getString() {
	stringCount++;
	return "String_" + to_string(stringCount);
}

void splitAssign(int vidx, bool isConstV) {
	Variable &v = vTable[vidx];
	vector<string> value = v.value;

	if (!isConstV) {
		v.value.clear();
	}
	if (value.empty()) {
		return;
	}
	if (v.dimCount == 0) {

		return;
	}
	else if (v.dimCount == 1) {
		int m = v.dim[0];
		for (int i = 0; i < m; i++) {

		}
		return;
	}
	else if (v.dimCount == 2) {
		int m = v.dim[0];
		int n = v.dim[1];
		for (int i = 0; i < m*n; i++) {

		}
		return;
	}
}

bool isNumber(string item) {
	if ((('0' <= char(item[0])) && (char(item[0]) <= '9'))) {
		return true;
	}
	if ((char(item[0]) == '+') || (char(item[0]) == '-')) {
		return true;
	}
	return false;
}

string isContainOffset(string item) {
	bool containOffset = false;
	string offset = "";
	int i = 0;
	while (i < item.size()) {
		if (char(item[i]) == '[') {
			containOffset = true;
			break;
		}
		i++;
	}
	if (!containOffset) {
		return "";
	}
	else {
		for (int j = i + 1; j < item.size() - 1; j++) {
			offset += item[j];
		}
		return offset;
	}
}

string getVarWithoutOffset(string item) {
	if (isContainOffset(item).size() == 0) {
		return item;
	}
	else {
		string ident;
		for (int i = 0; i < item.size(); i++) {
			if (item[i] != '[') {
				ident += item[i];
			}
			else {
				break;
			}
		}
		return ident;
	}
}

string merge(operation o, string left, string right = "") {
	bool isNumLeft = isNumber(left);
	bool isNumRight = isNumber(right);
	if (isNumLeft && isNumRight) {
		int l = stoi(left);
		int r = stoi(right);
		int merge;
		switch (o) {
		case PLUSOP:
			merge = l + r;
			break;
		case MINUOP:
			merge = l - r;
			break;
		case MULTOP:
			merge = l * r;
			break;
		case DIVOP:
			merge = l / r;
			break;
		case MODOP:
			merge = l % r;
			break;
		case ANDOP:
			merge = l && r;
			break;
		case OROP:
			merge = l || r;
			break;
		case LSSOP:
			merge = l < r;
			break;
		case LEQOP:
			merge = l <= r;
			break;
		case GREOP:
			merge = l > r;
			break;
		case GEQOP:
			merge = l >= r;
			break;
		case EQLOP:
			merge = l == r;
			break;
		case NEQOP:
			merge = l != r;
			break;
		case NOTOP:
			merge = !l;
		}
		return to_string(merge);
	}
	else {
		string merge = addVar(false, "", 0, 0);

		return merge;
	}
}
