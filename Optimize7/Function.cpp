
//#include "stdafx.h"
#include "Function.h"
#include<string>
#include<iostream>

using namespace std;

Function::Function()
{
}

Function::Function(string funcName, int type)
{
	Function::funcName = funcName;
	Function::type = type;
}

Function::~Function()
{
}

void Function::insertPara(string paraName, int type)
{
	paraType[paraName] = type;
	paraMap[paraName] = totalNum * 4;
	paras.push_back(paraName);
	totalNum++;
	paraNum++;
}

void Function::insertDef(string defName, int type, int size)
{
	defType[defName] = type;
	defMap[defName] = 0;
	for (int i = 0; i < paraNum; i++)
	{
		paraMap[paras[i]] += size;
	}
	for (int i = 0; i < defNum; i++)
	{
		defMap[defs[i]] += size;
	}
	defs.push_back(defName);
	totalNum++;
	defNum++;
	defAndRaSize += size;
}

void Function::insertDef(string defName, int type)
{
	defType[defName] = type;
	defMap[defName] = 0;
	for (int i = 0; i < paraNum; i++)
	{
		paraMap[paras[i]] += 4;
	}
	for (int i = 0; i < defNum; i++)
	{
		defMap[defs[i]] += 4;
	}
	defs.push_back(defName);
	totalNum++;
	defNum++;
	defAndRaSize += 4;
}

void Function::insertRa()
{
	for (int i = 0; i < paraNum; i++)
	{
		paraMap[paras[i]] += 4;
	}
	for (int i = 0; i < defNum; i++)
	{
		defMap[defs[i]] += 4;
	}
	raOff = 0;
	defAndRaSize += 4;
}

void Function::insert2DCols(string arrName, int cols)
{
	ArrCols[arrName] = cols;
	arrs2D.push_back(arrName);
}

void Function::offsetUp(int size)
{
	for (int i = 0; i < paraNum; i++)
	{
		paraMap[paras[i]] += size;
	}
	for (int i = 0; i < defNum; i++)
	{
		defMap[defs[i]] += size;
	}
	raOff += size;
}

void Function::offsetDown(int size)
{
	for (int i = 0; i < paraNum; i++)
	{
		paraMap[paras[i]] -= size;
	}
	for (int i = 0; i < defNum; i++)
	{
		defMap[defs[i]] -= size;
	}
	raOff -= size;
}

int Function::getOffset(string name)
{
	if (hasPara(name))
	{
		return paraMap[name];
	}
	else
	{
		return defMap[name];
	}
}

int Function::getType(string name)
{
	if (hasPara(name)) return paraType[name];
	else if (hasDef(name)) return defType[name];
	else
	{
		cout << "[getType] name not exist !!!!!!!!!!!!!!!!!!!!" << endl;
		return 0;
	}
}

void Function::showFuncInfo()
{
	cout << "ra\t" << raOff << endl;
	cout << "====[Defs]====\t" << defNum << endl;
	cout << "[name]\t[type]\t[offset]" << endl;
	for (int i = 0; i < defNum; i++)
	{
		cout << defs[i] << "\t" << numToType(defType[defs[i]]) << "\t" << defMap[defs[i]] << endl;
	}
	cout << "====[Paras]====\t" << paraNum << endl;
	cout << "[name]\t[type]\t[offset]" << endl;
	for (int i = 0; i < paraNum; i++)
	{
		cout << paras[i] << "\t" << numToType(paraType[paras[i]]) << "\t" << paraMap[paras[i]] << endl;
	}
	cout << "====[Arrs2D]====\t" << arrs2D.size() << endl;
	cout << "[arrName]\t[cols]" << endl;
	for (int i = 0; i < arrs2D.size(); i++)
	{
		cout << arrs2D[i] << "\t" << ArrCols[arrs2D[i]] << endl;
	}
}
