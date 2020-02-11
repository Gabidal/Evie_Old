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

void Parser::Init_Operator(int i)
{
	//a = 1
	//a < b
	if (Input.at(i)->is(_OPERATOR))
	{
		Token* New_Defined_Left_Side_Token = new Token();
		New_Defined_Left_Side_Token->Name = Input.at(i - 1)->WORD;
		Token* New_Defined_Right_Side_Token = new Token();
		New_Defined_Right_Side_Token->Name = Input.at(i + 1)->WORD;

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

}

void Parser::Factory()
{
}