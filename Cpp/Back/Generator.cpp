#include "..\..\H\Back\Generator.h"
extern vector<string> Pre_Defined_Tokens;

void Generator::Factory()
{
	for (Token*t : Input)
	{
		Detect_Condition(t);
		Detect_Function(t);
		Detect_Operator(t);
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
		IR* Start_Of_Condition = new IR;
		Start_Of_Condition->ID = "Label";
		Start_Of_Condition->PreFix = t->Name + to_string(t->ID);
			//
			IR* Comparison = new IR;
			Comparison->ID = "cmp";
			Comparison->Parameters = t->Left_Side_Token->Childs;  //get only the rignt and left of the operator  //fix!!
			//make the returning token as a label pointter.
				Token* End_Of_Condition = new Token;
				End_Of_Condition->ID = t->ID;
				End_Of_Condition->Name = t->Name + "End";
				End_Of_Condition->Flags |= _External_;
			//make the conditiond ir token
			IR* Condition = new IR;
			Condition->ID = t->Left_Side_Token->Childs.at(0)->Name; //get only the operator. //fix!!
			Condition->Parameters.push_back(End_Of_Condition);
			//put the condition into comparison
			Comparison->Childs.push_back(Condition);
		//make the ir tokens for the childs inside the condition.
		Generator g;
		g.Input.push_back(t->Left_Side_Token);
		g.Types = this->Types;
		g.Factory();
		for (IR* i : g.Output)
		{
			Comparison->Childs.push_back(i);
		}
		if (t->Name == "while")
		{
			IR* looper = new IR;
			looper->PreFix = "jmp";
			looper->
		}
		Start_Of_Condition->Childs.push_back(Comparison);
		Start_Of_Condition->Childs.push_back(End_Of_Condition);

	}
}

void Generator::Detect_Operator(Token* t)
{
}

void Generator::Detect_Parenthesis(Token* t)
{
}

void Generator::Detect_Pre_Defined_Tokens(Token* t)
{
	for (string T : Pre_Defined_Tokens)
	{
		if (t->Name == T)
		{
			IR *ir = new IR;
			ir->ID = T;
			ir->Parameters.push_back(t->Right_Side_Token);
			Output.push_back(ir);
		}
	}
}
