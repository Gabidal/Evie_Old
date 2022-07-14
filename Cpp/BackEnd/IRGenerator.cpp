#include "../../H/BackEnd/BackEnd.h"
#include "../../H/BackEnd/IRGenerator.h"
#include "../../H/BackEnd/Selector.h"
#include "../../H/Docker/Mangler.h"
#include "../../H/UI/Safe.h"
#include "../../H/UI/Usr.h"
#include "../../H/Parser/Parser.h"
#include "../../H/Parser/PostProsessor.h"

extern Selector* selector;
extern Usr* sys;
unsigned long long Reg_Random_ID_Addon = 0;
unsigned long long Label_Differential_ID = 0;

void IRGenerator::Factory()
{
	vector<Node*> All_Defined = Scope->Defined;
	Scope->Append(All_Defined, Scope->Inlined_Items);

	if (Scope->Name == "GLOBAL_SCOPE") 
		Output->push_back(new IR(new Token(TOKEN::OPERATOR | TOKEN::SECTION, "section"), { new Token(TOKEN::LABEL, ".text") }, nullptr));
	/*for (int i = 0; i < Input.size(); i++)
		Switch_To_Correct_Places(Input[i]);*/
	if (Scope->is(CLASS_NODE)) {
		for (auto i : All_Defined)
			Parse_Function(i);
		for (auto i : All_Defined)
			Parse_Classes(i);
	}

	for (int i = 0; i < Input.size(); i++) {
		Parse_Dynamic_Casting(Input[i]);
		Parse_Static_Casting(Input[i]);
		Parse_If(i);
		Parse_Loops(i);
		Parse_Arrays(i);
		Parse_Member_Fetch(Input[i]);
		Parse_Calls(i);
		Parse_Parenthesis(i);
		Parse_Reference_Count_Increase(i);
		Parse_Operators(i);
		Parse_Logical_Conditions(i);
		Parse_Pointers(i);
		Parse_Conditional_Jumps(i);
		Parse_PostFixes(i);
		Parse_PreFixes(i);
		Parse_Return(i);
		Parse_Jump(i);
		Parse_Labels(i);
	}
	if (Scope->Name == "GLOBAL_SCOPE") {
		Output->push_back(new IR(new Token(TOKEN::OPERATOR | TOKEN::SECTION, "section"), { new Token(TOKEN::LABEL, ".data") }, nullptr));
		for (auto i : Scope->Header)
			Parse_Global_Variables(i);
		for (auto i : All_Defined)
			Parse_Static_Variables(i);
	}
}

void IRGenerator::Parse_Classes(Node* Class){
	if (!Class->is(CLASS_NODE))
		return;
	if (Class->Is_Template_Object)
		return;
	

	IRGenerator(Class, {}, Output);

}

void IRGenerator::Parse_Function(Node* Func)
{
	if (Func->is(IMPORT)) {
		if (Func->is(IMPORT))
			Global_Scope->Header.push_back(Func);
	}
	if (!Func->is(FUNCTION_NODE))
		return;
	if (Func->Is_Template_Object)
		return;
	if (Func->is(PARSED_BY::IRGENERATOR))
		return;
	for (auto j : Func->Parameters)
		if (j->is("type") || j->Inherits_Template_Type())
			return;	//skip template functions.

	Func->Parsed_By |= PARSED_BY::IRGENERATOR;

	Node* Function_Scope = Scope;
	if (Func->Fetcher != nullptr)
		Function_Scope = Func->Fetcher;

	if (Func->Calling_Count == 0 && !Func->is("export"))
		return;

	if (Func->is("export"))
		Function_Scope->Header.push_back(Func);

	//label
	IR* Label = Make_Label(Func, true);
	Label->OPCODE->Set_Flags(Label->OPCODE->Get_Flags() | TOKEN::START_OF_FUNCTION);
	Output->push_back(Label);
	Reg_Random_ID_Addon = 0;

	if (sys->Info.Debug) {
		//the stack locaiton of these parameters are decided in IRPostProsessor.cpp
		int Max_Non_Decimal_Register_Count = selector->Get_Numerical_Parameter_Register_Count(Func->Parameters);
		int Max_Decimal_Register_Count = selector->Get_Floating_Parameter_Register_Count(Func->Parameters);

		for (int j = 0; j < Func->Parameters.size(); j++) {
			if (j <= Max_Decimal_Register_Count || j <= Max_Non_Decimal_Register_Count) {
				//first make a register representive out of the parameter.
				Token* Register = new Token(Func->Parameters[j], true);
				//then declare that the parameter now needs memory
				Function_Scope->Find(Func->Name, Function_Scope, Func->Type)->Parameters[j]->Requires_Address = true;
				//now the new token that is created is a memory representive of the original parameter.
				Token* Memory = new Token(TOKEN::MEMORY, { new Token(Func->Parameters[j]) }, Register->Get_Size(), Register->Get_Name());

				Output->push_back(new IR(new Token(TOKEN::OPERATOR, "="), { Memory, Register }, Func->Location));
			}
		}
	}

	//go through the childs of the function
	IRGenerator g(Func, Func->Childs, Output);


	Token* ret = new Token(TOKEN::FLOW, "return");
	ret->Set_Parent(Function_Scope->Find(Func->Name, Function_Scope, FUNCTION_NODE));
	Output->push_back(new IR(ret, {}, nullptr));

	//make the end of funciton like End Proc like label
	Output->push_back(new IR(new Token(TOKEN::END_OF_FUNCTION, MANGLER::Mangle(Func, "")), {}, nullptr));
}

void IRGenerator::Parse_Calls(int i)
{
	if (!Input[i]->is(CALL_NODE))
		return;
	if (Input[i]->Cast_Type != nullptr)
		return;
	if (Input[i]->is(PARSED_BY::IRGENERATOR))
		return;


	IRGenerator g(Scope, Output);

	//do the parameters
	//no ur wrong m8!
	//the IRPostprosessor takes care of the parameters here (:
	//nah why dont do it here? :)
	//ok. (:
	int Number_Register_Count = 0;
	int MAX_Number_Register_Count = selector->Get_Numerical_Parameter_Register_Count(Input[i]->Parameters);
	int Float_Register_Count = 0;
	int MAX_Floating_Register_Count = selector->Get_Floating_Parameter_Register_Count(Input[i]->Parameters);

	//to push everything currectly
	vector<Token*> Reversable_Pushes;

	//for selector to understand a more abstract picture of the whole parameters.
	vector<Token*> All_Parameters;
	//string All_Parameters_Names = "";

	int Parameter_Place = 0;
	for (Node* n : Input[i]->Parameters) {
		g.Generate({ n }, false);

		Token* p;
		//handle complex instructions
		if (g.Handle != nullptr)
			p = g.Handle;
		else
			p = new Token(n);	

		if (p->is(TOKEN::CONTENT))
			p = new Token(TOKEN::MEMORY, { p }, p->Get_Size(), p->Get_Name());

		int Level_Difference = Get_Amount("ptr", n) - Get_Amount("ptr", Input[i]->Function_Implementation->Parameters[Parameter_Place]);
		if (Level_Difference != 0)
			p = g.Operate_Pointter(p, Level_Difference, false, p->is(TOKEN::MEMORY));

		if (n->Format == "decimal") {
			if (Float_Register_Count < MAX_Floating_Register_Count) {
				//use a parameter register
				Token* reg = new Token(TOKEN::PARAMETER | TOKEN::REGISTER | TOKEN::DECIMAL, "REG_" + p->Get_Name() + "_Parameter" + to_string(rand()), p->Get_Size());
				reg->Parameter_Index = Parameter_Place;
				Token* opc = new Token(TOKEN::OPERATOR, "=");
				//make the parameter move
				IR* ir = new IR(opc, { reg, p }, Input[i]->Location);
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
					Token* reg = new Token(TOKEN::REGISTER | TOKEN::DECIMAL, "REG_" + p->Get_Name() + "_Parameter" + to_string(rand()), p->Get_Size());
					Token* opc = new Token(TOKEN::OPERATOR, "=");
					//make the tmp move
					IR* ir = new IR(opc, { reg, p }, Input[i]->Location);
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
				Token* reg = new Token(TOKEN::PARAMETER | TOKEN::REGISTER, "REG_" + p->Get_Name() + "_Parameter" + to_string(rand()), p->Get_Size());
				reg->Parameter_Index = Parameter_Place;
				Token* opc = new Token(TOKEN::OPERATOR, "=");
				//make the parameter move
				IR* ir = new IR(opc, { reg, p }, Input[i]->Location);
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
					Token* reg = new Token(TOKEN::REGISTER, "REG_" + p->Get_Name() + "_Parameter" + to_string(rand()), p->Get_Size());
					Token* opc = new Token(TOKEN::OPERATOR, "=");
					//make the tmp move
					IR* ir = new IR(opc, { reg, p }, Input[i]->Location);
					Output->push_back(ir);
					//now give the tmp register to reversible pushbacker
					Reversable_Pushes.push_back(reg);
					All_Parameters.push_back(reg);
				}
			}
		}
		Parameter_Place++;
		//All_Parameters_Names += All_Parameters.back()->Get_Name();
	}

	//reverse(Reversable_Pushes.begin(), Reversable_Pushes.end());

	Node* parent = Global_Scope->Get_Scope_As(FUNCTION_NODE, Input[i]);

	/*int allocation = 0;
	if (sys->Info.Debug) {
		for (auto p : Input[i]->Parameters)
			allocation += p->Size;
	}
	else
		for (auto p : Reversable_Pushes) {
			allocation += p->Get_Size();
		}
	*/

	int Stack_Offset = 0;
	for (auto p : Reversable_Pushes) {
		Output->push_back(new IR(new Token(TOKEN::OPERATOR, "="), {
			new Token(TOKEN::MEMORY, {
				new Token(TOKEN::OFFSETTER, "+", new Token(TOKEN::STACK_POINTTER | TOKEN::REGISTER, ".STACK", _SYSTEM_BIT_SIZE_), new Token(TOKEN::NUM, to_string(Stack_Offset + parent->Local_Allocation_Space)))
				}, p->Get_Size(), p->Get_Name() + "_REGISTER"),
			p
			}, Input[i]->Location));
		Stack_Offset += p->Get_Size();
	}

	if (parent->Size_of_Call_Space < Stack_Offset)
		parent->Size_of_Call_Space = Stack_Offset;

	Token* call = new Token(TOKEN::CALL, "call", All_Parameters);
	IR* ir;
	if (!Input[i]->Function_Ptr)
		ir = new IR(call, { new Token(TOKEN::LABEL, MANGLER::Mangle(Input[i]->Function_Implementation, "")) }, Input[i]->Location);
	else {
		Node* tmp = Input[i];
		tmp->Type = OBJECT_NODE;
		Token* Call_Variable = new Token(tmp);
		if (Call_Variable->is(TOKEN::CONTENT))
			Call_Variable = new Token(TOKEN::MEMORY, { Call_Variable }, Call_Variable->Get_Size(), Call_Variable->Get_Name());
		ir = new IR(call, { Call_Variable }, Input[i]->Location);
		
		//now remove one ptr from the fuz
		Input[i]->Inheritted.erase(Input[i]->Inheritted.begin() + Input[i]->Get_Index_of_Inheritted("ptr"));
	}

	Output->push_back(ir);

	//selector->DeAllocate_Stack(De_Allocate_Size, Output, Output->size());
	Input[i]->Update_Size();
	long long F = TOKEN::REGISTER | TOKEN::RETURNING;
	if (Input[i]->Format == "decimal")
		F |= TOKEN::DECIMAL;

	Token* returningReg = new Token(F, "RetREG_" + to_string(Reg_Random_ID_Addon++) /* + All_Parameters_Names*/, Input[i]->Size);

	if (Input[i]->Function_Ptr) {
		Input[i]->Inheritted.push_back("ptr");
	}

	Handle = returningReg;
	Input[i]->Parsed_By |= PARSED_BY::IRGENERATOR;
}

void IRGenerator::Parse_If(int i)
{
	if (!Input[i]->is(IF_NODE))
		return;
	if (Input[i]->is(PARSED_BY::IRGENERATOR))
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
	Input[i]->Parsed_By |= PARSED_BY::IRGENERATOR;
}

void IRGenerator::Loop_Elses(Node* e)
{
	//the if/else label
	if (e->Predecessor == nullptr)
		e->Name += "_" + to_string(Label_Differential_ID++);
	Node* tmp = new Node(e->Name, e->Location);
	Output->push_back(Make_Label(tmp, false));

	//init else names
	Node* Else = e->Succsessor;
	while (Else) {
		Else->Name += "_" + to_string(Label_Differential_ID++);
		Else = Else->Succsessor;
	}

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
		Node* tmp2 = new Node(e->Name + "_END", e->Location);
		Output->push_back(Make_Label(tmp2, false));

		//now construct the successor
		Loop_Elses(e->Succsessor);
	}
	else {
		Node* tmp2 = new Node(e->Name + "_END", e->Location);
		Output->push_back(Make_Label(tmp2, false));
	}

}

void IRGenerator::Parse_Conditional_Jumps(int i)
{
	//NOTICE: this must happen after all operator is created as IR!!!
	if (!Input[i]->is(CONDITION_OPERATOR_NODE))
		return;
	if (!Scope->is(IF_NODE) && !Scope->is(ELSE_IF_NODE) && !Scope->is(WHILE_NODE))
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
	string Next_Label = Scope->Name + "_END";
	if (Scope->Succsessor != nullptr)
		Next_Label = Scope->Succsessor->Name;

	//jmp if not correct
	string Condition = Get_Inverted_Condition(Input[i]->Name, Input[i]->Location);
	Node* Logical_Condition_Node = Input[i]->Get_Closest_Context(LOGICAL_OPERATOR_NODE);
	
	if (Logical_Condition_Node && Logical_Condition_Node->Name == "||")
		Condition = Input[i]->Name;

	Output->push_back(Make_Jump(Condition, Next_Label));

	Input[i]->Parsed_By |= PARSED_BY::IRGENERATOR;
}

void IRGenerator::Parse_Logical_Conditions(int i)
{
	if (!Input[i]->is(LOGICAL_OPERATOR_NODE))
		return;

	// a == 1 && b < 2
	// -->
	// cmp a, 1
	// jne end_of_if_children
	// cmp b, 2
	// jge end_of_if_children
	// condition_children:
	// 	   ..
	// end_of_if_children:

	// a == 1 || b < 2
	// -->
	// cmp a, 1
	// je condition_children
	// cmp b, 2
	// jl condition_children
	// jmp end_of_if_children
	// condition_children:
	// 	   ..
	// end_of_if_children:

	IRGenerator g(Scope, { Input[i]->Left, Input[i]->Right }, Output);

	string Next_Label = Scope->Name + "_END";
	if (Scope->Succsessor)
		Next_Label = Scope->Succsessor->Name;

	if (Input[i]->Name == "||") {
		Output->push_back(Make_Jump("jump", Next_Label));
	}
}

//Class move to other class
void IRGenerator::Parse_Cloning(int i)
{
	if (!Input[i]->is(ASSIGN_OPERATOR_NODE))
		return;

	//object non-ptr x = object y
	//object non-ptr x = object ptr y

	Token* Right;
	IRGenerator g(Scope, { Input[i]->Right }, Output);
	if (g.Handle != nullptr)
		Right = g.Handle;
	else 
		Right = new Token(Input[i]->Right);

	//check for pointters
	if (Input[i]->Right->is("ptr")) {								// -1 keep one pointter that there is
		Right = Operate_Pointter(Right, Get_Amount("ptr", Input[i]->Right) -1, true, Right->is(TOKEN::MEMORY), Input[i]->Right->Inheritted);
	}

	Token* Left;
	g.Generate({ Input[i]->Left }, true);
	if (g.Handle != nullptr)
		Left = g.Handle;
	else
		Left = new Token(Input[i]->Left);

	if (Left->is(TOKEN::MEMORY)) {
		//unwrap the insides from the memory.
		Left = Left->Childs.back();
	}

	//get the appropriate registers.
	//			size, count
	vector<pair<int, int>> Registers;

	int Object_Size = Input[i]->Left->Size;
	int Register_Size = _SYSTEM_BIT_SIZE_;
	int Count = 0;
	while (Object_Size > 0) {
		Count = Object_Size / Register_Size;
		if (Count > 0)
			Registers.push_back({Register_Size, Count});
		Object_Size -= Count * Register_Size;
		Register_Size /= 2;		//half the size.
	}

	int Current_Stack_Offset = 0;
	for (auto& j : Registers) {
		for (int c = 0; c < j.second; c++) {
			//x[Current_Offset] = y[Current_Offset]

			//load the right side.
			Token* Reg = new Token(TOKEN::REGISTER, "REG_" + Right->Get_Name() + to_string(c) + to_string(j.first), j.first);
			//convert the right side into memory.
			Token* Offset = new Token(TOKEN::OFFSETTER, "+", Right, new Token(TOKEN::NUM, to_string(Current_Stack_Offset)));
			Offset = new Token(TOKEN::MEMORY, { Offset }, Reg->Get_Size(), Right->Get_Name() + "_Mem");
			Output->push_back(new IR(new Token(TOKEN::OPERATOR, "="), { Reg, Offset }, Input[i]->Location));

			//set the Reg into the Left side.
			Token* Dest = new Token(TOKEN::OFFSETTER, "+", Left, new Token(TOKEN::NUM, to_string(Current_Stack_Offset)));
			
			Dest = new Token(TOKEN::MEMORY, { Dest }, Reg->Get_Size(), Left->Get_Name() + "_Mem");
			Output->push_back(new IR(new Token(TOKEN::OPERATOR, "="), { Dest, Reg }, Input[i]->Location));

			Current_Stack_Offset += Reg->Get_Size();
		}
	}

}

void IRGenerator::Parse_Operators(int i)
{
	if (!Input[i]->is(OPERATOR_NODE) && !Input[i]->is(BIT_OPERATOR_NODE) && !Input[i]->is(ASSIGN_OPERATOR_NODE) && !Input[i]->is(CONDITION_OPERATOR_NODE))
		return;
	
	if (Scope->Name == "GLOBAL_SCOPE")
		return;
	if (Input[i]->Name == ".")
		return;


	Update_Operator(Input[i]);
	Input[i]->Update_Format();

	if (!Input[i]->Left->Has({ ARRAY_NODE, OPERATOR_NODE, ASSIGN_OPERATOR_NODE, CONDITION_OPERATOR_NODE, BIT_OPERATOR_NODE, CONTENT_NODE, PREFIX_NODE, POSTFIX_NODE }))
		Input[i]->Left->Size = Scope->Find(Input[i]->Left, Scope)->Size;

	if (Input[i]->is(ASSIGN_OPERATOR_NODE) && Input[i]->Left->Size > _SYSTEM_BIT_SIZE_) {
		Parse_Cloning(i);
		Input[i]->Parsed_By |= PARSED_BY::IRGENERATOR;
		return;
	}

	Token* Left = nullptr;
	Token* Right = nullptr;

	IRGenerator g(Scope, { Input[i]->Left }, Output, Input[i]->is(ASSIGN_OPERATOR_NODE) || Is_In_Left_Side_Of_Operator);

	vector<IR*> tmp;
	IRGenerator g2(Scope, { Input[i]->Right }, &tmp);

	//If this operator is handling with pointters we cant use general operator handles
	int Level_Difference = (int)labs(Get_Amount("ptr", Input[i]->Left) - Get_Amount("ptr", Input[i]->Right));
	if (Level_Difference != 0)
		return;

	//if (Input[i]->Generated)
	//	return;

	long long F = 0;
	if (Input[i]->Format == "decimal")
		F |= TOKEN::DECIMAL;

	if (g.Handle != nullptr) {
		Left = g.Handle;
	}
	else {
		if (Input[i]->Name == "=" || Is_In_Left_Side_Of_Operator) {
			//dont load the value into a register
			Left = new Token(Input[i]->Left);
			if (Left->is(TOKEN::CONTENT))
				Left = new Token(TOKEN::MEMORY | F, { Left }, Input[i]->Find(Input[i]->Left, Input[i]->Left->Scope)->Size, Left->Get_Name());
		}
		else if (Is_In_Left_Side_Of_Operator || (!Input[i]->Left->is(PARAMETER_NODE) && !Input[i]->is(CONDITION_OPERATOR_NODE) || Input[i]->Left->is(NUMBER_NODE))) {
			Token* L = new Token(Input[i]->Left->Find(Input[i]->Left, Input[i]->Left->Scope));
			if (L->is(TOKEN::CONTENT))
				L = new Token(TOKEN::MEMORY | F, { L }, L->Get_Size(), L->Get_Name());

			Token* Reg = new Token(TOKEN::REGISTER | F, "REG_" + L->Get_Name() + to_string(Reg_Random_ID_Addon++), L->Get_Size());
			//create the IR
			Token* Opc = new Token(TOKEN::OPERATOR, "=");
			IR* ir = new IR(Opc, { Reg, L }, Input[i]->Location);

			Left = Reg;
			Output->push_back(ir);
		}
		else {
			Left = new Token(Input[i]->Left);
			if (Left->is(TOKEN::CONTENT))
				Left = new Token(TOKEN::MEMORY, { Left }, Left->Get_Size(), Left->Get_Name());
		}
	}

	if (g2.Handle != nullptr && g.Handle != nullptr) {
		if (g.Handle->Has(TOKEN::RETURNING))
			if (Input[i]->Right->Has(CALL_NODE).size() > 0) {
				//save left into other reg
				string Type = "=";
				if (Left->is(TOKEN::MEMORY))
					Type = "evaluate";
				Token* r = new Token(TOKEN::REGISTER | F, Left->Get_Name() + "Save from the right side callations" + to_string(Reg_Random_ID_Addon++), Left->Get_Size());
				Output->push_back(new IR(new Token(TOKEN::OPERATOR, Type), { r, new Token(*Left) }, Input[i]->Location));
				//wtf is this register to memory operator here m8?
				//r = new Token(TOKEN::MEMORY | F, { r }, Left->Get_Size(), Left->Get_Name());
				Left = r;
			}
	}

	/*bool Is_Parameter_Register = false;
	if (Input[i]->Right->is(PARAMETER_NODE)) {
		//check if the parameter is held in a register or not
		if (Token(Input[i]->Right).is(TOKEN::REGISTER))
			Is_Parameter_Register = true;
	}*/

	if (g2.Handle != nullptr) {
		Right = g2.Handle;
		Output->insert(Output->end(), tmp.begin(), tmp.end());
	}
	else if (!Input[i]->Right->is(NUMBER_NODE) && !Token(Input[i]->Right).is(TOKEN::REGISTER) && !Left->is(TOKEN::REGISTER)){//!Is_Parameter_Register) {
		Token* R = new Token(Input[i]->Right->Find(Input[i]->Right, Input[i]->Right->Scope));

		if (R->is(TOKEN::CONTENT))
			R = new Token(TOKEN::MEMORY | F, { R }, R->Get_Size(), R->Get_Name());

		Token* Reg = new Token(TOKEN::REGISTER | F, "REG_" + R->Get_Name() + to_string(Reg_Random_ID_Addon++), R->Get_Size());
		//create the IR
		Token* Opc = new Token(TOKEN::OPERATOR, "=");
		IR* ir = new IR(Opc, { Reg, R }, Input[i]->Location);

		Right = Reg;
		Output->push_back(ir);
	}
	else {
		Right = new Token(Input[i]->Right);
		if (Right->is(TOKEN::NUM))
			Right->Set_Size(Left->Get_Size());
		if (Right->is(TOKEN::CONTENT))
			Right = new Token(TOKEN::MEMORY | F, { Right }, Left->Get_Size() ,Right->Get_Name());
		//Right = new Token(TOKEN::NUM, Input[i]->Right->Name, 4);
	}
	
	/*if (Left->is({ TOKEN::CONTENT, TOKEN::GLOBAL_VARIABLE }) && Right->is({ TOKEN::CONTENT, TOKEN::GLOBAL_VARIABLE })) {
		//Global variable + Global variable does this.
		//Member fetcher returns into Handler: Content and global scope flagged tokens
		if (Input[i]->Name == "=") {
			//move right into register then set Left's value into the register value that right just putted.
			Token* Reg = new Token(TOKEN::REGISTER, Right->Get_Name(), Right->Get_Size());
		}
	}*/

	string Operator = Input[i]->Name;
	//this translates the condition operator into a compare operation then the parse_jumps,
	//will use the condition name to do the correct jump.
	if (Input[i]->is(CONDITION_OPERATOR_NODE))
		Operator = "compare";

	Token* Opcode = new Token(TOKEN::OPERATOR, Operator);

	IR* ir = new IR(Opcode, {Left, Right}, Input[i]->Location);

	Handle = Left;
	Output->push_back(ir);

	Input[i]->Parsed_By |= PARSED_BY::IRGENERATOR;
}

void IRGenerator::Parse_Pointers(int i)
{
	//int a = 0
	//int ptr b = a + f - e / g get the address of memory
	//int ptr c = b pass memory address of a to c
	//int d = c		load value of a into c
	if (Input[i]->is(PARSED_BY::IRGENERATOR))
		return;
	if (!Input[i]->is(OPERATOR_NODE) && !Input[i]->is(CONDITION_OPERATOR_NODE) && !Input[i]->is(BIT_OPERATOR_NODE) && !Input[i]->is(ASSIGN_OPERATOR_NODE))
		return;
	if (Scope->Name == "GLOBAL_SCOPE")
		return;
	if (Input[i]->Name == ".")
		return;


	Update_Operator(Input[i]);
	if (!Input[i]->Left->Has({ ARRAY_NODE, OPERATOR_NODE, ASSIGN_OPERATOR_NODE, CONDITION_OPERATOR_NODE, BIT_OPERATOR_NODE, CONTENT_NODE, PREFIX_NODE, POSTFIX_NODE }))
		Input[i]->Left->Size = Scope->Find(Input[i]->Left, Scope)->Size;

	if (Input[i]->is(ASSIGN_OPERATOR_NODE) && Input[i]->Left->Size > _SYSTEM_BIT_SIZE_) {
		//this has been already made in cloning objects
		return;
	}

	int Level_Difference = (int)labs(Get_Amount("ptr", Input[i]->Left) - Get_Amount("ptr", Input[i]->Right));
	if (Level_Difference == 0)
		return;

	Token* Right = nullptr;
	Token* Left = nullptr;

	//if (Input[i]->Generated)
	//	return;
	
	//handle complex Right
	IRGenerator g(Scope, { Input[i]->Right }, Output);
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
			Token* reg = new Token(TOKEN::REGISTER, Right->Get_Name() + "_REG" + to_string(Reg_Random_ID_Addon++), _SYSTEM_BIT_SIZE_);

			Token* Right_Mem = new Token(TOKEN::MEMORY, { Right }, _SYSTEM_BIT_SIZE_, Right->Get_Name());

			Output->push_back(new IR(new Token(TOKEN::OPERATOR, "evaluate"), { new Token(*reg), Right_Mem }, Input[i]->Location));
			Right = reg;
		}
		else {
			int Keep_Last_Address = 0;
			if (Input[i]->is(ASSIGN_OPERATOR_NODE))
				Keep_Last_Address = 1;
			Left = Operate_Pointter(Left, Level_Difference - Keep_Last_Address, false, Left->is(TOKEN::MEMORY), Input[i]->Left->Inheritted);
			if (Input[i]->is(ASSIGN_OPERATOR_NODE))
				Left = new Token(TOKEN::MEMORY, { Left }, _SYSTEM_BIT_SIZE_);
		}

		if (Right->is(TOKEN::CONTENT)) {
			//handle the other side into a usable register
			Right = new Token(TOKEN::MEMORY, { Right }, Right->Get_Size());
		}
	}
	else if (Left_Level < Right_Level) {
		Right = Operate_Pointter(Right, Level_Difference, false, Right->is(TOKEN::MEMORY), Input[i]->Right->Inheritted);
		if (Left->is(TOKEN::CONTENT)) {
				//handle the other side into a usable register
				Left = new Token(TOKEN::MEMORY, { Left }, Input[i]->Find(Left->Get_Name(), Left->Get_Parent())->Size);
			}
	}

	string Operator = Input[i]->Name;
	//this translates the condition operator into a compare operation then the parse_jumps,
	//will use the condition name to do the correct jump.
	if (Input[i]->is(CONDITION_OPERATOR_NODE))
		Operator = "compare";

	if (Left->is(TOKEN::CONTENT))
		Left = new Token(TOKEN::MEMORY, { Left }, Left->Get_Size(), Left->Get_Name());
	Output->push_back(new IR(new Token(TOKEN::OPERATOR, Operator), { Left, Right }, Input[i]->Location));

	Input[i]->Parsed_By |= PARSED_BY::IRGENERATOR;
}

void IRGenerator::Parse_Arrays(int i)
{
	if (!Input[i]->is(ARRAY_NODE))
		return;
	if (Scope->Name == "GLOBAL_SCOPE")
		return;
	if (Input[i]->is(PARSED_BY::IRGENERATOR))
		return;


	Token* Left = nullptr;
	Token* Right = nullptr;

	//the left side contains the owner from the offsetting happends
	IRGenerator g(Scope, { Input[i]->Left }, Output);
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
		vector<string> Type_Trace = Input[i]->Find(Input[i]->Left, Input[i]->Left->Scope)->Inheritted;
		//reverse(Type_Trace.begin(), Type_Trace.end());
		//int,[ptr, ptr]
		//x	  [123, 123]
		Token* handle = new Token(TOKEN::MEMORY, { Left}, _SYSTEM_BIT_SIZE_, Left->Get_Name());

		//the array is a ptr and it is in a memory then load the actual address the pointter points to
		if (Input[i]->Left->is("ptr"))
			if (Left->is(TOKEN::CONTENT)) {
				Token* UnLoaded_Left = new Token(TOKEN::REGISTER, Left->Get_Name() + "_UnLoaded", Left->Get_Size());
				Output->push_back(new IR(new Token(TOKEN::OPERATOR, "="), { UnLoaded_Left, new Token(*handle) }, nullptr));
				Left = UnLoaded_Left;

				handle->Get_Childs()->back() = Left;
				handle->Set_Name(UnLoaded_Left->Get_Name());
			}

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
			for (int tmp = (int)Type_Trace.size() - 1 - o; tmp >= 0; tmp--) {
				if (Type_Trace[tmp] == "ptr") {
					Scale = _SYSTEM_BIT_SIZE_;
					break;
				}
				else
					Scale += Global_Scope->Find(Type_Trace[tmp], Global_Scope)->Size;
			}

			int Next_Register_Size = 0;
			if (Is_In_Left_Side_Of_Operator)
				Next_Register_Size = _SYSTEM_BIT_SIZE_;
			else
				for (int tmp = (int)Type_Trace.size() - 2 - o; tmp >= 0; tmp--) {
					if (Type_Trace[tmp] == "ptr") {
						Next_Register_Size = _SYSTEM_BIT_SIZE_;
						break;
					}
					else
						Next_Register_Size += Global_Scope->Find(Type_Trace[tmp], Global_Scope)->Size;
				}

			int Next_Scaler_Size = 0;
			for (int tmp = (int)Type_Trace.size() - 2 - o; tmp >= 0; tmp--) {
				if (Type_Trace[tmp] == "ptr") {
					Next_Scaler_Size = _SYSTEM_BIT_SIZE_;
					break;
				}
				else
					Next_Scaler_Size += Global_Scope->Find(Type_Trace[tmp], Global_Scope)->Size;
			}

			reg = new Token(TOKEN::REGISTER, handle->Get_Name() + "_REG" + to_string(Reg_Random_ID_Addon++), Next_Register_Size);

			//parse through the Right childs for something complex.
			g.Generate({ Input[i]->Right->Childs[o] }, false);

			if (g.Handle != nullptr)
				Right = g.Handle;
			else
				Right = new Token(Input[i]->Right->Childs[o]);

			if (Input[i]->Right->Childs[o]->is("ptr"))
				//								//unload all ptr layers
				Right = Operate_Pointter(Right, Get_Amount("ptr", Input[i]->Right->Childs[o]), true, Right->is(TOKEN::MEMORY));
			else if (Right->is(TOKEN::CONTENT)) {
				//load variable into a register
				Output->push_back(new IR(new Token(TOKEN::OPERATOR, "="), {
					new Token(TOKEN::REGISTER, Right->Get_Name() + "_REG" + to_string(Reg_Random_ID_Addon++), _SYSTEM_BIT_SIZE_),
					new Token(TOKEN::MEMORY, {Right}, _SYSTEM_BIT_SIZE_, Right->Get_Name())
					}, Input[i]->Location));
				Right = new Token(TOKEN::REGISTER, Right->Get_Name() + "_REG" + to_string(Reg_Random_ID_Addon++), _SYSTEM_BIT_SIZE_);
			}

			//if this is not the last register it must be _SYSTEM_BIT_SIZE:d
			if (Right->is(TOKEN::REGISTER)) {
				if ((size_t)o + 1 < Input[i]->Right->Childs.size())
					Right->Set_Size(_SYSTEM_BIT_SIZE_);
			}

			Token* Offsetter = new Token(TOKEN::OFFSETTER, "+");
			Offsetter->Left = handle->Get_Childs()->back();
			Offsetter->Right = Right;

			Token* Scaler = new Token(TOKEN::SCALER, "*");
			Scaler->Left = Offsetter;
			Scaler->Right = new Token(TOKEN::NUM, to_string(Next_Scaler_Size));

			string Load_Type = "=";
			if (Is_In_Left_Side_Of_Operator && (size_t)o+1 >= Input[i]->Right->Childs.size())
				Load_Type = "evaluate";	//this happends when it is the last load and it is left side of a assign

			Output->push_back(new IR(new Token(TOKEN::OPERATOR, Load_Type), {reg, new Token(TOKEN::MEMORY, {Scaler}, Next_Register_Size, Input[i]->Left->Name + "_" + Input[i]->Right->Name) }, Input[i]->Location));
		
			handle->Get_Childs()->back() = reg;
			handle->Set_Name(reg->Get_Name());
			handle->Set_Size(Next_Register_Size);
		}

		//calculate the resulting size
		int Reg_Size = 0;
		for (int tmp = ((int)Type_Trace.size() - (int)Input[i]->Right->Childs.size()) - 1; tmp >= 0; tmp--) {
			if (Type_Trace[tmp] == "ptr") {
				Reg_Size = _SYSTEM_BIT_SIZE_;
				break;
			}
			else
				Reg_Size += Global_Scope->Find(Type_Trace[tmp], Global_Scope)->Size;
		}
		//get the remained inhertited types and set them for next to use
		vector<string> New_Inheritted;
		for (int tmp = ((int)Type_Trace.size() - (int)Input[i]->Right->Childs.size()) - 1; tmp >= 0; tmp--) {
			New_Inheritted.push_back(Type_Trace[tmp]);
		}

		Input[i]->Inheritted = New_Inheritted;

		if (Is_In_Left_Side_Of_Operator)
			Handle = new Token(TOKEN::MEMORY, { reg }, Reg_Size);
		else
			Handle = reg;
	}
	else {
		//this is where the 1D array operators are constructed.
		vector<string> Type_Trace = Input[i]->Find(Input[i]->Left, Input[i]->Left->Scope)->Inheritted;
		//reverse(Type_Trace.begin(), Type_Trace.end());
		//int,[ptr, ptr]
		//x	  [123, 123]

		Token* handle = new Token(TOKEN::MEMORY, { Left }, _SYSTEM_BIT_SIZE_, Left->Get_Name());

		//the array is a ptr and it is in a memory then load the actual address the pointter points to
		if (Input[i]->Left->is("ptr"))
			if (Left->is(TOKEN::CONTENT)) {
				Token* UnLoaded_Left = new Token(TOKEN::REGISTER, Left->Get_Name() + "_UnLoaded", Left->Get_Size());
				Output->push_back(new IR(new Token(TOKEN::OPERATOR, "="), { UnLoaded_Left, new Token(*handle) }, nullptr));
				Left = UnLoaded_Left;

				handle->Get_Childs()->back() = Left;
				handle->Set_Name(UnLoaded_Left->Get_Name());
			}

		Token* reg = nullptr;
		int Scale = 0;
		//calculate the current size and the next size for the scaling.
		for (int tmp = (int)Type_Trace.size() - 1; tmp >= 0; tmp--) {
			if (Type_Trace[tmp] == "ptr") {
				Scale = _SYSTEM_BIT_SIZE_;
				break;
			}
			else
				Scale += Global_Scope->Find(Type_Trace[tmp], Global_Scope)->Size;
		}

		int Next_Register_Size = 0;
		if (Is_In_Left_Side_Of_Operator)
			Next_Register_Size = _SYSTEM_BIT_SIZE_;
		else
			for (int tmp = (int)Type_Trace.size() - 2; tmp >= 0; tmp--) {
				if (Type_Trace[tmp] == "ptr") {
					Next_Register_Size = _SYSTEM_BIT_SIZE_;
					break;
				}
				else
					Next_Register_Size += Global_Scope->Find(Type_Trace[tmp], Global_Scope)->Size;
			}

		int Next_Scaler_Size = 0;
		for (int tmp = (int)Type_Trace.size() - 2; tmp >= 0; tmp--) {
			if (Type_Trace[tmp] == "ptr") {
				Next_Scaler_Size = _SYSTEM_BIT_SIZE_;
				break;
			}
			else
				Next_Scaler_Size += Global_Scope->Find(Type_Trace[tmp], Global_Scope)->Size;
		}

		reg = new Token(TOKEN::REGISTER, handle->Get_Name() + "_REG" + to_string(Reg_Random_ID_Addon++), Next_Register_Size);

		//parse through the Right childs for something complex.
		g.Generate({ Input[i]->Right }, false);

		if (g.Handle != nullptr)
			Right = g.Handle;
		else
			Right = new Token(Input[i]->Right);

		if (Input[i]->Right->is("ptr"))
			//								//unload all ptr layers
			Right = Operate_Pointter(Right, Get_Amount("ptr", Input[i]->Right), true, Right->is(TOKEN::MEMORY));
		else if (Right->is(TOKEN::CONTENT)) {
			//load variable into a register
			Token* New_Right = new Token(TOKEN::REGISTER, Right->Get_Name() + "_REG" + to_string(Reg_Random_ID_Addon++), Right->Get_Size());
			Output->push_back(new IR(new Token(TOKEN::OPERATOR, "="), {
				new Token(*New_Right),
				new Token(TOKEN::MEMORY, {Right}, Right->Get_Size(), Right->Get_Name())
				}, Input[i]->Location));
			New_Right->Set_Size(_SYSTEM_BIT_SIZE_);
			Right = New_Right;
		}
		//scale the offsetter into a usable system bit size.
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

		Output->push_back(new IR(new Token(TOKEN::OPERATOR, Load_Type), { reg, new Token(TOKEN::MEMORY, {Scaler}, Next_Register_Size, Left->Get_Name()) }, Input[i]->Location));

		handle->Get_Childs()->back() = reg;
		handle->Set_Name(reg->Get_Name());
		handle->Set_Size(Next_Register_Size);

		//calculate the resulting size
		int Reg_Size = 0;
		for (int tmp = (int)Type_Trace.size() - 2; tmp >= 0; tmp--) {
			if (Type_Trace[tmp] == "ptr") {
				Reg_Size = _SYSTEM_BIT_SIZE_;
				break;
			}
			else
				Reg_Size += Global_Scope->Find(Type_Trace[tmp], Global_Scope)->Size;
		}
		//get the remained inhertited types and set them for next to use
		vector<string> New_Inheritted;
		for (int tmp = (int)Type_Trace.size() - 2; tmp >= 0; tmp--) {
			New_Inheritted.push_back(Type_Trace[tmp]);
		}

		Input[i]->Inheritted = New_Inheritted;

		if (Is_In_Left_Side_Of_Operator)
			Handle = new Token(TOKEN::MEMORY, { reg }, Reg_Size, reg->Get_Name());
		else
			Handle = reg;
	}

	Input[i]->Parsed_By |= PARSED_BY::IRGENERATOR;
}

void IRGenerator::Parse_PreFixes(int i)
{
	if (!Input[i]->is(PREFIX_NODE))
		return;
	if (Input[i]->is(PARSED_BY::IRGENERATOR))
		return;


	//++i
	IRGenerator g(Scope, { Input[i]->Right }, Output);

	Token* Right = nullptr;

	if (g.Handle != nullptr)
		Right = g.Handle;
	else
		Right = new Token(Input[i]->Right);

	if (Right->is(TOKEN::CONTENT))
		Right = new Token(TOKEN::MEMORY, { Right }, Input[i]->Find(Right->Get_Name(), Right->Get_Parent())->Size);

	string Change_Type = "+";
	if (Input[i]->Name == "--")
		Change_Type = "-";

	Token* opc = new Token(TOKEN::OPERATOR, Change_Type);
	Token* num = new Token(TOKEN::NUM, "1", 4);

	IR* ir = new IR(opc, { Right, num }, Input[i]->Location);
	Output->push_back(ir);

	Handle = Right;
	Input[i]->Parsed_By |= PARSED_BY::IRGENERATOR;
}

void IRGenerator::Parse_PostFixes(int i)
{
	if (!Input[i]->is(POSTFIX_NODE))
		return;
	if (Input[i]->is(PARSED_BY::IRGENERATOR))
		return;

	//i++
	IRGenerator g(Scope, { Input[i]->Left }, Output, true);

	Token* Left = nullptr;

	if (g.Handle != nullptr)
		Left = g.Handle;
	else
		Left = new Token(Input[i]->Left);

	if (Left->is(TOKEN::CONTENT))
		Left = new Token(TOKEN::MEMORY, { Left }, Input[i]->Find(Left->Get_Name(), Left->Get_Parent())->Size);

	//i++
	//make a copy
	if (Input[i]->Context != nullptr) {
		Token* CR = new Token(TOKEN::REGISTER, "CLONEREG_" + Left->Get_Name(), Left->Get_Size());
		Token* copc = new Token(TOKEN::OPERATOR, "=");

		IR* cir = new IR(copc, { CR, Left }, Input[i]->Location);
		Output->push_back(cir);
		Handle = CR;
	}

	//add to the original variable
	Token* num = new Token(TOKEN::NUM, "1", Left->Get_Size());

	string Change_Type = "+";
	if (Input[i]->Name == "--")
		Change_Type = "-";

	Token* add = new Token(TOKEN::OPERATOR, Change_Type);

	IR* ir = new IR(add, { Left, num }, Input[i]->Location);
	Output->push_back(ir);
	if (Input[i]->Context == nullptr)
		Handle = Left;
	Input[i]->Parsed_By |= PARSED_BY::IRGENERATOR;
}

void IRGenerator::Parse_Reference_Count_Increase(int i)
{
	return;
	if (Input[i]->is(PARSED_BY::REFERENCE_COUNT_INCREASE))
		return;

	if (!Input[i]->is(ASSIGN_OPERATOR_NODE) || Input[i]->Right->Has({OPERATOR_NODE, CONDITION_OPERATOR_NODE, BIT_OPERATOR_NODE}))
		return;

	if (Input[i]->is("plain"))
		return;
	
	if (MANGLER::Is_Based_On_Base_Type(Input[i]))
		return;

	int Combined_Ptr_Count = Input[i]->Left->Get_All("ptr") + Input[i]->Right->Get_All("ptr");
	if (Combined_Ptr_Count < 1)
		return;

	int Ptr_Difference = Input[i]->Left->Get_All("ptr") - Input[i]->Right->Get_All("ptr");
	if (Ptr_Difference < 0)
		return;

	//make a temporary local variable that is to hold the value of the right side, if the right side if to be a function call that returns a class pointter.
	// [inheritted types] tmp01 = [operator right side]
	// tmp01.Reference_Count++
	// [operator left side] = tmp01

	PostProsessor P(Scope);

	Node* tmp = new Node(OBJECT_DEFINTION_NODE, Input[i]->Location);
	tmp->Copy_Node(tmp, Input[i]->Right, Input[i]->Right->Scope);
	tmp->Name += "_TMP_" + to_string((long long)tmp);
	tmp->Fetcher = nullptr;

	Scope->Defined.push_back(tmp);

	//update now the parent funcion to aling all the stack offset to right
	P.Define_Sizes(Scope);

	//the move from right to tmp needs to be hand made, because we dont have call to string functions.

	Node* Set = new Node(ASSIGN_OPERATOR_NODE, Input[i]->Location);
	Set->Name = "=";
	Set->Scope = Scope;
	Set->Left = tmp;
	Set->Right = Input[i]->Right;

	Set->Left->Context = Set;
	Set->Right->Context = Set;

	Set->Parsed_By |= PARSED_BY::REFERENCE_COUNT_INCREASE;
	Component Move("=", Flags::OPERATOR_COMPONENT);
	Move.node = Set;

	Parser p(Scope);
	p.Input.push_back(Move);
	tmp->Append(p.Input,Lexer::GetComponents("\n" + tmp->Name + ".Reference_Count++\n"));

	Set = new Node(ASSIGN_OPERATOR_NODE, Input[i]->Location);
	Set->Name = "=";
	Set->Scope = Scope;
	Set->Left = Input[i]->Left;
	Set->Right = tmp;
	Set->Parsed_By |= PARSED_BY::REFERENCE_COUNT_INCREASE;
	Move = Component("=", Flags::OPERATOR_COMPONENT);
	Move.node = Set;

	p.Input.push_back(Move);

	/*Input.erase(Input.begin() + i);	//erase the old move that initiated this whole function.
	i--;*/
	Input[i]->Parsed_By |= PARSED_BY::IRGENERATOR;
	p.Factory();

	P.Components = p.Input;
	P.Factory();

	IRGenerator g(Scope, P.Input, Output);
}

void IRGenerator::Parse_Jump(int i)
{
	if (Input[i]->Name != "jump")
		return;
	if (Input[i]->is(PARSED_BY::IRGENERATOR))
		return;

	string Label_Name = Input[i]->Right->Name;

	Node* Func = Scope->Find(Input[i]->Right->Name);

	if (Func != nullptr && Func->Has({ FUNCTION_NODE, IMPORT, EXPORT, PROTOTYPE }))
		Label_Name = Func->Mangled_Name;

	Output->push_back(Make_Jump("jump", Label_Name));
	Input[i]->Parsed_By |= PARSED_BY::IRGENERATOR;
}

void IRGenerator::Parse_Labels(int i)
{
	if (!Input[i]->is(LABEL_NODE))
		return;

	Output->push_back(new IR(new Token(TOKEN::LABEL, Input[i]->Name), {}, Input[i]->Location));
}

void IRGenerator::Parse_Parenthesis(int i)
{
	if (!Input[i]->is(CONTENT_NODE))
		return;
	if (Input[i]->is(PARSED_BY::IRGENERATOR))
		return;
	if (Input[i]->Paranthesis_Type == '(') {


		//b++ + (b++ + 1)
		IRGenerator g(Scope, Input[i]->Childs, Output);

		if (g.Handle != nullptr)
			Handle = g.Handle;
		else {
			//mov the variable into a reg.
			Token* C = new Token(Input[i]->Find(Input[i]->Childs[0], Input[i]->Childs[0]->Scope));
			if (C->is(TOKEN::CONTENT))
				C = new Token(TOKEN::MEMORY, { C }, C->Get_Size(), C->Get_Name());

			Token* Reg = new Token(TOKEN::REGISTER, "REG_" + C->Get_Name(), C->Get_Size());
			//create the IR
			Token* Opc = new Token(TOKEN::OPERATOR, "=");
			IR* ir = new IR(Opc, { Reg, C }, Input[i]->Location);

			Handle = Reg;
			Output->push_back(ir);
		}
	}
	else if (Input[i]->Paranthesis_Type == '{') {
		IRGenerator g(Scope, Input[i]->Childs, Output);
	}
	Input[i]->Parsed_By |= PARSED_BY::IRGENERATOR;
}

void IRGenerator::Update_Operator(Node* n)
{
	if (n == nullptr)
		return;
	if (!n->is(OPERATOR_NODE) && !n->is(ASSIGN_OPERATOR_NODE) && !n->is(CONDITION_OPERATOR_NODE) && !n->is(BIT_OPERATOR_NODE) && !n->is(LOGICAL_OPERATOR_NODE))
		return;
	Update_Operator(n->Left);
	Update_Operator(n->Right);

	n->Inheritted = n->Left->Inheritted;
}

void IRGenerator::Generate_Global_Variable(Node* label, Node* value)
{
	Output->push_back(Make_Label(label));

	long long Flag = 0;
	string Init_Type = "init";

	if (value->is(NUMBER_NODE)){

		Flag = TOKEN::NUM;

	}
	else if (value->is(STRING_NODE)){

		Flag = TOKEN::STRING;
		Init_Type = "ascii";


	}
	else{

		Flag = TOKEN::LABEL;

	}

	Token* Value = new Token(Flag, value->Get_Definition_Type()->Size);
	Value->Set_Name(Construct_Complex_Init_Values(value));

	Output->push_back(new IR(new Token(TOKEN::SET_DATA, Init_Type), { Value }, nullptr));
	
	if (Value->is(TOKEN::STRING))
		Output->push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::STRING, "0", 1) }, nullptr));
}

void IRGenerator::Parse_Global_Variables(Node* n)
{
	if (Scope->Name != "GLOBAL_SCOPE")
		return;

	if (!n->is(ASSIGN_OPERATOR_NODE))
		return;

	n->Right->Size = n->Find(n->Left, n)->Size;
	Generate_Global_Variable(n->Left, n->Right);
}

void IRGenerator::Parse_Static_Variables(Node* n)
{
	if (n->is(CLASS_NODE)) {
		//If the namespace in question is already inlined, 
		//then the static content is also moved to the main or _INIT_ function in global_scope
		for (auto i : n->Scope->Inlined_Namespaces) {
			if (i->Name == n->Name) {
				return;
			}
		}

		if (n->is("static"))
			//this is for the running code of a namespace for global variable initializations
			for (auto i : n->Childs)
				Parse_Static_Variables(i);
		else
			for (auto i : n->Header)
				Parse_Static_Variables(i);

		return;
	}

	if (n->Has({ OPERATOR_NODE, ASSIGN_OPERATOR_NODE, CONDITION_OPERATOR_NODE, BIT_OPERATOR_NODE })) {
		//{[Namespace name] + [Static variable name]} d[size] [Value]

		PostProsessor p(Scope);
		p.Update_Operator_Inheritance(n);

		//global variables that have been given an initial value.
		//static double Pi = 162351276534
		Node tmp = *n->Left;
		tmp.Mangled_Name = tmp.Scope->Name + "_" + tmp.Name;
		Generate_Global_Variable(&tmp, n->Right);
	}
	//inlined variables have their definition seen here, so make sure that this is the OG scope that
	//the global variable was defined in.
	else if (n->Has({ OBJECT_DEFINTION_NODE, OBJECT_NODE }) && n->Scope->Name == Scope->Name) {
		//{[Namespace name] + [Static variable name]} d[size] 0
		Node* value = new Node(NUMBER_NODE, "0", n->Left->Location);
		value->Size = n->Size;

		//un given value global variables
		Node tmp = *n->Left;
		tmp.Mangled_Name = tmp.Scope->Name + "_" + tmp.Name;
		Generate_Global_Variable(&tmp, value);
	}
}

string IRGenerator::Construct_Complex_Init_Values(Node* n)
{
	string Result = "";
	//This function computes foo - bar instances where foo and bar are both global variables.
	//there can also be numbers here and there.
	//There can also be address castings and normal castings, here and there.
	bool Get_Address = n->Cast_Type && n->Cast_Type->Name == "address";

	if (n->is(OPERATOR_NODE)) {
		if (n->Name == "*" || n->Name == "/" || n->Name == "%") {
			Report(Observation(ERROR, "Un-supported operator at global variable initialization."));
		}
		Result = Construct_Complex_Init_Values(n->Left);
		Result += " " + n->Name + " ";
		Result += Construct_Complex_Init_Values(n->Right);
	}
	else {
		if (!Get_Address && !n->is(NUMBER_NODE))
			Result = " [";
		Result += Token(n).Get_Name();
		if (!Get_Address && !n->is(NUMBER_NODE))
			Result += "] ";
	}

	return Result;
}

void IRGenerator::Parse_Member_Fetch(Node* n)
{
	if (n->Fetcher == nullptr)
		return;
	if (Handle != nullptr)
		return;		//the job has already been done
	if (n->is(NUMBER_NODE))
		return;	//x.size										//They're were Holders, both of em actually... srry, i dont know what this does m8!
	if ((!Is_In_Left_Side_Of_Operator && n->Context == nullptr) || (n->Scope != nullptr && n->Scope->Has({ CLASS_NODE, FUNCTION_NODE, IF_NODE, ELSE_IF_NODE, ELSE_NODE }) == false))
		return;
	if (n->is(CALL_NODE))
		return;
	if (n->is(PARSED_BY::IRGENERATOR))
		return;

	if (n->Size == 0){

		n->Size = n->Find(n, n->Scope)->Size;

	}

	//Namespace fetcher
	Token* Fetcher;
	if (n->Fetcher->is("static") && n->Fetcher->is(CLASS_NODE)) {
		Token * Result = new Token(TOKEN::MEMORY, { new Token(n) }, n->Size, n->Name);

		if (!Is_In_Left_Side_Of_Operator) {
			Token* Reg = new Token(TOKEN::REGISTER, n->Fetcher->Name + "_" + n->Name + "_REGISTER", n->Size);
			Output->push_back(new IR(new Token(TOKEN::OPERATOR, "="),
				{
					Reg, Result
				}, nullptr));
			Result = Reg;
		}

		n->Parsed_By |= PARSED_BY::IRGENERATOR;
		Handle = Result;
		return;
	}
	//The check for the fetcher of fetcher is for:
	//If the fetcher has it's own fetching then just call this same function recursively
	else if (n->Fetcher->is("static") && !n->Fetcher->Fetcher) {
		//The fetcher is a global variable
		Fetcher = new Token(TOKEN::MEMORY, { new Token(n->Fetcher) }, n->Fetcher->Size, n->Fetcher->Name);
	}
	else {
		IRGenerator g(n->Scope, { n->Fetcher }, Output, true);
		if (g.Handle != nullptr)
			Fetcher = g.Handle;
		else
			Fetcher = new Token(n->Fetcher);

		if (Fetcher->is(TOKEN::MEMORY)) {
			Fetcher = Fetcher->Childs.back();
		}
	}


	//if the fetcher is a memory we need to load it first to a register and that register is our handle for the member offset
	if (Fetcher->is(TOKEN::CONTENT) && !n->Fetcher->Has({ OPERATOR_NODE, CONDITION_OPERATOR_NODE, ASSIGN_OPERATOR_NODE, BIT_OPERATOR_NODE, ARRAY_NODE }) && n->Fetcher->is("ptr")) {
		//call the pointter handle system to do our job here :D
		//															 - 1 because the fecher being memory 
		//															the pointter operator alrerady because of that does one unwrap
		Fetcher = Operate_Pointter(Fetcher, n->Fetcher->Get_All("ptr"), false, false, n->Fetcher->Inheritted);

	}

	//make the member offset
	Token* Member_Offset = new Token(TOKEN::NUM, to_string(n->Find(n->Fetcher, n->Fetcher->Scope)->Find(n->Name)->Memory_Offset));

	Token* Member_Offsetter = new Token(TOKEN::OFFSETTER, "+");
	Member_Offsetter->Left = Fetcher;
	Member_Offsetter->Right = Member_Offset;

	long long Type = 0;
	if (n->Format == "decimal")
		Type = TOKEN::DECIMAL;

	Member_Offsetter = new Token(Type | TOKEN::MEMORY, { Member_Offsetter }, n->Find(n->Fetcher, n->Fetcher->Scope)->Find(n->Name)->Size, n->Fetcher->Name + "_" + n->Name);

	if (Is_In_Left_Side_Of_Operator) {
		Handle = Member_Offsetter;
		n->Parsed_By |= PARSED_BY::IRGENERATOR;
		return;
	}

	//if not then load this into register
	Token* r = new Token(Type | TOKEN::REGISTER, Member_Offsetter->Get_Name() + "_REG" + to_string(Reg_Random_ID_Addon++), n->Size);

	Output->push_back(new IR(new Token(TOKEN::OPERATOR, "="), { r, Member_Offsetter }, n->Location));

	Handle = new Token(*r);
	n->Parsed_By |= PARSED_BY::IRGENERATOR;
}

void IRGenerator::Parse_Static_Casting(Node* n)
{
	//first check is the n has a casting request, and its format casting, no other!
	//int a
	//return a->float
	if (n->Cast_Type == nullptr)
		return;
	if (n->Cast_Type->Name == "address")
		return;
	if (n->is(PARSED_BY::IRGENERATOR))
		return;

	n->Update_Format();

	Node* Caster = n->Find(n->Cast_Type, n, CLASS_NODE);

	if (Caster == nullptr) {
		//if this happends then the catser is not a class but a local defined cast type
		Caster = n->Find(n->Cast_Type, n, OBJECT_DEFINTION_NODE);
	}


	//parse calls, arrays etc..
	Node* cast_Type = n->Cast_Type;
	n->Cast_Type = nullptr;

	int Last_Output_Size = Output->size();

	IRGenerator g(n, { n }, Output);
	Token* Old_Format = nullptr;

	if (Output->size() > Last_Output_Size)
		Handle = g.Handle;

	n->Parsed_By |= PARSED_BY::IRGENERATOR;

	if (g.Handle != nullptr)
		Old_Format = g.Handle;
	else
		Old_Format = new Token(n);

	long long Additional_Flags = TOKEN::MEMORY;
	if (Old_Format->is(TOKEN::DECIMAL))
		Additional_Flags |= TOKEN::DECIMAL;
	if (Old_Format->is(TOKEN::CONTENT)) {
		Old_Format = new Token(Additional_Flags, { Old_Format },  Old_Format->Get_Size(), Old_Format->Get_Name() + "_REGISTER");
	}

	/*if (n->is("ptr") != -1) {
		int amount = 0;
		for (auto i : n->Inheritted)
			if (i == "ptr")
				amount++;
		Old_Format = Operate_Pointter(Old_Format, amount, true, n->Inheritted);
	}*/
	int Casted_Pointter_Count = Get_Amount("ptr", n);
	int Caster_Pointter_Count =	Get_Amount("ptr", Caster);
	
	if (Casted_Pointter_Count > Caster_Pointter_Count) {
		//revome exess ptr
		int Removable_Count = Casted_Pointter_Count - Caster_Pointter_Count;

		//go through all ptr and remove the excess ptr from n inheritance.
		for (int i = 0; i < n->Inheritted.size(); i++)
			if (n->Inheritted[i] == "ptr" && Removable_Count-- > 0)
				n->Inheritted.erase(n->Inheritted.begin() + i);
	}
	else if (Casted_Pointter_Count < Caster_Pointter_Count) {
		int Addable_Pointter_Count = Caster_Pointter_Count- Casted_Pointter_Count;
		for (int i = 0; i < Addable_Pointter_Count; i++) {
			n->Inheritted.push_back("ptr");
		}
	}

	if (n->is(NUMBER_NODE)) {
		n->Format = Caster->Format;
		return;
	}	
	
	//decimal to integer | integer to decimal
	if (Caster->Format == n->Format)
		return;

	long long Type = 0;
	if (n->Find(cast_Type, n, CLASS_NODE)->Format == "decimal")
		Type = TOKEN::DECIMAL;

	Token* r = new Token(Type | TOKEN::REGISTER, "REG_" + n->Name + to_string(Reg_Random_ID_Addon++), n->Find(cast_Type, n, CLASS_NODE)->Size);
	
	Output->push_back(new IR(new Token(TOKEN::OPERATOR, "convert"), {
		r, Old_Format
	}, n->Location));

	Handle = r;
	n->Cast_Type = cast_Type;
}

void IRGenerator::Parse_Dynamic_Casting(Node* n)
{
	if (n->Cast_Type == nullptr)
		return;
	if (n->Cast_Type->Name != "address")
		return;
	if (n->is(PARSED_BY::IRGENERATOR))
		return;


	Node* Other = n->Get_Pair();

	int Casted_Pointter_Count = Get_Amount("ptr", n);
	int Caster_Pointter_Count = Get_Amount("ptr", Other);

	if (Casted_Pointter_Count > Caster_Pointter_Count) {
		//revome exess ptr
		int Removable_Count = Casted_Pointter_Count - Caster_Pointter_Count;

		//go through all ptr and remove the excess ptr from n inheritance.
		for (int i = 0; i < n->Inheritted.size(); i++)
			if (n->Inheritted[i] == "ptr" && Removable_Count-- > 0)
				n->Inheritted.erase(n->Inheritted.begin() + i);
	}
	else if (Casted_Pointter_Count < Caster_Pointter_Count) {
		int Addable_Pointter_Count = Caster_Pointter_Count - Casted_Pointter_Count;
		for (int i = 0; i < Addable_Pointter_Count; i++) {
			n->Inheritted.push_back("ptr");
		}
	}

	n->Parsed_By |= PARSED_BY::IRGENERATOR;
}

void IRGenerator::Parse_Loops(int i)
{
	if (!Input[i]->is(WHILE_NODE))
		return;
	if (Input[i]->is(PARSED_BY::IRGENERATOR))
		return;

	//condition
	//loopinglabel:
	//content
	//condition again
	//end

	Input[i]->Name += "_" + to_string(Label_Differential_ID++);

	//make the condition
	vector<Node*> Header;
	if (Input[i]->Parameters[0]->is(OPERATOR_NODE) || Input[i]->Parameters[0]->is(ASSIGN_OPERATOR_NODE))
		Header = { Input[i]->Parameters[0] };

	vector<Node*> Header_Conditions;
	Input[i]->Append(Header_Conditions, Get_all(CONDITION_OPERATOR_NODE, Input[i]->Parameters));
	Input[i]->Append(Header, Input[i]->Append(Header_Conditions, Get_all(LOGICAL_OPERATOR_NODE, Input[i]->Parameters)));

	vector<Node*> Footer = Get_all(POSTFIX_NODE, Input[i]->Parameters);
	
	if (Input[i]->Parameters[Input[i]->Parameters.size() - 1]->is(OPERATOR_NODE))
		Input[i]->Append(Footer, { Input[i]->Parameters[Input[i]->Parameters.size() - 1] });
	
	Input[i]->Append(Footer, Get_all(PREFIX_NODE, Input[i]->Parameters));

	IRGenerator g(Input[i], Header, Output);

	//make the looping label
	Output->push_back(Make_Label(Input[i], false));

	int start_Index = (int)Output->size();

	//make ir tokens from the code inside the loop
	g.Generate(Input[i]->Childs, false);

	//make the Footter IR
	g.Generate(Footer, false);
	//now do the condition again
	//get the location of the condition
	//vector<Node*> Conditions = Node::Get_all(CONDITION_OPERATOR_NODE, Header);
	g.Generate(Header_Conditions, false);

	//now make the _END addon at the end of loop for the false condition to fall
	Output->push_back(Make_Jump("jump", Input[i]->Name));

	Node tmp = *Input[i];
	tmp.Name += "_END";

	Output->push_back(Make_Label(&tmp));

	//make here IR that states that every variable that is extern to this while define list must last the same end.
	Output->push_back(new IR(new Token(TOKEN::END_OF_LOOP), Get_All_Extern_Variables((int)Output->size(), start_Index, Input[i]), Input[i]->Location));

	Input[i]->Parsed_By |= PARSED_BY::IRGENERATOR;
}

string IRGenerator::Get_Inverted_Condition(string c, Position* p)
{
	if (c == "==")
		return "!=";
	else if (c == "!=")
		return "==";
	else if (c == "<")
		return ">=";
	else if (c == ">")
		return "<=";
	else if (c == "!<")
		return ">=";
	else if (c == "!>")
		return "<=";
	else if (c == "<=")
		return ">";
	else if (c == ">=")
		return "<";
	Report(Observation(ERROR, "Undefined Condition type " + c, *p));
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

Token* IRGenerator::Operate_Pointter(Token* p, int Difference, bool Needed_At_Address_Offsetting, bool Unwrap_Memory, vector<string> Types)
{
	if (p->is(TOKEN::CONTENT)) {
		p = new Token(TOKEN::MEMORY, { p }, _SYSTEM_BIT_SIZE_, p->Get_Name(), p->Get_Parent());
	}
	if (Difference > 0) {	//this p is more pointter that the other
		vector<string> Type_Trace = Types;
		if (Types.size() == 0)
			Type_Trace = Global_Scope->Find(p->Get_Name(), p->Get_Parent())->Inheritted;
		//reverse(Type_Trace.begin(), Type_Trace.end());

		//load the Left to right level
		//mov reg1, [(esp+123)]
		//mov reg2, [reg1]
		//give Left [reg2]
		//set the Left size into right system bit size
		p->Set_Size(_SYSTEM_BIT_SIZE_);
		Token* handle;
		if (!p->is(TOKEN::MEMORY))
			handle = new Token(TOKEN::MEMORY, { p }, _SYSTEM_BIT_SIZE_, p->Get_Name());	//start from the pointter 
		else
			handle = new Token(*p);
		Token* Reg = nullptr;
		//														  memory uploading needs more unwrapping.
		for (int j = 0; j <= Difference - !Needed_At_Address_Offsetting + Unwrap_Memory; j++) {
			int Reg_Size = _SYSTEM_BIT_SIZE_;
			if (j + 1 <= Difference + p->is(TOKEN::MEMORY)) {
				Reg_Size = 0;
				//	 -j because we need to remove the current ptr to see what is inside it
				for (int s = (int)Type_Trace.size() - 1 - j - !p->is(TOKEN::MEMORY); s >= 0; s--) {
					//keywords dont have defined in the find list so skip them and put ptr the scaler switch.
					if (Lexer::GetComponents(Type_Trace[s])[0].is(Flags::KEYWORD_COMPONENT)) {
						if (Type_Trace[s] == "ptr") {
							Reg_Size = _SYSTEM_BIT_SIZE_;
							break;
						}
					}
					else
						Reg_Size += Global_Scope->Find(Type_Trace[s], Scope)->Size;
				}

			}

			int Needed_Size = Reg_Size;
			if (Needed_At_Address_Offsetting)
				Needed_Size = _SYSTEM_BIT_SIZE_;
			handle->Set_Size(Needed_Size);
			Reg = new Token(TOKEN::REGISTER, handle->Get_Name() + "_REG" + to_string(Reg_Random_ID_Addon++), Needed_Size);

			//move from handle to reg
			Output->push_back(new IR(new Token(TOKEN::OPERATOR, "="), {
				new Token(*Reg), new Token(*handle)
			}, nullptr));

			//keep the old handle 
			//if (j + 1 < Level_Difference) {
			//replace the Original Left, to the new Reg for next loop.
			handle->Childs.back() = Reg;
			handle->Set_Name(Reg->Get_Name());
			//}
		}
		if (Needed_At_Address_Offsetting)
			Reg->Set_Size(_SYSTEM_BIT_SIZE_);
		return Reg;
	}
	if (Difference < 0) {
		//save the address of Right into Left
		Token* reg = new Token(TOKEN::REGISTER, p->Get_Name() + "_REG" + to_string(Reg_Random_ID_Addon++), _SYSTEM_BIT_SIZE_);

		Token* Right_Mem;
		if (!p->is(TOKEN::MEMORY))
			Right_Mem = new Token(TOKEN::MEMORY, { p }, _SYSTEM_BIT_SIZE_, p->Get_Name());
		else
			Right_Mem = p;

		if (Right_Mem->Get_Size() != reg->Get_Size())
			Right_Mem->Set_Size(reg->Get_Size());

		Output->push_back(new IR(new Token(TOKEN::OPERATOR, "evaluate"), { new Token(*reg), Right_Mem }, nullptr));
		return reg;
	}
	return p;
}

IR* IRGenerator::Make_Label(Node* n, bool Mangle)
{
	string name = n->Name;

	if (Mangle)
		name = MANGLER::Mangle(n, "");
	else if (n->Mangled_Name != "")
		name = n->Mangled_Name;

	Token* label_name = new Token(TOKEN::LABEL, name);
	label_name->OG = n->Name;

	Node* Scope_Path = Scope;
	if (n->Fetcher != nullptr)
		Scope_Path = n->Fetcher;

	label_name->Set_Parent(Scope_Path);

	IR* label = new IR(n->Location);
	label->OPCODE = label_name;
	return label;
}

IR* IRGenerator::Make_Label(string n)
{
	string name = n;
	Token* label_name = new Token(TOKEN::LABEL, name);
	IR* label = new IR(nullptr);
	label->OPCODE = label_name;
	return label;
}

IR* IRGenerator::Make_Jump(string condition, string l)
{
	Token* jmp = new Token(TOKEN::FLOW, condition);
	Token* label = new Token(TOKEN::LABEL, l);
	IR* op = new IR(nullptr);
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
	if (Input[i]->is(PARSED_BY::IRGENERATOR))
		return;


	if (Input[i]->Right) {
		bool Can_Modify_Last_Variable_Value = true;
		for (auto j : Input[i]->Right->Has(Input[i]->Right, OBJECT_NODE)) {
			if (j->Has({ OBJECT_DEFINTION_NODE, OBJECT_NODE }) && j->Find(j, j->Scope)->Scope == Global_Scope)
				Can_Modify_Last_Variable_Value = false;
			if (j->is("ptr"))
				Can_Modify_Last_Variable_Value = false;
		}

		IRGenerator g(Scope, Input[i]->Header, Output);

		g.Generate({ Input[i]->Right }, Can_Modify_Last_Variable_Value);

		Token* Return_Val = nullptr;
		if (g.Handle != nullptr)
			Return_Val = g.Handle;
		else
			Return_Val = new Token(Input[i]->Right);

		Node* p = Input[i]->Get_Scope_As(FUNCTION_NODE, Input[i]);

		int Returning_Reg_Size = 0;
		for (auto& j : p->Inheritted) {
			if (j == "ptr") {
				Returning_Reg_Size = _SYSTEM_BIT_SIZE_;
				break;
			}
			if (Lexer::GetComponents(j)[0].is(Flags::KEYWORD_COMPONENT))
				continue; //skip keywords
			Returning_Reg_Size += Global_Scope->Find(j, Global_Scope)->Size;
		}

		int Level_Difference = Get_Amount("ptr", Input[i]->Right) - Get_Amount("ptr", p);
		//int main(){
		//int ptr fuz = foo()
		//return fuz()
		//}
		if (Input[i]->Right->Function_Ptr) {
			if (Level_Difference < 0) {
				Return_Val = Operate_Pointter(Return_Val, Level_Difference, false, Return_Val->is(TOKEN::CONTENT), Input[i]->Right->Inheritted);
			}
			else if (Level_Difference > 0) {
				Level_Difference = 0;
			}
		}
		else if (Level_Difference != 0) {
			Return_Val = Operate_Pointter(Return_Val, Level_Difference, false, Return_Val->is(TOKEN::CONTENT), Input[i]->Right->Inheritted);
		}
		else if (Return_Val->is(TOKEN::CONTENT)) {
			Token* m = new Token(TOKEN::MEMORY, { Return_Val }, Returning_Reg_Size, Return_Val->Get_Name());
			Return_Val = m;
		}

		if (Return_Val->is(TOKEN::NUM) && Returning_Reg_Size != 0)
			Return_Val->Set_Size(Returning_Reg_Size);

		long long Flag = TOKEN::REGISTER | TOKEN::RETURNING;

		if (Return_Val->is(TOKEN::DECIMAL))
			Flag |= TOKEN::DECIMAL;

		Output->push_back(new IR(new Token(TOKEN::OPERATOR, "="), {
			new Token(Flag, "Returning_REG" + to_string(Reg_Random_ID_Addon++), Returning_Reg_Size),
			Return_Val }
		, Input[i]->Location));
	}
	//let the postprosessor to handle stack emptying!
	Token* ret = new Token(TOKEN::FLOW, "return");
	ret->Set_Parent(Scope);
	Output->push_back(new IR(ret, vector<Token*>{}, Input[i]->Location));

	Input[i]->Parsed_By |= PARSED_BY::IRGENERATOR;
}