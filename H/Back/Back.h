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
	string Get_Static_Agent(Token* t);
	string Get_Agent(bool Storing, Token* Dest, Token* Source);
	Token* Give_Context(int i, vector<Token*> in);
	//agent prepensitives
	string Get_Mem_Address(Token *t);
	string Get_Size_Translator(int Size);
	void Make(IR* ir, bool Storing_To_Mem);
	string Get_Name(Token* t);

	~Back() {}

private:

};


#endif