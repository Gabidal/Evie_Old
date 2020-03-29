#include "../../H/Interpreter/Modder.h"

/*
	vector<IR*> &Output;
	vector<Token*> Input;
	IR& I;
	*/

map<string, Symbol_Table*> Modder::Get_Member_Pointters()
{
	return {
		std::make_pair("i", (Symbol_Table*)&I),
		std::make_pair("IN", new SymbolTableList(Output)),
		std::make_pair("Pattern", new SymbolTableList(Input))
	};
}

map<string, Waiter*> Modder::Get_Member_Data()
{
	return map<string, Waiter*>();
}

void Modder::Factory()
{
}

void Modder::Detect_If(int i)
{
}

void Modder::Passing(int i)
{
}
