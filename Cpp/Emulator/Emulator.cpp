#include "../../H/Emulator/Emulator.h"
#include "../../H/Semantic/Semantic.h"
extern Semantic* S;

void Emulator::Long_Operation_Allocator(int i)
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
		Input.insert(Input.begin() + i, cmp);
		Input.at(i+1)->Parameters.clear();
		Input.at(i+1)->PreFix = Input.at(i+1)->ID;
		Input.at(i+1)->ID = Branching_Label.back() + "END";
	}
	else if (Input.at(i)->ID == "return" && (Input.at(i)->is(_Allocated_) != true))
	{
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
}

void Emulator::Label_Recorder(int i)
{
	if (Input.at(i)->ID == "label")
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
