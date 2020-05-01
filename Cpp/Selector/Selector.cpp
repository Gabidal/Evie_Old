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

map<Token, Token>* Selector::Get_Chunk(){
	return &Chunk.at(Context.back());
}

vector<Token*> Selector::Get_Right_Size_List(int s){
	if (s == 12)
		return Registers128;
	else if (s == 8)
		return Registers64;
	else if (s == 4)
		return Registers32;
	else if (s == 2)
		return Registers16;
	return Registers8;
}

int& Selector::Get_Right_Ongoing_Register_Index(int s){
	if (s == 12)
		return Reg_Turn128;
	else if (s == 8)
		return Reg_Turn64;
	else if (s == 4)
		return Reg_Turn32;
	else if (s == 2)
		return Reg_Turn16;
	return Reg_Turn8;
}

Token* Selector::Get_Register(Token* t){
	for (auto i: *Get_Chunk())
		if (i.first.Name == t->Name)
			return &i.second;
	return nullptr;
}

Token* Selector::Get_New_Register(Token* t){
	//remember to check for "Validated_registers()"
	//if this flag token already has a register!!!
	//our new register:
	Token* Reg = new Token;
	//custom flag for cache and others:
	int F = t->get();
	//get right vector
	vector<Token*> list = Get_Right_Size_List(t->Size);
	Token* reg = nullptr;
	int& i = Get_Right_Ongoing_Register_Index(t->Size);
	if (i >= list.size()) i = 0;
	for (; i < list.size(); i++){
		reg = list.at(i);
		if (reg->is(F))
			if (Check_Other_Owner(reg) == nullptr){
				//this already taken function returns a nullptr it means
				//that this register is free and nobody uses it.
				Chunk.at(Context.back()).insert({*t, *reg});
				return reg;
			}
	}
	//else if there is no more registers awaiable 
	//return nullptr so the caller can free up some registers for us.
	return nullptr;
}

vector<Token> Selector::Free_Registers(Token* t){
	//here we need to give order to generator to generate,
	//IR tokens for saving the freed registers.
	vector<Token> Output;
	//first get the next register that supports our usage.
	vector<Token*> list = Get_Right_Size_List(t->Size);
	//get the index and add it by 1 for next.
	int& i = Get_Right_Ongoing_Register_Index(t->Size);
	if (++i >= list.size()) i = 0;
	
	//now get the register from there.
	Token* Reg = new Token;
	for (int j = i; j < list.size(); j++)
		//search for the right flagged register
		if (list.at(j)->is(t->get()))
			Reg = list.at(j);
	//now try to find all the users of that reg on this context and other context.
	for (string context: Context)
		for (auto j: Chunk.at(context))
			if (j.second.Name == Reg->Name)
				Output.push_back(j.first);
	return Output;
}

Token* Selector::Check_Other_Owner(Token* t){
	for (auto i: *Get_Chunk())
		if (i.second.Name == t->Name)
			return t;
	return nullptr;
}