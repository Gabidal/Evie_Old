#include "../../H/Interpreter/Interpreter.h"
#include "../../H/Parser/Parser.h"

extern vector<Token*> Preprosessor_Tokens;

void Interpreter::Factory()
{
	Detect_Ifs();
	Detect_Patterns();
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
		Input.erase(Input.begin() + i, Input.begin() + i + 3);
		if (Input.at(i)->Tokens.size() > 0){
			//int s = Input.at(i)->Tokens.size();
			//Append(&Input, Input.at(i)->Tokens, i);
			Append(&Output, Input.at(i)->Tokens);
			Input.erase(Input.begin() + i, Input.begin() + i + 1);
		}
		else
		{
			Output.push_back(Input.at(i));
		}
	}
	else
	{
		Input.erase(Input.begin() + i, Input.begin() + i + 4);
	}
}

void Interpreter::Detect_Patterns()
{
	/*$pattern (
		$if (IN:(i:ID) == "lda")(
			$if (IN:(i:(Parameters:(0:Flags))) == "_Register_")(
				$if (IN:(i:(Parameters:(1:Name))) == "0")(
					IN:(i:(Parameters:(1))) = IN:(i:(Parameters:(0))),
					IN:(i:ID) = "^"
				)
			)
		)
	)*/
	if (Input.at(i)->WORD != "$")
		return;
	if (Input.at(i + 1)->WORD != "pattern")
		return;
	Token* pattern = new Token;
	pattern->Name = "pattern";
	pattern->add(_Preprosessor_);
	Parser p;
	p.Input = Input.at(i + 2)->Tokens;
	p.Defined_Keywords = Defined;
	p.Factory();
	pattern->Childs = p.Output;
	Preprosessor_Tokens.push_back(pattern);
	Input.erase(Input.begin() + i, Input.begin() + i + 3);
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
	if (auto left = Get_Const_Data(Condition->Left_Side_Token))
	{
		if (auto right = Get_Const_Data(Condition->Right_Side_Token))
		{
			bool result = *left.value() == *right.value();
			return Condition->Name == "!=" ? !result : result;
		}
	}
}

optional<Waiter*> Interpreter::Get_Const_Data(Token* t)
{
	//sys:Info
	if (t->Type == "system")
	{
		vector<string> members = Get_Members(t);
		if (members.size() < 2)
		{
			cout << "Error: " << "Cannot find data member --> " << t->Name + ", " + t->Type << endl;
			return nullopt;
		}
		Symbol_Table* Source = sys; //rember to make this dynamic!!
		for (int i = 1; i < members.size()-1; i++) {
			Source = Source->Get_Member_Pointter(members.at(i));
			if (Source == nullptr)
			{
				cout << "Error: " << "Illegal pointter fethcing! --> " << t->Name + ", " + t->Type << endl;
				return nullopt;
			}
		}
		Waiter* tmp = Source->Get_Member_Data(members.at(members.size() - 1));
		if (tmp == nullptr)
		{
			cout << "Error: " << "Illegal constant data fethcing! --> " << t->Name + ", " + t->Type << endl;
			return nullopt;
		}
		return optional<Waiter*> { tmp };
	}
	else if (t->is(_Number_))
	{
		return optional<Waiter*> { new IntWaiter(new int(atoi(t->Name.c_str()))) };
	}
	else if (t->is(_String_))
	{
		return optional<Waiter*> { new StringWaiter(new string(t->Name.substr(1, t->Name.size() - 2))) };
	}
	return nullopt;
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
	//sys:(Info:OS)
	vector<string> Phases;
	if (t->Name != "")
		Phases.push_back(t->Name);
	if (t->Offsetter != nullptr)
	{
		Append(&Phases, Get_Members(t->Offsetter));
	}
	else if (t->Childs.size() > 0)
	{
		Append(&Phases, Get_Members(t->Childs.at(0)));
	}
	return Phases;
}

void Interpreter::Append(vector<Word*>* Dest, vector<Word*> Source)
{
	for (auto i : Source)
	{
		Dest->push_back(i);
	}
}