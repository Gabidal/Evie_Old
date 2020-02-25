#ifndef BACK_H_
#define BACK_H_
#include <string>
#include "Token.h"
#include "Assembly_Definitions.h"
#include "../OpC/IR.h"
using namespace std;

class Back
{
public:
	Back(string& s) : Output(s)
	{
	}
	string& Output;
	bool Storing_Into_Mem = false;
	int Parameter_Amount = 0;
	//{
	//These are for direct register access
	bool Storing_Into_Reg = false;
	int Wanted_Reg_Flag = 0;
	//}
	IR* Input = nullptr;

	string Get_Initial_Operator();
	string Initialize(Token* t);
	string Get_Size_Specification();
	string Get_Mem_Address(Token* t);
	void Factory();

	string Get_Static_Agent(Token* t);
	string Get_Agent(bool Storing, Token* Dest, Token* Source);
	Token* Give_Context(int i, vector<Token*> in);
	//agent prepensitives
	string Get_Size_Translator(int Size);
	void Make(IR* ir, bool Storing_To_Mem);
	string Get_Name(Token* t);

	~Back() {}

private:

};


#endif