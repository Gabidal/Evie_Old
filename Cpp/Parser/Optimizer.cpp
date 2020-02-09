#include "../../H/Parser/Optimizer.h"

void Optimizer::Factory()
{
	int start = Find_Start_Of_Runnable();
	Simulate_Runnable(start);
}

int Optimizer::Find_Start_Of_Runnable()
{
	int i = 0;
	for (Token* t : Input)
	{
		if ((t->Name == "main") && (t->is(Function)))
		{
			return i;
		}
		i++;
	}
	return 0;
	Lib = true;
}

void Optimizer::Simulate_Runnable(int start)
{
	Emulator* E = new Emulator(Input);
	cout << E->Start_Simulation(start) << endl;
	Free_Registers();
}

void Optimizer::Free_Registers()
{
	R1->Base = nullptr;
	R1->Value = 0;

	R4->Base = nullptr;
	R4->Value = 0;

	R3->Base = nullptr;
	R3->Value = 0;

	R5->Base = nullptr;
	R5->Value = 0;

	R6->Base = nullptr;
	R6->Value = 0;

	R7->Base = nullptr;
	R7->Value = 0;

	R8->Base = nullptr;
	R8->Value = 0;

}
