#include "../../H/Parser/Parser.h"

int Layer = 0;
int ID = 0;
extern vector<string> Pre_Defined_Tokens;

void Parser::Init_Definition(int i)
{
	if (i >= (Input.size() - 1))
	{
		return;
	}
	//type var
	//var a
	//func a()
	if ((Input.at(i)->is(_KEYWORD) || Defined(Input.at(i)->WORD)) && Input.at(i+1)->is(_TEXT))
	{
		Token* New_Defined_Type = new Token();
		New_Defined_Type->Type = Input.at(i)->WORD;
		New_Defined_Type->Name = Input.at(i + 1)->WORD;
		Defined_Keywords.push_back(New_Defined_Type);
	}
}

void Parser::Init_Operator(int i)
{
	//a = 1
	//a < b
	if (Input.at(i)->is(_OPERATOR))
	{
		Parser P = *this;
		P.Output.clear();
		P.Input.clear();
		P.Input.push_back(Input.at(i)->Tokens.at(0));
		P.Factory();

		Token* New_Defined_Left_Side_Token = P.Output.at(0);

		P.Output.clear();
		P.Input.clear();
		P.Input.push_back(Input.at(i)->Tokens.at(1));
		P.Factory();

		Token* New_Defined_Right_Side_Token = P.Output.at(0);

		Token* New_Defined_Operator = new Token();
		New_Defined_Operator->Name = Input.at(i)->WORD;
		New_Defined_Operator->Left_Side_Token = New_Defined_Left_Side_Token;
		New_Defined_Operator->Right_Side_Token = New_Defined_Right_Side_Token;

		Output.push_back(New_Defined_Operator);
	}
}

void Parser::Patternize_Operations(int& i, string f)
{
	if (Input.at(i)->is(_OPERATOR) && (Input.at(i)->WORD == f) && (Input.at(i)->_initted != true))
	{
		Input.at(i)->Tokens.push_back(Input.at(i - 1));
		Input.at(i)->Tokens.push_back(Input.at(i + 1));
		Input.at(i)->_initted = true;

		Input.erase(Input.begin() + i + 1);
		Input.erase(Input.begin() + i - 1);
		i--;
	}
}

void Parser::Do_In_Order()
{
	//the combination and multilayering of operations.
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, ":");
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, "*");
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, "/");
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, "<<");
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, ">>");
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, "&");
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, "|");
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, "+");
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, "-");
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, "<");
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, ">");
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, "==");
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, "!=");
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, "<=");
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, ">=");
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, "!<");
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, "!>");
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, "=");
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
		Output.push_back(New_Defined_Parenthesis);
	}
}

void Parser::Init_Conditions(int i)
{
	if (i >= (Input.size() - 1))
	{
		return;
	}
	//if (a < b) (...)
	if (Input.at(i)->is(_KEYWORD) && Input.at(i+1)->is(_PAREHTHESIS))
	{
		Token* New_Defined_Condition = new Token();
		New_Defined_Condition->Name = Input.at(i)->WORD;
		New_Defined_Condition->ID = ID + Layer;
		ID++;

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

void Parser::Type_Definition(int i)
{
	if (i >= (Input.size() - 1))
	{
		return;
	}
	//func a() 
	//a() (...)
	if (Input.at(i)->is(_TEXT) && Defined(Input.at(i)->WORD))
	{
		//a() #like a function call
		//lets give the new parser new input tokens the other is the parameters
		//and the other is the child of the defined type
		Token* New_Defined_Text = new Token();
		if (Count_Familiar_Tokens(_PAREHTHESIS, i + 1) == 1)
		{
			Parser P = *this;
			P.Input.clear();
			P.Input.push_back(Input.at(i + 1));
			P.Factory();
			New_Defined_Text->Left_Side_Token = P.Output.at(0);
			New_Defined_Text->Flags |= _Call_;
			Input.erase(Input.begin() + i + 1);
		}
		else if (Count_Familiar_Tokens(_PAREHTHESIS, i + 1) == 2)
		{
			Parser P = *this;
			P.Input.clear();
			P.Input.push_back(Input.at(i + 2));
			P.Factory();
			New_Defined_Text->Right_Side_Token = P.Output.at(0);
			New_Defined_Text->Flags |= _Constructor_;


			P.Input.clear();
			P.Output.clear();
			P.Input.push_back(Input.at(i + 1));
			P.Factory();
			New_Defined_Text->Left_Side_Token = P.Output.at(0);


			Input.erase(Input.begin() + i + 2);
			Input.erase(Input.begin() + i + 1);
		}
		else
		{
			return;
		}
		New_Defined_Text->Name = Input.at(i)->WORD;
		for (Token* s : Defined_Keywords)
		{
			if (New_Defined_Text->Name == s->Name)
			{
				New_Defined_Text->Type = s->Type;
				break;
			}
		}
		Output.push_back(New_Defined_Text);
	}
}

bool Parser::Defined(string name)
{
	for (Token* t : Defined_Keywords)
	{
		if (t->Name == name)
		{
			return true;
		}
	}
	return false;
}

int Parser::Count_Familiar_Tokens(int F, int i)
{
	int u = 0;
	for (int j = i; j < Input.size(); j++)
	{
		if (Input.at(j)->is(F))
		{
			u++;
		}
		else
		{
			return u;
		}
	}
}

void Parser::Init_Variable(int i)
{
	//var a = 1
	if (Input.at(i)->is(_TEXT) && Defined(Input.at(i)->WORD) && (Layer > 1))
	{
		Token* New_Variable = new Token();
		New_Variable->Name = Input.at(i)->WORD;
		Output.push_back(New_Variable);
	}
	if (Input.at(i)->is(_NUMBER) && (Layer > 1))
	{
		Token* New_Number = new Token();
		New_Number->Name = Input.at(i)->WORD;
		New_Number->Flags |= _Number_;
		New_Number->Size = 4;
		Output.push_back(New_Number);
	}
}

void Parser::Check_For_Correlation(int i)
{
	for (string s: Pre_Defined_Tokens)
		if (Input.at(i)->WORD == s)
		{
			Token* New_Pre_Defined_Token = new Token();
			New_Pre_Defined_Token->Type = s;

			Parser P = *this;
			P.Input.clear();
			P.Input.push_back(Input.at(i + 1));
			P.Factory();

			New_Pre_Defined_Token->Right_Side_Token = P.Output.at(0);
			Output.push_back(New_Pre_Defined_Token);
			Input.erase(Input.begin() + i + 1);
			return;
		}
}

void Parser::Factory()
{
	Layer++;
	for (int i = 0; i < Input.size(); i++)
		Init_Definition(i);
	Do_In_Order();
	for (int i = 0; i < Input.size(); i++)
	{
		Init_Operator(i);
		Init_Variable(i);
		Init_Parenthesis(i);
		Init_Conditions(i);
		Type_Definition(i);
		Check_For_Correlation(i);
	}
	Layer--;
}