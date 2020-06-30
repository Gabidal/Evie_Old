#include "../../H/Parser/Parser.h"
#include "../../H/Interpreter/Interpreter.h"

bool Inside_Of_Constructor_As_Parameter = false;
bool Inside_Of_Constructor = false;
bool Inside_Of_Class = false; //indicates if inside of Size keyword for members to use only local
bool Inside_Of_PreProcess = false;
int Layer = 0;
int ID = 1;
int String_ID = 0;
int Global_Stack_Offset = 0;
int Local_Stack_Offest = 0;
int LINE_NUMBER = 0;
vector<string> Global_Comment;
vector<Token*> Global_Data;
vector<Token*> Defined_Local_To_Global_Variables;
extern int _SYSTEM_BIT_TYPE;
extern vector<string> Included_Files; //for loop holes to not exist
extern vector<string> Pre_Defined_Tokens;

string Working_Dir = "";
string Parser::Update_Dir(string File_Name)
{
	int i = (int)File_Name.find_last_of('/');
	if (i != -1)
	{
		Working_Dir += File_Name.substr(0, (size_t)i + 1);
		return File_Name.substr((size_t)i + 1);
	}
	return File_Name;
}

void Parser::Include_Files(int i)
{
	if (Input.at(i).Value == "use")
	{
		bool Do_As_PreProsessor = false;
		string filename = Input.at((size_t)i + 1).Value.substr(1, Input.at((size_t)i + 1).Value.size() - 2);
		if (i - 1 >= 0)
			if (Input.at(i - 1).Value == "$") {
				//this made for the asm prpose
				Do_As_PreProsessor = true;
				for (string s : Included_Files)
					if (Input.at((size_t)i + 1).is(STRING_COMPONENT) && (filename == s))
					{
						cout << "Warning: " << Input.at((size_t)i + 1).Value << " has already been included." << endl;
						Input.erase(Input.begin() + i + 1);
						Input.erase(Input.begin() + i);
						return;
					}
			}
		string Name = Update_Dir(filename);
		//now include the file 
		Docker* D;
		//if prerosessing is needed use Docker if not make an %include "text" include as a Token*
		if (Do_As_PreProsessor)
			D = new Docker(Name, Working_Dir, "");
		else {
			Token* Include = new Token;
			Include->Name = filename;
			Include->_IS_ASM_INCLUDE_ = true;
			Output.push_back(Include);
		}

		//vector<Component> tmp = Lexer::GetComponentsFromFile(Working_Dir + Name);
		Input.erase(Input.begin() + i + 1);
		Input.erase(Input.begin() + i);
		if (Do_As_PreProsessor) {
			Input.erase(Input.begin() + i - 1);
			Input.insert(Input.begin() + i, D->Output.begin(), D->Output.end());
		}
		Included_Files.push_back(filename);
		if (i == Input.size())
			return;
		if (Do_As_PreProsessor)
			if (Input.at(i - 1).Value == "use")
				Include_Files(i-1);
		if (Input.at(i).Value == "use")
			Include_Files(i);
	}
}

void Parser::Connect_Array(int i)
{
	if (Input.at(i).Value == ":" || Input.at(i).Value == "::" || (Input.at(i).is(PAREHTHESIS_COMPONENT) && Input.at(i).Value.at(0) == '[' && i-1 > 0))
	{
	}
	else
		return;
	//get the offsetter getting position
	int Offsetter = 0;
	if (Input.at(i).is(PAREHTHESIS_COMPONENT))
		Offsetter = i;		//<[0]>
	else
		Offsetter = i + 1; //<::> <0>
	//b = a:b
	Input.at((size_t)i - 1).Offsetter = new Component(Input.at((size_t)Offsetter));
	if (Input.at(i).Value == "::" || (Input.at(i).is(PAREHTHESIS_COMPONENT) && Input.at(i).Value.at(0) == '['))
	{
		Input.at((size_t)i-1).IsPointter = true;
	}
	if (!Input.at(i).is(PAREHTHESIS_COMPONENT))
		Input.erase(Input.begin() + i + 1);
	Input.erase(Input.begin() + i);
	return;
}

void Parser::Connect_Address(int i)
{
	if (Input.at(i).Value != "@") return;
	Input.at((size_t)i + 1).IsGivingAddress = true;
	Input.erase(Input.begin() + i);
}

void Parser::Init_Definition(int& i)
{
	if (i >= (Input.size() - 1))
		return;
	if ((Collect_All_Inherited_Types(i).size() < 1) || (i + Collect_All_Inherited_Types(i).size() > Input.size() - 1))
		return;
	if (!Input.at(i + Collect_All_Inherited_Types(i).size()).is(TEXT_COMPONENT))
		return;
	if (Defined(Input.at(i + Collect_All_Inherited_Types(i).size()).Value) != "")
		return;
	//import func banana()()
	//func banana()()
	//export loyal func banana()()
	//type var
	//var a
	//a = b
	//const var b
	//func a()
	//if ((Input.at(i)->is(_KEYWORD) || (Defined(Input.at(i).Value) != "")) && ((Input.at(i+1)->is(_TEXT)) || (Input.at(i + 1)->is(_KEYWORD))) && (Input.at(i).Value != ","))
	Token* New_Defined_Type = new Token();
	New_Defined_Type->Types = Collect_All_Inherited_Types(i);
	
	New_Defined_Type->Name = Input.at(i + New_Defined_Type->Types.size()).Value;
	if (New_Defined_Type->is("type"))
	{
		//REMEMBER!!! this token* size is the raw Size x token
		Token* Size = Get_Setting(i, New_Defined_Type, "size");
		if (Size == nullptr)
			New_Defined_Type->Size = 0;
		else if (Size->Right_Side_Token->Name == "$")
			New_Defined_Type->_Dynamic_Size_ = true;
		else if (Size->Right_Side_Token->is(_Number_))
			New_Defined_Type->Size = atoi(Size->Right_Side_Token->Name.c_str());
		else if (Defined(Size->Right_Side_Token->Name) != "")
			New_Defined_Type->Size = Find(Size->Right_Side_Token->Name, Defined_Keywords)->Size;
		else if (Size->Right_Side_Token->is(_Parenthesis_)) {
			//size (int a, int b, int c) give them into this defined keyword
			New_Defined_Type->Size = Size->Right_Side_Token->Size;
			Append(&New_Defined_Type->Childs, Size->Right_Side_Token->Childs);
		}
		Token* State = Get_Setting(i, New_Defined_Type, "state");
		if (State != nullptr)
			New_Defined_Type->State = State->Right_Side_Token->Name;
	}
	else if (New_Defined_Type->is("func"))
		New_Defined_Type->Size = _SYSTEM_BIT_TYPE;
	else
	{
		for (string s : New_Defined_Type->Types)
			for (Token* t : Defined_Keywords)
				if (s == t->Name)
				{
					New_Defined_Type->Size += t->Size;
					New_Defined_Type->State = t->State;
					New_Defined_Type->_Dynamic_Size_ |= t->_Dynamic_Size_;
					Append(&New_Defined_Type->Childs, t->Childs);
				}
	}
	if (Global_Comment.size() > 0) {
		New_Defined_Type->Comments = Global_Comment;
		Global_Comment.clear();
	}
	New_Defined_Type->Context = Context;
	//if (!New_Defined_Type->is("cache"))
	if (!New_Defined_Type->is("cache"))
		Set_Right_Stack_Offset(New_Defined_Type);
	Set_Right_Flag_Info(New_Defined_Type);

	if (Inside_Of_Constructor || Inside_Of_Constructor_As_Parameter || Inside_Of_Class)
		Defined_Local_Keywords.push_back(New_Defined_Type);

	Defined_Keywords.push_back(New_Defined_Type);

	if (!New_Defined_Type->is("cache")) {
		if (New_Defined_Type->is("ptr"))
			Space_Reservation += _SYSTEM_BIT_TYPE;
		else
			Space_Reservation += New_Defined_Type->Size;
	}
	i += (int)New_Defined_Type->Types.size();

}

void Parser::Init_Comments(int i)
{
	if (Input.at(i).is(COMMENT_COMPONENT))
		Global_Comment.push_back(Input.at(i).Value);
	Input.erase(Input.begin() + i);
	if (Input.at(i).is(COMMENT_COMPONENT))
		Init_Comments(i);
	return;
}

vector<string> Parser::Collect_All_Inherited_Types(int start) //returned vector size needs to be deleted from input
{
	//[defined]import [defined]loyal [keyword]func [plain text]banana
	vector<string> r;
	for (int i = start; i < Input.size(); i++)
	{
		if ((Defined(Input.at(i).Value) != "") || Input.at(i).is(KEYWORD_COMPONENT))
		{
			r.push_back(Input.at(i).Value);
		}
		else
		{
			break;
		}
	}
	return r;
}

Token* Parser::Get_Setting(int i, Token* defined, string setting)
{
	//type a()(..)
	if (Count_Familiar_Tokens(PAREHTHESIS_COMPONENT, i + 2) < 2)
		return nullptr;
	Parser p;
	int Next_Parenthesis_Index = 3;
	if (Input.at(i + Next_Parenthesis_Index).Value == "\n")
		Next_Parenthesis_Index = 4;
	p.Input = Input.at((size_t)i + Next_Parenthesis_Index).Components;
	p.Defined_Keywords = Defined_Keywords;
	Inside_Of_Class = true;
	int tmp = Local_Stack_Offest;
	Local_Stack_Offest = 0;
	p.Factory();
	Local_Stack_Offest = tmp;
	Inside_Of_Class = false;
	Token* t = nullptr;
	for (int j = 0; j < p.Output.size(); j++) {
		if (p.Output.at(j)->is(setting))
		{
			t = p.Output.at(j);
		}
	}
	return t;
}

Token* Parser::Find(string name, vector<Token*> list)
{
	for (Token* i : list)
		if (i->Name == name)
			return i;
	return nullptr;
}

vector<Component> Parser::Find_Root(Component parent)
{
	vector<Component> Route;
	Component* i = &parent;

	while (i->is(PAREHTHESIS_COMPONENT)) {
		//push the member
		Route.push_back(i->Components.at(1));
		//set up the new component
		i = &i->Components.at(0);
	}
	//now add the top hieararchy parent
	Route.push_back(*i);
	reverse(Route.begin(), Route.end());
	return Route;
}

void Parser::Init_Operator(int i)
{
	if (Input.size() < 1)
		return;
	if (Input.at(i).Value == "$")
		return;
	if (Input.at(i).Value == ",")
		return;
	if (Input.at(i).Value == ";")
		return;
	if (Input.at(i).Value == ".")
		return;
	//a = 1
	//a < b
	if (Input.at(i).is(OPERATOR_COMPONENT))
	{
		Parser P = *this;
		P.Output.clear();
		P.Input.clear();
		P.Input.push_back(Input.at(i).Components.at(0));
		P.Factory();
		Token* New_Defined_Left_Side_Token = P.Output.at(0);


		P.Output.clear();
		P.Input.clear();
		P.Input.push_back(Input.at(i).Components.at(1));
		P.Factory();
		Token* New_Defined_Right_Side_Token = P.Output.at(0);

		//EXPERIEMENTAL!!
		//for non operative tokens
		P.Output.clear();
		P.Input.clear();
		P.Input.push_back(*Input.at(i).Left);
		P.Factory();
		Token* New_Left_Non_Operative_Token = P.Output.at(0);

		P.Output.clear();
		P.Input.clear();
		P.Input.push_back(*Input.at(i).Right);
		P.Factory();
		Token* New_Right_Non_Operative_Token = P.Output.at(0);

		Token* New_Defined_Operator = new Token();
		New_Defined_Operator->Context = Context;
		New_Defined_Operator->Name = Input.at(i).Value;
		New_Defined_Operator->Left_Side_Token = New_Defined_Left_Side_Token;
		New_Defined_Operator->Right_Side_Token = New_Defined_Right_Side_Token;
		New_Defined_Operator->Left_Non_Operative_Token = New_Left_Non_Operative_Token;
		New_Defined_Operator->Right_Non_Operative_Token = New_Right_Non_Operative_Token;

		New_Defined_Operator->add(_Operator_);
		Output.push_back(New_Defined_Operator);
	}
}

void Parser::Init_Member_Reaching(int i)
{
	//get the members offset from the initialized types list
	if (!Input.at(i).HasMemberOffsetting)
		return;
	Input.at(i).HasMemberOffsetting = false;
	//we have a operator that has the member and the object
	//a.b
	//we just need to make a operator 'a:[b's address]'
	/*
	type banana(){
		size (
			int a
			int b
			int c
		)
	}
	banana x
	x.a must be translated into
	x:(4-systemsize) == x:0
	*/
	//first get the defined class
	//i.components.at(0) == parent or ()
	//i.components.at(1) == member
	//try to find the parents member template.
	vector<Component> Route_To_Member = Find_Root(Input.at(i));

	Token* Master = Find(Route_To_Member.at(0).Value, Defined_Keywords);
	Token* object = Find(Route_To_Member.at(0).Value, Defined_Keywords);
	vector<Token*> Types = object->Childs;

	int StackOffset = 0;

	for (int j = 1; j < Route_To_Member.size(); j++) {
		object = Find(Route_To_Member.at(j).Value, Types);
		StackOffset += object->StackOffset - _SYSTEM_BIT_TYPE;
		Types = object->Childs;
	}
	//save the giving address
	Route_To_Member.back().IsGivingAddress = Input.at(i).IsGivingAddress;
	//first lets make a copy of the last member's data of pointter/arrays
	Input.at(i) = Route_To_Member.back();
	//now lets name it as master x so that the variable creator can access to is data
	Input.at(i).Value = Master->Name;
	Input.at(i).Flags = TEXT_COMPONENT;
	Input.at(i).Components.clear();
	//now make a new pareser and parse all pointter/array/addressgiving it has
	Parser p;
	p.Input.push_back(Input.at(i));
	p.Defined_Keywords = Defined_Keywords;
	p.Factory();
	//now the Output should have all that we need
	Token* Result = p.Output.back();
	//give it the right size
	Result->Hidden_Size = object->Size;
	Result->Size = _SYSTEM_BIT_TYPE;
	//give it the right stack offset
	Result->StackOffset = StackOffset + Master->StackOffset;
	//the object that remainds is the final member we want!
	//now that we have the 
	Output.push_back(new Token(*Result));
	return;
}

void Parser::Reserve_Member_Offsetting(int &i)
{
	if (Input.at(i).Value != ".")
		return;
	//i-1 is the object
	//i+1 is the member
	//we need preserve this for the core to handle not for preprosessed
	//so we wnat to wrap these into parenthses
	//and then later on we unravel em.
	//first make a parenthesis component
	Component P = Lexer::GetComponents("( )").back();
	//now put the member addressing into the parenthsesis
	P.HasMemberOffsetting = true;
	P.Components.push_back(Input.at(i - 1));
	P.Components.push_back(Input.at(i + 1));
	Input.erase(Input.begin() + i + 1);
	Input.erase(Input.begin() + i - 1);
	Input.at(i - 1) = P;
	i--;
}

void Parser::Reserve_Operator_Tokens(int i)
{
	if (Input.at(i).Value == "$")
		return;
	if (Input.at(i).Value == ",")
		return;
	if (Input.at(i).Value == ";")
		return;
	if ((Input.at(i).is(OPERATOR_COMPONENT) == true) && (Input.at(i).IsInitialized == false))
	{
	}
	else
		return;
	if (i-1 < 0)
	{
		//negatable operator
		Input.at((size_t)i + 1).PreFix = Input.at(i).Value;
		Input.erase(Input.begin() + i);
	}
	else
	{
		Input.at(i).Left = new Component(Input.at((size_t)i - 1));
		Input.at(i).Right = new Component(Input.at((size_t)i + 1));
	}
}

void Parser::Reserve_Function_Parameters(int i)
{
	if (Input.at(i).is(TEXT_COMPONENT) && (Defined(Input.at(i).Value) != ""))
	{
		if (Count_Familiar_Tokens(PAREHTHESIS_COMPONENT, i + 1) == 1)
		{
			Input.at(i).Components.push_back(Input.at((size_t)i + 1));
			Input.at(i).IsCall = true;
			Input.erase(Input.begin() + i + 1);
		}
	}
}

void Parser::Patternize_Operations(int& i, vector<string> operators)
{
	if (Input.at(i).Value == "$")
		return;
	if (Input.at(i).Value == ",")
		return;
	if (Input.at(i).Value == ";")
		return;
	for (string s: operators)
		if (Input.at(i).is(OPERATOR_COMPONENT) && (Input.at(i).Value == s) && (Input.at(i).IsInitialized != true))
		{
			Input.at(i).Components.push_back(Input.at((size_t)i - 1));
			Input.at(i).Components.at(0).IsOperatorized = false;
			Input.at(i).Components.push_back(Input.at((size_t)i + 1));
			Input.at(i).Components.at(1).IsOperatorized = false;
			Input.at(i).IsInitialized = true;

			//Input.at(i + 1)->_operatorized = true;
			//Input.at(i - 1)->_operatorized = true;
			Input.erase(Input.begin() + i + 1);
			Input.erase(Input.begin() + i - 1);
			i--;
			break;
		}
	return;
}

void Parser::Do_In_Order()
{
	//the combination and multilayering of operations.
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, { ":" });
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, { "." });
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, { "*", "/" , "%" });
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, { "<<", ">>" });
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, { "&", "!&" });
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, { "?" });
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, { "|", "!|" });
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, { "+", "-" });
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, { "<", ">" });
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, { "==", "!=", "<=", ">=", "!<", "!>" , "|=", "&="});
	for (int i = 0; i < Input.size(); i++)
		Patternize_Operations(i, { "=" });
}

void Parser::Init_Parenthesis(int i)
{
	if (Input.size() < 1)
		return;
	if (Input.at(i).is(PAREHTHESIS_COMPONENT) && (!Input.at(i).HasMemberOffsetting))
	{
		LINE_NUMBER = 0; //zero the line number because its based on relative to its woner like funciont a:1
		Token* New_Defined_Parenthesis = new Token();
		Parser P = *this;
		P.Space_Reservation = 0;
		P.Output.clear();
		P.Input = Input.at(i).Components;
		P.Factory();
		New_Defined_Parenthesis->Childs = P.Output;
		New_Defined_Parenthesis->add(_Parenthesis_);
		New_Defined_Parenthesis->Reservable_Size = P.Space_Reservation;
		New_Defined_Parenthesis->Size = P.Space_Reservation;
		Output.push_back(New_Defined_Parenthesis);
		this->Space_Reservation = P.Space_Reservation;
		this->Defined_Local_Keywords = P.Defined_Local_Keywords;
		if (Inside_Of_Constructor_As_Parameter)
		{
			this->Defined_Keywords = P.Defined_Keywords;
		}
		LINE_NUMBER = 0; //zero the line number because its based on relative to its woner like funciont a:1
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
	if (Input.at(i).is(KEYWORD_COMPONENT) && Input.at((size_t)i+1).is(PAREHTHESIS_COMPONENT))
	{
		Token* New_Defined_Condition = new Token();
		New_Defined_Condition->Name = Input.at(i).Value;
		New_Defined_Condition->ID = ID + Layer;
		New_Defined_Condition->add(_Condition_);
		New_Defined_Condition->add(_External_);
		ID++;


		Parser P = *this;

		//update context
		P.Context = New_Defined_Condition->Name + to_string(New_Defined_Condition->ID);

		P.Output.clear();
		P.Input.clear();
		P.Input.push_back(Input.at((size_t)i + 1));				//The parameters for the condition.
		P.Factory();

		New_Defined_Condition->Left_Side_Token = P.Output.at(0);


		int Next_Parenthesis_Index = 2;
		if (Input.at(i + 2).Value == "\n")
			Next_Parenthesis_Index = 3;

		P.Output.clear();
		P.Input.clear();
		P.Input.push_back(Input.at((size_t)i + Next_Parenthesis_Index));				//The Childs if that condition happends.
		P.Factory();

		New_Defined_Condition->Right_Side_Token = P.Output.at(0);

		Input.erase(Input.begin() + i + Next_Parenthesis_Index);
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
	if (Input.at(i).is(TEXT_COMPONENT) && (Defined(Input.at(i).Value) != ""))
	{
		//a() #like a function call
		//lets give the new parser new input tokens the other is the parameters
		//and the other is the child of the defined type
		Token* New_Defined_Text = new Token();
		if (Input.at(i).IsCall)
		{

			Parser P = *this;
			//update context
			P.Context = "Parameter";
			P.Input.clear();
			P.Output.clear();
			P.Input = Input.at(i).Components;
			Inside_Of_Constructor_As_Parameter = true;
			P.Factory();
			Inside_Of_Constructor_As_Parameter = false;
			New_Defined_Text->Defined_Local_Types = P.Defined_Local_Keywords;

			New_Defined_Text->Left_Side_Token = P.Output.at(0);
			reverse(New_Defined_Text->Left_Side_Token->Childs.begin(), New_Defined_Text->Left_Side_Token->Childs.end());
			New_Defined_Text->add(_Call_);
			New_Defined_Text->Size = _SYSTEM_BIT_TYPE;
			New_Defined_Text->Context = Context;
			if (New_Defined_Text->Left_Side_Token->Reservable_Size > 0 || (New_Defined_Text->Left_Side_Token->Childs.size() > 0))
			{
				New_Defined_Text->add(_Need_For_Space_);
				for (Token* t : New_Defined_Text->Left_Side_Token->Childs) {
					if (t->is("ptr"))
						New_Defined_Text->Reservable_Size += _SYSTEM_BIT_TYPE;
					else
					New_Defined_Text->Reservable_Size += t->Size;
				}
				New_Defined_Text->Reservable_Size += New_Defined_Text->Left_Side_Token->Reservable_Size;
			}
		}
		else if (Count_Familiar_Tokens(PAREHTHESIS_COMPONENT, i + 1) == 2)
		{


			Parser P = *this;
			//update context
			P.Context = "Parameter";

			P.Input.clear();
			P.Output.clear();
			//parameters.
			Inside_Of_Constructor_As_Parameter = true;


			P.Input.push_back(Input.at((size_t)i + 1));
			P.Factory();
			Inside_Of_Constructor_As_Parameter = false;
			New_Defined_Text->Defined_Local_Types = P.Defined_Local_Keywords;

			Local_Stack_Offest = 0;
			New_Defined_Text->Left_Side_Token = P.Output.at(0);


			if (New_Defined_Text->Left_Side_Token->Reservable_Size > 0)
			{
				New_Defined_Text->add(_Need_For_Space_);
			}

			New_Defined_Text->Left_Side_Token->Reservable_Size = 0;


			int Next_Parenthesis_Index = 2;
			if (Input.at(i + Next_Parenthesis_Index).Value == "\n")
				Next_Parenthesis_Index = 3;

			//update context
			P.Context = Input.at(i).Value;

			P.Output.clear();
			P.Input.clear();
			//childs
			Inside_Of_Constructor = true;
			P.Input.push_back(Input.at((size_t)i + Next_Parenthesis_Index));
			P.Space_Reservation = 0;			//!!!!!!!!!!!!!!
			P.Factory();
			Inside_Of_Constructor = false;
			Append(&New_Defined_Text->Defined_Local_Types, P.Defined_Local_Keywords);

			Local_Stack_Offest = 0;
			New_Defined_Text->Right_Side_Token = P.Output.at(0);
			New_Defined_Text->add(_Constructor_);
			New_Defined_Text->add(_External_);

			if (New_Defined_Text->Right_Side_Token->Reservable_Size > 0)
			{
				New_Defined_Text->add(_Need_For_Space_);
				New_Defined_Text->Reservable_Size = New_Defined_Text->Right_Side_Token->Reservable_Size;
			}

			Input.erase(Input.begin() + i + Next_Parenthesis_Index);
			Input.erase(Input.begin() + i + 1);

		}
		else
		{
			return;
		}
		New_Defined_Text->Name = Input.at(i).Value;
		//if only a call seek the information from defined
		if (New_Defined_Text->is(_Call_) || New_Defined_Text->is(_Constructor_))
			for (Token* t : Defined_Keywords)
				if (t->Name == New_Defined_Text->Name && (!New_Defined_Text->is(_Combined_)))
				{
					//check if have to make a new clone of the original with mangled
					bool Different = false;
					if (t->Left_Side_Token == nullptr) Different = false;
					else if (t->Left_Side_Token->Childs.size() != New_Defined_Text->Left_Side_Token->Childs.size()) Different = true;
					else
						for (int x = 0; x < t->Left_Side_Token->Childs.size(); x++) {
							if (t->Left_Side_Token->Childs[x]->Types.size() != New_Defined_Text->Left_Side_Token->Childs[x]->Types.size()) {
								Different = true;
								break;
							}
							for (int y = 0; y < t->Left_Side_Token->Childs[x]->Types.size(); y++)
								if (t->Left_Side_Token->Childs[x]->Types[y] != New_Defined_Text->Left_Side_Token->Childs[x]->Types[y])  Different = true;
						}
					if (Different) {
						//start making the clone
						New_Defined_Text->StackOffset = t->StackOffset;
						New_Defined_Text->Size = t->Size;
						New_Defined_Text->add(t->get());
						New_Defined_Text->Types = t->Types;
						New_Defined_Text->add(_Combined_);
						Defined_Keywords.push_back(new Token(*New_Defined_Text));
						break;
					}
					else
					{
						New_Defined_Text->StackOffset = t->StackOffset;
						New_Defined_Text->Size = t->Size;
						New_Defined_Text->add(t->get());
						New_Defined_Text->Types = t->Types;
						New_Defined_Text->add(_Combined_);
						if (New_Defined_Text->is(_Constructor_))
							t->Left_Side_Token = New_Defined_Text->Left_Side_Token;
						break;
					}
				}
		//update the callation amount of repsesentive funcion
		Update_Used_Functions_Value(New_Defined_Text);
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
	if (Inside_Of_Constructor || Inside_Of_Class)
		t->StackOffset = Local_Stack_Offest + 4;
	else if (Inside_Of_Constructor_As_Parameter)
		t->StackOffset = (_SYSTEM_BIT_TYPE * 2) + Local_Stack_Offest;
	else
		t->StackOffset = Global_Stack_Offset;
	//because cached variables do not use mem
	if (Inside_Of_Constructor || Inside_Of_Constructor_As_Parameter || Inside_Of_Class) {
		if (t->is("ptr"))
			Local_Stack_Offest += _SYSTEM_BIT_TYPE;
		else
			Local_Stack_Offest += t->Size;
	}
	else {
		if (t->is("ptr"))
			Global_Stack_Offset += _SYSTEM_BIT_TYPE;
		else
			Global_Stack_Offset += t->Size;
	}
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
		if (Input.at(j).is(COMMENT_COMPONENT))
			continue;
		if (Input.at(j).is(F))
		{
			u++;
		}
		else if (!Input.at(j).is(END_COMPONENT))
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
	if (Input.at(i).IsOperatorized)
		return;
	if (((size_t)i + 1) > (Input.size() - 1)){	}
	else if (Input.at((size_t)i+1).is(TEXT_COMPONENT))
		return;
	if (Input.at(i).IsCall)
		return;
	/*for (Token* t : Defined_Keywords)
		if ((Input.at(i).Value == t->Name) && (t->is(_Call_)) && (!Input.at(i).IsGivingAddress))
			return;*/

	if (Input.at(i).is(TEXT_COMPONENT) && (Defined(Input.at(i).Value) != "") && (Layer > 1))
	{
		Token* New_Variable = new Token();
		New_Variable->Name = Input.at(i).Value;
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
				New_Variable->State = t->State;
				New_Variable->_Dynamic_Size_ = t->_Dynamic_Size_;
				New_Variable->Childs = t->Childs;
				break;
			}
		if (Input.at(i).Offsetter != nullptr)
		{
			Parser p;
			p.Input.push_back(*Input.at(i).Offsetter);
			p.Defined_Keywords = this->Defined_Keywords;
			p.Factory();
			New_Variable->Offsetter = p.Output.at(0);
			if (Input.at(i).IsPointter)
				New_Variable->add(_Pointting_);
			else
				New_Variable->add(_Array_);
		}
		if (Input.at(i).IsGivingAddress)
		{
			New_Variable->add(_Giving_Address_);
		}
		New_Variable->Context = Context;
		Output.push_back(New_Variable);
		//Generated_Undefined_Tokens.push_back(Output.back());
	}
	if (Input.at(i).is(NUMBER_COMPONENT) && (Layer > 1))
	{
		Token* New_Number = new Token();
		New_Number->Name = Input.at(i).PreFix;
		New_Number->Name += Input.at(i).Value;
		New_Number->Types.push_back("number");
		New_Number->add(_Number_);
		New_Number->Context = Context;
		if (Input.at(i).Offsetter != nullptr)
		{
			Parser p;
			p.Input.push_back(*Input.at(i).Offsetter);
			p.Defined_Keywords = this->Defined_Keywords;
			p.Factory();
			New_Number->Offsetter = p.Output.at(0);
			if (Input.at(i).IsPointter)
				New_Number->add(_Pointting_);
			else
				New_Number->add(_Array_);
		}
		if (New_Number->Name.find('.') != -1)
		{
			//floating unit
			New_Number->Size = _SYSTEM_BIT_TYPE;
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
	if (Input.at(i).is(STRING_COMPONENT) && (Layer > 1) && Inside_Of_PreProcess)
	{
		Token* Str = new Token;
		Str->add(_String_);
		Str->Name = Input.at(i).Value;
		Str->Size = _SYSTEM_BIT_TYPE;
		Str->Types.push_back("string");
		Str->Context = Context;
		Output.push_back(Str);
	}
	else if (Input[i].is(STRING_COMPONENT)) {

		//first start to find if this same stirng is already defined
		for (Token* t : Global_Data)
			if (t->Right_Side_Token->is(_String_))
				if (t->Right_Side_Token->Name == Input.at(i).Value) {
					Output.push_back(t->Left_Side_Token);
					return;
				}


		//S1 db "hello World!"
		//push S1
		//mov reg, S1
		//this is the raw string
		Token* Str_Word = new Token;
		Str_Word->add(_String_);
		Str_Word->Name = Input.at(i).Value;
		Str_Word->Size = _SYSTEM_BIT_TYPE;
		Str_Word->Types.push_back("string");
		Str_Word->Context = Context;

		//now make the string global variable pointter
		//string a = Str_Word
		Token* Str_Ptr = new Token;
		Str_Ptr->Name = "S" + to_string(String_ID);
		String_ID++;
		Str_Ptr->Size = _SYSTEM_BIT_TYPE; //space needed to reserve the string pointter
		Str_Ptr->Hidden_Size = 1; //scaling size by char
		Str_Ptr->Types.push_back("ptr");
		Str_Ptr->add(_Pointting_);
		Str_Ptr->add(_External_);
		if (Input[i].IsGivingAddress) {
			Str_Ptr->_Give_String_Address_ = true;
		}
		Str_Ptr->Context = Context;

		//save this as an defined type
		Defined_Keywords.push_back(Str_Ptr);
		//also for definer.cpp
		Defined_Local_To_Global_Variables.push_back(Str_Ptr);

		//we need now to add this into Global_Data list
		//S0 = "Hello world!"
		//and then return Str_Ptr into output
		Token* Op = new Token;
		Op->Name = "=";
		Op->add(_Operator_);
		Op->Left_Side_Token = new Token(*Str_Ptr);
		Op->Right_Side_Token = new Token(*Str_Word);
		Op->Left_Non_Operative_Token = new Token(*Str_Ptr);
		Op->Right_Non_Operative_Token = new Token(*Str_Word);
		Op->Context = Context;
		//save the operattor
		Global_Data.push_back(Op);

		//now return the S pointter
		Output.push_back(new Token(*Str_Ptr));

		//clean the remnant of the original string
		Input.erase(Input.begin() + i);
		if (Input.size() == 0)
			return;
	}
	if (Input.at(i).Value == "$")
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
		if (Input.at(i).Value == s)
		{
			Token* New_Pre_Defined_Token = new Token();
			New_Pre_Defined_Token->Types.push_back(s);
			//return 0;
			//return;
			if (Input.at(i).Components.size() > 0) {
				Parser P = *this;
				P.Defined_Keywords = Defined_Keywords;
				P.Output.clear();
				P.Input.clear();
				P.Input = Input.at(i).Components;
				P.Factory();

				if (P.Output.size() > 0)
					New_Pre_Defined_Token->Right_Side_Token = P.Output.at(0);
				else
				{
					Token* Empty_And_Potentially_Useless = new Token;
					Empty_And_Potentially_Useless->Name = Input.at(i).Components.at(0).Value;
					New_Pre_Defined_Token->Right_Side_Token = Empty_And_Potentially_Useless;
				}
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
		if (Input.at(i).Value == s)
		{
			//return;
			if (i + 1 >= (int)Input.size())
				return;
			if (Input.at((size_t)i + 1).Value == ";" || Input.at((size_t)i + 1).Value == "\n")
				return;
			Input.at(i).Components.push_back(Input.at((size_t)i + 1));
			Input.erase(Input.begin() + i + 1);
			return;
		}
}

void Parser::Check_For_Preprosessor(int i)
{
	if (Input.size() - 1 < (size_t)i + 1)
		return;
	if (Input.at(i).Value == "$")
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
	if (Input.at(i).Value == "$")
	{
		//loops if these is right behind it another "$"
		Check_For_Preprosessor(i);
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
		Reserve_Member_Offsetting(i);
	for (int i = 0; i < Input.size(); i++)
		Connect_Address(i);
	for (int i = 0; i < Input.size(); i++)
		Reserve_Function_Parameters(i);
	for (int i = 0; i < Input.size(); i++)
		Init_Definition(i);
	for (int i = 0; i < Input.size(); i++)
		Reserve_Operator_Tokens(i);
	//do the ast like tree with the operators
	Do_In_Order();
	for (int i = 0; i < Input.size(); i++)
		Check_For_Correlation_Link(i);		//link like return etc with the parameter
	for (int i = 0; i < Input.size(); i++)
	{
		Init_Member_Reaching(i);
		Update_Line_Number(Input.at(i));
		Check_For_Preprosessor(i);
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

void Parser::Append(vector<Component>* Dest, vector<Component> Source)
{
	for (Component i : Source)
	{
		Dest->push_back(i);
	}
}

void Parser::Update_Line_Number(Component& t)
{
	if (t.Value == "\n" && t.IsInitialized == false) {
		LINE_NUMBER++;
		t.IsInitialized = true;
	}
}

void Parser::Update_Used_Functions_Value(Token* call)
{
	if (!call->is(_Call_))
		return;
	//this function seraches the types list to find the representative
	for (Token* t : Defined_Keywords)
		if (call->Name == t->Name) {
			t->Callation_Count++;
			return;
		}
}