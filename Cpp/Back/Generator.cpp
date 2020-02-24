#include "..\..\H\Back\Generator.h"
extern vector<string> Pre_Defined_Tokens;

void Generator::Factory()
{
	for (Token*t : Input)
	{
		Detect_Condition(t);
		Detect_Function(t);
		Detect_Operator(t);
		Detect_Parenthesis(t);
		Detect_Pre_Defined_Tokens(t);
	}
}

void Generator::Detect_Function(Token* t)
{
	if (t->is(_Constructor_))
	{
		//make a label OpC*
		IR* ir = new IR;
		ir->ID = "label";
		ir->PreFix = t->Name;
		ir->Flags |= _Start_Of_Label;
		//make the insights of this constructor
		Generator g;
		g.Input.push_back(t->Right_Side_Token);
		g.Types = this->Types;
		g.Factory();
		//get the output as the new IR's childs.
		ir->Childs = g.Output;
		Output.push_back(ir);
	}
	else if (t->is(_Call_))
	{
		//make a callation OpC*
		IR* ir = new IR;
		ir->ID = "call";
		//when we give the token call, (name) to it and in parser defined as
		//_External_ it can do something like this: call [banana] ; as a global variable.
		ir->Parameters.push_back(t);
		//generate the parameters as IR tokens
		Generator g;
		g.Input.push_back(t->Left_Side_Token);
		g.Types = this->Types;
		g.Factory();
		//get the output from the generator and store then into the parent IR operator.
		ir->Childs = g.Output;
		Output.push_back(ir);
	}
}

void Generator::Detect_Condition(Token* t)
{
	//if (condition is not what wanted then jump into end of if)
	//(
	//	insides of condition if condition is true
	//)
	//looping condition if loop token
	//end of condition
	if (t->is(_Condition_))
	{
		//make the starting label token as a label pointter.
		IR* Condition = new IR;
		Condition->ID = "label";
		Condition->PreFix = t->Name + to_string(t->ID);
		Condition->Flags |= _Start_Of_Label;
		//make IR tokens for condition.
		Generator g;
		g.Types = this->Types;
		g.Input.clear();
		g.Input.push_back(t->Left_Side_Token);
		g.Factory();
		//the back end for architecture specific allocates-
		//more IR tokens for example "CMP" and for the JMP condition.
		//So this is just a straight line of intermadiate-
		//assembly tokens that we can optimize and affect and etc...
		Condition->Childs = g.Output;
		//Now we need the Insides of the condition to be placed into here:
		g.Input.clear();
		g.Output.clear();
		g.Input.push_back(t->Right_Side_Token);
		g.Factory();
		Append(&Condition->Childs, g.Output);
		//Check if this condition need for repeating itself.
		if (t->Name == "while")
		{
			//this jumps straigt to start of the condition loop
			IR* Loop = new IR;
			Loop->PreFix = "jmp";
			Loop->ID = t->Name + to_string(t->ID);
			Condition->Childs.push_back(Loop);
		}
		//Now we need to make the exit label for the condition.
		IR* Exit_Label = new IR;
		Exit_Label->PreFix = t->Name + to_string(t->ID) + "END";
		Exit_Label->ID = "label";
		Exit_Label->Flags |= _End_Of_Label;
		Condition->Childs.push_back(Exit_Label);
		Output.push_back(Condition);
	}
}

void Generator::Detect_Operator(Token* t)
{
	if (t->is(_Operator_) != true)
		return;
	// (a = {[<b * c> * x] + [d / e]})
	IR* Operator = new IR;
	Operator->ID = t->Name;
	if (t->Left_Side_Token->is(_Operator_))
	{
		Detect_Operator(t->Left_Side_Token);
	}
	Operator->Parameters.push_back(t->Left_Non_Operative_Token);
	if (t->Right_Side_Token->is(_Operator_))
	{
		Detect_Operator(t->Right_Side_Token);
	}
	Operator->Parameters.push_back(t->Right_Non_Operative_Token);
	Output.push_back(Operator);
}

void Generator::Detect_Parenthesis(Token* t)
{
	if (t->is(_Parenthesis_) && t->Childs.size() > 0)
	{
		Generator g;
		g.Input = t->Childs;
		g.Types = this->Types;
		g.Factory();
		Append(&Output, g.Output);
	}
}

void Generator::Detect_Pre_Defined_Tokens(Token* t)
{
	for (string T : Pre_Defined_Tokens)
	{
		if (t->Type == T)
		{
			IR *ir = new IR;
			ir->ID = T;
			ir->Parameters.push_back(t->Right_Side_Token);
			Output.push_back(ir);
		}
	}
}

void Generator::Append(vector<IR*> *Dest, vector<IR*> Source)
{
	for (IR* i : Source)
	{
		Dest->push_back(i);
	}
}
