#include "../../H/Back/Generator.h"
#include "../../H/Selector/Selector.h"
extern Selector* S;
extern vector<string> Pre_Defined_Tokens;
extern int _SYSTEM_BIT_TYPE;
bool Double_Tasking = false;
int Personalize = 0;

void Generator::Factory()
{
	for (int i = 0; i < (int)Input.size(); i++)
	{
		//Detect_Prefixes(Input.at(i));
		Detect_Pointters(Input.at(i));
		Detect_Arrays(Input.at(i));
		Detect_Address_Pointing(Input.at(i));
		Detect_Condition(Input.at(i));
		Detect_Function(Input.at(i));
		Detect_Operator(Input.at(i));
		Detect_Parenthesis(Input.at(i));
		Detect_Pre_Defined_Tokens(Input.at(i));
		Initialize_Global_Variable(i);
	}
}

void Generator::Detect_Function(Token* t)
{
	if (t->is("type"))
		return;
	if (t->is(_Constructor_))
	{
		//make a label OpC*
		Detect_Prefixes(t);
		IR* ir = new IR;
		ir->ID = "label";
		ir->PreFix = t->Name;
		ir->add(_Start_Of_Label);
		Double_Tasking = false;
		//make the stackfrmae
		if (t->is(_Need_For_Space_))
		{
			Double_Tasking = true;
			//save ebp
			//stack base
			Token* ebp = new Token;
			ebp->Name = "ebp";
			ebp->Size = _SYSTEM_BIT_TYPE;
			ebp->add(_Register_);
			ebp->add(Task_For_Type_Address_Basing);
			//mov ebp, esp
			IR* push = new IR;
			push->ID = "push";
			push->Parameters.push_back(ebp);
			ir->Childs.push_back(push);
			//load the atm stack head
			//stack head
			Token* esp = new Token;
			esp->Name = "esp";
			esp->Size = _SYSTEM_BIT_TYPE;
			esp->add(_Register_);
			esp->add(Task_For_Type_Address);
			//mov ebp, esp
			IR* movebpesp = new IR;
			movebpesp->ID = "ldr";
			movebpesp->Parameters.push_back(ebp);
			movebpesp->Parameters.push_back(esp);
			ir->Childs.push_back(movebpesp);
			if (t->Reservable_Size > 0)
			{
				//make the register
				Token* esp = new Token;
				esp->add(_Register_);
				esp->add(Task_For_Type_Address);
				esp->Name = "reserve memory please!";
				esp->Size = _SYSTEM_BIT_TYPE;
				//make the number to subtract from esp
				Token* num = new Token;
				num->Name = to_string(t->Reservable_Size);
				num->Size = _SYSTEM_BIT_TYPE;
				num->add(_Number_);
				//make the IR token
				IR* space = new IR;
				space->ID = "-";
				space->Parameters.push_back(esp);
				space->Parameters.push_back(num);
				ir->Childs.push_back(space);
			}
		}
		//make the insights of this constructor
		Generator g;
		g.Input.push_back(t->Right_Side_Token);
		g.Types = this->Types;
		g.Factory();
		//get the output as the new IR's childs.
		Append(&ir->Childs, g.Output);
		Output.push_back(ir);
	}
	else if (t->is(_Call_))
	{
		//make a callation OpC*
		IR* ir = new IR;
		ir->ID = "call";
		//when we give the token call, (name) to it and in parser defined as
		//_External_ it can do something like this: call [banana] ; as a global variable.
		t->ID = Personalize++;
		ir->Parameters.push_back(t);

		for (Token* t : t->Left_Side_Token->Childs)
		{
			Generator g;
			g.Types = Types;
			g.Input.push_back(t);
			g.Factory();

			Append(&Output, g.Output);

			IR* push = new IR;
			push->ID = "push";

			if (g.Handle != nullptr) {
				push->Parameters.push_back(g.Handle);
			}
			else {
				push->Parameters.push_back(t);
			}
			Output.push_back(push);
		}
		//generate the parameters as IR tokens
		//Generator g;
		//g.Input.push_back(t->Left_Side_Token);
		//g.Types = this->Types;
		//g.Factory();
		//get the output from the generator and store then into the parent IR operator.
		//ir->Childs = g.Output;
		//make better reverser so that ur pointter loading wont be also reversed XD!!
		//reverse(g.Output.begin(), g.Output.end());
		//Append(&Output, g.Output);


		Output.push_back(ir);
		//handle
		Token* T = new Token;
		T->add(_Register_);
		T->add(Task_For_Returning);
		T->Name = t->Name;
		T->ID = t->ID;
		T->Size = _SYSTEM_BIT_TYPE;
		Handle = T;
		//check if this has init some objects so that we can reserve stack for it.
		if ((t->Reservable_Size > 0) && !t->is("loyal"))
		{
			//make the register
			Token* esp = new Token;
			esp->add(_Register_);
			esp->add(Task_For_Type_Address);
			esp->Name = "reserve memory please!";
			esp->Size = _SYSTEM_BIT_TYPE;
			//make the number to subtract from esp
			Token* num = new Token;
			num->Name = to_string(t->Reservable_Size);
			num->Size = _SYSTEM_BIT_TYPE;
			num->add(_Number_);
			//make the IR token
			IR* space = new IR;
			space->ID = "+";
			space->Parameters.push_back(esp);
			space->Parameters.push_back(num);
			Output.push_back(space);
		}
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
		Condition->add(_Start_Of_Label);
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
		Exit_Label->add(_End_Of_Label);
		Condition->Childs.push_back(Exit_Label);
		Output.push_back(Condition);
	}
}

void Generator::Scaler(Token* l, Token* r)
{
	if (l->is(_Number_))
	{
		if (l->Size < r->Size)
		{
			l->Size = r->Size;
		}
	}
	if (r->is(_Number_))
	{
		if (r->Size < l->Size)
		{
			r->Size = l->Size;
		}
	}
	if (r->_Dynamic_Size_)
	{
		r->Size = l->Size;
	}
	if (l->_Dynamic_Size_)
	{
		l->Size = r->Size;
	}
}

void Generator::Dodge(Token* l, Token* r)
{
	if (l->is(_Call_) && r->is(_Call_))
	{
		//create the Right side now and give the eax into ebx for dodging the left side calling
		Generator g;
		g.Input.push_back(new Token(*r));
		g.Types = Types;
		g.Factory();

		//save the calling
		Append(&Output, g.Output);

		//make the saving register
		Token* reg = new Token;
		reg->Name = r->Name + "_Saving_" + to_string(r->ID);
		reg->add(Task_For_General_Purpose);
		reg->add(_Register_);
		reg->Size = _SYSTEM_BIT_TYPE;

		//now g.Handle has the EAX
		//now save it into someother register
		IR* save = new IR;
		save->ID = "ldr";
		save->Parameters.push_back(reg);
		save->Parameters.push_back(g.Handle);
		Output.push_back(save);
		//now overwrite the existing calling convension by the newwly made register
		*r = *reg;
	}
}

void Generator::Initialize_Global_Variable(int i)
{
	Token* t = Input.at(i);
	if (t->is(_Initialized_))
	{
		Scaler(t, t->Initial_Value);
		IR* init = new IR;
		t->Initial_Value->add(_Locked_);
		init->Parameters.push_back(t->Initial_Value);
		if (t->Initial_Value->is(_String_))
		{
			init->ID = "makestring";
		}
		else if (t->Initial_Value->Size == 1)
		{
			init->ID = "db";
		}
		else if (t->Initial_Value->Size == 2)
		{
			init->ID = "dw";
		}
		else if (t->Initial_Value->Size == 4)
		{
			init->ID = "dd";
		}
		else if (t->Initial_Value->Size == 8)
		{
			init->ID = "dq";
		}
		else if (t->Initial_Value->Size == 12)
		{
			init->ID = "dt";
		}
		IR* label = new IR;
		label->PreFix = t->Name;
		label->ID = "raw_label";
		label->Childs.push_back(init);
		Output.push_back(label);
		Input.erase(Input.begin() + i);

		if (i < Input.size())
		{
			Token* t = Input.at(i);
			if (t->is(_Initialized_))
				Initialize_Global_Variable(i);
		}
	}
}

void Generator::Detect_Operator(Token* t)
{
	if (t->is(_Operator_) != true)
		return;
	if (t->is(_Generated_) == true)
		return;
	t->add(_Generated_);
	// a = a + 1 + a
	// mov eax, [a]
	// cvsi2sd xmm0, eax
	// mov [a], xmm0
	//basic tools:

	Scaler(t->Right_Side_Token, t->Left_Side_Token);

	Dodge(t->Left_Side_Token, t->Right_Side_Token);

	Token* Left_Token = nullptr;
	Token* Right_Token = nullptr;
	bool Normal_Left = false;
	bool Normal_Right = false;
	//now do the same but for right side.
	Generator g;
	g.Input.push_back(t->Right_Side_Token);
	g.Factory();
	//save the information gived by the generator yet again.
	Append(&Output, g.Output);
	//check if right side has more complex instruction.
	if (g.Handle != nullptr)
		Right_Token = g.Handle;
	//if normal right side.
	else if(!(t->Right_Side_Token->is(_Register_)))
		Normal_Right = true;
	else
	{
		Right_Token = t->Right_Side_Token;
	}
	//create a new IR token.
	IR* opCode = new IR;
	opCode->ID = t->Name;
	opCode->add(_Operator_);
	//give the new ir generator the left side of operation.
	g.Output.clear();
	g.Input.clear();
	g.Handle = nullptr;
	g.Input.push_back(t->Left_Side_Token);
	g.Factory();
	//save the information that the new generator gived.
	Append(&Output, g.Output);
	//check if left side holds a more complex instruction for loading into a register.
	if (g.Handle != nullptr)
		Left_Token = g.Handle;
	//if not then probably just a normal number/variable
	else if (!(t->Left_Side_Token->is(_Register_)))
		Normal_Left = true;
	else
	{
		Left_Token = t->Left_Side_Token;
	}
	//check if this is a storing opcode:
	bool Storing = (t->Name == "=" || t->Name == "str");
	//b:0 = a:0
	//lea edi, [(ebp-offset)+ecx*size]
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
			Reg->add(Task_For_General_Purpose);
			Reg->add(_Register_);
			Reg->Name = "Reg1_" + t->Left_Side_Token->Name;
			Reg->Size = t->Left_Side_Token->Size;
			Left_Token = Reg;
			//make the loading IR token
			IR* load = new IR;
			load->ID = "ldr";
			load->Parameters.push_back(new Token(*Reg));
			load->Parameters.push_back(new Token(*t->Left_Side_Token));
			Output.push_back(load);
			//more check if the destination is too big for the loaded register, in Emulator
		}
	}
	if (Normal_Right)
	{
		//make a handle register
		Token* Reg = new Token;
		Reg->add(Task_For_General_Purpose);
		Reg->add(_Register_);
		Reg->Name = "Reg2_" + t->Right_Side_Token->Name;
		Reg->Size = t->Right_Side_Token->Size;
		Right_Token = Reg;
		//make the loading IR token
		IR* load = new IR;
		load->ID = "ldr";
		load->Parameters.push_back(new Token(*Reg));
		load->Parameters.push_back(new Token(*t->Right_Side_Token));
		Output.push_back(load);
	}
	opCode->Parameters.push_back(new Token(*Left_Token));
	opCode->Parameters.push_back(new Token(*Right_Token));
	Handle = Left_Token;
	Output.push_back(opCode);
}

void Generator::Detect_Pointters(Token* t)
{
	//a::0 --> mov reg, [a] --> mov reg2, [reg+0]
	//a::0 == _Pointing_

	//a:0 --> mov reg, [a+0]
	//a:0 == _Array_
	if (t->Offsetter == nullptr)
		return;
	if (!t->is(_Pointting_))
		return;
	Token* tmp_t = new Token;
	*tmp_t = *t;
	//empty the offsetter from tmp
	tmp_t->Offsetter = nullptr;
	Token* Offsetter = new Token;

	Scaler(t, t->Offsetter);
	//load the Offsetter into a reg or if number stay number.
	Generator g;
	g.Input.clear();
	g.Output.clear();
	g.Types = Types;

	g.Input.push_back(t->Offsetter);
	g.Factory();
	Append(&Output, g.Output);
	if (g.Handle != nullptr)
		//a::(a:b) --> more complex
		*Offsetter = *g.Handle;
	else if (!t->Offsetter->is(_Number_)) {
		//a::a --> more simpler offsetter
		//setup the offsetter token to be the handle for the variable loading
		Offsetter->add(_Register_);
		Offsetter->add(Task_For_General_Purpose);
		Offsetter->Name = t->Offsetter->Name + "_Offsetted_Handle_Reg";
		//load the variable into a rgister
		IR* load = new IR;
		load->ID = "ldr";
		load->Parameters.push_back(Offsetter);
		load->Parameters.push_back(t->Offsetter);
		Output.push_back(load);
	}
	else
		//a::0 --> just a number offsetter in other words no need to do enything.
		*Offsetter = *t->Offsetter;
	//now load the main variable:
	Token* Offsetter_Register = new Token;
	Offsetter_Register->add(_Register_);
	Offsetter_Register->add(Task_For_General_Purpose);
	Offsetter_Register->Name = t->Name + "_Offsetter_Reg";
	Offsetter_Register->Size = t->Size;

	//mov sec_reg, [a]
	IR* load_Secondary = new IR;
	load_Secondary->ID = "ldr";
	//make a copy so that when we add the offsetter it doesnt explode :D
	load_Secondary->Parameters.push_back(new Token(*Offsetter_Register));
	load_Secondary->Parameters.push_back(tmp_t);

	Output.push_back(load_Secondary);

	//now load the main, from secondary handle + offsetter
	//mov reg, [sec_reg+offsetter]
	Token* Main_Handle = new Token;
	Main_Handle->add(_Register_);
	Main_Handle->add(Task_For_General_Purpose);
	Main_Handle->Name = t->Name + "_main_Handle_reg";
	Main_Handle->Size = t->Size;

	Offsetter_Register->Offsetter = Offsetter;
	Offsetter_Register->add(_Pointting_);

	//make the initial mov
	IR* Main_Load = new IR;
	Main_Load->ID = "ldr";
	Main_Load->Parameters.push_back(Main_Handle);
	Main_Load->Parameters.push_back(Offsetter_Register);

	Output.push_back(Main_Load);

	Handle = Main_Handle;
}

void Generator::Detect_Arrays(Token* t)
{
	//a:0 --> mov reg, [(ebp-4) + offsetter]
	if (!t->is(_Array_))
		return;
	if (t->Offsetter == nullptr)
		return;
	//make the offsetter handle
	Token* Offsetter = new Token;

	Scaler(t, t->Offsetter);
	//load the Offsetter into a reg or if number stay number.
	Generator g;
	g.Input.clear();
	g.Output.clear();
	g.Types = Types;

	g.Input.push_back(t->Offsetter);
	g.Factory();
	Append(&Output, g.Output);
	if (g.Handle != nullptr)
		//a:(a:b) --> more complex
		*Offsetter = *g.Handle;
	else if (!t->Offsetter->is(_Number_)) {
		//a:a --> more simpler offsetter
		//setup the offsetter token to be the handle for the variable loading
		Offsetter->add(_Register_);
		Offsetter->add(Task_For_General_Purpose);
		Offsetter->Name = t->Offsetter->Name + "_Offsetted_Handle_Reg";
		//load the variable into a rgister
		IR* load = new IR;
		load->ID = "ldr";
		load->Parameters.push_back(Offsetter);
		load->Parameters.push_back(t->Offsetter);
		Output.push_back(load);
	}
	else
		//a:0 --> just a number offsetter in other words no need to do enything.
		*Offsetter = *t->Offsetter;

	//set the original offsetter into the new one
	t->Offsetter = Offsetter;

	//make the returning handle register
	Token* Main_Handle = new Token;
	Main_Handle->add(_Register_);
	Main_Handle->add(Task_For_General_Purpose);
	Main_Handle->Size = t->Size;
	Main_Handle->Name = t->Name + "_Main_Handle";

	//make the main load
	IR* Main_Load = new IR;
	Main_Load->ID = "ldr";
	Main_Load->Parameters.push_back(Main_Handle);
	Main_Load->Parameters.push_back(new Token(*t));

	Output.push_back(Main_Load);

	Handle = Main_Handle;
}

void Generator::Detect_Address_Pointing(Token* t)
{
	//@a
	if (t->is(_Giving_Address_) != true) return;
	//lea eax, [ebp -4 + ecx]
	//eax
	//make a token reg for to handle future of the pointers usage.
	Token* Reg = new Token;
	Reg->Name = t->Name;
	Reg->Size = t->Size;
	Reg->add(Task_For_General_Purpose);
	Reg->add(_Register_);

	IR* lea = new IR;
	lea->ID = ":";
	lea->Parameters.push_back(Reg);
	lea->Parameters.push_back((new Token(*t)));
	*t = *Reg;
	Output.push_back(lea);
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
		Handle = g.Handle;
		if ((t->Childs.size() == 1) && (t->Childs.at(0)->is(_Operator_) == false) && (Handle == nullptr))
		{
			Handle = t->Childs.at(0);
		}
	}
}

void Generator::Detect_Pre_Defined_Tokens(Token* t)
{
	for (string T : Pre_Defined_Tokens)
	{
		if (t->is(T))
		{
			IR *ir = new IR;
			ir->ID = T;
			Generator g;
			g.Input.push_back(t->Right_Side_Token);
			g.Factory();
			Append(&Output, g.Output);
			if (g.Handle != nullptr)
			{
				ir->Parameters.push_back(g.Handle);
			}
			else
			{
				ir->Parameters.push_back(t->Right_Side_Token);
			}
			if (Double_Tasking)
				ir->add(_Double_Task_);
			Output.push_back(ir);
			return;
		}
	}
}

void Generator::Detect_Prefixes(Token* t)
{
	for (string s: t->Types) {
		if (s == "Hidden")
			return;
		if (s == "type" || s == "func" || s == "loyal")
			continue;
		IR* ir = new IR;
		ir->PreFix = s;
		ir->ID = t->Name;
		Output.push_back(ir);
	}
}

void Generator::Append(vector<IR*> *Dest, vector<IR*> Source)
{
	for (IR* i : Source)
	{
		Dest->push_back(i);
	}
}
