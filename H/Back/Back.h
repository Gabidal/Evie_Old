#ifndef BACK_H_
#define BACK_H_
#include <string>
#include "Token.h"
#include "Assembly_Definitions.h"
#include "../OpC/IR.h"
#include "Comment.h"
using namespace std;

class Back
{
public:
	Back(string& s) : Output(s)
	{
	}
	string& Output;
	IR* Input = nullptr;
	Token* Handle = nullptr;
	string Get_Direction(Token* t);
	string Get_Handler(Token* t);
	string Get_Info_Of(Token* t);
	string Get_Size(Token* t);
	string Get_Address(Token* t);
	string Get_Call(Token* t);
	//bool Check_For(string dest, vector<string> source);

	string Get_Frame(string inside);
	void Make();
	void Factory();

	~Back() {}

private:
	bool storing = false;
};


#endif