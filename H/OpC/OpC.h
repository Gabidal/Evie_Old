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

	OpC(int c, string id, string opcode)
	{
		Cycles = c;
		ID = id;
		OpCode = opcode;
	}
	~OpC();
private:

};

#endif