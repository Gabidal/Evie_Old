#include "../../H/BackEnd/BackEnd.h"
#include "..\..\H\BackEnd\IRGenerator.h"
#include "../../H/BackEnd/Selector.h"

extern Selector* selector;

void IRGenerator::Factory()
{
	for (int i = 0; i < Input.size(); i++)
		Un_Wrap_Inline(i);
	for (int i = 0; i < Input.size(); i++) {
		Parse_Function(i);
	}
	for (int i = 0; i < Input.size(); i++) {
		Parse_If(i);
		Parse_Loops(i);
		Parse_Arrays(i);
		Parse_Calls(i);
		Parse_Operators(i);
		Parse_Pointers(i);
		Parse_Jumps(i);
		Parse_PostFixes(i);
		Parse_PreFixes(i);
		Parse_Return(i);
	}
}

void IRGenerator::Parse_Function(int i)
{
	if (!Input[i]->is(FUNCTION_NODE))
		return;
	for (auto j : Input[i]->Parameters)
		if (j->is("type") != -1)
			return;	//skip template functions.

	Output->push_back(new IR(new Token(TOKEN::START_OF_FUNCTION, Input[i]->Name), {}));

	//label
	Output->push_back(Make_Label(Input[i]));

	//go through the childs of the function
	IRGenerator g(Input[i], Input[i]->Childs, Output);

	//TODO: Make the return IR here
	Token* ret = new Token(TOKEN::FLOW, "return");
	ret->Set_Parent(Global_Scope->Find(Input[i]->Name));
	Output->push_back(new IR(ret, {}));

	//make the end of funciton like End Proc like label
	Output->push_back(new IR(new Token(TOKEN::END_OF_FUNCTION), {}));
}

void IRGenerator::Parse_Calls(int i)
{
	if (!Input[i]->is(CALL_NODE))
		return;

	IRGenerator g(Parent, Output);
	//do the parameters
	//no ur wrong m8!
	//the IRPostprosessor takes care of the parameters here (:
	//nah why dont do it here? :)
	//ok. (:
	int Number_Register_Count = 0;
	int MAX_Number_Register_Count = selector->Get_Numerical_Parameter_Register_Count();
	int Float_Register_Count = 0;
	int MAX_Floating_Register_Count = selector->Get_Floating_Parameter_Register_Count();

	//to push everything currectly
	vector<Token*> Reversable_Pushes;

	//for selector to understand a more abstract picture of the whole parameters.
	vector<Token*> All_Parameters;

	int Parameter_Place = 0;
	for (Node* n : Input[i]->Parameters) {
		g.Generate({ n });

		Token* p;
		//handle complex instructions
		if (g.Handle != nullptr)
			p = g.Handle;
		else
			p = new Token(n);

		if (n->Has_Floating_Point_Value) {
			if (Float_Register_Count < MAX_Floating_Register_Count) {
				//use a parameter register
				Token* reg = new Token(TOKEN::PARAMETER | TOKEN::REGISTER | TOKEN::DECIMAL, "REG_" + p->Get_Name() + "_Parameter", p->Get_Size());
				reg->Parameter_Index = Parameter_Place;
				Token* opc = new Token(TOKEN::OPERATOR, "move");
				//make the parameter move
				IR* ir = new IR(opc, { reg, p });
				Output->push_back(ir);
				Float_Register_Count++;
				All_Parameters.push_back(reg);
			}
			else {
				//use stack
				//check is n is a complex
				if (p->is(TOKEN::REGISTER) || p->is(TOKEN::NUM)) {
					//is complex
					Reversable_Pushes.push_back(p);
					All_Parameters.push_back(p);
				}
				else if (p->is(TOKEN::MEMORY)) {
					//is non-complex variable
					//use a any tmp register
					Token* reg = new Token(TOKEN::REGISTER | TOKEN::DECIMAL, "REG_" + p->Get_Name() + "_tmp", p->Get_Size());
					Token* opc = new Token(TOKEN::OPERATOR, "move");
					//make the tmp move
					IR* ir = new IR(opc, { reg, p });
					Output->push_back(ir);
					//now give the tmp register to reversible pushbacker
					Reversable_Pushes.push_back(reg);
					All_Parameters.push_back(reg);
				}
			}
		}
		else {
			if (Number_Register_Count < MAX_Number_Register_Count) {
				//use a parameter register
				Token* reg = new Token(TOKEN::PARAMETER | TOKEN::REGISTER, "REG_" + p->Get_Name() + "_Parameter", p->Get_Size());
				reg->Parameter_Index = Parameter_Place;
				Token* opc = new Token(TOKEN::OPERATOR, "move");
				//make the parameter move
				IR* ir = new IR(opc, { reg, p });
				Output->push_back(ir);
				Number_Register_Count++;
				All_Parameters.push_back(reg);
			}
			else {
				//use stack
				//check is n is a complex
				if (p->is(TOKEN::REGISTER) || p->is(TOKEN::NUM)) {
					//is complex
					Reversable_Pushes.push_back(p);
					All_Parameters.push_back(p);
				}
				else if (p->is(TOKEN::MEMORY)) {
					//is non-complex variable
					//use a any tmp register
					Token* reg = new Token(TOKEN::REGISTER, "REG_" + p->Get_Name() + "_tmp", p->Get_Size());
					Token* opc = new Token(TOKEN::OPERATOR, "move");
					//make the tmp move
					IR* ir = new IR(opc, { reg, p });
					Output->push_back(ir);
					//now give the tmp register to reversible pushbacker
					Reversable_Pushes.push_back(reg);
					All_Parameters.push_back(reg);
				}
			}
		}
		Parameter_Place++;
	}

	//reverse(Reversable_Pushes.begin(), Reversable_Pushes.end());

	Node* Parent = Global_Scope->Get_Parent_As(FUNCTION_NODE, Input[i]);

	int allocation = 0;
	for (auto p : Reversable_Pushes) {
		allocation += p->Get_Size();
	}

	if (Parent->Max_Allocation_Space < allocation)
		Parent->Max_Allocation_Space = allocation;

	int Stack_Offset = 0;
	for (auto p : Reversable_Pushes) {
		Output->push_back(new IR(new Token(TOKEN::OPERATOR, "="), {
			new Token(TOKEN::MEMORY, {
				new Token(TOKEN::OFFSETTER, "+", new Token(TOKEN::STACK_POINTTER | TOKEN::REGISTER, _SYSTEM_BIT_SIZE_), new Token(TOKEN::NUM, to_string(Stack_Offset)))
				}, p->Get_Size(), p->Get_Name()),
			p
			}));
		Stack_Offset += p->Get_Size();
	}

	Token* call = new Token(TOKEN::CALL, "call", All_Parameters);
	IR* ir = new IR(call, { new Token(TOKEN::LABEL, Input[i]->Name) });

	Output->push_back(ir);

	//int De_Allocate_Size = 0;
	//for (auto j : Reversable_Pushes) {
	//	De_Allocate_Size += j->Get_Size();
	//}

	//selector->DeAllocate_Stack(De_Allocate_Size, Output, Output->size());

	Node* tmp = Global_Scope->Find(Input[i], Global_Scope);
	tmp->Update_Size_By_Inheritted();

	Token* returningReg = new Token(TOKEN::REGISTER | TOKEN::RETURNING, "RetREG_" + call->Get_Name(), tmp->Size);

	Handle = returningReg;
}

void IRGenerator::Parse_If(int i)
{
	if (!Input[i]->is(IF_NODE))
		return;

	//check next condition goto it else goto check this condition then goto end
	//cmp eax, ecx		;1 != a
	//je L1
	//..
	//jmp L3
	//L1:
	//cmp eax, ebx		;1 == b
	//jne L2
	//..
	//jmp L3
	//L2:
	//..
	//L3:
	//do parameters
	Loop_Elses(Input[i]);
}

void IRGenerator::Loop_Elses(Node* e)
{

	//the if/else label
	Node* tmp = new Node(e->Name);
	Output->push_back(Make_Label(tmp));

	//do an subfunction that can handle coditions and gets the label data for the condition data from the Parent given.
	IRGenerator p(e, e->Parameters, Output);
	//then do childs
	IRGenerator c(e, e->Childs, Output);

	if (e->Succsessor != nullptr) {
		//get the last successor name
		Node* s = e->Succsessor;
		while (true) {
			if (s->Succsessor == nullptr)
				break;	//s is now last
			s = s->Succsessor;
		}
		//the end of every conditon to true fall to
		Output->push_back(Make_Jump("jump", s->Name + "_END"));

		//skip the last end jump if the condition is not met
		Node* tmp = new Node(e->Name + "_END");
		Output->push_back(Make_Label(tmp));

		//now construct the successor
		Loop_Elses(e->Succsessor);
	}
	else {
		Node* tmp = new Node(e->Name + "_END");
		Output->push_back(Make_Label(tmp));
	}

}

void IRGenerator::Parse_Jumps(int i)
{
	//NOTICE: this must happen after all operator is created as IR!!!
	if (!Input[i]->is(CONDITION_OPERATOR_NODE))
		return;
	if (!Parent->is(IF_NODE) && !Parent->is(ELSE_IF_NODE) && !Parent->is(WHILE_NODE))
		// a = b * c < d
		//...
		return;
	/*
	int Level_Difference = (int)labs(Get_Amount("ptr", Input[i]->Left) - Get_Amount("ptr", Input[i]->Right));
	if (Level_Difference != 0)
		return;

	// if (a == 1)
	//give the right side as left side to IRGenerator
	IRGenerator g(Parent, { Input[i]->Right }, Output);

	Token* Right = nullptr;
	Token* Left = nullptr;

	if (g.Handle != nullptr)
		Right = g.Handle;
	else {
		//move to register
		Token* R = new Token(Input[i]->Right->Find(Input[i]->Right, Input[i]->Right->Parent));
		if (R->is(TOKEN::CONTENT))
			R = new Token(TOKEN::MEMORY, { R }, _SYSTEM_BIT_SIZE_);

		Token* Reg = new Token(TOKEN::REGISTER, "REG_" + R->Get_Name(), R->Get_Size());

		Token* opc = new Token(TOKEN::OPERATOR, "move");

		IR* ir = new IR(opc, { Reg, R });
		Output->push_back(ir);

		Right = Reg;
	}

	g.Generate({ Input[i]->Left});

	if (g.Handle != nullptr)
		Left = g.Handle;
	else {		
		//move to register
		Token* L = new Token(Input[i]->Left->Find(Input[i]->Left, Input[i]->Left->Parent));
		if (L->is(TOKEN::CONTENT))
			L = new Token(TOKEN::MEMORY, { L }, _SYSTEM_BIT_SIZE_);

		Token* Reg = new Token(TOKEN::REGISTER, "REG_" + L->Get_Name(), L->Get_Size());

		Token* opc = new Token(TOKEN::OPERATOR, "move");

		IR* ir = new IR(opc, { Reg, L });
		Output->push_back(ir);

		Left = Reg;
	}

	Token* cmp = new Token(TOKEN::OPERATOR, "compare");

	IR* ir = new IR(cmp, { Left, Right });
	Output->push_back(ir);
	*/
	string Next_Label = Parent->Name + "_END";
	if (Parent->Succsessor != nullptr)
		Next_Label = Parent->Succsessor->Name;

	//jmp if not correct
	Output->push_back(Make_Jump(Get_Inverted_Condition(Input[i]->Name), Next_Label));
}

void IRGenerator::Un_Wrap_Inline(int i)
{
	if (!(Input[i]->Header.size() > 0))
		return;

	IRGenerator g(Parent, Input[i]->Header, Output);
}

void IRGenerator::Parse_Operators(int i)
{
	if (!Input[i]->is(OPERATOR_NODE) && !Input[i]->is(BIT_OPERATOR_NODE) && !Input[i]->is(ASSIGN_OPERATOR_NODE) && !Input[i]->is(CONDITION_OPERATOR_NODE))
		return;

	Update_Operator(Input[i]);
	//If this operator is handling with pointters we cant use general operator handles
	int Level_Difference = (int)labs(Get_Amount("ptr", Input[i]->Left) - Get_Amount("ptr", Input[i]->Right));
	if (Level_Difference != 0)
		return;

	Token* Left = nullptr;
	Token* Right = nullptr;

	IRGenerator g(Parent, { Input[i]->Left }, Output, Input[i]->is(ASSIGN_OPERATOR_NODE));

	if (g.Handle != nullptr)
		Left = g.Handle;
	else {
		if (Input[i]->Name == "=") {
			//dont load the value into a register
			Left = new Token(Input[i]->Left);
			if (Left->is(TOKEN::CONTENT))
				Left = new Token(TOKEN::MEMORY, { Left }, Input[i]->Find(Input[i]->Left, Input[i]->Left->Parent)->Get_Size());
			//else if (Left->is(TOKEN::REGISTER) || Left->is(TOKEN::PARAMETER))
			//	Left = Left; //:D no need to do enything
		}
		else if (!Input[i]->Left->is(NUMBER_NODE) && !Input[i]->Left->is(PARAMETER_NODE) && !Input[i]->is(CONDITION_OPERATOR_NODE)) {
			Token* L = new Token(Input[i]->Left->Find(Input[i]->Left, Input[i]->Left->Parent));
			if (L->is(TOKEN::CONTENT))
				L = new Token(TOKEN::MEMORY, { L }, L->Get_Size(), L->Get_Name());

			Token* Reg = new Token(TOKEN::REGISTER, "REG_" + L->Get_Name(), L->Get_Size());
			//create the IR
			Token* Opc = new Token(TOKEN::OPERATOR, "move");
			IR* ir = new IR(Opc, { Reg, L });

			Left = Reg;
			Output->push_back(ir);
		}
		else {
			Left = new Token(Input[i]->Left);
		}
	}

	g.Generate({ Input[i]->Right });

	bool Is_Parameter_Register = false;
	if (Input[i]->Right->is(PARAMETER_NODE)) {
		//check if the parameter is held in a register or not
		if (Token(Input[i]->Right).is(TOKEN::REGISTER))
			Is_Parameter_Register = true;
	}

	if (g.Handle != nullptr)
		Right = g.Handle;
	else if (!Input[i]->Right->is(NUMBER_NODE) && !Is_Parameter_Register) {
		Token* R = new Token(Input[i]->Right->Find(Input[i]->Right, Input[i]->Right->Parent));
		if (R->is(TOKEN::CONTENT))
			R = new Token(TOKEN::MEMORY, { R }, R->Get_Size(), R->Get_Name());

		Token* Reg = new Token(TOKEN::REGISTER, "REG_" + R->Get_Name(), R->Get_Size());
		//create the IR
		Token* Opc = new Token(TOKEN::OPERATOR, "move");
		IR* ir = new IR(Opc, { Reg, R });

		Right = Reg;
		Output->push_back(ir);
	}
	else {
		Right = new Token(Input[i]->Right);
		//Right = new Token(TOKEN::NUM, Input[i]->Right->Name, 4);
	}
	


	string Operator = Input[i]->Name;
	//this translates the condition operator into a compare operation then the parse_jumps,
	//will use the condition name to do the correct jump.
	if (Input[i]->is(CONDITION_OPERATOR_NODE))
		Operator = "compare";

	Token* Opcode = new Token(TOKEN::OPERATOR, Operator);

	IR* ir = new IR(Opcode, {Left, Right});

	Handle = Left;
	Output->push_back(ir);
}

void IRGenerator::Parse_Pointers(int i)
{
	//int a = 0
	//int ptr b = a + f - e / g get the address of memory
	//int ptr c = b pass memory address of a to c
	//int d = c		load value of a into c

	if (!Input[i]->is(OPERATOR_NODE) && !Input[i]->is(CONDITION_OPERATOR_NODE) && !Input[i]->is(BIT_OPERATOR_NODE) && !Input[i]->is(ASSIGN_OPERATOR_NODE))
		return;

	Update_Operator(Input[i]);

	int Level_Difference = (int)labs(Get_Amount("ptr", Input[i]->Left) - Get_Amount("ptr", Input[i]->Right));
	if (Level_Difference == 0)
		return;

	Token* Right = nullptr;
	Token* Left = nullptr;
	
	//handle complex Right
	IRGenerator g(Parent, { Input[i]->Right }, Output);
	if (g.Handle != nullptr)
		Right = g.Handle;
	else
		Right = new Token(Input[i]->Right);

	//handle complex Left
	g.Generate({ Input[i]->Left }, Input[i]->is(ASSIGN_OPERATOR_NODE));
	if (g.Handle != nullptr)
		Left = g.Handle;
	else
		Left = new Token(Input[i]->Left);

	Update_Operator(Input[i]);

	int Left_Level = Get_Amount("ptr", Input[i]->Left);
	int Right_Level = Get_Amount("ptr", Input[i]->Right);

	if (Left_Level == Right_Level) {
		//this means some part was apointer but also a array so it is no more because its unwrapped already.
		Parse_Operators(i);
		return;
	}
	if (Left_Level > Right_Level) {
		//here left has more ptr init check this is assignment
		if (Input[i]->is(ASSIGN_OPERATOR_NODE) && !Right->is(TOKEN::NUM) && !Input[i]->Right->is(OPERATOR_NODE)) {
			//save the address of Right into Left
			Token* reg = new Token(TOKEN::REGISTER, Right->Get_Name() + "_REG", _SYSTEM_BIT_SIZE_);

			Token* Right_Mem = new Token(TOKEN::MEMORY, { Right }, _SYSTEM_BIT_SIZE_, Right->Get_Name());

			Output->push_back(new IR(new Token(TOKEN::OPERATOR, "evaluate"), { new Token(*reg), Right_Mem }));
			Right = reg;
		}
		else {
			int Keep_Last_Address = 0;
			if (Input[i]->is(ASSIGN_OPERATOR_NODE))
				Keep_Last_Address = 1;
			Left = Operate_Pointter(Left, Level_Difference - Keep_Last_Address);
			if (Input[i]->is(ASSIGN_OPERATOR_NODE))
				Left = new Token(TOKEN::MEMORY, { Left }, _SYSTEM_BIT_SIZE_);
		}

		if (Right->is(TOKEN::CONTENT)) {
			//handle the other side into a usable register
			Right = new Token(TOKEN::MEMORY, { Right }, Input[i]->Find(Right->Get_Name(), Right->Get_Parent())->Get_Size());
		}
	}
	else if (Left_Level < Right_Level) {
		Right = Operate_Pointter(Right, Level_Difference);
		if (Left->is(TOKEN::CONTENT)) {
				//handle the other side into a usable register
				Left = new Token(TOKEN::MEMORY, { Left }, Input[i]->Find(Left->Get_Name(), Left->Get_Parent())->Get_Size());
			}
	}

	string Operator = Input[i]->Name;
	//this translates the condition operator into a compare operation then the parse_jumps,
	//will use the condition name to do the correct jump.
	if (Input[i]->is(CONDITION_OPERATOR_NODE))
		Operator = "compare";
	Output->push_back(new IR(new Token(TOKEN::OPERATOR, Operator), { Left, Right }));
}

void IRGenerator::Parse_Arrays(int i)
{
	if (!Input[i]->is(ARRAY_NODE))
		return;

	Token* Left = nullptr;
	Token* Right = nullptr;

	//the left side contains the owner from the offsetting happends
	IRGenerator g(Parent, { Input[i]->Left }, Output);
	if (g.Handle != nullptr)
		Left = g.Handle;
	else
		Left = new Token(Input[i]->Left);

	//how parser array ast is buildt
	//x[123, 123][123, 123]
	//((x, {123, 123}), {123, 123})
	//((x, 123), 123)
	//x, 123
	if (Input[i]->Right->Childs.size() > 1) {
		//this is where the 2D array operators are constructed.
		vector<string> Type_Trace = Input[i]->Find(Left->Get_Name(), Left->Get_Parent())->Inheritted;
		//reverse(Type_Trace.begin(), Type_Trace.end());
		//int,[ptr, ptr]
		//x	  [123, 123]
		Token* handle = new Token(TOKEN::MEMORY, { Left}, _SYSTEM_BIT_SIZE_, Left->Get_Name());
		Token* reg = nullptr;
		for (int o = 0; o < Input[i]->Right->Childs.size(); o++) {
			/*int Current_Size = Global_Scope->Find(Type_Trace[Type_Trace.size()-1 - o], Global_Scope)->Get_Size();
			for (int tmp = Type_Trace.size() - 1 - o; tmp >= 0; tmp--) {
				if (Type_Trace[tmp] == "ptr") {
					Current_Size = _SYSTEM_BIT_SIZE_;
					break;
				}
				else
					Current_Size += Global_Scope->Find(Type_Trace[tmp], Global_Scope)->Get_Size();
			}*/
			
			int Scale = 0;
			//calculate the current size and the next size for the scaling.
			for (int tmp = Type_Trace.size() - 1 - o; tmp >= 0; tmp--) {
				if (Type_Trace[tmp] == "ptr") {
					Scale = _SYSTEM_BIT_SIZE_;
					break;
				}
				else
					Scale += Global_Scope->Find(Type_Trace[tmp], Global_Scope)->Get_Size();
			}

			int Next_Register_Size = 0;
			if (Is_In_Left_Side_Of_Operator)
				Next_Register_Size = _SYSTEM_BIT_SIZE_;
			else
				for (int tmp = Type_Trace.size() - 2 - o; tmp >= 0; tmp--) {
					if (Type_Trace[tmp] == "ptr") {
						Next_Register_Size = _SYSTEM_BIT_SIZE_;
						break;
					}
					else
						Next_Register_Size += Global_Scope->Find(Type_Trace[tmp], Global_Scope)->Get_Size();
				}

			int Next_Scaler_Size = 0;
			for (int tmp = Type_Trace.size() - 2 - o; tmp >= 0; tmp--) {
				if (Type_Trace[tmp] == "ptr") {
					Next_Scaler_Size = _SYSTEM_BIT_SIZE_;
					break;
				}
				else
					Next_Scaler_Size += Global_Scope->Find(Type_Trace[tmp], Global_Scope)->Get_Size();
			}

			reg = new Token(TOKEN::REGISTER, handle->Get_Name() + "_REG", Next_Register_Size);

			//parse through the Right childs for something complex.
			g.Generate({ Input[i]->Right->Childs[o] });

			if (g.Handle != nullptr)
				Right = g.Handle;
			else
				Right = new Token(Input[i]->Right->Childs[o]);

			if (Input[i]->Right->Childs[o]->is("ptr") != -1)
				//								//unload all ptr layers
				Right = Operate_Pointter(Right, Get_Amount("ptr", Input[i]->Right->Childs[o]), true);
			else if (Right->is(TOKEN::CONTENT)) {
				//load variable into a register
				Output->push_back(new IR(new Token(TOKEN::OPERATOR, "="), {
					new Token(TOKEN::REGISTER, Right->Get_Name() + "_REG", _SYSTEM_BIT_SIZE_),
					new Token(TOKEN::MEMORY, {Right}, _SYSTEM_BIT_SIZE_, Right->Get_Name())
					}));
				Right = new Token(TOKEN::REGISTER, Right->Get_Name() + "_REG", _SYSTEM_BIT_SIZE_);
			}

			//if this is not the last register it must be _SYSTEM_BIT_SIZE:d
			if (Right->is(TOKEN::REGISTER)) {
				if (o + 1 < Input[i]->Right->Childs.size())
					Right->Set_Size(_SYSTEM_BIT_SIZE_);
			}

			Token* Offsetter = new Token(TOKEN::OFFSETTER, "+");
			Offsetter->Left = handle->Get_Childs()->back();
			Offsetter->Right = Right;

			Token* Scaler = new Token(TOKEN::SCALER, "*");
			Scaler->Left = Offsetter;
			Scaler->Right = new Token(TOKEN::NUM, to_string(Next_Scaler_Size));

			string Load_Type = "=";
			if (Is_In_Left_Side_Of_Operator && o+1 >= Input[i]->Right->Childs.size())
				Load_Type = "evaluate";	//this happends when it is the last load and it is left side of a assign

			Output->push_back(new IR(new Token(TOKEN::OPERATOR, Load_Type), {reg, new Token(TOKEN::MEMORY, {Scaler}, Next_Register_Size) }));
		
			handle->Get_Childs()->back() = reg;
			handle->Set_Name(reg->Get_Name());
			handle->Set_Size(Next_Register_Size);
		}

		//calculate the resulting size
		int Reg_Size = 0;
		for (int tmp = (Type_Trace.size() - Input[i]->Right->Childs.size()) - 1; tmp >= 0; tmp--) {
			if (Type_Trace[tmp] == "ptr") {
				Reg_Size = _SYSTEM_BIT_SIZE_;
				break;
			}
			else
				Reg_Size += Global_Scope->Find(Type_Trace[tmp], Global_Scope)->Get_Size();
		}
		//get the remained inhertited types and set them for next to use
		vector<string> New_Inheritted;
		for (int tmp = (Type_Trace.size() - Input[i]->Right->Childs.size()) - 1; tmp >= 0; tmp--) {
			New_Inheritted.push_back(Type_Trace[tmp]);
		}

		Input[i]->Inheritted = New_Inheritted;

		if (Is_In_Left_Side_Of_Operator)
			Handle = new Token(TOKEN::MEMORY, { reg }, Reg_Size);
		else
			Handle = reg;
	}
	else {
		//this is where the 2D array operators are constructed.
		vector<string> Type_Trace = Input[i]->Find(Left->Get_Name(), Left->Get_Parent())->Inheritted;
		//reverse(Type_Trace.begin(), Type_Trace.end());
		//int,[ptr, ptr]
		//x	  [123, 123]
		Token* handle = new Token(TOKEN::MEMORY, { Left }, _SYSTEM_BIT_SIZE_, Left->Get_Name());
		Token* reg = nullptr;
		int Scale = 0;
		//calculate the current size and the next size for the scaling.
		for (int tmp = Type_Trace.size() - 1; tmp >= 0; tmp--) {
			if (Type_Trace[tmp] == "ptr") {
				Scale = _SYSTEM_BIT_SIZE_;
				break;
			}
			else
				Scale += Global_Scope->Find(Type_Trace[tmp], Global_Scope)->Get_Size();
		}

		int Next_Register_Size = 0;
		if (Is_In_Left_Side_Of_Operator)
			Next_Register_Size = _SYSTEM_BIT_SIZE_;
		else
			for (int tmp = Type_Trace.size() - 2; tmp >= 0; tmp--) {
				if (Type_Trace[tmp] == "ptr") {
					Next_Register_Size = _SYSTEM_BIT_SIZE_;
					break;
				}
				else
					Next_Register_Size += Global_Scope->Find(Type_Trace[tmp], Global_Scope)->Get_Size();
			}

		int Next_Scaler_Size = 0;
		for (int tmp = Type_Trace.size() - 2; tmp >= 0; tmp--) {
			if (Type_Trace[tmp] == "ptr") {
				Next_Scaler_Size = _SYSTEM_BIT_SIZE_;
				break;
			}
			else
				Next_Scaler_Size += Global_Scope->Find(Type_Trace[tmp], Global_Scope)->Get_Size();
		}

		reg = new Token(TOKEN::REGISTER, handle->Get_Name() + "_REG", Next_Register_Size);

		//parse through the Right childs for something complex.
		g.Generate({ Input[i]->Right });

		if (g.Handle != nullptr)
			Right = g.Handle;
		else
			Right = new Token(Input[i]->Right);

		if (Input[i]->Right->is("ptr") != -1)
			//								//unload all ptr layers
			Right = Operate_Pointter(Right, Get_Amount("ptr", Input[i]->Right), true);
		else if (Right->is(TOKEN::CONTENT)) {
			//load variable into a register
			Output->push_back(new IR(new Token(TOKEN::OPERATOR, "="), {
				new Token(TOKEN::REGISTER, Right->Get_Name() + "_REG", _SYSTEM_BIT_SIZE_),
				new Token(TOKEN::MEMORY, {Right}, _SYSTEM_BIT_SIZE_, Right->Get_Name())
				}));
			Right = new Token(TOKEN::REGISTER, Right->Get_Name() + "_REG", _SYSTEM_BIT_SIZE_);
		}
		if (Right->is(TOKEN::REGISTER))
			Right->Set_Size(_SYSTEM_BIT_SIZE_);

		Token* Offsetter = new Token(TOKEN::OFFSETTER, "+");
		Offsetter->Left = handle->Get_Childs()->back();
		Offsetter->Right = Right;

		Token* Scaler = new Token(TOKEN::SCALER, "*");
		Scaler->Left = Offsetter;
		Scaler->Right = new Token(TOKEN::NUM, to_string(Next_Scaler_Size));

		string Load_Type = "=";
		if (Is_In_Left_Side_Of_Operator)
			Load_Type = "evaluate";	//this happends when it is the last load and it is left side of a assign

		Output->push_back(new IR(new Token(TOKEN::OPERATOR, Load_Type), { reg, new Token(TOKEN::MEMORY, {Scaler}, Next_Register_Size) }));

		handle->Get_Childs()->back() = reg;
		handle->Set_Name(reg->Get_Name());
		handle->Set_Size(Next_Register_Size);

		//calculate the resulting size
		int Reg_Size = 0;
		for (int tmp = Type_Trace.size() - 2; tmp >= 0; tmp--) {
			if (Type_Trace[tmp] == "ptr") {
				Reg_Size = _SYSTEM_BIT_SIZE_;
				break;
			}
			else
				Reg_Size += Global_Scope->Find(Type_Trace[tmp], Global_Scope)->Get_Size();
		}
		//get the remained inhertited types and set them for next to use
		vector<string> New_Inheritted;
		for (int tmp = Type_Trace.size() - 2; tmp >= 0; tmp--) {
			New_Inheritted.push_back(Type_Trace[tmp]);
		}

		Input[i]->Inheritted = New_Inheritted;

		if (Is_In_Left_Side_Of_Operator)
			Handle = new Token(TOKEN::MEMORY, { reg }, Reg_Size);
		else
			Handle = reg;
	}
	
}

void IRGenerator::Parse_PreFixes(int i)
{
	if (!Input[i]->is(PREFIX_NODE))
		return;

	//++i
	IRGenerator g(Parent, { Input[i]->Right }, Output);

	Token* Right = nullptr;

	if (g.Handle != nullptr)
		Right = g.Handle;
	else
		Right = new Token(Input[i]->Right);

	if (Right->is(TOKEN::CONTENT))
		Right = new Token(TOKEN::MEMORY, { Right }, Input[i]->Find(Right->Get_Name(), Right->Get_Parent())->Get_Size());


	Token* opc = new Token(TOKEN::OPERATOR, "+");
	Token* num = new Token(TOKEN::NUM, "1", 4);

	IR* ir = new IR(opc, { Right, num });
	Output->push_back(ir);

	Handle = Right;
}

void IRGenerator::Parse_PostFixes(int i)
{
	if (!Input[i]->is(POSTFIX_NODE))
		return;
	//i++
	IRGenerator g(Parent, { Input[i]->Left }, Output);

	Token* Left = nullptr;

	if (g.Handle != nullptr)
		Left = g.Handle;
	else
		Left = new Token(Input[i]->Left);

	if (Left->is(TOKEN::CONTENT))
		Left = new Token(TOKEN::MEMORY, { Left }, Input[i]->Find(Left->Get_Name(), Left->Get_Parent())->Get_Size());

	//i++
	//make a copy
	if (Input[i]->Holder != nullptr) {
		Token* CR = new Token(TOKEN::REGISTER, "CLONEREG_" + Left->Get_Name(), Left->Get_Size());
		Token* copc = new Token(TOKEN::OPERATOR, "move");

		IR* cir = new IR(copc, { CR, Left });
		Output->push_back(cir);
		Handle = CR;
	}

	//add to the original variable
	Token* num = new Token(TOKEN::NUM, "1", 4);

	Token* add = new Token(TOKEN::OPERATOR, "+");

	IR* ir = new IR(add, { Left, num });
	Output->push_back(ir);
	if (Input[i]->Holder != nullptr)
		Handle = Left;
}

void IRGenerator::Parse_Jump(int i)
{
	if (Input[i]->Name != "jump")
		return;

	Output->push_back(Make_Jump("jump", Input[i]->Right->Name));
}

void IRGenerator::Update_Operator(Node* n)
{
	if (n == nullptr)
		return;
	if (!n->is(OPERATOR_NODE) && !n->is(ASSIGN_OPERATOR_NODE) && !n->is(CONDITION_OPERATOR_NODE) && !n->is(BIT_OPERATOR_NODE))
		return;
	Update_Operator(n->Left);
	Update_Operator(n->Right);

	n->Inheritted = n->Left->Inheritted;
}

void IRGenerator::Parse_Loops(int i)
{
	if (!Input[i]->is(WHILE_NODE))
		return;

	//condition
	//loopinglabel:
	//content
	//condition again
	//end

	//make the condition
	vector<Node*> Header;
	if (Input[i]->Parameters[0]->is(OPERATOR_NODE) || Input[i]->Parameters[0]->is(ASSIGN_OPERATOR_NODE))
		Header = { Input[i]->Parameters[0] };
	Input[i]->Append(Header, Node::Get_all(CONDITION_OPERATOR_NODE, Input[i]->Parameters));

	vector<Node*> Footer = Node::Get_all(POSTFIX_NODE, Input[i]->Parameters);
	if (Input[i]->Parameters[Input[i]->Parameters.size() - 1]->is(OPERATOR_NODE))
		Input[i]->Append(Footer, { Input[i]->Parameters[Input[i]->Parameters.size() - 1] });
	Input[i]->Append(Footer, Node::Get_all(PREFIX_NODE, Input[i]->Parameters));

	IRGenerator g(Input[i], Header, Output);

	//make the looping label
	Output->push_back(Make_Label(Input[i]));

	int start_Index = Output->size();

	//make ir tokens from the code inside the loop
	g.Generate(Input[i]->Childs);

	//make the Footter IR
	g.Generate(Footer);
	//now do the condition again
	//get the location of the condition
	vector<Node*> Conditions = Node::Get_all(CONDITION_OPERATOR_NODE, Header);
	g.Generate(Conditions);

	//now make the _END addon at the end of loop for the false condition to fall
	Output->push_back(Make_Jump("jump", Input[i]->Name));

	Output->push_back(new IR(new Token(TOKEN::LABEL, Input[i]->Name + "_END"), {}));

	//make here IR that states that every variable that is extern to this while define list must last the same end.
	Output->push_back(new IR(new Token(TOKEN::END_OF_LOOP), Get_All_Extern_Variables(Output->size(), start_Index, Input[i])));
}

string IRGenerator::Get_Inverted_Condition(string c)
{
	if (c == "==")
		return "!=";
	else if (c == "!=")
		return "==";
	else if (c == "<")
		return ">";
	else if (c == ">")
		return "<";
	else if (c == "!<")
		return ">=";
	else if (c == "!>")
		return "<=";
	else if (c == "<=")
		return ">";
	else if (c == ">=")
		return "<";
	cout << "Error: Undefined Condition type " << c << endl;
	return "";
}

vector<Token*> IRGenerator::Get_All_Extern_Variables(int end_index, int start_index, Node* scope)
{
	vector<Token*> Result;
	for (int i = start_index; i < end_index; i++) {
		for (auto a : Output->at(i)->Arguments) {
			if (Find(TOKEN::CONTENT, a).size() > 0) {
				for (auto f : Find(TOKEN::CONTENT, a)) {
					bool is_extern = true;
					for (auto d : scope->Defined) {
						if (f->Get_Name() == d->Name) {
							is_extern = false;
						}
					}
					if (is_extern)
						Result.push_back(f);
				}
			}
			if (Find(TOKEN::PARAMETER, a).size() > 0) {
				for (auto f : Find(TOKEN::PARAMETER, a)) {
					bool is_extern = true;
					for (auto d : scope->Defined) {
						if (f->Get_Name() == d->Name) {
							is_extern = false;
						}
					}
					if (is_extern)
						Result.push_back(f);
				}
			}
		}
	}
	return Result;
}

vector<Token*> IRGenerator::Find(string n, Token* t)
{
	vector<Token*> Result;
	if (t->Get_Name() == n)
		Result.push_back(t);
	if (t->is(TOKEN::CONTENT) || t->is(TOKEN::MEMORY))
		for (auto i : t->Childs)
			if (Find(n, i).size() > 0)
				Global_Scope->Append(Result, Find(n, i));
	if (t->is(TOKEN::OFFSETTER) || t->is(TOKEN::DEOFFSETTER) || t->is(TOKEN::SCALER)) {
		if (Find(n, t->Left).size() > 0)
			Global_Scope->Append(Result, Find(n, t->Left));
		else if (Find(n, t->Right).size() > 0)
			Global_Scope->Append(Result, Find(n, t->Right));
	}
	return Result;
}

vector<Token*> IRGenerator::Find(long n, Token* t)
{
	vector<Token*> Result;
	if (t->is(n))
		Result.push_back(t);
	if (t->is(TOKEN::CONTENT) || t->is(TOKEN::MEMORY))
		for (auto i : t->Childs)
			if (Find(n, i).size() > 0)
				Global_Scope->Append(Result, Find(n, i));
	if (t->is(TOKEN::OFFSETTER) || t->is(TOKEN::DEOFFSETTER) || t->is(TOKEN::SCALER)) {
		if (Find(n, t->Left).size() > 0)
			Global_Scope->Append(Result, Find(n, t->Left));
		if (Find(n, t->Right).size() > 0)
			Global_Scope->Append(Result, Find(n, t->Right));
	}
	return Result;
}

Token* IRGenerator::Operate_Pointter(Token* p, int Difference, bool Needed_At_Addressing)
{
	if (p->is(TOKEN::CONTENT)) {
		p = new Token(TOKEN::MEMORY, { p }, _SYSTEM_BIT_SIZE_);
	}
	else if (Difference > 0) {	//this p is more pointter that the other
		vector<string> Type_Trace = Global_Scope->Find(p->Get_Name(), p->Get_Parent())->Inheritted;
		//reverse(Type_Trace.begin(), Type_Trace.end());

		//load the Left to right level
		//mov reg1, [(esp+123)]
		//mov reg2, [reg1]
		//give Left [reg2]
		//set the Left size into right system bit size
		p->Set_Size(_SYSTEM_BIT_SIZE_);
		Token* handle = new Token(TOKEN::MEMORY, { p }, _SYSTEM_BIT_SIZE_, p->Get_Name());	//start from the pointter 
		Token* Reg = nullptr;
		for (int j = 0; j <= Difference; j++) {
			int Reg_Size = _SYSTEM_BIT_SIZE_;
			if (j + 1 >= Difference) {
				Reg_Size = 0;
				//	 -j because we need to remove the current ptr to see what is inside it
				for (int s = Type_Trace.size() - 1 - j; s >= 0; s--) {
					//keywords dont have defined in the find list so skip them and put ptr the scaler switch.
					if (Lexer::GetComponents(Type_Trace[s])[0].is(Flags::KEYWORD_COMPONENT)) {
						if (Type_Trace[s] == "ptr") {
							Reg_Size = _SYSTEM_BIT_SIZE_;
							break;
						}
					}
					else
						Reg_Size += Global_Scope->Find(Type_Trace[s], Parent)->Size;
				}

			}

			int Needed_Size = Reg_Size;
			if (Needed_At_Addressing)
				Needed_Size = _SYSTEM_BIT_SIZE_;
			Reg = new Token(TOKEN::REGISTER, handle->Get_Name() + "_REG", Needed_Size);

			//move from handle to reg
			Output->push_back(new IR(new Token(TOKEN::OPERATOR, "="), {
				new Token(*Reg), new Token(*handle)
				}));

			//keep the old handle 
			//if (j + 1 < Level_Difference) {
			//replace the Original Left, to the new Reg for next loop.
			handle->Childs.back() = Reg;
			handle->Set_Name(Reg->Get_Name());
			//}
		}
		if (Needed_At_Addressing)
			Reg->Set_Size(_SYSTEM_BIT_SIZE_);
		return Reg;
	}
	else if (Difference < 0) {
		//save the address of Right into Left
		Token* reg = new Token(TOKEN::REGISTER, p->Get_Name() + "_REG", _SYSTEM_BIT_SIZE_);

		Token* Right_Mem = new Token(TOKEN::MEMORY, { p }, _SYSTEM_BIT_SIZE_, p->Get_Name());

		Output->push_back(new IR(new Token(TOKEN::OPERATOR, "evaluate"), { new Token(*reg), Right_Mem }));
		return reg;
	}
}

IR* IRGenerator::Make_Label(Node* n)
{
	Token* label_name = new Token(TOKEN::LABEL, n->Name);
	IR* label = new IR();
	label->OPCODE = label_name;
	return label;
}

IR* IRGenerator::Make_Jump(string condition, string l)
{
	Token* jmp = new Token(TOKEN::FLOW, condition);
	Token* label = new Token(TOKEN::LABEL, l);
	IR* op = new IR();
	op->OPCODE = jmp;
	op->Arguments.push_back(label);
	return op;
}

int IRGenerator::Get_Amount(string t, Node* n)
{
	int result = 0;
	for (string s : n->Inheritted)
		if (s == t)
			result++;

	return result;
}

void IRGenerator::Parse_Return(int i) {
	if (!Input[i]->is(FLOW_NODE))
		return;
	if (Input[i]->Name != "return")
		return;

	IRGenerator g(Parent, { Input[i]->Right }, Output);

	Token* Return_Val = nullptr;
	if (g.Handle != nullptr)
		Return_Val = g.Handle;
	else
		Return_Val = new Token(Input[i]->Right);

	Node* p = Input[i]->Right;
	while (true) {
		if (p == nullptr)
			break;
		if (p->is(FUNCTION_NODE))
			break;
		else
			p = p->Parent;
	}

	int Level_Difference = (int)labs(Get_Amount("ptr", p) - Get_Amount("ptr", Input[i]->Right));
	if (Level_Difference != 0) {
		Return_Val = Operate_Pointter(Return_Val, Level_Difference);
	}
	else if (Return_Val->is(TOKEN::CONTENT)) {
		Token* m = new Token(TOKEN::MEMORY, { Return_Val }, _SYSTEM_BIT_SIZE_);
		Return_Val = m;
	}
	/*
	if (Return_Val->is(TOKEN::CONTENT)) {
		Token* m = new Token(TOKEN::MEMORY, { Return_Val }, _SYSTEM_BIT_SIZE_);
		Return_Val = m;
	}
	else if (Level_Difference != 0) {
		vector<string> Type_Trace = Input[i]->Find(Return_Val->Get_Name(), Return_Val->Get_Parent())->Inheritted;
		//reverse(Type_Trace.begin(), Type_Trace.end());

		//load the Left to right level
		//mov reg1, [(esp+123)]
		//mov reg2, [reg1]
		//give Left [reg2]
		//set the Left size into right system bit size
		Return_Val->Set_Size(_SYSTEM_BIT_SIZE_);
		Token* handle = new Token(TOKEN::MEMORY, { Return_Val }, _SYSTEM_BIT_SIZE_, Return_Val->Get_Name());	//start from the pointter 
		Token* Reg = nullptr;
		int Keep_Last_Address = 0;
		if (Input[i]->is(ASSIGN_OPERATOR_NODE))
			Keep_Last_Address = 1;
		for (int j = 0; j <= Level_Difference - Keep_Last_Address; j++) {
			int Reg_Size = _SYSTEM_BIT_SIZE_;
			if (j + 1 >= Level_Difference) {
				Reg_Size = 0;
				//	 -j because we need to remove the current ptr to see what is inside it
				for (int s = Type_Trace.size() - 1 - j; s >= 0; s--) {
					//keywords dont have defined in the find list so skip them and put ptr the scaler switch.
					if (Lexer::GetComponents(Type_Trace[s])[0].is(Flags::KEYWORD_COMPONENT)) {
						if (Type_Trace[s] == "ptr") {
							Reg_Size = _SYSTEM_BIT_SIZE_;
							break;
						}
					}
					else
						Reg_Size += Input[i]->Find(Type_Trace[s], Parent)->Size;
				}

			}

			Reg = new Token(TOKEN::REGISTER, handle->Get_Name() + "_REG", Reg_Size);
			//move from handle to reg
			Output->push_back(new IR(new Token(TOKEN::OPERATOR, "="), {
				new Token(*Reg), new Token(*handle)
				}));

			//keep the old handle 
			//if (j + 1 < Level_Difference) {
			//replace the Original Left, to the new Reg for next loop.
			handle->Childs.back() = Reg;
			handle->Set_Name(Reg->Get_Name());
			//}
		}
		if (Input[i]->is(ASSIGN_OPERATOR_NODE))
			Return_Val = handle;	//handle already has the 
		else
			Return_Val = Reg;
	}*/

	int Returning_Reg_Size = 0;
	for (auto j : p->Inheritted) {
		if (j == "ptr") {
			Returning_Reg_Size = _SYSTEM_BIT_SIZE_;
			break;
		}
		if (Lexer::GetComponents(j)[0].is(Flags::KEYWORD_COMPONENT))
			continue; //skip keywords
		Returning_Reg_Size += Global_Scope->Find(j, Global_Scope)->Size;
	}

	if ((Input[i]->Right != nullptr) && (Returning_Reg_Size == 0)) {
		cout << "Error: You are trying to return value inside a void function, not good.\n";
		cout << "Solution: Your return value size seems to be: '" << Return_Val->Get_Size() * 8 << "' so ";
		cout << "try using '" << Global_Scope->Find(Return_Val->Get_Size(), Global_Scope)->Name << "' as your function return type." << endl;
		throw::exception("\nReturn error.\n");
	}

	Output->push_back(new IR(new Token(TOKEN::OPERATOR, "move"), {
		new Token(TOKEN::REGISTER | TOKEN::RETURNING, "Returning_REG", Returning_Reg_Size),
		Return_Val }));

	//let the postprosessor to handle stack emptying!
	Token* ret = new Token(TOKEN::FLOW, "return");
	ret->Set_Parent(Parent);
	Output->push_back(new IR(ret, vector<Token*>{}));
}