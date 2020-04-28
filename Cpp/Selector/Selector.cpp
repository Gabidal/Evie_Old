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
	for (IR* i: Input){
		Flow_Controll(i);
		for (Token* j : i->Parameters)
			Load_Variable(j);
	}
	return;
}

vector<Token*> Selector::Get_Right_Current_Register_List(int size){
	if (size == 1)
		return Registers8;
	if (size == 2)
		return Registers16;
	if (size == 4)
		return Registers32;
	if (size == 8)
		return Registers64;
	else
		return Registers128;
}

int& Selector::Get_Right_Current_Register_Index(int size){
	if (size == 1)
		return Reg_Turn8;
	if (size == 2)
		return Reg_Turn16;
	if (size == 4)
		return Reg_Turn32;
	if (size == 8)
		return Reg_Turn64;
	else
		return Reg_Turn128;
}

void Selector::Flow_Controll(IR* t){
	if (t->ID == "label" || (t->ID == "raw_label"))
	{
		if (t->is(_Start_Of_Label))
		{
			Flow.push_back(t->PreFix);
		}
		else if (t->is(_End_Of_Label))
		{
			Flow.pop_back();
		}
	}
	else if (t->ID == "return")
	{
		Flow.pop_back();
	}
}

map<Token*, Token*> Selector::Get_Chunk(){
	return Register_Lock_Chunk[Flow.back()];
}

Token* Selector::Validate_Register(Token* flag){
	//first try if this flagged tmp regiser already has a register.
	for (auto r: Get_Chunk())
		if (r.first->Name == flag->Name)
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
	if (flag->is(_Register_)) return nullptr;
	//remember to check for "Validated_registers()"
	//if this flag token already has a register!!!
	//our new register:
	Token* Reg = new Token;
	//custom flag for cache and others:
	int F = flag->get();
	//get right vector
	vector<Token*> list = Get_Right_Current_Register_List(flag->Size);
	Token* reg = nullptr;
	int& i = Get_Right_Current_Register_Index(flag->Size);
	if (i >= list.size()) i = 0;
	for (; i < list.size(); i++){
		reg = list.at(i);
		if (reg->is(F))
			if (Already_Is_Taken(reg) == nullptr){
				//this already taken function returns a nullptr it means
				//that this register is free and nobody uses it.
				Register_Lock_Chunk.at(Flow.back()).insert({flag, reg});
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
	vector<Token*> list = Get_Right_Current_Register_List(flag->Size);
	//get the index and add it by 1 for next.
	int& i = Get_Right_Current_Register_Index(flag->Size);
	if (++i >= list.size()) i = 0;
	
	//now get the register from there.
	Token* Reg = list.at(i);
	//now try to find all the users of that reg on this context and other context.
	for (string context: Flow)
		for (auto j: Register_Lock_Chunk.at(context))
			if (j.second->Name == Reg->Name)
				Save_Variable(j.first);
}

void Selector::Save_Variable(Token* flag){
	//first make the ldr IR token
	IR* save = new IR;
	save->ID = "=";
	save->Parameters.push_back(new Token(*flag));
	save->Parameters.push_back(new Token(*Validate_Register(flag)));
	//now insert it to input list
	Input.insert(Input.begin() + I, save);
}

void Selector::Load_Variable(Token* flag){
	if (flag->is(_Register_)) return;
	if (Validate_Register(flag) != nullptr)
		return;
	if (Get_New_Register(flag) != nullptr){
		//so there is awaiable register now load it
		IR* ldr = new IR;
		ldr->ID = "ldr";
		ldr->Parameters.push_back(new Token(*Validate_Register(flag)));
		ldr->Parameters.push_back(new Token(*flag));
		//now insert it to input
		Input.insert(Input.begin() + I, ldr);
		return;
	}
	Free_Registers(flag);
	Load_Variable(flag);
}

void Selector::Clear(){
	Register_Lock_Chunk.clear();
	Flow.clear();
	return;
}

Token* Selector::Get_Right_Reg(int f, int s){
	//get the list 
	vector<Token*> list = Get_Right_Current_Register_List(s);
	for (Token* t: list)
		if (t->is(f))
			return t;
	return nullptr;
}

string Selector::Get_ID(string id, string trust, vector<int> minmax)
{
	if (id == "")
		return "";

	vector<int> i_Sizes = minmax;
	for (OpC* o : OpCodes)
	{
		vector<int> o_Sizes = o->MinMax;
		if (o_Sizes.size() != (i_Sizes.size() * 2))
			continue;
		for (int i = 0; i < (int)i_Sizes.size(); i++)
		{
			int in = i_Sizes.at(i);
			int in_min = o_Sizes.at(i * 2);
			int in_max = o_Sizes.at(i * 2 + 1);
			if ((in_min <= in) && (in_max >= in))
				continue;
			else
				goto CONTINUE;
		}
		if (o->ID == id)
			return o->OpCode;
		CONTINUE:;
	}
	if ((trust == "export") || (trust == "import") || (trust == "raw_label") || (trust == "global"))
		return id;
	if ((trust != "label") && (trust != "<") && (trust != ">") && (trust != "!<") && (trust != "!>") && (trust != "==") && (trust != "!=") && (trust != "<=") && (trust != ">=") && (trust != "jmp"))
	{
		cout << "Warning: This is here because your'e using a illegal opcode: " << id << " ";
		for (int i : minmax)
		{
			cout << i << ", ";
		}
		cout << endl;
	}

	return "_" + id;
}