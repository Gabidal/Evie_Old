#include "..\..\H\Semantic\Semantic.h"

void Semantic::Factory()
{
	Operator_Breaker(Input);
}

void Semantic::Right_Sided_Derivation_Solver(Token* t)
{

}

void Semantic::Operator_Breaker(Token *t)
{
	//this function breaks the ast in the operator-
	//token and puts it as a raw token list in a vector
	// a = b + c * d - e
	if (t->Parameters.at(0)->is(OPERATOR))
	{
		Operator_Breaker(t->Parameters.at(0));
	}
	else
	{
		Raw_Order.push_back(t->Parameters.at(0));
	}
	Raw_Order.push_back(t);
	Raw_Order.push_back(t->Childs.at(0));
}

void Semantic::Assembler()
{
	//this function assembles the insides 
	//of the Raw_list of mathematical tokens
	//a = b + [c * d] - e
}

void Semantic::Order_Finder()
{
	//for loop until you can find most importance token
	int Base = 0;
	int Current = 0;
	for (int i = 0; i < Raw_Order.size(); i++)
	{
		if (Raw_Order.at(i)->Name == "*" || Raw_Order.at(i)->Name == "/")
		{
			Current = 1;
		}
		else if (Raw_Order.at(i)->Name == "+" || Raw_Order.at(i)->Name == "-")
		{
			Current = 0;
		}
		if (Current > Base)
		{
			Base = Current;
		}
	}
}
