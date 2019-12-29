#include "../../H/Parser/Optimizer.h"

void Optimizer::Factory()
{
	int start_point = Get_Start_Of_Runnable();
	Analyse_Function(start_point);
}

int Optimizer::Get_Start_Of_Runnable()
{
	for (int i = 0; i < Input.size(); i++)
	{
		if ((Input.at(i)->Name == "main") && (Input.at(i)->is(Function)))
		{
			Input.at(i)->Flags |= Used;
			return i;
		}
	}
}

void Optimizer::Analyse_Function(int i)
{
	for (Token *t : Input.at(i)->Childs)
	{
		Analyse_Math(*t);
	}
}

void Optimizer::Analyse_Math(Token& t)
{
	if (t.is(OPERATOR))
	{
		//get destination and check if its used anywhere usefull.
		Token &Dest = Get_Abselute_Destination(t);
		if (Look_up_Probality_To_Be_Used(Dest).Probability >= 1.0)
		{
			Dest.Flags |= Used;
			Handle_Source(t);
		}
		else if (t.Childs.at(0)->is(Call))
		{
			Handle_Function_Call(*t.Childs.at(0));
		}
	}
}

Token& Optimizer::Get_Abselute_Destination(Token &t)
{
	for (Token* i : t.Parameters)
	{
		return Get_Abselute_Destination(*i);
	}
	return t;
}

Token& Optimizer::Look_up_Probality_To_Be_Used(Token& t)
{
	if (t.is(Public))
	{
		t.Probability += 1.0;
	}
	if (t.is(Parameter))
	{
		if (t.ParentFunc->Callations->size() > 0)
		{
			int ptrs = Ptr | Array | NotOriginal;
			if (t.ParentFunc->Callations->at(0)->Parameters.at(t.ParameterOffset/4)->Any(ptrs))
			{
				t.Probability += 1.0;
			}
		}
	}
	if (t.ParentFunc->is(Returning))
	{
		Find_Return(*t.ParentFunc);
	}
	return t;
}

void Optimizer::Find_Return(Token& T)
{
	for (Token *t: T.Childs)
	{
		if (t->is(If) || t->is(Else) || t->is(While))
		{
			Find_Return(*t);
		}
		if (t->Name == "return")
		{
			t->Childs.at(0)->Probability += 1.0;
			t->Probability += 1.0;
		}
	}
}

void Optimizer::Handle_Source(Token& t)
{
	if (t.Parameters.at(0)->is(OPERATOR))
	{
		Handle_Source(*t.Parameters.at(0));
	}
	else if (t.Childs.at(0)->is(Call))
	{
		Handle_Function_Call(*t.Childs.at(0));
	}
}

void Optimizer::Handle_Function_Call(Token& t)
{
	for (Token* i : t.Parameters)
	{
		if (i->is(Ptr) || i->is(Array) || i->is(NotOriginal))
		{
			i->Probability += 0.5;
			t.Probability = 1.0;
		}
	}
}
