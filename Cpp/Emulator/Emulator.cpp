#include "../../H/Emulator/Emulator.h"
#include "../../H/Selector/Selector.h"
#include "../../H/UI/Usr.h"
extern Selector* S;
		// Register, Regiser using token
extern map<string, Token*> Preprosessor_Tokens;
extern Object* Root;
extern int _SYSTEM_BIT_TYPE;

Token* Emulator::Get_Info(Token* t)
{
	if (t->is(_Parenthesis_))
	{
		return t->Childs.at(0);
	}
	else
	{
		return t;
	}
}

void Emulator::Long_Operation_Allocator(int &i)
{
	if ((Input.at(i)->ID == "==") || (Input.at(i)->ID == "!=") || (Input.at(i)->ID == "<") || (Input.at(i)->ID == ">") || (Input.at(i)->ID == "!<") || (Input.at(i)->ID == "!>") || (Input.at(i)->ID == "<=") || (Input.at(i)->ID == ">="))
	{
		//conditional operators need the cmp, and the condition jump operation.
		//Token* Reg = new Token;
		//Reg->add(_Register_);
		//Reg->add(Task_For_General_Purpose);
		//Reg->Name = Input.at(i)->Parameters.at(0)->Name;
		//Reg->Size = Input.at(i)->Parameters.at(0)->Size;

		IR* cmp = new IR;
		*cmp = *Input.at(i);
		cmp->ID = "cmp";
		Input.at(i)->Parameters.clear();
		Input.at(i)->PreFix = Input.at(i)->ID;
		Input.at(i)->ID = Branching_Label.back() + "END";
		Input.insert(Input.begin() + i, cmp);
	}
	else if (Input.at(i)->ID == "return" && (Input.at(i)->is(_Allocated_) != true))
	{
		//make the returning
		Token* Reg = new Token;
		Reg->add(_Register_);
		Reg->add(Task_For_Returning);
		Reg->Name = Get_Info(Input.at(i)->Parameters.at(0))->Name + "_returning_register";
		Reg->Size = Get_Info(Input.at(i)->Parameters.at(0))->Size;

		IR* mov_to_return_Reg = new IR;
		mov_to_return_Reg->ID = "ldr";
		mov_to_return_Reg->Parameters.push_back(Reg);
		mov_to_return_Reg->Parameters.push_back(Get_Info(Input.at(i)->Parameters.at(0)));
		Input.at(i)->Parameters.clear();
		Input.at(i)->add(_Allocated_);
		Input.insert(Input.begin() + i, mov_to_return_Reg);

		//make the leave
		if (Input.at(i + 1)->is(_Double_Task_))
		{
			IR* Leave = new IR;
			Leave->ID = "leave";
			Input.insert(Input.begin() + i + 1, Leave);
		}
	}
	else if (Input.at(i)->PreFix == "export")
	{
		IR* global = new IR;
		global->PreFix = "global";
		global->ID = Input.at(i)->ID;
		Input.insert(Input.begin() + i + 1, global);

		IR* label = new IR;
		label->PreFix = Input.at(i)->ID;
		label->ID = "raw_label";
		label->add(_Start_Of_Label);
		label->Childs = Input.at(i)->Childs;
		Input.at(i)->Childs.clear();
		Input.insert(Input.begin() + i + 2 , label);
	}
	else if (Input.at(i)->ID == "asm")
	{

	}
	if (Input.at(i)->is(_Operator_) && (Input.at(i)->is(_Allocated_) != true))
	{
		Input.at(i)->add(_Allocated_);
		if (Input.at(i)->Parameters.size() > 1)
		{
			Token* L = new Token;
			*L	= *Input.at(i)->Parameters.at(0);
			L->Name = "tmp_" + L->Name;
			Token* R = new Token;
			*R	= *Input.at(i)->Parameters.at(1);
			if (L->Size != R->Size)
			{
				Token* Smaller = new Token;
				Token* Converted = new Token;
				Token* Bigger = new Token;
				Token* Handle = new Token;
				//find witch one is smaller
				//copy it into smaller & bigger so that we can set convetion from small into big
				if (R->Size < L->Size) {
					*Smaller = *R;
					*Converted = *R;
					*Bigger = *L;
					Handle = Input.at(i)->Parameters.at(1);
				}
				else {
					*Smaller = *L;
					*Converted = *L;
					*Bigger = *R;
					Handle = Input.at(i)->Parameters.at(0);
				}
				Converted->Name += "_Converted";

				Register_Loader(*Smaller, i);
				Register_Chooser(Smaller);

				Converted->Size = Bigger->Size;
				Register_Chooser(Converted);

				IR* converter = new IR;
				converter->ID = "convert";
				converter->Parameters.push_back(new Token(*Converted));
				converter->Parameters.push_back(new Token(*Smaller));
				Input.insert(Input.begin() + i, converter);
				*Handle = *Converted;
			}
			//change number moving into empty 
			//chache variables into number moving into cache registers
			//mov [ebp - 0], 1 -->
			//mov reg, 1
			if (L->is("cache") && R->is(_Number_))
			{
				Token* tmp_L = new Token;
				*tmp_L = *Input.at(i)->Parameters.at(0);
				//make loading
				Input.at(i)->ID = "ldr";
				//make the tmp register
				Token* reg = new Token;
				reg->Name = tmp_L->Name + "_tmp_loading_register";
				reg->Size = tmp_L->Size;
				reg->add(_Register_);
				reg->add(Task_For_General_Purpose);
				*Input.at(i)->Parameters.at(0) = *reg;
				//choose the right reg
				Register_Chooser(reg);
				//now link this register with the cache variable.
				Register_Lock.insert({tmp_L, reg });
			}
			
		}
	}
}

void Emulator::Label_Recorder(int i)
{
	if (Input.at(i)->ID == "label" || (Input.at(i)->ID == "raw_label"))
	{
		if (Input.at(i)->is(_Start_Of_Label))
		{
			Branching_Label.push_back(Input.at(i)->PreFix);
		}
		else if (Input.at(i)->is(_End_Of_Label))
		{
			Branching_Label.pop_back();
		}
	}
	else if (Input.at(i)->ID == "return")
	{
		Branching_Label.pop_back();
		Register_Lock.clear();
	}
}

void Emulator::Register_Chooser(Token* t)
{
	if (t == nullptr)
		return;
	if (S->Fixable_Register(t) != nullptr){
		//if the name is already a name of register
		*t = *S->Fixable_Register(t);
		t->UID = t->Name;
		Skip_Chained_Registers(t);
		return;
	}
	if (t->is(_Register_))
	{
		if (!(t->is(Task_For_Returning))) {
			for (auto i : Register_Lock)
			{
				if (i.first->Name == t->Name)
				{
					//if this is finded
					t->UID = i.second->Name;
					return;
				}
			}
		}
		//if not
		Token* Reg = S->Get_Right_Reg(t->get(), t->Size);
		Skip_Chained_Registers(Reg);
		Register_Lock.insert({ t, Reg });
		t->UID = Reg->Name;
		return;
	}
	//this is commented because this is useless because eax is not e general register enymore.
	//else if (t->is(_Call_))
	//{
	//	if (S->Check_For_Reg(_SYSTEM_BIT_TYPE)->is(Task_For_Returning))
	//	{
	//		S->Increase(_SYSTEM_BIT_TYPE);
	//	}
	//}
}

void Emulator::Register_Loader(Token& t, int i)
{
	if (t.is(_Register_) != true)
	{

		//make a handle register
		Token* Reg = new Token;
		Reg->add(Task_For_General_Purpose);
		Reg->add(_Register_);
		Reg->Name = t.Name;
		Reg->Size = t.Size;
		//make the loading IR token
		IR* load = new IR;
		load->ID = "ldr";
		load->Parameters.push_back(Reg);
		load->Parameters.push_back(&t);
		t = *Reg;
		Input.insert(Input.begin() + i, load);
	}
}

void Emulator::Frame_Handler(int i)
{

}

void Emulator::FPU_Choser(int i)
{
}

void Emulator::Child(int i)
{
	if (Input.at(i)->Childs.size() > 0)
	{
		Emulator e = *this;
		e.Input = Input.at(i)->Childs;
		e.Factory();
	}
}

void Emulator::Use_Assembly(int i)
{
	if (Input.at(i)->is(_Skip_))
		return;

	Back b(Output);
	b.Input = Input.at(i);
	b.Factory();
	Output += NL;
}

void Emulator::Factory()
{
	for (int i = 0; i < (int)Input.size(); i++)
		Long_Operation_Allocator(i);
	for (int i = 0; i < (int)Input.size(); i++)
		Load_UID(i);
	for (int i = 0; i < (int)Input.size(); i++)
	{
		if (Input.at(i)->ID == "size" || Input.at(i)->ID == "state")
		{
			continue;
		}
		Label_Recorder(i);
		Frame_Handler(i);
		FPU_Choser(i);
		Pattern_User(i);
		Use_Assembly(i);
		Child(i);
	}
}

void Emulator::Pattern_User(int i)
{
	IR* p = new IR;
	IR* n = new IR;
	if (i - 1 >= 0)
		p = Input.at(i - 1);
	if (i + 1 <= (int)Input.size() - 1)
		n = Input.at(i + 1);
	IR* c = Input.at(i);
	Token* Pattern = new Token();
	if (Preprosessor_Tokens.find("") != Preprosessor_Tokens.end())
	{
		Pattern = Preprosessor_Tokens[""];
		Modder m(*p, *c, *n, Input, Pattern->Childs);
		m.Factory();
	}
	if (Branching_Label.size() > 0)
	{
		if (Preprosessor_Tokens.find(Branching_Label.back()) == Preprosessor_Tokens.end())
			return;
		Pattern = Preprosessor_Tokens[Branching_Label.back()];
		Modder m(*p, *c, *n, Input, Pattern->Childs);
		m.Factory();
	}
}

void Emulator::Skip_Chained_Registers(Token* reg){
	if (!reg->is(_Register_))
		return;
	for (Token* linked_reg : reg->Childs){
		//this mission is to seek for all the childs 
		//and theyre childs and add to the regi_turnX if it is on the mark.
		//try to do same to childs of childs of etc...
		Skip_Chained_Registers(linked_reg);
		//now get the indexed child's index
		int i = S->Get_Right_Reg_Index(linked_reg->Size, linked_reg);
		//now get the right vector list
		int& current_index = S->Get_Ongoing_Index(linked_reg->Size);
		//now just check for correlation
		while (true){
			if (current_index == i)
				current_index++;
			else if (((current_index+1) == i) || ((current_index+2) == i))
				if (S->Get_Register_List(linked_reg->Size).at(current_index)->get() != S->Get_Register_List(linked_reg->Size).at(i)->get()){
					current_index++;
					if ((current_index+1) == i) current_index++;
				}
				else
					break;
			else
				break;
		}
		//{a, b, c, d}
		// ^ <-- invalid
		//do simple register getting emulation.
	}
}

void Emulator::Link_Cache_User(Token* t){
	if (t->is(_Register_))
		return;
	if (t->Offsetter != nullptr)
		return;
	if (!t->is("cache"))
		return;
	//try to find register lock match on the same scoped context.
	for (auto i : Register_Lock)
		if (i.first->Name == t->Name)
			*t = *i.second;
}

void Emulator::Load_UID(int i)
{
	for (Token* T : Input.at(i)->Parameters)
	{
		Optimized_Register_Linking_Between_Different_Parameters(T);
		Link_Cache_User(T);
		Skip_Chained_Registers(T);
		Register_Chooser(T);
		if (T->Offsetter != nullptr)
			Register_Chooser(T->Offsetter);
	}
}

void Emulator::Optimized_Register_Linking_Between_Different_Parameters(Token* o){
	if (o->Name_Of_Same_Using_Register == "")
		return;
	//this functions mission is to look up for name of using register as the Name_Of_Same_Using_Register
	//and set it as this Token* o's register as well on register_lock.
	Token* Register = nullptr;
	//find the register that o->Name_Of_Same_Using_Register named object uses.
	for (auto i: Register_Lock)
		if (i.first->Name == o->Name_Of_Same_Using_Register)
			Register = i.second;
	if (Register == nullptr) return;
	//now lock these register'n o.
	Register_Lock.insert(make_pair(new Token(*o), new Token(*Register)));
}

