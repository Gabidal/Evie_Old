
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