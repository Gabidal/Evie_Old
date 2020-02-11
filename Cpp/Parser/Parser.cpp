#include "../../H/Parser/Parser.h"

int ID = 0;

void Parser::Init_Definition(int i)
{
	//type var
	//var a
	//func a()
	if (Input.at(i)->is(_KEYWORD) && Input.at(i+1)->is(_TEXT))
	{
		Token* New_Defined_Type = new Token();
		New_Defined_Type->Type = Input.at(i)->WORD;
		New_Defined_Type->Name = Input.at(i + 1)->WORD;
		Defined_Keywords.push_back(New_Defined_Type->Name);
	}
}

void Parser::Init_Operator(int i, string Filter)
{
	//a = 1
	//a < b
	if (Input.at(i)->is(_OPERATOR) && (Input.at(i)->WORD == Filter))
	{
		Parser P = *this;
		P.Input.clear();
		P.Input.push_back(Input.at(i - 1));
		P.Factory();

		Token* New_Defined_Left_Side_Token = P.Output.at(0);

		P.Output.clear();
		P.Input.clear();
		P.Input.push_back(Input.at(i - 1));
		P.Factory();

		Token* New_Defined_Right_Side_Token = P.Output.at(0);

		Token* New_Defined_Operator = new Token();
		New_Defined_Operator->Name = Input.at(i)->WORD;
		New_Defined_Operator->Left_Side_Token = New_Defined_Left_Side_Token;
		New_Defined_Operator->Right_Side_Token = New_Defined_Right_Side_Token;

		Output.push_back(New_Defined_Operator);
	}
}

void Parser::Init_Parenthesis(int i)
{
	if (Input.at(i)->is(_PAREHTHESIS))
	{
		Token* New_Defined_Parenthesis = new Token();
		Parser P = *this;
		P.Input = Input.at(i)->Tokens;
		P.Factory();
		New_Defined_Parenthesis->Childs = P.Output;
		New_Defined_Parenthesis->Flags |= _Parenthesis_;
	}
}

void Parser::Init_Conditions(int i)
{
	//if (a < b) (...)
	if (Input.at(i)->is(_KEYWORD) && Input.at(i+1)->is(_PAREHTHESIS))
	{
		Token* New_Defined_Condition = new Token();
		New_Defined_Condition->Name = Input.at(i)->WORD;

		Parser P = *this;
		P.Input.clear();
		P.Input.push_back(Input.at(i + 1));				//The parameters for the condition.
		P.Factory();

		New_Defined_Condition->Left_Side_Token = P.Output.at(0);

		P.Output.clear();
		P.Input.clear();
		P.Input.push_back(Input.at(i + 2));				//The Childs if that condition happends.
		P.Factory();

		New_Defined_Condition->Right_Side_Token = P.Output.at(0);

		Output.push_back(New_Defined_Condition);
	}
}

void Parser::Math_Order()
{
	int i = 0;
	for (Word* W : Input)
	{
		Init_Operator(i, "*");
		Init_Operator(i, "/");
		Init_Operator(i, "<<");
		Init_Operator(i, ">>");
		Init_Operator(i, "+");
		Init_Operator(i, "-");
		Init_Operator(i, "<");
		Init_Operator(i, ">");
		Init_Operator(i, "==");
		Init_Operator(i, "!=");
		Init_Operator(i, "<=");
		Init_Operator(i, ">=");
		Init_Operator(i, "!<");
		Init_Operator(i, "!>");
		i++;
	}
}

void Parser::Init_Function(int i)
{
	//func a() (...)
	if (Input.at(i)->is(_KEYWORD) && Input.at(i + 1)->is(_TEXT) && Input.at(i + 1)->is(_PAREHTHESIS))
	{

	}
}

void Parser::Factory()
{
}