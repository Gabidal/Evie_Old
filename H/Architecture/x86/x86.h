#ifndef _X86_H_
#define _X86_H_
#include "../../OpC/OpC.h"
namespace x86
{
	vector<OpC*> OpCodes;
	void Factory();
	int x86_ADD(vector<int> Parameters)
	{
		return Parameters.at(0) + Parameters.at(1);
	}

	int x86_SUB(vector<int>Parameters)
	{
		return Parameters.at(0) - Parameters.at(1);
	}

	int x86_IMUL(vector<int>Parameters)
	{
		return Parameters.at(0) * Parameters.at(1);
	}

	int x86_IDIV(vector<int>Parameters)
	{
		return Parameters.at(0) / Parameters.at(1);
	}

	int x86_MUL(vector<int>Parameters)
	{
		return Parameters.at(0) * Parameters.at(1);
	}

	int x86_DIV(vector<int>Parameters)
	{
		return Parameters.at(0) / Parameters.at(1);
	}
}


#endif