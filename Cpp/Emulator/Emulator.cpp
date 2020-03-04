#include "../../H/Emulator/Emulator.h"
#include "../../H/Semantic/Semantic.h"
extern Semantic* S;
		// Register, Regiser using token
extern map<string, Token*> Register_Lock;
void Emulator::Long_Operation_Allocator(IR* t, int i)
{
	if ((t->ID == "==") || (t->ID == "!=") || (t->ID == "<") || (t->ID == ">") || (t->ID == "!<") || (t->ID == "!>") || (t->ID == "<=") || (t->ID == ">="))
	{
		//conditional operators need the cmp, and the condition jump operation.
		Token* Reg = new Token;
		Reg->Flags |= _Register_;
		Reg->Flags |= Task_For_General_Purpose;
		Reg->Name = t->Parameters.at(0)->Name;
		Reg->Size = t->Parameters.at(0)->Size;

		IR* cmp = new IR;
		*cmp = *t;
		cmp->ID = "cmp";
		cmp->Parameters.at(0) = Reg;
		t->Parameters.clear();
		t->PreFix = t->ID;
		t->ID = Branching_Label.back() + "END";
		Input.insert(Input.begin() + i, cmp);
	}
	else if (t->ID == "return" && (t->is(_Allocated_) != true))
	{
		Token* Reg = new Token;
		Reg->Flags |= _Register_;
		Reg->Flags |= Task_For_Returning;
		Reg->Name = t->Parameters.at(0)->Name;
		Reg->Size = t->Parameters.at(0)->Size;

		IR* mov_to_return_Reg = new IR;
		mov_to_return_Reg->ID = "ldr";
		mov_to_return_Reg->Parameters.push_back(Reg);
		mov_to_return_Reg->Parameters.push_back(t->Parameters.at(0));
		t->Parameters.clear();
		t->Flags |= _Allocated_;
		Input.insert(Input.begin() + i, mov_to_return_Reg);
	}
	else if (t->PreFix == "export")
	{
		IR* label = new IR;
		label->PreFix = t->ID;
		label->ID = "raw_label";
		label->Flags |= _Start_Of_Label;
		label->Childs = t->Childs;
		t->Childs.clear();
		Input.insert(Input.begin() + i + 1 , label);
	}
}

void Emulator::Label_Recorder(IR* t)
{
	if (t->ID == "label" || (t->ID == "raw_label"))
	{
		if (t->is(_Start_Of_Label))
		{
			Branching_Label.push_back(t->PreFix);
		}
		else if (t->is(_End_Of_Label))
		{
			Branching_Label.pop_back();
		}
	}
	else if (t->ID == "return")
	{
		Branching_Label.pop_back();
	}
}

void Emulator::Register_Chooser(Token* t)
{
	if (t->is(_Register_))
	{
		for (map<string, Token*>::iterator i = Register_Lock.begin(); i != Register_Lock.end(); i++)
		{
			if (i->second->Name == t->Name)
			{

			}
		}
	}
}

void Emulator::Frame_Handler(IR* t)
{

}

void Emulator::FPU_Choser(IR* t)
{
}

void Emulator::Child(IR* t)
{
	if (t->Childs.size() > 0)
	{
		Emulator e = *this;
		e.Input = t->Childs;
		e.Factory();
	}
}

void Emulator::Use_Assembly(IR* t)
{
	for (Token* T : t->Parameters)
	{
		Register_Chooser(T);
	}

	Back b(Output);
	b.Input = t;
	b.Factory();
	Output += NL;
}

void Emulator::Factory()
{
	int i = -1;
	for (IR *t : Input)
	{
		i++;
		if (t->ID == "Size" || t->ID == "Static")
		{
			continue;
		}
		Long_Operation_Allocator(t, i);
		Label_Recorder(t);
		Frame_Handler(t);
		FPU_Choser(t);
		Use_Assembly(t);
		Child(t);
	}
}
