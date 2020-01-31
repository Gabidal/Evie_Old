#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_
#include <vector>
#include "../Back/Token.h"

//this is the Semantic analyser

class Semantic
{
	Token* Output = nullptr;
	Token* Input = nullptr;
	vector<Token*> Raw_Order;
public:
	void Factory();
	void Right_Sided_Derivation_Solver(Token *t);
	void Operator_Breaker(Token* t);
	void Assembler();
	void Order_Finder(string x, string y);
	Semantic(Token& Dest, Token *Source)
	{
		Input = Source;
		Factory();
		Dest = *Output;
	}

	~Semantic()
	{
	}

private:

};


#endif