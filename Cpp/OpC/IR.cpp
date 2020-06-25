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
		make_pair("_FLAGS_", new IntObject(&Flags)),
		make_pair("_PARAMETERS_", new SymbolTableList(Parameters)),
		make_pair("_CHILDS_", new SymbolTableList(Childs)),
		std::make_pair("_REG_FLAG_", new IntObject(&Reg_Flag)),
		std::make_pair("_PREFIX_", new StringObject(&PreFix)),
		std::make_pair("_ID_", new StringObject(&ID)),
		std::make_pair("_COMMENT_", new SymbolTableList(Comments)),
	};
}
