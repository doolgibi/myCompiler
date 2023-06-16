
//#include "stdafx.h"
#include"ErrorProcess.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<string>

using namespace std;

ofstream eout("error.txt");

void ErrorProcess::sortErrOutVec()
{
	sort(errOutVec.begin(), errOutVec.end(), cmp);
}

ErrorProcess::ErrorProcess()
{
}

ErrorProcess::~ErrorProcess()
{
	eout.close();
}

void ErrorProcess::insertError(int lineID, string errType)
{
	ErrorOutput err{ lineID, errType };

	if (errOutVec.empty()) errOutVec.push_back(err);
	else
	{
		if (checkLineEqual(err, errOutVec.back()) && err.errType == "d" && errOutVec.back().errType == "e")
		{
			errOutVec.pop_back();
			errOutVec.push_back(err);
		}
		else if (!checkErrEqual(err, errOutVec.back()))
		{
			errOutVec.push_back(err);
		}
	}
}

void ErrorProcess::outputError()
{
	sortErrOutVec();
	for (int i = 0; i < getErrNum(); i++)
	{
		eout << errOutVec[i].lineID << " " << errOutVec[i].errType << endl;
	}
}