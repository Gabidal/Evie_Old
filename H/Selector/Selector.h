#ifndef SELECTOR_H_
#define SELECTOR_H_
#include <vector>
#include <iostream>
using namespace std;

#if _ARM_
#include "../Architecture/ARM/ARM.h"
using namespace ARM;
#else
#include "../Architecture/x86/x86.h"
using namespace x86;
#endif
class Token;

//Selector's mission is to get right and the best solutionary opecodes for every operation.
class Selector
{
public:
	Token* Input;
	string I = "";
	OpC* OpCode_Selector();
	string Get_ID(string id);
	Register* Get_Reg(string id);
	string Get_Right_Reg(int F);
	Selector(Token* T);
	Selector();
	~Selector();
private:

};


#endif