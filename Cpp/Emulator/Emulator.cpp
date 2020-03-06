#include "../../H/Emulator/Emulator.h"
#include "../../H/Selector/Selector.h"
extern Selector* S;
		// Register, Regiser using token
extern map<string, Token*> Register_Lock;
void Emulator::Long_Operation_Allocator(int &i)
{
	if ((Input.at(i)->ID == "==") || (Input.at(i)->ID == "!=") || (Input.at(i)->ID == "<") || (Input.at(i)->ID == ">") || (Input.at(i)->ID == "!<") || (Input.at(i)->ID == "!>") || (Input.at(i)->ID == "<=") || (Input.at(i)->ID == ">="))
	{
		//conditional operators need the cmp, and the condition jump operation.
		Token* Reg = new Token;
		Reg->Flags |= _Register_;
		Reg->Flags |= Task_For_General_Purpose;
		Reg->Name = Input.at(i)->Parameters.at(0)->Name;
		Reg->Size = Input.at(i)->Parameters.at(0)->Size;

		IR* cmp = new IR;
		*cmp = *Input.at(i);
		cmp->ID = "cmp";
		cmp->Parameters.at(0) = Reg;
		Input.at(i)->Parameters.clear();
		Input.at(i)->PreFix = Input.at(i)->ID;
		Input.at(i)->ID = Branching_Label.back() + "END";
		Input.insert(Input.begin() + i, cmp);
	}
	else if (Input.at(i)->ID == "return" && (Input.at(i)->is(_Allocated_) != true))
	{
		//make the returning
		Token* Reg = new Token;
		Reg->Flags |= _Register_;
		Reg->Flags |= Task_For_Returning;
		Reg->Name = Input.at(i)->Parameters.at(0)->Name;
		Reg->Size = Input.at(i)->Parameters.at(0)->Size;

		IR* mov_to_return_Reg = new IR;
		mov_to_return_Reg->ID = "ldr";
		mov_to_return_Reg->Parameters.push_back(Reg);
		mov_to_return_Reg->Parameters.push_back(Input.at(i)->Parameters.at(0));
		Input.at(i)->Parameters.clear();
		Input.at(i)->Flags |= _Allocated_;
		Input.insert(Input.begin() + i, mov_to_return_Reg);

		//make the leave
		IR* Leave = new IR;
		Leave->ID = "leave";
		Input.insert(Input.begin() + i + 1, Leave);
	}
	else if (Input.at(i)->PreFix == "export")
	{
		IR* label = new IR;
		label->PreFix = Input.at(i)->ID;
		label->ID = "raw_label";
		label->Flags |= _Start_Of_Label;
		label->Childs = Input.at(i)->Childs;
		Input.at(i)->Childs.clear();
		Input.insert(Input.begin() + i + 1 , label);
	}
	else if (Input.at(i)->ID == "call")
	{
		//go though the parameters (in left side childs) and make them a push IR tokens;
		for (Token* j : Input.at(i)->Parameters.at(0)->Left_Side_Token->Childs)
		{
			IR* p = new IR;
			p->ID = "push";
			p->Parameters.push_back(j);
			for (Token* T : p->Parameters)
			{
				Register_Chooser(T);
			}

			Back b(Output);
			b.Input = p;
			b.Factory();
			Output += NL;

		}
	}
	else if (Input.at(i)->is(_Operator_) && (Input.at(i)->is(_Allocated_) != true))
	{
		Input.at(i)->Flags |= _Allocated_;
		if (Input.at(i)->Parameters.size() > 1)
		{
			Token* L = new Token;
			*L	= *Input.at(i)->Parameters.at(0);
			Token* R = new Token;
			*R	= *Input.at(i)->Parameters.at(1);
			if (L->Size != R->Size)
			{
				IR* D = Input.at(i);
				//make a handle register
				Register_Loader(*R, i);
				Register_Chooser(R);
				Register_Loader(*L, i);
				Register_Chooser(L);


				IR* converter = new IR;
				converter->ID = "convert";
				converter->Parameters.push_back(L);
				converter->Parameters.push_back(R);
				Input.insert(Input.begin() + i, converter);
				D->Parameters.at(1) = L;
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
	}
}

void Emulator::Register_Chooser(Token* t)
{
	if (t->is(_Register_))
	{
		for (auto i : Register_Lock)
		{
			if (i.first == t->Name)
			{
				//if this is finded
				t->UID = i.second->Name;
				return;
			}
		}
		//if not
		Token* Reg = S->Get_Right_Reg(t->Flags, t->Size);
		Register_Lock.insert({ t->Name, Reg });
		t->UID = Reg->Name;
		return;
	}
}

void Emulator::Register_Loader(Token& t, int i)
{
	if (t.is(_Register_) != true)
	{

		//make a handle register
		Token* Reg = new Token;
		Reg->Flags |= Task_For_General_Purpose;
		Reg->Flags |= _Register_;
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
	for (Token* T : Input.at(i)->Parameters)
	{
		Register_Chooser(T);
	}

	Back b(Output);
	b.Input = Input.at(i);
	b.Factory();
	Output += NL;
}

void Emulator::Factory()
{
	for (int i = 0; i < Input.size(); i++)
	{
		if (Input.at(i)->ID == "Size" || Input.at(i)->ID == "Static")
		{
			continue;
		}
		Long_Operation_Allocator(i);
		Label_Recorder(i);
		Frame_Handler(i);
		FPU_Choser(i);
		Use_Assembly(i);
		Child(i);
	}
}
