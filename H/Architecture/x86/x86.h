#ifndef _X86_H_
#define _X86_H_
#include "../../OpC/OpC.h"

class x86
{
public:
	int OpCodes_Amount = 6;
	vector<OpC*> OpCodes;
	void Factory();
	int x86_ADD(int x, int y);
	int x86_SUB(int x, int y);
	int x86_IMUL(int x, int y);
	int x86_IDIV(int x, int y);
	int x86_MUL(int x, int y);
	int x86_DIV(int x, int y);
	x86()
	{
	}
	~x86();

private:

};


#endif