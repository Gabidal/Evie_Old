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
	vector<Token*> Ordered_List;
public:
	void Factory();
	void Operator_Breaker(Token* t);
	void Assembler();
	void Order_Finder(string x, string y);
	void Order_Pusher(string x, string y);
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