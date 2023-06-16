#pragma once
#include <string>
#include <map>
#include <vector>

using namespace std;

vector<string> regPool = { "$v1", "$a1", "$a2", "$a3", "$t3", "$t4", "$t5", "$t6", "$t7", "$t8", "$t9", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$fp" };

inline int getRegPoolSize() { return regPool.size(); }

enum OP
{
	ADD,
	SUB,
	MUL,
	DIV
};

inline string reverseOp(string op)
{
	if (op == "==") {
		return "!=";
	}
	else if (op == "!=") {
		return "==";
	}
	else if (op == "<=") {
		return ">";
	}
	else if (op == ">=") {
		return "<";
	}
	else if (op == "<") {
		return ">=";
	}
	else if (op == ">") {
		return "<=";
	}
	else {
		return op;
	}
}

inline bool isCmpOp(string op) { return op == "==" || op == "!=" || op == "<" || op == ">" || op == "<=" || op == ">="; }
inline bool isDigit(string value) { return (value[0] >= '0' && value[0] <= '9') || value[0] == '-'; }
inline bool isChar(string value) { return value[0] == '\''; }

inline string calc(string x, string y, int op)
{
	int n1, n2;
	
	if (isDigit(x)) {
		n1 = stoi(x);
	}
	else {
		n1 = (int)x[1];
	}

	if (isDigit(y)) {
		n2 = stoi(y);
	}
	else {
		n2 = (int)y[1];
	}

	int ans = 0;

	switch (op)
	{
	case ADD: ans = n1 + n2;
		break;
	case SUB: ans = n1 - n2;
		break;
	case MUL: ans = n1 * n2;
		break;
	case DIV: ans = n1 / n2;
		break;
	default: break;

	}

	return to_string(ans);

}

inline int getValue(string s)
{
	if (isDigit(s)) {
		return stoi(s);
	}
	else {
		return (int)s[1];
	}
}

inline int getPow(int x)
{
	int cnt = 0;

	if (x < 0) {
		x = -x;
	}

	while (x > 1) {
		if (x % 2 == 0) {
			cnt++;
		}
		else {
			return -1;
		}

		x = x / 2;
	}
	return cnt;

}