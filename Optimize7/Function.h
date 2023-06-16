
#pragma once
#include<string>
#include<vector>
#include<map>
#include"symbolTable.h"

using namespace std;

class Function
{
private:
	string funcName;
	int type;
	vector<string> paras;
	vector<string> defs;
	vector<string> arrs2D;
	map<string, int> paraMap;
	map<string, int> defMap;
	map<string, int> paraType;
	map<string, int> defType;
	map<string, int> ArrCols;
	int raOff = -1;
	int paraNum = 0;
	int defNum = 0;
	int totalNum = 0;
	int defAndRaSize = 0;

public:
	Function();
	Function(string funcName, int type);
	~Function();

	void insertPara(string paraName, int type);
	void insertDef(string defName, int type, int size);
	void insertDef(string defName, int type);
	void insertRa();
	void insert2DCols(string arrName, int cols);

	void offsetUp(int size);
	void offsetDown(int size);

	inline bool hasPara(string paraName) { return paraMap.find(paraName) != paraMap.end(); }
	inline bool hasDef(string defName) { return defMap.find(defName) != defMap.end(); }
	inline bool hasCheck(string name) { return hasPara(name) || hasDef(name); }

	inline int getRaOff() { return raOff; }
	int getOffset(string name);

	inline int getParaSize() { return paraNum * 4; }
	inline int getDefAndRaSize() { return defAndRaSize; }

	inline string getParaName(int paraId) { return paras[paraId]; }

	inline int getParaNum() { return paraNum; }
	inline int getDefNum() { return defNum; }
	inline int getTotalNum() { return totalNum; }

	int getType(string name);

	inline int getArrCols(string arrName) { return ArrCols[arrName]; }

	inline string getFuncName() { return funcName; }

	void showFuncInfo();
};