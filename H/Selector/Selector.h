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
	string Board_type = "";
	int Reg_Turn32 = 0;
	int Reg_Turn16 = 0;
	int Reg_Turn8 = 0;
	vector<Register*> Registers32;
	vector<Register*> Registers16;
	vector<Register*> Registers8;
	vector<OpC*> OpCodes;
	Token* Input;
	string I = "";
	OpC* OpCode_Selector();
	string Get_ID(string id, string trust = "");
	Register* Get_Reg(int Size);
	Register* Get_Right_Reg(int F, int Size);
	Register* Get_Belonging_Reg(string name);
	Selector(string s);
	~Selector();
private:

};


#endif