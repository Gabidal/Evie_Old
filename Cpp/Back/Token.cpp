
#include <string>
#include "../../H/Back/Token.h"
#include "../../H/Back/Assembly_Definitions.h"
using namespace std;
int RegisterTurn = 0;

map<string, Symbol_Table*> Token::Get_Member_Pointters()
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
	};
}

map<string, Waiter*> Token::Get_Member_Data()
{
	/*
    int Flags = 0;
    int Size = 0;
    int StackOffset = 0;
    int ParameterCount = 0;
    int ID = 0;
    string Name = "";
    string Type = "";
    string PreFix_Type = "";
    string UID = "";
    string State;*/
	return {
		std::make_pair("Flags", new IntWaiter(&Flags)),
		std::make_pair("Size", new IntWaiter(&Size)),
		std::make_pair("StackOffset", new IntWaiter(&StackOffset)),
		std::make_pair("ParameterCount", new IntWaiter(&ParameterCount)),
		std::make_pair("ID", new IntWaiter(&ID)),
		std::make_pair("Name", new StringWaiter(&Name)),
		std::make_pair("Type", new StringWaiter(&Type)),
		std::make_pair("PreFix_Type", new StringWaiter(&PreFix_Type)),
		std::make_pair("UID", new StringWaiter(&UID)),
		std::make_pair("State", new StringWaiter(&State))
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