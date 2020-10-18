#include "../../H/BackEnd/Selector.h"
#include "../../H/UI/Usr.h"

extern Usr* sys;
extern x86_64_Win X86_64_WIN;

void Selector::Init() {
	if (sys->Info.Architecture == "x86") {
		if (sys->Info.Bits_Mode == "8") {
			if (sys->Info.OS == "win32") {
				X86_64_WIN.Init();
				for (auto i : X86_64_WIN.Registers)
					Registers.push_back({ nullptr, i });
				for (auto i : X86_64_WIN.Parameter_Registers)
					Parameter_Registers.push_back({ nullptr, i });
			}
		}

	}
}

Token* Selector::Get_New_Reg(vector<IR*> source, int i, Token* t)
{
	//try to find if this t* is used in future
	//also check if it intersects cllations
	bool Intersects_Calls = false;
	int Parameter_Place = -1;
	int Last_Usage = i;
	for (int j = i; j < source.size(); j++) {
		for (auto k : source[j]->Arguments)
			//TODO: Cheking names wont work on duplicated local varibles inside a condition like scopes.
			if (k->Get_Name() == t->Get_Name())
				//check if this is the same variable...
				Last_Usage = j;
		if (source[j]->is(TOKEN::CALL)) {
			Intersects_Calls = true;
			for (int k = 0; k < source[j]->Arguments.size(); k++)
				if (source[j]->Arguments[k]->Get_Name() == t->Get_Name())
					Parameter_Place = k;
		}
		if (source[j]->is(TOKEN::END_OF_FUNCTION))
			break;
	}
	if (Parameter_Place != -1) {
		return Parameter_Registers[Parameter_Place].second->Get_Child(t->Get_Size());
	}

	long Reg_Type = 0;
	if (Intersects_Calls)
		Reg_Type |= TOKEN::NONVOLATILE;
	else
		Reg_Type |= TOKEN::VOLATILE;

	for (auto r : Registers) {
		if (r.first == nullptr) {
			if (r.second->is(Reg_Type)) {
				if (r.second->Get_Size() == t->Get_Size()) {
					r.first->Last_Usage_Index = Last_Usage;
					r.first->User = t->Get_Name();
					return r.second;
				}
			}
		}
		else if (r.first->Last_Usage_Index < i){
			if (r.second->is(Reg_Type)) {
				if (r.second->Get_Size() == t->Get_Size()) {
					r.first->Last_Usage_Index = Last_Usage;
					r.first->User = t->Get_Name();
					return r.second;
				}
			}
		}
		else if (r.first->User == t->Get_Name()) {
			return r.second;
		}
	}
}
