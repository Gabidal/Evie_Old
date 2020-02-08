#include "..\..\H\Selector\Selector.h"


void Selector::OpCode_Selector()
{
	int Outcome = Values.at(0); //emulators made outcome
	OpC* Result;
		vector<int> P;
		P.push_back(Values.at(1));
		if ((Values.size()-1) > 1 )
		{
			P.push_back(Values.at(2));
		}
		for (auto* opc : OpCodes)
		{
			if (opc->_Function(P) == Values.at(0))
			{
				Output = opc;
				return;
			}
		}
		if ((Values.size() - 1) > 1)
		{
			cout << "No Opcode changes " << Values.at(1) << " and " << Values.at(2) << " into " << Values.at(0) << endl;
		}
		else
		{
			cout << "No Opcode changes " << Values.at(1) << " into " << Values.at(0) << endl;
		}
}
