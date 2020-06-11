#ifndef GENERATOR_H_
#define GENERATOR_H_
#include <vector>
#include "Token.h"
#include "../OpC/IR.h"
#include "../Lexer/Lexer.h"
#include "../Lexer/Component.h"
#include "Back.h"
#include "../Mangler/Mangler.h"
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
	void Detect_Pointters(Token* t);
	void Detect_Arrays(Token* t);
	void Detect_Address_Pointing(Token* t);
	void Detect_Parenthesis(Token* t);
	void Detect_Pre_Defined_Tokens(Token* t);
	void Detect_Prefixes(Token* t);
	void Scaler(Token* l, Token* r);
	void Dodge(Token* l, Token* r);
	void Rotator(Token* l, Token* r);
	void Initialize_Global_Variable(int i);
	void Append(vector<IR*> *Dest, vector<IR*> Source);
	void Hide_Un_Used_Function(int i);
	void Hide_Real_Size(Token* t);
	//void Update_Used_Functions_Value(Token* call);
	Generator()
	{
	}

	~Generator(){}

private:

};


#endif