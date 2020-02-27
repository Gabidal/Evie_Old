
#include <string>
#include "../../H/Back/Token.h"
#include "../../H/Back/Assembly_Definitions.h"
#include "../../H/Back/Registers.h"
using namespace std;
int RegisterTurn = 0;

bool Token::is(int flag)
{
    return (Flags & flag) == flag;
}

bool Register::is(int flag)
{
	return (Flags & flag) == flag;
}

bool Token::Any(int flags)
{
    return (Flags & flags) != 0;
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

Token& Token::operator=(const Token& name)
{
	Flags = name.Flags;
	Size = name.Size;
	Const_Value = name.Const_Value;
	Dynamic_Value = name.Dynamic_Value;
	StackOffset = name.StackOffset;
	ParameterCount = name.ParameterCount;
	ID = name.ID;
	Offsetter = name.Offsetter;
	Childs = name.Childs;
	Left_Side_Token = name.Left_Side_Token;
	Right_Side_Token = name.Right_Side_Token;
	Name = name.Name;
	Type = name.Type;
	Reg = name.Reg;
	Semanticked = name.Semanticked;
	return *this;
}

void Register::Link(Token* Requester)
{
	this->Base = Requester;
	History.push_back(Requester);
}