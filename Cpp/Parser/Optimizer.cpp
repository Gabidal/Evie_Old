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
	EAX->Base = nullptr;
	EAX->Current = nullptr;
	EAX->Value = 0;

	EDX->Base = nullptr;
	EDX->Current = nullptr;
	EDX->Value = 0;

	ECX->Base = nullptr;
	ECX->Current = nullptr;
	ECX->Value = 0;

	EDI->Base = nullptr;
	EDI->Current = nullptr;
	EDI->Value = 0;

	ESI->Base = nullptr;
	ESI->Current = nullptr;
	ESI->Value = 0;

	ESP->Base = nullptr;
	ESP->Current = nullptr;
	ESP->Value = 0;

	EBP->Base = nullptr;
	EBP->Current = nullptr;
	EBP->Value = 0;

}
