#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_
#include <vector>
#include "../Back/Token.h"

//this is the Semantic analyser

class Semantic
{
	Token* Output;
	Token* Input;
	vector<Token*> Raw_Order;
	int Tip_Of_Importance = 0;
public:
	void Factory();
	void Right_Sided_Derivation_Solver(Token *t);
	void Operator_Breaker(Token* t);
	void Assembler();
	void Order_Finder();
	Semantic(Token *i, Token& o)
	{
		Input = i;
		Factory();
		o = *Output;
	}

	~Semantic()
	{
	}

private:

};


#endif