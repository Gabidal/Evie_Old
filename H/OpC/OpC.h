#ifndef _OPC_H_
#define _OPC_H_
#include <string>
#include <vector>
using namespace std;
#define __Loader (1<<0)
#define __Storer (1<<1)

class OpC
{
public:
	string ID = "";
	string OpCode = "";

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