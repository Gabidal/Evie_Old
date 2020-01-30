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
