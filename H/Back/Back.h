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
	IR* Input = nullptr;
	Register* Handle = nullptr;
	string Get_Direction(Token* t);
	string Get_Info_Of(Token* t, bool Storing);
	void Load_To_Reg();
	void Store_To_Reg();
	void Make();
	void Factory();

	~Back() {}

private:

};


#endif