#include "../../H/OpC/IR.h"

void IR::add(int Flag)
{
	this->Flags |= Flag;
}

int IR::get()
{
	return Flags;
}

map<string, Object*> IR::Get_Members()
{

	return {
		make_pair("Flags", new IntObject(&Flags)),
		make_pair("Parameters", new SymbolTableList(Parameters)),
		make_pair("Childs", new SymbolTableList(Childs)),
		std::make_pair("Reg_Flag", new IntObject(&Reg_Flag)),
		std::make_pair("PreFix", new StringObject(&PreFix)),
		std::make_pair("ID", new StringObject(&ID)),
		std::make_pair("Comment", new SymbolTableList(Comments)),
	};
}
