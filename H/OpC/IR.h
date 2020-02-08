#ifndef IR_H_
#define IR_H_
#include "OpC.h" //ASM opcode
#include "../Back/Registers.h" //Register
#include "../Back/Token.h" //Variable
#include "../Selector/Selector.h"
#include <vector>

//IR's mission is to get the right parameters for the optimized opcode that Selector has selected.
//And return it to Token.cpp to write the output
class IR
{
private:
	void Factory();
	vector<Register*>* Used_Registers;
	vector<OpC*> Input;
public:
	string Output = "";
	IR(Token* in, vector<Register*> &UR)
	{
		Used_Registers = &UR;
		Selector* S = new Selector();
		S->Input = in;
		S->Factory(); //Get right OpCode
		Input = S->Output;
		this->Factory(); //Get right registers for the OpCoded
	}

	~IR();
};

#endif