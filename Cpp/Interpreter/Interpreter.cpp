#include "../../H/Interpreter/Interpreter.h"
#include "../../H/Parser/Parser.h"
#include <optional>

void Interpreter::Factory()
{
	Detect_Ifs();
}

void Interpreter::Detect_Ifs()
{
	//$if (sys:Info:OS == "win32")(
	//	using "win32_std.e"
	//)
	//$if(sys:Info:OS == "unix")(
	//	using "unix_std.e"
	//)
	if (Input.at(i)->WORD != "$")
		return;
	if (Input.at(i + 1)->WORD != "if")
		return;
	//construct the condition,
	//then check if it is true or not.
	if (Constructable(i + 2)) {

	}
}

bool Interpreter::Constructable(int i)
{
	//make a tmp parser and give it the condition method
	Parser p;
	p.Input = Input.at(i)->Tokens;
	p.Defined_Keywords = this->Defined;
	p.Factory();
	//get the made tokens to define what is for example sys.info stuff to compare
	//our job here is to detect the system typed tokens and handle them.
	Token* Condition = p.Output.at(0);
	//sys:(Info:OS) == "win32"
	//if (*(string*)sys->Get_Member_Pointter("Info")->Get_Member_Data("OS") == Token->Type->Name)
	if (Get_Const_Data(Condition->Left_Side_Token) == Get_Const_Data(Condition->Right_Side_Token)) {

	}
}

string Interpreter::Get_Const_Data(Token* t)
{
	//sys:Info
	if (t->Type == "system")
	{
		vector<string> members = Get_Members(t);
		if (members.size() < 2)
		{
			cout << "Error: " << "Cannot find data member --> " << t->Name + ", " + t->Type << endl;
			return "";
		}
		Symbol_Table* Source = sys; //rember to make this dynamic!!
		for (int i = 1; i < members.size()-1; i++) {
			Source = Source->Get_Member_Pointter(members.at(i));
			if (Source == nullptr)
			{
				cout << "Error: " << "Illegal pointter fethcing! --> " << t->Name + ", " + t->Type << endl;
				return "";
			}
		}
		string* tmp = Source->Get_Member_Data(members.at(members.size() - 1));
		if (tmp == nullptr)
		{
			cout << "Error: " << "Illegal constant data fethcing! --> " << t->Name + ", " + t->Type << endl;
			return "";
		}

	}
}

void Interpreter::Append(vector<string>* Dest, vector<string> Source)
{
	for (string i : Source)
	{
		Dest->push_back(i);
	}
}

vector<string> Interpreter::Get_Members(Token* t)
{
	vector<string> Phases;
	Phases.push_back(t->Name);
	if (t->Offsetter != nullptr)
	{
		Append(&Phases, Get_Members(t->Offsetter));
	}
	return Phases;
}
