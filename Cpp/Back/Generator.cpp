#include "..\..\H\Back\Generator.h"
#include "../../H/Selector/Selector.h"
extern Selector* S;
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
	if (t->Type == "type")
		return;
	if (t->is(_Constructor_))
	{
		//make a label OpC*
		IR* ir = new IR;
		ir->ID = "label";
		ir->PreFix = t->Name;
		ir->Flags |= _Start_Of_Label;
		if (t->Type == "export")
		{
			ir->PreFix = "export";
			ir->ID = t->Name;
		}
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
		//handle
		Token* T = new Token;
		T->Flags |= _Register_;
		T->Flags |= Task_For_Returning;
		T->Name = t->Name;
		T->Size = t->Size;
		Handle = T;
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
	// a = a + 1 + a
	// mov eax, [a]
	// add eax, 1
	// add eax, [a]
	// mov [a], eax
	//basic tools:
	Token* Left_Token = nullptr;
	Token* Right_Token = nullptr;
	bool Normal_Left = false;
	bool Normal_Right = false;
	//create a new IR token.
	IR* opCode = new IR;
	opCode->ID = t->Name;
	//give the new ir generator the left side of operation.
	Generator g;
	g.Input.push_back(t->Left_Side_Token);
	g.Factory();
	//save the information that the new generator gived.
	Append(&Output, g.Output);
	//check if left side holds a more complex instruction for loading into a register.
	if (g.Handle != nullptr)
		Left_Token = g.Handle;
	//if not then probably just a normal number/variable
	else
		Normal_Left = true;
	//now do the same but for right side.
	g.Input.clear();
	g.Handle = nullptr;
	g.Input.push_back(t->Right_Side_Token);
	g.Factory();
	//save the information gived by the generator yet again.
	Append(&Output, g.Output);
	//check if right side has more complex instruction.
	if (g.Handle != nullptr)
		Right_Token = g.Handle;
	//if normal right side.
	else
		Normal_Right = true;
	//check if this is a storing opcode:
	bool Storing = (t->Name == "=" || t->Name == "str");
	if (Normal_Left)
	{
		if (Storing)
		{
			Left_Token = t->Left_Side_Token;
		}
		else
		{
			//make a handle register
			Token* Reg = new Token;
			Reg->Flags |= Task_For_General_Purpose;
			Reg->Flags |= _Register_;
			Reg->Name = t->Left_Side_Token->Name;
			Reg->Size = t->Left_Side_Token->Size;
			Left_Token = Reg;
			//make the loading IR token
			IR* load = new IR;
			load->ID = "ldr";
			load->Parameters.push_back(Reg);
			load->Parameters.push_back(t->Left_Side_Token);
			Output.push_back(load);
		}
	}
	if (Normal_Right)
	{
		//make a handle register
		Token* Reg = new Token;
		Reg->Flags |= Task_For_General_Purpose;
		Reg->Flags |= _Register_;
		Reg->Name = t->Right_Side_Token->Name;
		Reg->Size = t->Right_Side_Token->Size;
		Right_Token = Reg;
		//make the loading IR token
		IR* load = new IR;
		load->ID = "ldr";
		load->Parameters.push_back(Reg);
		load->Parameters.push_back(t->Right_Side_Token);
		Output.push_back(load);
	}
	else
	{
		//somehting complex here:
	}
	opCode->Parameters.push_back(Left_Token);
	opCode->Parameters.push_back(Right_Token);
	Handle = Left_Token;
	Output.push_back(opCode);
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
			return;
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
