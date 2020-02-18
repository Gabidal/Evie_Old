#ifndef IR_H_
#define IR_H_
#include "OpC.h"
#include "../Back/Token.h"

class IR
{
public:
	string Comment = "";
	vector<OpC*> Instructions;
	IR()
	{
	}

	~IR();

private:

};


#endif