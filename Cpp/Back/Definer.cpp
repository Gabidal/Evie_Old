#include "../../H/Back/Definer.h"
#include <iostream>
using namespace std;
extern vector<string> Pre_Defined_Tokens;
extern vector<Token*> Generated_Undefined_Tokens; 
extern map<string, Token*> Preprosessor_Tokens;
extern int _SYSTEM_BIT_TYPE;

string Definer::Get_All(vector<string> x, string add)
{
	string r = "";
	for (string s : x)
		r += s + add;
	return r;
}

int Definer::Get_Location_Of_Type_Constructor(string type)
{
	int i = 0;
	for (Token* T : Input_Of_Tokens)
	{
		if (T->is(_Constructor_) && T->Name == type)
		{
			return i;
		}
		i++;
	}
	return -1;
}

int Definer::Get_Definition_Setting(Token* t, string f)
{
	for (Token* i : t->Right_Side_Token->Childs)
	{
		//go a double loop and make a vector for type settings like: Size, etc...
		//loop and find if that type constructor has correlating settings and set em.
		if (i->Type == f)
		{
			return atoi(i->Right_Side_Token->Name.c_str());
		}
	}
	return 0;
}

void Definer::Get_Modded_Content(string dest, string source)
{
	if (source == "")
		return;
	if (Preprosessor_Tokens.find(dest) != Preprosessor_Tokens.end())
		return;
	if (Preprosessor_Tokens.find(source) == Preprosessor_Tokens.end())
		return;
	Preprosessor_Tokens[dest] = Preprosessor_Tokens[source];
}

void Definer::Type_Collect(Token* t)
{
	if (t->is(_Inheritting_) != true)
		return;
	for (string s : t->PreFix_Type)
		t->Size += FIND(s)->Size;
	for (string s : t->PreFix_Type)
		t->State += " " + FIND(s)->State;
	cout << "Warning: You are using an inheritance type on --> " << t->Name + ", " + Get_All(t->PreFix_Type, ", ") << endl;
}

Token* Definer::FIND(string name)
{
	for (int i = 0; i < Output.size(); i++)
	{
		if (Output.at(i)->Name == name)
		{
			return Output.at(i);
		}
	}
	for (int i = 0; i < Generated_Undefined_Tokens.size(); i++)
	{
		if (Generated_Undefined_Tokens.at(i)->Name == name)
		{
			return Generated_Undefined_Tokens.at(i);
		}
	}
	cout << "Waring: uninitialized pre type: " + name + "." << endl;
	Token* t = new Token;
	return t;
}

bool Definer::Has(Token* t, string s)
{
	if (t->Right_Side_Token == nullptr)
	{
		return false;
	}
	for (Token* T : t->Right_Side_Token->Childs)
	{
		if (T->Name == s)
		{
			return true;
		}
	}
	return false;
}

void Definer::Initialize_Global_Variables()
{
	for (Token* t: Defined_Types)
		if (t->is(_External_) && (t->Size > 0))
		{
			//if the token is declared as global then try to 
			//find the first given value and set it as the initial value setted by that label.
			int j = 0;
			for (Token* i : Input_Of_Tokens) {
				if (i->is(_Operator_) && (i->Left_Side_Token->Name == t->Name) && (i->Left_Side_Token->is(_External_) && (i->Name == "=")))
				{
					t->Initial_Value = new Token(*i->Right_Side_Token);
					t->add(_Initialized_);
					Input_Of_Tokens.erase(Input_Of_Tokens.begin() + j);
					Input_Of_Tokens.push_back(new Token(*t));
					break;
				}
				j++;
			}
		}
}

void Definer::Factory()
{
	//type var()
	//(
	//  Size 4		#the size of var type is 4Bits.
	//	Static 0	#the value can change.
	//)
	//func main()
	//(
	//	return 0
	//)
	for (Token* s : Defined_Types)
	{
		Token* New_Defined_Class = new Token();
		//first lets find the defined types
		int i = Get_Location_Of_Type_Constructor(s->Name);
		if (i == -1)
		{
			continue;
		}
		New_Defined_Class->State = Get_Definition_Setting(Input_Of_Tokens.at(i), "State");
		Get_Modded_Content(s->Name, Get_All(s->PreFix_Type, ""));
		New_Defined_Class->Name = s->Name;
		New_Defined_Class->Type = s->Type;
		New_Defined_Class->_Dynamic_Size_ = s->_Dynamic_Size_;
		if (Has(s, "return"))
		{
			New_Defined_Class->add(_Returning_);
		}
		Output.push_back(New_Defined_Class);
	}
	for (Token* i : Generated_Undefined_Tokens)
	{
		//ADVANCED
		Type_Collect(i);
	}
	Initialize_Global_Variables();
}
