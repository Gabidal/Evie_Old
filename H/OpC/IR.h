#ifndef IR_H_
#define IR_H_
#include "OpC.h" //ASM opcode
#include "../Back/Token.h" //Variable
#include "../Selector/Selector.h"
#include <vector>

//IR's mission is to get the right parameters for the optimized opcode that Selector has selected.
//And return it to Token.cpp to write the output
class IR
{
private:
	Register* Get_Register();
	void Factory();
	vector<Register*>* Used_Registers;
	OpC* OpCode;
	Token* T;
	string Left = "";
	string Right = "";
public:
	string Output = "";
	IR(Token* in, vector<Register*> &UR, vector<int> Values)
	{
		T = in;
		Used_Registers = &UR;
		Selector* S = new Selector(Values); //values at 0 is the outcome of the later childs that make that outcome
		S->Input = in; //OPERATOR
		S->OpCode_Selector();
		OpCode = S->Output;
		this->Factory(); //Get right registers for the OpCoded
	}

	~IR();
};

#endif