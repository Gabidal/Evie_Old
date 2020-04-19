#include "../../H/Parser/Parser.h"
#include "../../H/Interpreter/Interpreter.h"

bool Inside_Of_Constructor_As_Parameter = false;
bool Inside_Of_Constructor = false;
int Layer = 0;
int ID = 1;
int Global_Stack_Offset = 0;
int Local_Stack_Offest = 0;
extern int _SYSTEM_BIT_TYPE;
extern vector<string> Included_Files; //for loop holes to not exist
extern vector<string> Pre_Defined_Tokens;
extern vector<Token*> Generated_Undefined_Tokens;

void Parser::Include_Files(int i)
{
	if (Input.at(i)->WORD == "use")
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
	if (Input.at(i)->WORD == "use")
	Include_Files(i);
}

void Parser::Connect_Array(int i)
{
	if (Input.at(i)->is(_OPERATOR) != true)
		return;
	if (Input.at(i)->WORD != ":" && Input.at(i)->WORD != "::")
		return;
	//b = a:0
	Input.at(i - 1)->Offsetter = Input.at(i + 1);
	if (Input.at(i)->WORD == "::")
	{
		Input.at(i-1)->Self_Mirroring = true;
	}
	Input.erase(Input.begin() + i + 1);
	Input.erase(Input.begin() + i);
}

void Parser::Connect_Address(int i)
{
	if (Input.at(i)->WORD != "@") return;
	Input.at(i + 1)->_Giving_Address = true;
	Input.erase(Input.begin() + i);
}

void Parser::Init_Definition(int& i)
{
	if (i >= (Input.size() - 1))
		return;
	if ((Collect_All_Inherited_Types(i).size() < 1))
		return;
	if (!Input.at(i + Collect_All_Inherited_Types(i).size())->is(_TEXT))
		return;
	if (Defined(Input.at(i + Collect_All_Inherited_Types(i).size())->WORD) != "")
		return;
	//import func banana()()
	//func banana()()
	//export loyal func banana()()
	//type var
	//var a
	//a = b
	//const var b
	//func a()
	//if ((Input.at(i)->is(_KEYWORD) || (Defined(Input.at(i)->WORD) != "")) && ((Input.at(i+1)->is(_TEXT)) || (Input.at(i + 1)->is(_KEYWORD))) && (Input.at(i)->WORD != ","))
	Token* New_Defined_Type = new Token();
	New_Defined_Type->Types = Collect_All_Inherited_Types(i);
	if (New_Defined_Type->Types.size() > 1)
		New_Defined_Type->add(_Inheritting_);
	
	New_Defined_Type->Name = Input.at(i + New_Defined_Type->Types.size())->WORD;
	if (Input.at(i)->is(_KEYWORD))
	{
		string Size = Get_Size(i);
		if (Size == "$")
		{
			New_Defined_Type->_Dynamic_Size_ = true;
			New_Defined_Type->Size = 0;
		}
		else
		{
			New_Defined_Type->Size = atoi(Size.c_str());
		}
	}
	else
	{
		for (Token* t : Defined_Keywords)
		{
			if (New_Defined_Type->is(t->Name))
			{
				New_Defined_Type->Size += t->Size;
				New_Defined_Type->_Dynamic_Size_ |= t->_Dynamic_Size_;
			}
			
		}
	}
	New_Defined_Type->Context = Context;
	Set_Right_Stack_Offset(New_Defined_Type);
	Set_Right_Flag_Info(New_Defined_Type);
	Defined_Keywords.push_back(New_Defined_Type);
	Generated_Undefined_Tokens.push_back(New_Defined_Type);
	Space_Reservation += New_Defined_Type->Size;
	i += New_Defined_Type->Types.size();

}

vector<string> Parser::Collect_All_Inherited_Types(int start) //returned vector size needs to be deleted from input
{
	//[defined]import [defined]loyal [keyword]func [plain text]banana
	vector<string> r;
	for (int i = start; i < Input.size(); i++)
	{
		if ((Defined(Input.at(i)->WORD) != "") || Input.at(i)->is(_KEYWORD))
		{
			r.push_back(Input.at(i)->WORD);
		}
		else
		{
			break;
		}
	}
	return r;
}

string Parser::Get_Size(int i)
{
	//type a()(..)
	if (Count_Familiar_Tokens(_PAREHTHESIS, i + 2) < 2)
		return "0";
	if (Input.at(i)->WORD == "func")
		return to_string(_SYSTEM_BIT_TYPE);
	Parser p;
	p.Input = Input.at(i + 3)->Tokens;
	p.Defined_Keywords = Defined_Keywords;
	p.Factory();
	Token* t = nullptr;
	for (int j = 0; j < p.Output.size(); j++) {
		if (p.Output.at(j)->is("size"))
		{
			t = p.Output.at(j);
		}
	}
	if (t == nullptr)
	{
		return "0";
	}
	if (t->Right_Side_Token->is(_Number_))
	{
		//if the size is defined by a number.
		return t->Right_Side_Token->Name;
	}
	else if (t->Right_Side_Token->Name == "$")
	{
		return "$";
	}
	else
	{
		//if the number is defined by a variable.
		return to_string(t->Right_Side_Token->Size);
	}
}

void Parser::Init_Operator(int i)
{
	if (Input.size() < 1)
		return;
	if (Input.at(i)->WORD == "$")
		return;
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
		/*P.Output.clear();
		P.Input.clear();
		P.Input.push_back(Input.at(i)->L);
		P.Factory();
		Token* New_Left_Non_Operative_Token = P.Output.at(0);

		P.Output.clear();
		P.Input.clear();
		P.Input.push_back(Input.at(i)->R);
		P.Factory();
		Token* New_Right_Non_Operative_Token = P.Output.at(0);*/

		Token* New_Defined_Operator = new Token();
		New_Defined_Operator->Context = Context;
		New_Defined_Operator->Name = Input.at(i)->WORD;
		New_Defined_Operator->Left_Side_Token = New_Defined_Left_Side_Token;
		New_Defined_Operator->Right_Side_Token = New_Defined_Right_Side_Token;
		//New_Defined_Operator->Left_Non_Operative_Token = New_Left_Non_Operative_Token;
		//New_Defined_Operator->Right_Non_Operative_Token = New_Right_Non_Operative_Token;

		New_Defined_Operator->add(_Operator_);
		Output.push_back(New_Defined_Operator);
	}
}

void Parser::Reserve_Operator_Tokens(int i)
{
	if (Input.at(i)->WORD == "$")
		return;
	if (Input.at(i)->WORD == ",")
		return;
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
	if (Input.at(i)->WORD == "$")
		return;
	if (Input.at(i)->WORD == ",")
		return;
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
		Patternize_Operations(i, "?");
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, "!&");
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, "|");
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, "!|");
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
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, "|=");
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, "&=");
}

void Parser::Init_Parenthesis(int i)
{
	if (Input.size() < 1)
		return;
	if (Input.at(i)->is(_PAREHTHESIS))
	{
		Token* New_Defined_Parenthesis = new Token();
		Parser P = *this;
		P.Space_Reservation = 0;
		P.Output.clear();
		P.Input = Input.at(i)->Tokens;
		P.Factory();
		New_Defined_Parenthesis->Childs = P.Output;
		New_Defined_Parenthesis->add(_Parenthesis_);
		New_Defined_Parenthesis->Reservable_Size = P.Space_Reservation;
		New_Defined_Parenthesis->Size = P.Space_Reservation;
		for (Token* j : New_Defined_Parenthesis->Childs)
		{
			New_Defined_Parenthesis->Size += j->Size;
		}
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
	if (Input.size() < 1)
		return;
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
		New_Defined_Condition->add(_Condition_);
		New_Defined_Condition->add(_External_);
		ID++;


		Parser P = *this;

		//update context
		P.Context = Input.at(i)->WORD;

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
	if (Input.size() < 1)
		return;
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
			//update context
			P.Context = "Parameter";
			P.Input.clear();
			P.Output.clear();
			P.Input = Input.at(i)->Tokens;
			Inside_Of_Constructor_As_Parameter = true;
			P.Factory();
			Inside_Of_Constructor_As_Parameter = false;

			New_Defined_Text->Left_Side_Token = P.Output.at(0);
			reverse(New_Defined_Text->Left_Side_Token->Childs.begin(), New_Defined_Text->Left_Side_Token->Childs.end());
			New_Defined_Text->add(_Call_);
			New_Defined_Text->Size = _SYSTEM_BIT_TYPE;
			if (New_Defined_Text->Left_Side_Token->Reservable_Size > 0 || (New_Defined_Text->Left_Side_Token->Childs.size() > 0))
			{
				New_Defined_Text->add(_Need_For_Space_);
				for (Token* t: New_Defined_Text->Left_Side_Token->Childs)
				New_Defined_Text->Reservable_Size += t->Size;
				New_Defined_Text->Reservable_Size += New_Defined_Text->Left_Side_Token->Reservable_Size;
			}
		}
		else if (Count_Familiar_Tokens(_PAREHTHESIS, i + 1) == 2)
		{


			Parser P = *this;
			//update context
			P.Context = "Parameter";

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
				New_Defined_Text->add(_Need_For_Space_);
			}

			New_Defined_Text->Left_Side_Token->Reservable_Size = 0;


			//update context
			P.Context = Input.at(i)->WORD;

			P.Output.clear();
			P.Input.clear();
			//childs
			Inside_Of_Constructor = true;
			P.Input.push_back(Input.at(i + 2));
			P.Space_Reservation = 0;			//!!!!!!!!!!!!!!
			P.Factory();
			Inside_Of_Constructor = false;


			Local_Stack_Offest = 0;
			New_Defined_Text->Right_Side_Token = P.Output.at(0);
			New_Defined_Text->add(_Constructor_);
			New_Defined_Text->add(_External_);

			if (New_Defined_Text->Right_Side_Token->Reservable_Size > 0)
			{
				New_Defined_Text->add(_Need_For_Space_);
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
		//if only a call seek the information from defined
		if (New_Defined_Text->is(_Call_) || New_Defined_Text->is(_Constructor_))
			for (Token* t : Defined_Keywords)
				if (t->Name == New_Defined_Text->Name && (!New_Defined_Text->is(_Combined_)))
				{
					New_Defined_Text->StackOffset = t->StackOffset;
					New_Defined_Text->Size = t->Size;
					New_Defined_Text->add(t->get());
					New_Defined_Text->Types = t->Types;
					New_Defined_Text->add(_Combined_);
					break;
				}
		//get the predefined types/prefixtypes.
		if (New_Defined_Text->Types.size() > 0)
		{
			//this new defined thing has already the needed requerems, no need to combine
			Output.push_back(New_Defined_Text);
		}
		else {
			for (Token* t : Defined_Keywords) {
				if (t->Name == New_Defined_Text->Name)
				{
					t->Right_Side_Token = New_Defined_Text->Right_Side_Token;
					t->Left_Side_Token = New_Defined_Text->Left_Side_Token;
					t->add(New_Defined_Text->get());
				}
			}
		}
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
		t->add(_Parameter_);
	}
	else
	{
		t->add(_External_);
	}
}

string Parser::Defined(string name)
{
	for (Token* t : Defined_Keywords)
	{
		if (t->Name == name)
		{
			return t->Name; //!!!!!
		}
	}
	return "";
}

vector<string> Parser::Get_Type(string name)
{
	for (Token* t : Defined_Keywords)
		if (t->Name == name)
			return t->Types;
	cout << "Error: " << name << " is not defined!" << endl;
	throw runtime_error(name + " is not defined!");
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
	return u;
}

void Parser::Init_Variable(int i)
{
	if (Input.size() < 1)
		return;
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
	for (Token* t : Defined_Keywords)
		if ((Input.at(i)->WORD == t->Name) && (t->is("func")) && (!Input.at(i)->_Giving_Address))
			return;
	if (Input.at(i)->is(_TEXT) && (Defined(Input.at(i)->WORD) != "") && (Layer > 1))
	{
		Token* New_Variable = new Token();
		New_Variable->Name = Input.at(i)->WORD;
		//idk
		New_Variable->Types = Get_Type(New_Variable->Name);
		if (New_Variable->is("type"))
			return;
		for (Token* t : Defined_Keywords)
			if (t->Name == New_Variable->Name)
			{
				New_Variable->StackOffset = t->StackOffset;
				New_Variable->add(t->get());
				New_Variable->Types = t->Types;
				New_Variable->Size = t->Size;
				New_Variable->_Dynamic_Size_ = t->_Dynamic_Size_;
				break;
			}
		if (Input.at(i)->Offsetter != nullptr)
		{
			Parser p;
			p.Input.push_back(Input.at(i)->Offsetter);
			p.Defined_Keywords = this->Defined_Keywords;
			p.Factory();
			New_Variable->Offsetter = p.Output.at(0);
			if (Input.at(i)->Self_Mirroring)
				New_Variable->add(_Pointting_);
			else
				New_Variable->add(_Array_);
		}
		if (Input.at(i)->_Giving_Address)
		{
			New_Variable->add(_Giving_Address_);
		}
		New_Variable->Context = Context;
		Output.push_back(New_Variable);
		//Generated_Undefined_Tokens.push_back(Output.back());
	}
	if (Input.at(i)->is(_NUMBER) && (Layer > 1))
	{
		Token* New_Number = new Token();
		New_Number->Name = Input.at(i)->_Pre_Modded;
		New_Number->Name += Input.at(i)->WORD;
		New_Number->Types.push_back("number");
		New_Number->add(_Number_);
		if (Input.at(i)->Offsetter != nullptr)
		{
			Parser p;
			p.Input.push_back(Input.at(i)->Offsetter);
			p.Defined_Keywords = this->Defined_Keywords;
			p.Factory();
			New_Number->Offsetter = p.Output.at(0);
			if (Input.at(i)->Self_Mirroring)
				New_Number->add(_Pointting_);
			else
				New_Number->add(_Array_);
		}
		if (New_Number->Name.find('.') != -1)
		{
			New_Number->Size = 4;
		}
		else if (Inside_Of_Constructor_As_Parameter)
		{
			New_Number->Size = _SYSTEM_BIT_TYPE;
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
	if (Input.at(i)->is(_STRING) && (Layer > 1))
	{
		Token* Str = new Token;
		Str->add(_String_);
		Str->Name = Input.at(i)->WORD;
		Str->Size = _SYSTEM_BIT_TYPE;
		Str->Types.push_back("string");
		Output.push_back(Str);
	}
	if (Input.at(i)->WORD == "$")
	{
		Token* Let = new Token;
		Let->Name = "$";
		Let->Types.push_back("Preprosessor");
		Output.push_back(Let);
	}
}

void Parser::Check_For_Correlation(int i)
{
	if (Input.size() < 1)
		return;
	for (string s: Pre_Defined_Tokens)
		if (Input.at(i)->WORD == s)
		{
			Token* New_Pre_Defined_Token = new Token();
			New_Pre_Defined_Token->Types.push_back(s);

			Parser P = *this;
			P.Defined_Keywords = Defined_Keywords;
			P.Output.clear();
			P.Input.clear();
			P.Input = Input.at(i)->Tokens;
			P.Factory();

			if (P.Output.size() > 0)
				New_Pre_Defined_Token->Right_Side_Token = P.Output.at(0);
			else
			{
				Token* Empty_And_Potentially_Useless = new Token;
				Empty_And_Potentially_Useless->Name = Input.at(i)->Tokens.at(0)->WORD;
				New_Pre_Defined_Token->Right_Side_Token = Empty_And_Potentially_Useless;
			}
			Output.push_back(New_Pre_Defined_Token);
			return;
		}
}

void Parser::Check_For_Correlation_Link(int i)
{
	if (Input.size() < 1)
		return;
	for (string s : Pre_Defined_Tokens)
		if (Input.at(i)->WORD == s)
		{
			Input.at(i)->Tokens.push_back(Input.at(i + 1));
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

void Parser::Check_For_Inter(int i)
{
	if (Input.size() - 1 < i + 1)
		return;
	if (Input.at(i)->WORD == "$")
	{
		Interpreter I(Input, i, Defined_Keywords);
		Parser p;
		p.Input = I.Output;
		p.Defined_Keywords = this->Defined_Keywords;
		p.Factory();
		Append(&Output, p.Output);
		Defined_Keywords = p.Defined_Keywords;
	}
	if (Input.size() < 1)
		return;
	if (Input.at(i)->WORD == "$")
	{
		//loops if these is right behind it another "$"
		Check_For_Inter(i);
	}
}

void Parser::Factory()
{
	Layer++;
	for (int i = 0; i < Input.size(); i++)
		Include_Files(i);
	for (int i = 0; i < Input.size(); i++)
		Connect_Array(i);
	for (int i = 0; i < Input.size(); i++)
		Connect_Address(i);
	for (int i = 0; i < Input.size(); i++)
		Check_For_Correlation_Link(i);		//link
	for (int i = 0; i < Input.size(); i++)
		Init_Definition(i);
	for (int i = 0; i < Input.size(); i++)
		Reserve_Function_Parameters(i);
	for (int i = 0; i < Input.size(); i++)
		Reserve_Operator_Tokens(i);
	Do_In_Order();
	for (int i = 0; i < Input.size(); i++)
	{
		Check_For_Inter(i);
		Init_Operator(i);
		Init_Variable(i);
		Init_Parenthesis(i);
		Type_Definition(i);
		Init_Conditions(i);
		Check_For_Correlation(i);	//make
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