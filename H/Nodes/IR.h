#ifndef _IR_H_
#define _IR_H_
#include "Token.h"
#include "../Lexer/Position.h"
#include <vector>
#include <string>

using namespace std;

class IR {
public:
	//[Token:OPC] [Token:arg], [Token:arg], [Token:arg]
	Token* OPCODE = nullptr;
	string ID = "";
	Position* Location;

	vector<Token*> Arguments;
	vector<vector<pair<Token*, pair<int, int>>>> Order;
	vector<IR*> (*Complex)(vector<Token*>) = nullptr;

	IR(Position* p) : Location(p){}
	IR(Token* opc, vector<Token*> args, Position* p) : OPCODE(opc), Arguments(args), Location(p) {  }
	IR(string id, Token* opc, vector<Token*> args, Position* p) : ID(id), OPCODE(opc), Arguments(args), Location(p) {}
	IR(string id, Token* opc, vector<vector<pair<Token*, pair<int, int>>>> order) : ID(id), OPCODE(opc), Order(order) {}
	IR(string id, Token* opc, vector<IR*> (*c)(vector<Token*>), Position* p) : ID(id), OPCODE(opc), Complex(c), Location(p) {}
	IR(string id, Token* opc, vector<vector<pair<Token*, pair<int, int>>>> order, vector<IR*> (*c)(vector<Token*>)) : ID(id), OPCODE(opc), Order(order), Complex(c) {}

	bool is(int flag) { return OPCODE->is(flag); }
};

#endif