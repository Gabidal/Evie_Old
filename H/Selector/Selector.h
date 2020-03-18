#ifndef SELECTOR_H_
#define SELECTOR_H_
#include <vector>
#include <iostream>
#include "../Architecture/ARM/ARM.h"
#include "../Architecture/x86/x86.h"
#include <map>
using namespace std;
class Token;

//Selector's mission is to get right and the best solutionary opecodes for every operation.
class Selector
{
public:
	string Board_type = "";
	int Reg_Turn128 = 0;
	int Reg_Turn64 = 0;
	int Reg_Turn32 = 0;
	int Reg_Turn16 = 0;
	int Reg_Turn8 = 0;
	vector<Token*> Registers128;
	vector<Token*> Registers64;
	vector<Token*> Registers32;
	vector<Token*> Registers16;
	vector<Token*> Registers8;
	vector<OpC*> OpCodes;
	Token* Input;
	string I = "";
	OpC* OpCode_Selector();
	string Get_ID(string id, string trust, vector<int> minmax);
	Token* Get_Right_Reg(int F, int Size);
	Token* Get_Reg(vector<Token*> regs, int F, int &previus);
	Selector(string s);
	~Selector();
private:

};


#endif