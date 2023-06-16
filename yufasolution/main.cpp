#include "stdafx.h"

#include <iostream>
#include <fstream>
#include "lexer.h"
#include "parser.h"
#include "utils.h"

using namespace std;

extern string sysc;
ifstream inputFile;
ofstream outputFile;

void parseSysC() {
	resetsymbolTable();
	getNP();
	GrammarAnalysis();
}

int main() {
	inputFile.open("testfile.txt", ios::in);
	outputFile.open("output.txt", ios::out | ios::ate);

	string str;
	while (getline(inputFile, str)) {
		sysc.append(str);
		sysc.append("\n");
	}

	LexerAnalysis();

	parseSysC();

	inputFile.close();
	outputFile.close();

	return 0;
}
