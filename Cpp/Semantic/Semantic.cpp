#include "..\..\H\Semantic\Semantic.h"

void Semantic::Factory()
{
	Operator_Breaker(Input);
	Assembler();
	Output = Raw_Order.at(0);
	Output->Semanticked = true;
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
	//[[[a = b] + [c * d]] - e]
	/*Order_Pusher("=", "=");
	Order_Pusher("*", "/");
	Order_Pusher("<<", ">>");
	Order_Pusher("+", "-");*/
	while (Raw_Order.size() > 1)
	{
		Order_Finder("=", "=");
		Order_Finder("*", "/");
		Order_Finder("<<", ">>");
		Order_Finder("+", "-");
	}
}

void Semantic::Order_Finder(string x, string y)
{
	//for loop until you can find most importance token

	for (int i = 0; i < Raw_Order.size(); i++)
	{
		if (Raw_Order.at(i)->Semanticked)
		{
			continue;
		}
		if (Raw_Order.at(i)->Name == x || Raw_Order.at(i)->Name == y)
		{
			Raw_Order.at(i)->Parameters.at(0) = Raw_Order.at(i - 1);
			Raw_Order.at(i)->Childs.at(0) = Raw_Order.at(i + 1);
			Raw_Order.at(i)->Semanticked = true;
			Raw_Order.erase(Raw_Order.begin() + i - 1);
			Raw_Order.erase(Raw_Order.begin() + i);
			i -= 2;
		}
	}
}

void Semantic::Order_Pusher(string x, string y)
{
	int i = 0;
	for (Token* t : Raw_Order)
	{
		if (t->Name == x || t->Name == y)
		{
			*t->Parameters.at(0) = *Raw_Order.at(i - 1);
			*t->Childs.at(0) = *Raw_Order.at(i + 1);
			Ordered_List.push_back(t);
			Raw_Order.erase(Raw_Order.begin() + i - 1);
			Raw_Order.erase(Raw_Order.begin() + i);
		}
		i++;
	}
}

