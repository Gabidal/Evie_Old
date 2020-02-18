#ifndef IR_H_
#define IR_H_
#include "OpC.h"
#include "../Back/Token.h"

class IR
{
public:
	string Comment = "";
	//for single line:
		string PreFix = "";
		string ID = "";
		vector<Token*> Parameters;
	//for multi levelled opcodes:
		vector<IR*> Childs;
	IR()
	{
	}

	~IR();

private:

};


#endif