#include "../../H/Parser/Parser.h"

int Layer = 0;
int ID = 1;
int Global_Stack_Offset = 0;
int Local_Stack_Offest = 0;
bool Inside_Of_Constructor_As_Parameter = false;
bool Inside_Of_Constructor = false;
extern vector<string> Pre_Defined_Tokens;
extern vector<Token*> Generated_Undefined_Tokens;
extern int _SYSTEM_BIT_TYPE;
extern vector<string> Included_Files; //for loop holes to not exist

void Parser::Include_Files(int i)
{
	if (Input.at(i)->WORD == "using")
	{
		string filename = Input.at(i + 1)->WORD.substr(1, Input.at(i + 1)->WORD.size() - 2);
		for (string s : Included_Files)
			if (Input.at(i+1)->is(_STRING) && (filename == s))
			{
				cout << "Warning:: " + Input.at(i + 1)->WORD + " has already been included." << endl;
				Input.erase(Input.begin() + i + 1);
				return;
			}
		//now include the file
		Lexer l;
		l.OpenFile(filename.c_str());
		Input.erase(Input.begin() + i + 1);
		Input.erase(Input.begin() + i);
		Input.insert(Input.begin() + i, l.output.begin(), l.output.end());
		Included_Files.push_back(filename);
	}
}

void Parser::Init_Definition(int i)
{
	if (i >= (Input.size() - 1))
		return;
	//type var
	//var a
	//a = b
	//const var b
	//func a()
	if ((Input.at(i)->is(_KEYWORD) || (Defined(Input.at(i)->WORD) != "")) && (Input.at(i+1)->is(_TEXT)) && (Defined(Input.at(i + 1)->WORD) == ""))
	{
		Token* New_Defined_Type = new Token();
		New_Defined_Type->Type = Input.at(i)->WORD;
		New_Defined_Type->Name = Input.at(i + 1)->WORD;

		if (i - 1 >= 0)
		{
			if (Defined(Input.at(i - 1)->WORD) != "")
			{
				if (i - 2 >= 0)
				{
					if (Input.at(i - 2)->is(_OPERATOR))
					{
						goto skip;
					}
				}
				New_Defined_Type->PreFix_Type = Input.at(i - 1)->WORD;
				New_Defined_Type->Flags |= _Inheritting_;
			}
		}
	skip:;
		if (Input.at(i)->is(_KEYWORD))
		{
			New_Defined_Type->Size = Get_Size(i);
		}
		else
		{
			for (Token* t : Defined_Keywords)
			{
				if (New_Defined_Type->Type == t->Name)
				{
					New_Defined_Type->Size = t->Size;
					break;
				}
			}
		}
		Set_Right_Stack_Offset(New_Defined_Type);
		Set_Right_Flag_Info(New_Defined_Type);
		Defined_Keywords.push_back(New_Defined_Type);
		Space_Reservation++;
	}
}

int Parser::Get_Size(int i)
{
	//type a()(..)
	Parser p;
	p.Input = Input;
	if (p.Count_Familiar_Tokens(_PAREHTHESIS, i + 2) == 2);
	{
		p.Input = Input.at(i + 3)->Tokens;
		for (int j = 0; j < p.Input.size(); j++)
		{
			if (p.Input.at(j)->WORD == "Size")
			{
				return atoi(p.Input.at(j + 1)->WORD.c_str());
			}
		}
	}
	return 0;
}

void Parser::Init_Operator(int i)
{
	if (Input.at(i)->WORD == ",")
		return;
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

		//for non operative tokens
		P.Output.clear();
		P.Input.clear();
		P.Input.push_back(Input.at(i)->L);
		P.Factory();
		Token* New_Left_Non_Operative_Token = P.Output.at(0);

		P.Output.clear();
		P.Input.clear();
		P.Input.push_back(Input.at(i)->R);
		P.Factory();
		Token* New_Right_Non_Operative_Token = P.Output.at(0);

		Token* New_Defined_Operator = new Token();
		New_Defined_Operator->Name = Input.at(i)->WORD;
		New_Defined_Operator->Left_Side_Token = New_Defined_Left_Side_Token;
		New_Defined_Operator->Right_Side_Token = New_Defined_Right_Side_Token;
		New_Defined_Operator->Left_Non_Operative_Token = New_Left_Non_Operative_Token;
		New_Defined_Operator->Right_Non_Operative_Token = New_Right_Non_Operative_Token;

		New_Defined_Operator->Flags |= _Operator_;
		Output.push_back(New_Defined_Operator);
	}
}

void Parser::Reserve_Operator_Tokens(int i)
{
	if ((Input.at(i)->is(_OPERATOR) == true) && (Input.at(i)->_initted == false))
	{
	}
	else
		return;
	if (i-1 < 0)
	{
		//negatable operator
		Input.at(i + 1)->_Pre_Modded = Input.at(i)->WORD;
		Input.erase(Input.begin() + i);
	}
	else
	{
		Input.at(i)->L = Input.at(i - 1);
		Input.at(i)->R = Input.at(i + 1);
	}
}

void Parser::Reserve_Function_Parameters(int i)
{
	if (Input.at(i)->is(_TEXT) && (Defined(Input.at(i)->WORD) != ""))
	{
		if (Count_Familiar_Tokens(_PAREHTHESIS, i + 1) == 1)
		{
			Input.at(i)->Tokens.push_back(Input.at(i + 1));
			Input.at(i)->_Call = true;
			Input.erase(Input.begin() + i + 1);
		}
	}
}

void Parser::Patternize_Operations(int& i, string f)
{
	if (Input.at(i)->is(_OPERATOR) && (Input.at(i)->WORD == f) && (Input.at(i)->_initted != true))
	{
		Input.at(i)->Tokens.push_back(new Word (*Input.at(i - 1)));
		Input.at(i)->Tokens.at(0)->_operatorized = false;
		Input.at(i)->Tokens.push_back(new Word (*Input.at(i + 1)));
		Input.at(i)->Tokens.at(1)->_operatorized = false;
		Input.at(i)->_initted = true;

		//Input.at(i + 1)->_operatorized = true;
		//Input.at(i - 1)->_operatorized = true;
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
		Patternize_Operations(i, "%");
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
		P.Space_Reservation = 0;
		P.Output.clear();
		P.Input = Input.at(i)->Tokens;
		P.Factory();
		New_Defined_Parenthesis->Childs = P.Output;
		New_Defined_Parenthesis->Flags |= _Parenthesis_;
		New_Defined_Parenthesis->Reservable_Size = P.Space_Reservation;
		Output.push_back(New_Defined_Parenthesis);
		this->Space_Reservation = P.Space_Reservation;
		if (Inside_Of_Constructor_As_Parameter)
		{
			this->Defined_Keywords = P.Defined_Keywords;
		}
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
		New_Defined_Condition->Flags |= _Condition_;
		New_Defined_Condition->Flags |= _External_;
		ID++;

		Parser P = *this;
		P.Output.clear();
		P.Input.clear();
		P.Input.push_back(Input.at(i + 1));				//The parameters for the condition.
		P.Factory();

		New_Defined_Condition->Left_Side_Token = P.Output.at(0);

		P.Output.clear();
		P.Input.clear();
		P.Input.push_back(Input.at(i + 2));				//The Childs if that condition happends.
		P.Factory();

		New_Defined_Condition->Right_Side_Token = P.Output.at(0);

		Input.erase(Input.begin() + i + 2);
		Input.erase(Input.begin() + i + 1);

		//for space reservation
		if (P.Space_Reservation > 0)
		{
			this->Space_Reservation = P.Space_Reservation;
			New_Defined_Condition->Reservable_Size = New_Defined_Condition->Right_Side_Token->Reservable_Size;
		}

		Output.push_back(New_Defined_Condition);
	}
}

void Parser::Type_Definition(int i)
{
	if (i > (Input.size() - 1))
	{
		return;
	}
	//func a() 
	//a() (...)
	if (Input.at(i)->is(_TEXT) && (Defined(Input.at(i)->WORD) != ""))
	{
		//a() #like a function call
		//lets give the new parser new input tokens the other is the parameters
		//and the other is the child of the defined type
		Token* New_Defined_Text = new Token();
		if (Input.at(i)->_Call)
		{
			Parser P = *this;
			P.Input.clear();
			P.Output.clear();
			P.Input = Input.at(i)->Tokens;
			P.Factory();
			New_Defined_Text->Left_Side_Token = P.Output.at(0);
			New_Defined_Text->Flags |= _Call_;
			New_Defined_Text->Size = _SYSTEM_BIT_TYPE;
		}
		else if (Count_Familiar_Tokens(_PAREHTHESIS, i + 1) == 2)
		{

			Parser P = *this;

			P.Input.clear();
			P.Output.clear();
			//parameters.
			Inside_Of_Constructor_As_Parameter = true;
			P.Input.push_back(Input.at(i + 1));
			P.Factory();
			Inside_Of_Constructor_As_Parameter = false;
			Local_Stack_Offest = 0;
			New_Defined_Text->Left_Side_Token = P.Output.at(0);

			if (New_Defined_Text->Left_Side_Token->Reservable_Size > 0)
			{
				New_Defined_Text->Flags |= _Need_For_Space_;
				New_Defined_Text->Reservable_Size = New_Defined_Text->Left_Side_Token->Reservable_Size;
			}

			P.Output.clear();
			P.Input.clear();
			//childs
			Inside_Of_Constructor = true;
			P.Input.push_back(Input.at(i + 2));
			P.Factory();
			Inside_Of_Constructor = false;
			Local_Stack_Offest = 0;
			New_Defined_Text->Right_Side_Token = P.Output.at(0);
			New_Defined_Text->Flags |= _Constructor_;
			New_Defined_Text->Flags |= _External_;

			if (New_Defined_Text->Right_Side_Token->Reservable_Size > 0)
			{
				New_Defined_Text->Flags |= _Need_For_Space_;
				New_Defined_Text->Reservable_Size = New_Defined_Text->Right_Side_Token->Reservable_Size;
			}

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
				New_Defined_Text->PreFix_Type = s->PreFix_Type;
				break;
			}
		}
		for (int j = 0; j < Output.size(); j++)
		{
			if (Output.at(j)->Name == New_Defined_Text->Name)
			{
				Output.at(j) = New_Defined_Text;
				return;
			}
		}
		Output.push_back(New_Defined_Text);
	}
}

void Parser::Set_Right_Stack_Offset(Token* t)
{
	//the stack place giver
	if (Inside_Of_Constructor)
		t->StackOffset = Local_Stack_Offest + 4;
	else if (Inside_Of_Constructor_As_Parameter)
		t->StackOffset = (_SYSTEM_BIT_TYPE * 2) + Local_Stack_Offest;
	else
		t->StackOffset = Global_Stack_Offset;
	if (Inside_Of_Constructor || Inside_Of_Constructor_As_Parameter)
		Local_Stack_Offest += t->Size;
	else
		Global_Stack_Offset += t->Size;
}

void Parser::Set_Right_Flag_Info(Token* t)
{
	if (Inside_Of_Constructor)
	{
		//idk
	}
	else if (Inside_Of_Constructor_As_Parameter)
	{
		t->Flags |= _Parameter_;
	}
	else
	{
		t->Flags |= _External_;
	}
}

string Parser::Defined(string name)
{
	for (Token* t : Defined_Keywords)
	{
		if (t->Name == name)
		{
			return t->Type;
		}
	}
	return "";
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
	return -1;
}

void Parser::Init_Variable(int i)
{
	//var a = 1
	if (Input.at(i)->_operatorized)
	{
		return;
	}
	if ((i + 1) > (Input.size() - 1))
	{
		
	}
	else if (Input.at(i+1)->is(_TEXT))
	{
		return;
	}
	if (Input.at(i)->is(_TEXT) && (Defined(Input.at(i)->WORD) != "") && (Layer > 1))
	{
		Token* New_Variable = new Token();
		New_Variable->Name = Input.at(i)->WORD;
		//idk
		New_Variable->Type = Defined(New_Variable->Name);
		if (New_Variable->Type == "type")
			return;
		for (Token* t : Defined_Keywords)
			if (t->Name == New_Variable->Name)
			{
				New_Variable->StackOffset = t->StackOffset;
				New_Variable->Flags = t->Flags;
				New_Variable->PreFix_Type = t->PreFix_Type;
				New_Variable->Size = t->Size;
				break;
			}
		Output.push_back(New_Variable);
		Generated_Undefined_Tokens.push_back(Output.back());
	}
	if (Input.at(i)->is(_NUMBER) && (Layer > 1))
	{
		Token* New_Number = new Token();
		New_Number->Name = Input.at(i)->_Pre_Modded;
		New_Number->Name += Input.at(i)->WORD;
		New_Number->Type = "number";
		New_Number->Flags |= _Number_;
		if (New_Number->Name.find('.') != -1)
		{
			New_Number->Size = 4;
		}
		else
		{
			int Size = atoi(New_Number->Name.c_str());
		    if ((Size <= 255) && (Size >= -128))
			{
				New_Number->Size = 1;
			}
			else if ((Size <= 65536) && (Size >= -32768))
			{
				New_Number->Size = 2;
			}
			else
			{
				New_Number->Size = 4;
			}
		}
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
			P.Output.clear();
			P.Input.clear();
			P.Input.push_back(Input.at(i + 1));
			P.Factory();

			New_Pre_Defined_Token->Right_Side_Token = P.Output.at(0);
			Output.push_back(New_Pre_Defined_Token);
			Input.erase(Input.begin() + i + 1);
			return;
		}
}

void Parser::Set_Special_Feature(int i)
{
	if ((i + 2) >= Input.size())
		return;
	Word* Access_Modifier = Input.at(i);
	Word* Keyword = Input.at(i + 1);
	Word* Name = Input.at(i + 2);
	if (Access_Modifier->is(_KEYWORD) && Keyword->is(_KEYWORD) && Name->is(_TEXT))
	{
		//export type main
		//export int a
		//const char b
	}
}

void Parser::Factory()
{
	Layer++;
	for (int i = 0; i < Input.size(); i++)
		Include_Files(i);
	for (int i = 0; i < Input.size(); i++)
		Init_Definition(i);
	for (int i = 0; i < Input.size(); i++)
		Reserve_Function_Parameters(i);
	for (int i = 0; i < Input.size(); i++)
		Reserve_Operator_Tokens(i);
	Do_In_Order();
	for (int i = 0; i < Input.size(); i++)
	{
		Init_Operator(i);
		Init_Variable(i);
		Init_Parenthesis(i);
		Type_Definition(i);
		Init_Conditions(i);
		Check_For_Correlation(i);
	}
	Layer--;
}

void Parser::Append(vector<Token*>* Dest, vector<Token*> Source)
{
	for (Token* i : Source)
	{
		Dest->push_back(i);
	}
}