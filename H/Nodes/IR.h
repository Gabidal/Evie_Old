#ifndef _IR_H_
#define _IR_H_
#include "Token.h"
#include "../Lexer/Position.h"
#include <vector>
#include <string>

using namespace std;

class Structure {
public:
	Token* Type = nullptr;
	int Min_Size = 0;
	int Max_Size = 0;

	Structure(Token* t, int mins, int maxs) {
		Type = t;
		Min_Size = mins;
		Max_Size = maxs;
	}
};

enum class OPCODE_ENCODING {
	NaN,
	MR,
	RM,
	FD,
	TD,
	OI,
	MI,
	ZO,

	M,
	R,
	I,
	A,
	B,
	C,
	D
};

class Pattern {
public:
	vector<Structure> Order;
	int ID = 0;
	OPCODE_ENCODING Encoding = OPCODE_ENCODING::NaN;
	int Post_Fix = 0;
	int Pre_Fix = 0;

	Pattern(vector<Structure> order, int id = 0, OPCODE_ENCODING en = OPCODE_ENCODING::NaN, int post = 0, int pre_fix = 0) {
		Order = order;
		ID = id;
		Encoding = en;
		Post_Fix = post;
		Pre_Fix = pre_fix;
	}
};

class IR {
public:
	//[Token:OPC] [Token:arg], [Token:arg], [Token:arg]
	Token* OPCODE = nullptr;
	string ID = "";
	Position* Location;

	vector<Token*> Arguments;
	//Type, min_-size, max_size, Base_Opcode_id
	//vector<vector<pair<Token*, pair<pair<int, int>, int>>>> Order;
	vector<Pattern> Order;
	vector<IR*> (*Complex)(vector<Token*>) = nullptr;

	IR(Position* p) : Location(p){}
	IR(Token* opc, vector<Token*> args, Position* p) : OPCODE(opc), Arguments(args), Location(p) {  }
	IR(string id, Token* opc, vector<Token*> args, Position* p) : ID(id), OPCODE(opc), Arguments(args), Location(p) {}
	IR(string id, Token* opc, vector<Pattern> order) : ID(id), OPCODE(opc), Order(order) {}
	IR(string id, Token* opc, vector<IR*> (*c)(vector<Token*>), Position* p) : ID(id), OPCODE(opc), Complex(c), Location(p) {}
	IR(string id, Token* opc, vector<Pattern> order, vector<IR*> (*c)(vector<Token*>)) : ID(id), OPCODE(opc), Order(order), Complex(c) {}

	bool is(int flag) { return OPCODE->is(flag); }
	vector<Token*> Get_All(long long F)
	{
		vector<Token*> Result;
		for (auto i : Arguments) {
			vector<Token*> Tmp = i->Get_All(F);
			Result.insert(Result.begin(), Tmp.begin(), Tmp.end());
		}
		if (OPCODE) {
			vector<Token*> Tmp = OPCODE->Get_All(F);
			Result.insert(Result.begin(), Tmp.begin(), Tmp.end());
		}

		return Result;
	}

};

#endif