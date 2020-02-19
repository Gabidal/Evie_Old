#include "..\..\H\Back\Generator.h"
extern vector<string> Pre_Defined_Tokens;

void Generator::Factory()
{
	for (Token*t : Input)
	{
		Detect_Condition(t);
		Detect_Function(t);
		Detect_Operator(t);
		Detect_Pre_Defined_Tokens(t);
	}
}

void Generator::Detect_Function(Token* t)
{
	if (t->is(_Constructor_))
	{
		//make a label OpC*
		IR* ir = new IR;
		ir->ID = "label";
		ir->PreFix = t->Name;
		//make the insights of this constructor
		Generator g;
		g.Input.push_back(t->Right_Side_Token);
		g.Types = this->Types;
		g.Factory();
		//get the output as the new IR's childs.
		ir->Childs = g.Output;
		Output.push_back(ir);
	}
	else if (t->is(_Call_))
	{
		//make a callation OpC*
		IR* ir = new IR;
		ir->ID = "call";
		//when we give the token call, (name) to it and in parser defined as
		//_External_ it can do something like this: call [banana] ; as a global variable.
		ir->Parameters.push_back(t);
		//generate the parameters as IR tokens
		Generator g;
		g.Input.push_back(t->Left_Side_Token);
		g.Types = this->Types;
		g.Factory();
		//get the output from the generator and store then into the parent IR operator.
		ir->Childs = g.Output;
		Output.push_back(ir);
	}
}

void Generator::Detect_Condition(Token* t)
{
}

void Generator::Detect_Operator(Token* t)
{
}

void Generator::Detect_Parenthesis(Token* t)
{
}

void Generator::Detect_Pre_Defined_Tokens(Token* t)
{
	for (string T : Pre_Defined_Tokens)
	{
		if (t->Name == T)
		{
			IR *ir = new IR;
			ir->ID = T;
			ir->Parameters.push_back(t->Right_Side_Token);
			Output.push_back(ir);
		}
	}
}
