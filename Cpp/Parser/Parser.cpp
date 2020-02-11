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

}

void Parser::Factory()
{
}