#ifndef _OPC_H_
#define _OPC_H_
#include <string>
#include <vector>
using namespace std;

class OpC
{
public:
	string ID = "";
	int Parameters_Amount = 0;
	int Left_Bit_Size = 0;
	int Right_Bit_Size = 0;
	int Cycle_Amount = 0;
	int OpCode_Size = 4;
	int (*_Function)(vector<int>);
	OpC(string id, int PA, int LP, int RP, int C, int (*F)(vector<int>))
	{
		ID = id;
		Parameters_Amount = PA;
		Left_Bit_Size = LP;
		Right_Bit_Size = RP;
		Cycle_Amount = C;
		_Function = F;
	}
	~OpC();
private:

};

#endif