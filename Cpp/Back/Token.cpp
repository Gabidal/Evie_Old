
#include <string>
#include "../../H/Back/Token.h"
#include "../../H/Back/Assembly_Definitions.h"
using namespace std;
int RegisterTurn = 0;

map<string, Object*> Token::Get_Members()
{
	/*
		Token* Left_Side_Token = nullptr;
		Token* Right_Side_Token = nullptr;
		Token* Offsetter = nullptr;
		vector<Token*> Childs;*/
	return {
		std::make_pair("Left_Side_Token", Left_Side_Token),
		std::make_pair("Right_Side_Token", Right_Side_Token),
		std::make_pair("Offsetter", Offsetter),
		std::make_pair("Childs", new SymbolTableList(Childs)),
		std::make_pair("Flags", new IntObject(&Flags)),
		std::make_pair("Size", new IntObject(&Size)),
		std::make_pair("StackOffset", new IntObject(&StackOffset)),
		std::make_pair("ParameterCount", new IntObject(&ParameterCount)),
		std::make_pair("ID", new IntObject(&ID)),
		std::make_pair("Name", new StringObject(&Name)),
		std::make_pair("Type", new StringObject(&Type)),
		std::make_pair("PreFix_Type", new SymbolTableList(PreFix_Type)),
		std::make_pair("UID", new StringObject(&UID)),
		std::make_pair("State", new StringObject(&State))
	};
}

bool Token::is(int flag)
{
    return (Flags & flag) == flag;
}

bool Token::Any(int flags)
{
    return (Flags & flags) != 0;
}

void Token::add(int flag)
{
	this->Flags |= flag;
}

void Token::remove(int flag)
{
	this->Flags ^= (Flags & flag);
}

int Token::get()
{
	return Flags;
}

string Token::Get_Additive_Operator()
{
	if (this->is(_Parameter_))
	{
		return " + ";
	}
	else
	{
		return " - ";
	}
}