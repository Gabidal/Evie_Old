#include "..\..\H\Semantic\Semantic.h"

void Semantic::Factory()
{
	Operator_Breaker(Input);
	Assembler();
	Output = Raw_Order.at(0);
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
	Order_Finder("*", "/");
	Order_Finder("<<", ">>");
	Order_Finder("+", "-");
	Order_Finder("=", "=");
}

void Semantic::Order_Finder(string x, string y)
{
	//for loop until you can find most importance token

	int i = 0;
	for (Token* t : Raw_Order)
	{
		if (t->Name == x || t->Name == y)
		{
			*t->Parameters.at(0) = *Raw_Order.at(i - 1);
			*t->Parameters.at(0) = *Raw_Order.at(i + 1);
			Raw_Order.erase(Raw_Order.begin() + i - 1);
			Raw_Order.erase(Raw_Order.begin() + i + 1);
		}
		i++;
	}
}

