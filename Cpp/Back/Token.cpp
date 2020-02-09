
#include <string>
#include "../../H/Back/Token.h"
#include "../../H/Back/Assembly_Definitions.h"
#include "../../H/Back/Registers.h"
using namespace std;
int RegisterTurn = 0;
Selector* S;

bool Token::is(int flag)
{
    return (Flags & flag) == flag;
}

bool Token::Any(int flags)
{
    return (Flags & flags) != 0;
}

string Token::getFullName()
{
	return string();
}

bool Token::Optimize_Register_Usage()
{
	return false;
}

Register* Token::getNewRegister()
{
	return nullptr;
}

Register* Token::getReg()
{
	return nullptr;
}

string Token::InitVariable()
{
	return string();
}

string Token::MOVE(Token* Source)
{
	return string();
}

string Token::SUM(Token* Source, Token* Dest)
{
	return string();
}

string Token::SUBSTRACT(Token* Source, Token* Dest)
{
	return string();
}

string Token::MULTIPLY(Token* Source)
{
	return string();
}

string Token::DIVIDE(Token* Source)
{
	return string();
}

string Token::SHIFT_RIGHT(Token* Source)
{
	return string();
}

string Token::SHIFT_LEFT(Token* Source)
{
	return string();
}

string Token::_AND(Token* Source)
{
	return string();
}

string Token::_OR(Token* Source)
{
	return string();
}

string Token::_XOR(Token* Source)
{
	return string();
}

string Token::COMPARE(Token* Source)
{
	return string();
}

string Token::MOVEINSTACK()
{
	return string();
}

string Token::GetAddress()
{
	return string();
}

string Token::SX()
{
	string result = "";
	//use Syntax int instead of Layer int
	for (int i = 0; i < Syntax; i++)
	{
		result += " ";
	}
	return result;
}

void Token::addChild(Token* local, bool func)
{
	Childs.push_back(local);
	if (func)
		local->ParentFunc = this;
	else if (func == false)
		local->ParentType = this;
	local->StackOffset = this->StackOffset;
	this->StackOffset += local->Size;
	this->Size += local->Size;
	local->Flags |= Private;
}

void Token::addParameter(Token* Param)
{
	Param->ParameterOffset = this->ParameterOffset;
	Parameters.push_back(Param);
	this->ParameterOffset += Param->Size;
}

void Token::InitFunction()
{
}

void Token::CallFunc(Token* Fetcher)
{
}

void Token::PTRING(Token*& T)
{
}

string Token::Return_Value()
{
	return string();
}


Token& Token::operator=(const Token& name)
{
	Flags = name.Flags;
	Size = name.Size;
	Value = name.Value;
	StackOffset = name.StackOffset;
	ParameterCount = name.ParameterCount;
	AddedOffset = name.AddedOffset;
	ParameterOffset = name.ParameterOffset;
	ID = name.ID;
	Offsetter = name.Offsetter;
	ParentType = name.ParentType;
	ParentFunc = name.ParentFunc;
	Parameters = name.Parameters;
	SuccessorToken = name.SuccessorToken;
	Childs = name.Childs;
	Name = name.Name;
	Reg = name.Reg;
	output = name.output;
	Origin = name.Origin;
	Semanticked = name.Semanticked;
	return *this;
}
