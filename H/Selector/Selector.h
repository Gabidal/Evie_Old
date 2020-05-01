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
	vector<OpC*> OpCodes;
	vector<Token*> Get_Right_Size_List(int s);
	int& Get_Right_Ongoing_Register_Index(int s);
	//the map for every register paired
	//map<context, map<variable, register>>
	map<string, map<Token, Token>> Chunk;
	vector<string> Context;
public:
	map<Token, Token>* Get_Chunk();
	//get id
	string Get_ID(string id, string trust, vector<int> minmax);
	//look up for owned register(s).
	Token* Get_Register(Token* t);
	//this returns nullptr if all registers are use, use Free_registers to get registers freed.
	Token* Get_New_Register(Token* t);
	//freeing registers by token.
	vector<Token> Free_Registers(Token* t);
	//check if register is already someones elses.
	Token* Check_Other_Owner(Token* t); 
	Selector(string s);
	~Selector(){}
private:

};


#endif