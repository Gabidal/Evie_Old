#ifndef GENERATOR_H_
#define GENERATOR_H_
#include <vector>
#include "Token.h"
#include "../OpC/IR.h"
#include "Back.h"
using namespace std;


class Generator
{
public:
	string TMP = "";
	vector<Token*> Types;
	vector<Token*> Input;
	vector<IR*> Output;
	vector<string> Initted_Variables;
	Token* Handle = nullptr;
	void Factory();
	void Detect_Function(Token* t);
	void Detect_Condition(Token* t);
	void Detect_Operator(Token* t);
	void Detect_Parenthesis(Token* t);
	void Detect_Pre_Defined_Tokens(Token* t);
	void Append(vector<IR*> *Dest, vector<IR*> Source);
	Generator()
	{
	}

	~Generator(){}

private:

};


#endif