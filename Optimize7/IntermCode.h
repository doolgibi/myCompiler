
#pragma once
#include<string>
#include<vector>

using namespace std;

struct Quaternion
{
	string ans;
	string x;
	string op;
	string y;
};

struct SymAndCnt
{
	string idenfr;
	int cnt;
};

class IntermCode
{
public:
	IntermCode();
	~IntermCode();

	void insertQuat(string ans, string x, string op, string y);
	int getQuatNum() const { return quatVec.size(); }
	void outputQuats();
	Quaternion getQuaternion(int index) const { return quatVec[index]; }
	void OptimizeCode();
	void processSym(string idenfr);
	vector<SymAndCnt> getSortedSymCnt();

private:
	vector<Quaternion> quatVec;
	vector<SymAndCnt> SymCntSort;

};