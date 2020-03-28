#include "../../H/OpC/IR.h"

void IR::add(int Flag)
{
	this->Flags |= Flag;
}

int IR::get()
{
	return Flags;
}

map<string, Symbol_Table*> IR::Get_Member_Pointters()
{

	return {
		make_pair("Parameters", new SymbolTableList(Parameters)),
		make_pair("Childs", new SymbolTableList(Childs))
	};
}

/*
		int Reg_Flag = 0;
		string PreFix = "";
		string ID = "";
		vector<Token*> Parameters;
		vector<IR*> Childs;
		void add(int Flag);
		int get();
		*/

map<string, Waiter*> IR::Get_Member_Data()
{
	return {
		std::make_pair("Reg_Flag", new IntWaiter(&Reg_Flag)),
		std::make_pair("PreFix", new StringWaiter(&PreFix)),
		std::make_pair("ID", new StringWaiter(&ID)),
	};
}
