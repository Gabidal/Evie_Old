#ifndef SELECTOR_H_
#define SELECTOR_H_
#include <vector>
#include <iostream>
#include "../Architecture/ARM/ARM.h"
#include "../Architecture/x86/x86.h"
using namespace std;
class Token;

//Selector's mission is to get right and the best solutionary opecodes for every operation.
class Selector
{
public:
	int Reg_Turn = 0;
	vector<Register*> Registers;
	vector<OpC*> OpCodes;
	Token* Input;
	string I = "";
	OpC* OpCode_Selector();
	string Get_ID(string id);
	Register* Get_Reg(string id);
	string Get_Right_Reg(int F);
	Register* Get_Belonging_Reg(string name);
	Selector(string s);
	~Selector();
private:

};


#endif