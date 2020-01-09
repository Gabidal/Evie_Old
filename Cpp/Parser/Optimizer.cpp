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
}
