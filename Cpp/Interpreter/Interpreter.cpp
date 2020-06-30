#include "../../H/Interpreter/Interpreter.h"
#include "../../H/Parser/Parser.h"
extern Object* Root;

extern map<string, Token*> Preprosessor_Tokens;
extern bool Inside_Of_PreProcess;
string Layer_Name = "";

void Interpreter::Factory()
{
	Detect_Ifs();
	Detect_Patterns();
	Detect_Mod();
}

void Interpreter::Detect_Ifs()
{
	if (Input.size() < 1)
		return;
	//$if (sys:Info:OS == "win32")(
	//	using "win32_std.e"
	//)
	//$if(sys:Info:OS == "unix")(
	//	using "unix_std.e"
	//)
	if (Input.at(i).Value != "$")
		return;
	if (Input.at(i + 1).Value != "if")
		return;
	//construct the condition,
	//then check if it is true or not.
	if (Constructable(i + 2)) {
		Input.erase(Input.begin() + i, Input.begin() + i + 3);
		if (Input.at(i).Components.size() > 0){
			//int s = Input.at(i)->Tokens.size();
			//Append(&Input, Input.at(i)->Tokens, i);
			Append(Output, Input.at(i).Components);
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
	if (Input.size() < 1)
		return;
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
	if (Input.at(i).Value != "$")
		return;
	if (Input.at(i + 1).Value != "pattern")
		return;
	Token* pattern = new Token;
	pattern->Name = "pattern";
	pattern->add(_Preprosessor_);
	pattern->add(_Parenthesis_);
	Parser p;
	p.Input = Input.at(i + 2).Components;
	p.Defined_Keywords = Defined;
	Inside_Of_PreProcess = true;
	p.Factory();
	Inside_Of_PreProcess = false;
	pattern->Childs = p.Output;
	if (Preprosessor_Tokens.find(Layer_Name) == Preprosessor_Tokens.end())
	{
		Token* pack = new Token;
		pack->add(_Parenthesis_);
		pack->Childs.push_back(pattern);
		Preprosessor_Tokens.insert(make_pair(Layer_Name, pack));
	}
	else
	{
		Preprosessor_Tokens[Layer_Name]->Childs.push_back(pattern);
	}
	Input.erase(Input.begin() + i, Input.begin() + i + 3);
}

bool Interpreter::Constructable(int i)
{
	//make a tmp parser and give it the condition method
	Parser p;
	p.Input = Input.at(i).Components;
	p.Defined_Keywords = this->Defined;
	Inside_Of_PreProcess = true;
	p.Factory();
	Inside_Of_PreProcess = false;
	//get the made tokens to define what is for example sys.info stuff to compare
	//our job here is to detect the system typed tokens and handle them.
	Token* Condition = p.Output.at(0);
	//sys:(Info:OS) == "win32"
	//if (*(string*)sys->Get_Member_Pointter("Info")->Get_Member_Data("OS") == Token->Type->Name)
	if (auto left = Root->Get_Const_Data(Condition->Left_Side_Token))
	{
		if (auto right = Root->Get_Const_Data(Condition->Right_Side_Token))
		{
			bool result = *left.value() == *right.value();
			return Condition->Name == "!=" ? !result : result;
		}
	}
	return false;
}

void Interpreter::Detect_Mod()
{
	if (Input.size() < 1)
		return;
	if (Input.at(i).Value != "$")
		return;
	if (Input.at(i + 1).Value != "mod")
		return;
	Layer_Name = Input.at(i + 2).Value;
	Parser p;
	p.Input = Input.at(i + 2).Components;
	p.Defined_Keywords = Defined;
	Inside_Of_PreProcess = true;
	p.Factory();
	Inside_Of_PreProcess = false;
	Input.erase(Input.begin() + i, Input.begin() + i + 3);
	Layer_Name = "";
}

void Interpreter::Append(vector<Component>& Dest, vector<Component> Source)
{
	for (auto& i : Source)
	{
		Dest.push_back(i);
	}
}