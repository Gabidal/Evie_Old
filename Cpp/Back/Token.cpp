
#include <string>
#include "../../H/Back/Token.h"
#include "../../H/Back/Assembly_Definitions.h"
using namespace std;
int RegisterTurn = 0;

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

Token& Token::operator=(const Token& name)
{
	Flags = name.Flags;
	Size = name.Size;
	Initial_Value = name.Initial_Value;
	Changable_Value = name.Changable_Value;
	StackOffset = name.StackOffset;
	ParameterCount = name.ParameterCount;
	ID = name.ID;
	Childs = name.Childs;
	Left_Side_Token = name.Left_Side_Token;
	Right_Side_Token = name.Right_Side_Token;
	Name = name.Name;
	Type = name.Type;
	Semanticked = name.Semanticked;
	return *this;
}