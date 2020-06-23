#include "../../H/Emulator/Emulator.h"
#include "../../H/Selector/Selector.h"
#include "../../H/UI/Usr.h"
extern Selector* S;
		// Register, Regiser using token
extern map<string, Token*> Preprosessor_Tokens;
extern Object* Root;
extern int _SYSTEM_BIT_TYPE;
string SYNTAX_TABS = "";

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
		int DOUBLETASKPOSITION = i;
		Input.at(i)->add(_Allocated_);
		if (Input.at(i)->Parameters.size() > 0) {
			//make the returning
			Token* Reg = new Token;
			Reg->add(_Register_);
			Reg->add(Task_For_Returning);
			//Reg->Name = Get_Info(Input.at(i)->Parameters.at(0))->Name + "_returning_register";
			Reg->Name = "eax";
			//Reg->Size = Get_Info(Input.at(i)->Parameters.at(0))->Size;
			//for safety
			Reg->Size = _SYSTEM_BIT_TYPE;

			//fix the returning number size
			if (Input.at(i)->Parameters.at(0)->is(_Number_))
				if (Input.at(i)->Parameters.at(0)->Size < _SYSTEM_BIT_TYPE)
					Input.at(i)->Parameters.at(0)->Size = _SYSTEM_BIT_TYPE;

			IR* mov_to_return_Reg = new IR;
			mov_to_return_Reg->ID = "ldr";
			mov_to_return_Reg->Parameters.push_back(Reg);
			mov_to_return_Reg->Parameters.push_back(Get_Info(Input.at(i)->Parameters.at(0)));
			Input.at(i)->Parameters.clear();
			Input.insert(Input.begin() + i, mov_to_return_Reg);
			DOUBLETASKPOSITION++;
		}
		//make the leave
		if (Input.at(DOUBLETASKPOSITION)->is(_Double_Task_))
		{
			IR* Leave = new IR;
			Leave->ID = "leave";
			Input.insert(Input.begin() + DOUBLETASKPOSITION, Leave);
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
				Register_Chooser(Smaller, i);

				Converted->Size = Bigger->Size;
				Register_Chooser(Converted, i);

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
				reg->add(Task_For_Non_Volatiling);
				*Input.at(i)->Parameters.at(0) = *reg;
				//choose the right reg
				Register_Chooser(reg, i);
				//now link this register with the cache variable.
				S->Link_Register(tmp_L, reg);
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
			S->Context.push_back(Input.at(i)->PreFix);
		}
		else if (Input.at(i)->is(_End_Of_Label))
		{
			Branching_Label.pop_back();
			S->Context.pop_back();
		}
		Update_Syntax_Tabs();
	}
}

void Emulator::Register_Chooser(Token* t, int i)
{
	if (t == nullptr)
		return;
	if (S->Get_Index_Of(t) != -1){
		//if the name is already a name of register
		*t = *S->Get_Right_Size_List(t->Size).at(S->Get_Index_Of(t));
		Skip_Chained_Registers(t);
		return;
	}
	if (t->is(_Register_))
	{
		if (!(t->is(Task_For_Returning))) {
			if (S->Get_Register(t->Name) != nullptr){
				t->UID = S->Get_Register(t->Name)->UID;
				return;
			}
		}

		//lets try to find the future use of this token and 
		//thus determine the volatile/non-volatility register we give em
		if (t->is(Task_For_General_Purpose))
			t->add(S->Get_Right_Task_Flags(Input, i, t));

		Token* Reg = S->Get_New_Register(t);
		if (Reg == nullptr)
		{
			//need to free more space on registers.
			vector<Token*> savable = S->Free_Registers(t, Input, i, false); //dont take the last checked
			//the free registers gives us a vector list of no saving requed values.
			//now we need to check the life time of the freeable register and second question ouw selfs
			//savable = S->Get_Lifetime_Of(savable, Input, i);
			//if (savable.size() < 1)
				//then try to free some other register's
			//	savable = S->Free_Registers(t);
			//disconnect the saved variables from register chunk list .
			Disconnect_Register(savable);
			//now try to use the freed register.
			Reg = S->Get_New_Register(t);
			//if still the register is nullptr try to put the used registers into mem and reserve some mem also plzz
			if (Reg == nullptr) {
				vector<Token*> savable = S->Free_Registers(t, Input, i, true); //take the last checked
				//now the free_register vill give us list of variables that we need to save

				Disconnect_Register(savable);
				Reg = S->Get_New_Register(t);
			}
		}
		
		Skip_Chained_Registers(Reg);
		t->UID = Reg->UID;
		return;
	}
}

void Emulator::Register_Loader(Token& t, int i)
{
	if (!t.is(_Register_))
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
	Set_Syntax_Tabs(Input.at(i));
	Back b(Output);
	b.Input = Input.at(i);
	b.Factory();
	Output += NL;
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
		int i = S->Get_Index_Of(linked_reg);
		//now get the right vector list
		int& current_index = S->Get_Right_Ongoing_Register_Index(linked_reg->Size);
		//now just check for correlation
		while (true){
			if (current_index == i)
				current_index++;
			else if (((current_index+1) == i) || ((current_index+2) == i))
				if (S->Get_Right_Size_List(linked_reg->Size).at(current_index)->get() != S->Get_Right_Size_List(linked_reg->Size).at(i)->get()){
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
	if (S->Get_Register(t->Name) != nullptr){
		*t = *S->Get_Register(t->Name);
		return;
	}
	//if this is then something is wrong
	cout << "Error: Too long use of " << t->Name << "." << endl;
	return;
}

void Emulator::Load_UID(int i)
{
	for (Token* T : Input.at(i)->Parameters)
	{
		Optimized_Register_Linking_Between_Different_Parameters(T);
		Link_Cache_User(T);
		Skip_Chained_Registers(T);
		Register_Chooser(T, i);
		if (T->Offsetter != nullptr){
			Optimized_Register_Linking_Between_Different_Parameters(T->Offsetter);
			Link_Cache_User(T->Offsetter);
			Skip_Chained_Registers(T->Offsetter);
			Register_Chooser(T->Offsetter, i);
		}
	}
}

void Emulator::Optimized_Register_Linking_Between_Different_Parameters(Token* o){
	if (o->Name_Of_Same_Using_Register == "")
		return;
	//this functions mission is to look up for name of using register as the Name_Of_Same_Using_Register
	//and set it as this Token* o's register as well on register_lock.
	//find the register that o->Name_Of_Same_Using_Register named object uses.
	if (S->Get_Register(o->Name_Of_Same_Using_Register) != nullptr)
		//now lock these register'n o.
		S->Link_Register(o, S->Get_Register(o->Name_Of_Same_Using_Register));
	return;
}

/*void Emulator::Save_Variable(Token* t, int i){
	//we need to save the token* t
	IR* save = new IR;
	save->ID = "=";
	save->Parameters.push_back(S->Find_Owner(t));
	save->Parameters.push_back(S->Get_Register(t->Name));
	//put
	Input.insert(Input.begin() + i, save);
}*/

void Emulator::Disconnect_Register(vector<Token*> t){
	for (Token* i : t)
		S->Disconnect_Register(i);
	return;
}

void Emulator::Update_Syntax_Tabs()
{
	//first clear the syntax_tabs to start fresh.
	SYNTAX_TABS = "";
	if (Branching_Label.size() < 2)
		return;
	//then start gather them
	for (string s : Branching_Label)
		SYNTAX_TABS += " ";
	return;
}

void Emulator::Set_Syntax_Tabs(IR* t)
{
	t->Tabs = SYNTAX_TABS;
	return;
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