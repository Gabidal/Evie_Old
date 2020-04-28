#include "../../H/Selector/Selector.h"
#include "../../H/Back/Token.h"
extern int _SYSTEM_BIT_TYPE;

Selector::Selector(string s)
{
	Board_type = s;
	if (s == "x86")
	{
		x86 x;
		x.ARC_Factory();
		Registers128 = x.Registers128;
		Registers64 = x.Registers64;
		Registers32 = x.Registers32;
		Registers16 = x.Registers16;
		Registers8 = x.Registers8;
		OpCodes = x.OpCodes;
	}
	else if (s == "arm")
	{
		ARM x;
		x.ARC_Factory();
		Registers128 = x.Registers128;
		Registers64 = x.Registers64;
		Registers32 = x.Registers32;
		Registers16 = x.Registers16;
		Registers8 = x.Registers8;
		OpCodes = x.OpCodes;
	}
}

void Selector::Factory(){

}

vector<Token*> Selector::Get_Right_Current_Register_List(Token* t){
	if (t->Size == 1)
		return Registers8;
	if (t->Size == 2)
		return Registers16;
	if (t->Size == 4)
		return Registers32;
	if (t->Size == 8)
		return Registers64;
	if (t->Size == 12)
		return Registers128;
}

int& Selector::Get_Right_Current_Register_Index(Token* t){
	if (t->Size == 1)
		return Reg_Turn8;
	if (t->Size == 2)
		return Reg_Turn16;
	if (t->Size == 4)
		return Reg_Turn32;
	if (t->Size == 8)
		return Reg_Turn64;
	if (t->Size == 12)
		return Reg_Turn128;
}

void Selector::Flow_Controll(IR* t){
	if (t->ID == "label" || t->ID == "raw_label")
		Flow.push_back(t->PreFix);
	else if (t->PreFix == "label" || t->PreFix == "raw_label")
		Flow.push_back(t->ID);
}

map<string, Token*> Selector::Get_Chunk(){
	return Register_Lock_Chunk.at(Flow.back());
}

Token* Selector::Validate_Register(Token* flag){
	//first try if this flagged tmp regiser already has a register.
	for (auto r: Get_Chunk())
		if (r.first == flag->Name)
			return r.second;
	//if there is no givan valid register.
	return nullptr;
}

Token* Selector::Already_Is_Taken(Token* r){
	for (auto i: Get_Chunk())
		if (i.second->Name == r->Name)
			return r;
	return nullptr;
}

Token* Selector::Get_New_Register(Token* flag){
	//remember to check for "Validated_registers()"
	//if this flag token already has a register!!!
	//our new register:
	Token* Reg = new Token;
	//custom flag for cache and others:
	int F = flag->get();
	//get right vector
	vector<Token*> list = Get_Right_Current_Register_List(flag);
	Token* reg = nullptr;
	int& i = Get_Right_Current_Register_Index(flag);
	if (i >= list.size()) i = 0;
	for (; i < list.size(); i++){
		reg = list.at(i);
		if (reg->is(F))
			if (Already_Is_Taken(reg) == nullptr){
				//this already taken function returns a nullptr it means
				//that this register is free and nobody uses it.
				Register_Lock_Chunk.at(Flow.back()).insert({flag->Name, reg});
				return reg;
			}
	}
	//else if there is no more registers awaiable 
	//return nullptr so the caller can free up some registers for us.
	return nullptr;
}

void Selector::Free_Registers(Token* flag){
	//here we need to give order to generator to generate,
	//IR tokens for saving the freed registers.

	//first get the next register that supports our usage.
	vector<Token*> list = Get_Right_Current_Register_List(flag);
	//get the index and add it by 1 for next.
	int& i = Get_Right_Current_Register_Index(flag);
	i++;
	//now get the register from there.
	Token* Reg = list.at(i);
	//now try to find all the 
}