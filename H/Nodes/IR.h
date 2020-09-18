#ifndef _IR_H_
#define _IR_H_
#include "Token.h"
#include <vector>
#include <string>

using namespace std;

class IR {
public:
	//[Token:OPC] [Token:arg], [Token:arg], [Token:arg]
	Token* OPCODE = nullptr;
	vector<Token*> Arguments;

	IR(){}
	IR(Token* opc, vector<Token*> args) { OPCODE = opc; Arguments = args; }
};

#endif