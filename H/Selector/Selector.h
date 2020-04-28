#ifndef SELECTOR_H_
#define SELECTOR_H_
#include <vector>
#include <iostream>
#include "../Architecture/ARM/ARM.h"
#include "../Architecture/x86/x86.h"
#include "../OpC/IR.h"
#include <map>
using namespace std;
class Token;

//Selector's mission is to get right and the best solutionary opecodes for every operation.
class Selector
{
private:
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
	//functions for giving good & optimized registers
	vector<string> Flow;
	map<string, map<string, Token*>> Register_Lock_Chunk;
	vector<Token*> Get_Right_Current_Register_List(Token* t);
	int& Get_Right_Current_Register_Index(Token* t);
	//set the right label into Flow vector for chunks to open.
	void Flow_Controll(IR* t);
	map<string, Token*> Get_Chunk();
	//this gives a valid Token* ,if there is a free register.
	Token* Validate_Register(Token* flag);
	//check if this is already taken
	Token* Already_Is_Taken(Token* r);
	//give new register.
	Token* Get_New_Register(Token* flag);
	//if the above function return nullptr it means we need to free up some registers:
	void Free_Registers(Token* flag);
public:
	vector<IR*> Input;
	void Factory();
	vector<OpC*> OpCodes;
	Selector(string s);
	~Selector(){}
private:

};


#endif