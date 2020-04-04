#include "../../H/Interpreter/Modder.h"
#include <iostream>
extern Object* Root;
extern Object* FT;

/*
	vector<IR*> &Output;
	vector<Token*> Input;
	IR& I;
	*/

map<string, Object*> Modder::Get_Members()
{
	Root->Set("c", &C);
	return {
		std::make_pair("Flag", FT),
		std::make_pair("_p", (Object*)&P),
		std::make_pair("_c", (Object*)&C),
		std::make_pair("_n", (Object*)&N),
		std::make_pair("IN", new SymbolTableList(Output)),
		std::make_pair("Pattern", new SymbolTableList(Input))
	};
}

void Modder::Factory()
{
	for (Token* t: Input)
	{
		Detect_If(t);
		Detect_Operator(t);
		Detect_Parenthesis(t);
	}
}

//make a IS() for the flags to be on == !!!

void Modder::Detect_If(Token* t)
{
	if (t->is(_Condition_))
	{
		if (Passing(t->Left_Side_Token->Childs.at(0)))
		{
			Modder m = *this;
			m.Input.clear();
			m.Input.push_back(t->Right_Side_Token);
			m.Factory();
		}
	}
}

bool Modder::Passing(Token* condition)
{
	if (auto left = Get_Const_Data(condition->Left_Side_Token))
	{
		if (auto right = Get_Const_Data(condition->Right_Side_Token))
		{
			//std::cout << left.value()->Get_Value() << " , " << right.value()->Get_Value() << std::endl;
			bool result = false;
			if (condition->Name == "&")
			{
				result = atoi(left.value()->Get_Value().c_str()) & atoi(right.value()->Get_Value().c_str());
			}
			else if (condition->Name == "!&")
			{
				result = !(atoi(left.value()->Get_Value().c_str()) & atoi(right.value()->Get_Value().c_str()));
			}
			else if (condition->Name == "|")
			{
				result = atoi(left.value()->Get_Value().c_str()) | atoi(right.value()->Get_Value().c_str());
			}
			else if (condition->Name == "!|")
			{
				result = !(atoi(left.value()->Get_Value().c_str()) | atoi(right.value()->Get_Value().c_str()));
			}
			else
			{
				result = *left.value() == *right.value();
				return condition->Name == "!=" ? !result : result;
			}
			return result;
		}
	}
	return false;
}

void Modder::Detect_Parenthesis(Token* t)
{
	if (t->is(_Parenthesis_))
	{
		Modder m = *this;
		m.Input = t->Childs;
		m.Factory();
	}
}

void Modder::Detect_Operator(Token* t)
{
	if (t->is(_Operator_))
	{
		if (t->Name == "=")
		{
			Get_Const_Data(t->Left_Side_Token).value()->Put(*Get_Const_Data(t->Right_Side_Token).value());
		}
		else if (t->Name == "|=")
		{
			IntObject* L = (IntObject*)Get_Const_Data(t->Left_Side_Token).value();
			IntObject* R = (IntObject*)Get_Const_Data(t->Right_Side_Token).value();
			L->Get_Int_Value() |= R->Get_Int_Value();
		}
	}
}
