#include "../../H/BackEnd/BackEnd.h"

extern Node* Global_Scope;
extern Usr* sys;
extern x86_64_Win X86_64_WIN;
extern Selector* selector;

void BackEnd::Init()
{
	if (sys->Info.Architecture == "x86") {
		if (sys->Info.Bits_Mode == "8") {
			if (sys->Info.OS == "win32") {
				X86_64_WIN.Init();
				Seperator = X86_64_WIN.Seperator;
				Register_Pre_Fix = X86_64_WIN.Register_Pre_Fix;
				Number_Pre_Fix = X86_64_WIN.Number_Pre_Fix;
				Label_Post_Fix = X86_64_WIN.Label_Post_Fix;

				Opcodes = X86_64_WIN.Opcodes;
			}
		}

	}
}

void BackEnd::Factory()
{
	for (auto i : Input)
		Builder(i);
}

void BackEnd::Builder(IR* i)
{
	//leave data handling into other algorithm
	if (!i->is(TOKEN::OPERATOR))
		return;
	//get the needed opcode
	IR* opc = selector->Get_Opcode(i);

	//set up the parameters
}
