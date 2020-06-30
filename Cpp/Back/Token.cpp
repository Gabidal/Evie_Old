
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
		std::make_pair("_LEFT_SIDE_TOKEN_", Left_Side_Token),
		std::make_pair("_RIGHT_SIDE_TOKEN_", Right_Side_Token),
		std::make_pair("_OFFSETTER_", Offsetter),
		std::make_pair("_CHILDS_", new SymbolTableList(Childs)),
		std::make_pair("_DEFINED_LOCAL_TYPES_", new SymbolTableList(Defined_Local_Types)),
		std::make_pair("_FLAGS_", new IntObject(&Flags)),
		std::make_pair("_SIZE_", new IntObject(&Size)),
		std::make_pair("_STACK_OFFSET_", new IntObject(&StackOffset)),
		std::make_pair("_PARAMETER_COUNT_", new IntObject(&ParameterCount)),
		std::make_pair("_ID_", new IntObject(&ID)),
		std::make_pair("_NAME_", new StringObject(&Name)),
		std::make_pair("_TYPES_", new SymbolTableList(Types)),
		std::make_pair("_UID_", new StringObject(&UID)),
		std::make_pair("_STATE_", new StringObject(&State))
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