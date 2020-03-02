#ifndef _OPC_H_
#define _OPC_H_
#include <string>
#include <vector>
using namespace std;
class Token;

class OpC
{
public:
	string ID = "";
	string OpCode = "";
	vector<Token*> Parameters;
	int Cycles = 0;
	vector<int> MinMax;

	OpC(int c, string id, string opcode, vector<int> minmax)
	{
		Cycles = c;
		ID = id;
		OpCode = opcode;
		MinMax = minmax;
	}
	~OpC();
private:

};

#endif