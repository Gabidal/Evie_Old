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
public:
	void Factory();
	void Right_Sided_Derivation_Solver(Token *t);
	void Operator_Breaker();
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