#include "../../H/BackEnd/BackEnd.h"

extern Node* Global_Scope;

void BackEnd::Init()
{
	if (sys->Info.Architecture == "x86") {
		if (sys->Info.Bits_Mode == "8") {
			if (sys->Info.OS == "win32") {
				x86_64_Win::Init();
				Seperator = x86_64_Win::Seperator;
				Register_Pre_Fix = x86_64_Win::Register_Pre_Fix;
				Number_Pre_Fix = x86_64_Win::Number_Pre_Fix;
				Label_Post_Fix = x86_64_Win::Label_Post_Fix;

				Registers = x86_64_Win::Registers;
				Parameter_Registers = x86_64_Win::Parameter_Registers;
				Opcodes = x86_64_Win::Opcodes;
			}
		}

	}
}

void BackEnd::Factory()
{

}
