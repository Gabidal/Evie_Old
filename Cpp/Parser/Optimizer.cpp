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
	int eax = 0;
	int ebx = 0;
	int ecx = 0;
	int edx = 0;
	int edi = 0;
	int esi = 0;
	int ebp = 0;
	int esp = 0;
	Emulator* E = new Emulator(Input, start, eax, ebx, ecx, edx, edi, esi, esp, ebp);
	E->Factory();
	cout << E->_EAX << endl << E->_EBX << endl << E->_ECX << endl << E->_EDX << endl << E->_EDI << endl << E->_ESI << endl << E->_ESP << endl << E->_EBP << endl;
}
