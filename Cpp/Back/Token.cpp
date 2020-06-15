
#include <string>
#include "../../H/Back/Token.h"
#include "../../H/Back/Assembly_Definitions.h"
#include <iostream>
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
		std::make_pair("Types", new SymbolTableList(Types)),
		std::make_pair("UID", new StringObject(&UID)),
		std::make_pair("State", new StringObject(&State))
	};
}

string Token::Gather_Types(string comma)
{
	string r = "";
	for (string s : Types)
		r += s + comma;
	return r;
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

bool Token::is(string type)
{
	for (string s : Types) {
		if (s == type) {
			return true;
		}
	}
	return false;
}

string Token::Get_Types()
{
	string result;
	for (int i = 0; i < Types.size() - 1; i++) {
		result += Types[i] + " ,";
	}
	result += Types[Types.size() - 1];
	return result;
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