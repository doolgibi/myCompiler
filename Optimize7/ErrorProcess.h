#pragma once
#include<vector>
#include<fstream>
#include<string>
#include<iostream>

using namespace std;

struct ErrorOutput
{
	int lineID;
	string errType;
};

class ErrorProcess
{
private:
	vector<ErrorOutput> errOutVec;

	inline int checkLineEqual(ErrorOutput e1, ErrorOutput e2) { return e1.lineID == e2.lineID; }
	inline int checkErrEqual(ErrorOutput e1, ErrorOutput e2) { return checkLineEqual(e1, e2) && e1.lineID == e2.lineID; }
	static inline bool cmp(ErrorOutput e1, ErrorOutput e2) { return e1.lineID < e2.lineID; }
	void sortErrOutVec();

public:
	ErrorProcess();
	~ErrorProcess();

	void insertError(int lineID, string errType);
	int getErrNum() const { return errOutVec.size(); }
	void outputError();
};
