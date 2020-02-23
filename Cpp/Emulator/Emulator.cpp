#include "../../H/Emulator/Emulator.h"

void Emulator::Long_Operation_Allocator(int &i)
{
	if (Input.at(i)->ID == "==" || Input.at(i)->ID == "!=" || Input.at(i)->ID == "<" || Input.at(i)->ID == ">" || Input.at(i)->ID == "!<" || Input.at(i)->ID == "!>" || Input.at(i)->ID == "<=" || Input.at(i)->ID == ">=")
	{
		//conditional operators need the cmp, and the condition jump operation.
		IR* cmp = new IR;
		*cmp = *Input.at(i);
		cmp->ID = "cmp";
		Input.insert(Input.begin() + i, cmp);
		Input.at(i)->Parameters.clear();
		Input.at(i)->PreFix = Input.at(i)->ID;
		Input.at(i)->ID = Branching_Label.back() + "END";
		i++;
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

void Emulator::Math(int i)
{
}
