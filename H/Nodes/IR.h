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
	string ID = "";
	vector<Token*> Arguments;
	vector<vector<pair<Token*, pair<int, int>>>> Order;
	vector<IR*> (*Complex)(vector<Token*>) = nullptr;

	IR(){}
	IR(Token* opc, vector<Token*> args) { OPCODE = opc; Arguments = args; }
	IR(string id, Token* opc, vector<Token*> args) : ID(id), OPCODE(opc), Arguments(args){}
	IR(string id, Token* opc, vector<vector<pair<Token*, pair<int, int>>>> order) : ID(id), OPCODE(opc), Order(order){}
	IR(string id, Token* opc, vector<IR*> (*c)(vector<Token*>)) : ID(id), OPCODE(opc), Complex(c){}
	IR(string id, Token* opc, vector<vector<pair<Token*, pair<int, int>>>> order, vector<IR*> (*c)(vector<Token*>)) : ID(id), OPCODE(opc), Order(order), Complex(c) {}

	bool is(int flag) { return OPCODE->is(flag); }
};

#endif