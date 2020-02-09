
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

string Token::Get_Agent(bool Giver)
{
	//if it is number.
	if (this->is(Number))
	{
		return this->Name;
	}
	//first find if this token has a register to it.
	for (Register* r : Registers)
	{
		if (r->Base == nullptr)
		{
			continue;
		}
		else if (r->Base->Name == this->Name)
		{
			return r->Name;
		}
	}
	//then get it from mem.
	if (Giver)
	{
		return Get_Mem_Address();
	}
	else
	{
		return Get_Reg();
	}
}

string Token::Get_Mem_Address()
{
	if (this->is(Private))
	{
		for (Register* r : Registers)
		{
			if (r->is(Task_For_Type_Address_Basing))
			{
				return "[" + r->Name + Get_Additive_Operator() + to_string(this->StackOffset) + "]";
			}
		}
	}
	else
	{
		return "[" + this->Name + "]";
	}
}

string Token::Get_Additive_Operator()
{
	if (this->is(Parameter))
	{
		return " + ";
	}
	else
	{
		return " - ";
	}
}

string Token::Get_Reg()
{
	Selector Select;
	string Reg_Name = Registers.at(Reg_Turn)->Name;

	output += Select.Get_ID("=") + Reg_Name + FROM + Get_Mem_Address() + NL;
	if (Reg_Turn > Registers.size() - 1)
	{
		Reg_Turn = 0;
	}
	else
	{
		Reg_Turn++;
	}
	return Reg_Name;
}

string Token::Make(Token* Source, string Operator)
{
	Selector Select;
	output += Select.Get_ID(Operator) + this->Get_Agent(true) + FROM + Source->Get_Agent(false) + NL;
	return "";
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

void Register::Link(Token* Requester)
{
	this->Base = Requester;
	History.push_back(Requester);
}