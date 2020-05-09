#include "../../H/Selector/Selector.h"
extern int _SYSTEM_BIT_TYPE;

bool Selector::Skipable(Token* r, vector<IR*> Input, int i)
{
	int Max_Lenght = i + 2;
	if (Max_Lenght >= Input.size())
		return false;		//do not skip
	for (int j = i; j < Max_Lenght; j++)
		for (Token* t : Input.at(j)->Parameters) {
			if (r->Name == t->Name)
				return true;		//no  skip
			else if (t->Offsetter != nullptr)
				if (r->Name == t->Offsetter->Name)
					return true;		//no  skip
		}
	return false;
}

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
			int in_min = o_Sizes.at((size_t)i * 2);
			int in_max = o_Sizes.at((size_t)i * 2 + 1);
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

map<Token*, Token*>& Selector::Get_Chunk(){
	return Chunk[Context.back()];
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

Token* Selector::Get_Register(string t){
	for (string c: Context)
		for (auto i: Chunk[c])
			if ((i.first != nullptr) && i.first->Name == t)
				return i.second;
	return nullptr;
}

Token* Selector::Get_New_Register(Token* t){
	//remember to check for "Validated_registers()"
	//if this flag token already has a register!!!
	//our new register:
	//custom flag for cache and others:
	int F = t->get();
	//get right vector
	vector<Token*> list = Get_Right_Size_List(t->Size);
	Token* reg = nullptr;
	//int& i = Get_Right_Ongoing_Register_Index(t->Size);
	int i = 0;
	if (i >= list.size()) i = 0;
	for (; i < list.size(); i++){
		reg = list.at(i);
		if (reg->is(F))
			if (Check_Other_Owner(reg) == nullptr){
				//this already taken function returns a nullptr it means
				//that this register is free and nobody uses it.
				Get_Chunk().insert(make_pair(t, new Token(*reg)));
				return reg;
			}
	}
	//else if there is no more registers awaiable 
	//return nullptr so the caller can free up some registers for us.
	return nullptr;
}

vector<Token*> Selector::Free_Registers(Token* t, vector<IR*> Input, int i){
	//here we need to give order to generator to generate,
	//IR tokens for saving the freed registers.
	vector<Token*> Output;
	//first get the next register that supports our usage.
	vector<Token*> list = Get_Right_Size_List(t->Size);
	//get the index and add it by 1 for next.
	//int& i = Get_Right_Ongoing_Register_Index(t->Size);
	//if (++i >= list.size()) i = 0;
	//else --i;
	
	//now get the register from there.
	Token* Reg = new Token;
	for (int j = 0; j < list.size(); j++)
		//search for the right flagged register
		if (list.at(j)->is(t->get())){
			Reg = list.at(j);
			//skipable return true if the life time is still important
			if ((Get_Register_Holder(Reg) != nullptr) && Skipable(Get_Register_Holder(Reg), Input, i)) {
				continue;
			}
			//i = j;
			break;
		}
	//now try to find all the users of that reg on this context and other context.
	for (string context: Context)
		for (auto j: Chunk.at(context))
			if ((j.first != nullptr) && j.second->Name == Reg->Name)
				Output.push_back(j.first);
	return Output;
}

Token* Selector::Check_Other_Owner(Token* t){
	for (auto i: Get_Chunk())
		if ((i.first != nullptr) && i.second->Name == t->Name)
			return t;
	return nullptr;
}

int Selector::Get_Index_Of(Token* t){
	vector<Token*> list = Get_Right_Size_List(t->Size);
	for (int i = 0; i < list.size(); i++)
		if (list.at(i)->Name == t->Name)
			return i;
	//cout << "Error: Cannot find index of " << t->Name << "." << endl;
	return -1;
}

void Selector::Disconnect_Register(Token* t){
	for (string c: Context){
		vector<Token*> removables;
		for (auto j: Chunk[c])
			if ((j.first != nullptr) && j.first->Name == t->Name){
				removables.push_back(j.first);
			}
		for (Token* i : removables)
			Chunk[c].erase(i);
	}
	return;
}

void Selector::Link_Register(Token* t, Token* r){
	Get_Chunk().insert(make_pair(t, r));
	return;
}

Token* Selector::Get_Right_Reg(int F, int s){
	vector<Token*> list = Get_Right_Size_List(s);
	for (Token* i : list)
		if (i->is(F))
			return i;
	return nullptr;
}

vector<Token*> Selector::Get_Lifetime_Of(vector<Token*> Think_Need_Freeing, vector<IR*> Input, int i){
	vector<Token*> Deletable;
	int Max_Lenght = i+2;
	if (Max_Lenght >= Input.size())
		return Deletable;
	for (Token* r: Think_Need_Freeing)
		for (int j = i; j < Max_Lenght; j++)
			for (Token* t: Input.at(j)->Parameters){
				if (r->Name == t->Name)
					Deletable.push_back(r);
				else if (t->Offsetter != nullptr)
					if (r->Name == t->Offsetter->Name)
						Deletable.push_back(r);
			}

	for (Token* t: Deletable)
		for (int j = 0; j < Think_Need_Freeing.size(); j++)
			if (t->Name == Think_Need_Freeing.at(j)->Name){
				Think_Need_Freeing.erase(Think_Need_Freeing.begin() + j);
				break;
			}
	return Think_Need_Freeing;
}

Token* Selector::Get_Register_Holder(Token* r){
	for (string c: Context)
		for (auto i: Chunk[c])
			if ((i.first != nullptr) && i.second->Name == r->Name)
				return i.first;
	return nullptr;
}

