#ifndef IR_H_
#define IR_H_
#include "OpC.h" //ASM opcode
#include "../Back/Registers.h" //Register
#include "../Back/Token.h" //Variable
#include "../Selector/Selector.h"
#include <vector>

//IR's mission is to get the right parameters for the optimized opcode that Selector has selected.
class IR
{
public:
	vector<OpC*> Input;
	string Output = "";
	void Factory();
	IR(Token* in)
	{
		Selector* S = new Selector();
		S->Input = in;
		Input = S->Output;
	}

	~IR();
private:

};

#endif