#include "../../H/BackEnd/BackEnd.h"
#include "../../H/BackEnd/IRGenerator.h"
#include "../../H/BackEnd/Selector.h"
#include "../../H/Docker/Mangler.h"
#include "../../H/UI/Safe.h"
#include "../../H/UI/Usr.h"

extern Selector* selector;
extern Usr* sys;
unsigned long long Reg_Random_ID_Addon = 0;

void IRGenerator::Factory()
{
	if (Parent->Name == "GLOBAL_SCOPE") 
		Output->push_back(new IR(new Token(TOKEN::OPERATOR, "section"), { new Token(TOKEN::LABEL, ".text") }, nullptr));
	for (int i = 0; i < Input.size(); i++)
		Un_Wrap_Inline(i);
	for (int i = 0; i < Input.size(); i++)
		Switch_To_Correct_Places(Input[i]);
	for (auto i : Parent->Defined)
		Parse_Function(i);
	for (auto i : Parent->Defined)
		Parse_Member_Functions(i);

	for (int i = 0; i < Input.size(); i++) {
		Parse_Dynamic_Casting(Input[i]);
		Parse_Static_Casting(Input[i]);
		Parse_If(i);
		Parse_Loops(i);
		Parse_Arrays(i);
		Parse_Member_Fetch(Input[i]);
		Parse_Calls(i);
		Parse_Parenthesis(i);
		Parse_Operators(i);
		Parse_Pointers(i);
		Parse_Jumps(i);
		Parse_PostFixes(i);
		Parse_PreFixes(i);
		Parse_Return(i);
	}
	if (Parent->Name == "GLOBAL_SCOPE") {
		Output->push_back(new IR(new Token(TOKEN::OPERATOR, "section"), { new Token(TOKEN::LABEL, ".data") }, nullptr));
		for (auto i : Parent->Header)
			Parse_Global_Variables(i);
		for (auto i : Parent->Defined)
			Parse_Static_Variables(i);
	}
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
	for (auto j : Func->Parameters)
		if (j->is("type") != -1)
			return;	//skip template functions.

	Node* Scope = Parent;
	if (Func->Fetcher != nullptr)
		Scope = Func->Fetcher;

	if ((Scope->Find(Func->Name, Scope, FUNCTION_NODE)->Calling_Count == 0) && Scope->Find(Func->Name, Scope, FUNCTION_NODE)->is("export") == -1)
		return;

	if (Func->is("export") != -1)
		Scope->Header.push_back(Func);

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
				Scope->Find(Func->Name, Scope, Func->Type)->Parameters[j]->Requires_Address = true;
				//now the new token that is created is a memory representive of the original parameter.
				Token* Memory = new Token(TOKEN::MEMORY, { new Token(Func->Parameters[j]) }, Register->Get_Size(), Register->Get_Name());

				Output->push_back(new IR(new Token(TOKEN::OPERATOR, "="), { Memory, Register }, Func->Location));
			}
		}
	}

	//go through the childs of the function
	IRGenerator g(Func, Func->Childs, Output);


	Token* ret = new Token(TOKEN::FLOW, "return");
	ret->Set_Parent(Scope->Find(Func->Name, Scope, FUNCTION_NODE));
	Output->push_back(new IR(ret, {}, nullptr));

	//make the end of funciton like End Proc like label
	Output->push_back(new IR(new Token(TOKEN::END_OF_FUNCTION, Func->Name), {}, nullptr));
}

void IRGenerator::Parse_Member_Functions(Node* Class)
{
	if (!Class->is(CLASS_NODE))
		return;
	if (Class->Templates.size() > 0)
		return;

	for (auto i : Class->Defined) {
		if (i->is(FUNCTION_NODE))
			if (i->Fetcher == nullptr) {	//if this function has a fetcher then it is defined in global scope.
				IRGenerator g(Class, Output);
				g.Parse_Function(i);
			}
		else if (i->is(CLASS_NODE))
			Parse_Member_Functions(i);
	}
}

void IRGenerator::Parse_Calls(int i)
{
	if (!Input[i]->is(CALL_NODE))
		return;
	if (Input[i]->Cast_Type != "")
		return;
	if (Handle != nullptr)
		return;
	if (Input[i]->Generated)
		return;


	IRGenerator g(Parent, Output);

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

	Node* parent = Global_Scope->Get_Parent_As(FUNCTION_NODE, Input[i]);

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
		ir = new IR(call, { new Token(TOKEN::LABEL, MANGLER::Mangle(Input[i]->Function_Implementation)) }, Input[i]->Location);
	else {
		Node* tmp = Input[i];
		tmp->Type = OBJECT_NODE;
		Token* Call_Variable = new Token(tmp);
		if (Call_Variable->is(TOKEN::CONTENT))
			Call_Variable = new Token(TOKEN::MEMORY, { Call_Variable }, Call_Variable->Get_Size(), Call_Variable->Get_Name());
		ir = new IR(call, { Call_Variable }, Input[i]->Location);
	}

	Output->push_back(ir);

	//int De_Allocate_Size = 0;
	//for (auto j : Reversable_Pushes) {
	//	De_Allocate_Size += j->Get_Size();
	//}

	//selector->DeAllocate_Stack(De_Allocate_Size, Output, Output->size());
	Input[i]->Update_Size();
	long long F = TOKEN::REGISTER | TOKEN::RETURNING;
	if (Input[i]->Format == "decimal")
		F |= TOKEN::DECIMAL;

	Token* returningReg = new Token(F, "RetREG_" + to_string(Reg_Random_ID_Addon++) /* + All_Parameters_Names*/, Input[i]->Size);

	Handle = returningReg;
	Input[i]->Generated = true;
}

void IRGenerator::Parse_If(int i)
{
	if (!Input[i]->is(IF_NODE))
		return;
	if (Input[i]->Generated)
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
	Input[i]->Generated = true;
}

void IRGenerator::Loop_Elses(Node* e)
{
	//the if/else label
	Node* tmp = new Node(e->Name, e->Location);
	Output->push_back(Make_Label(tmp, false));

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

void IRGenerator::Parse_Jumps(int i)
{
	if (Input[i]->Generated)
		return;

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
	Output->push_back(Make_Jump(Get_Inverted_Condition(Input[i]->Name, Input[i]->Location), Next_Label));

	Input[i]->Generated = true;
}

void IRGenerator::Un_Wrap_Inline(int i)
{
	if (!(Input[i]->Header.size() > 0))
		return;

	IRGenerator g(Parent, Input[i]->Header, Output);
}

//Classs move to other class
void IRGenerator::Parse_Cloning(int i)
{
	if (!Input[i]->is(ASSIGN_OPERATOR_NODE))
		return;

	//object non-ptr x = object y
	//object non-ptr x = object ptr y

	Token* Right;
	IRGenerator g(Parent, { Input[i]->Right }, Output);
	if (g.Handle != nullptr)
		Right = g.Handle;
	else 
		Right = new Token(Input[i]->Right);

	//check for pointters
	if (Input[i]->Right->is("ptr") != -1) {								// -1 keep one pointter that there is
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

	int Object_Size = Input[i]->Left->Get_Size();
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
	if (Parent->Name == "GLOBAL_SCOPE")
		return;
	if (Input[i]->Name == ".")
		return;


	Update_Operator(Input[i]);
	Input[i]->Update_Format();

	if (!Input[i]->Left->Has({ ARRAY_NODE, OPERATOR_NODE, ASSIGN_OPERATOR_NODE, CONDITION_OPERATOR_NODE, BIT_OPERATOR_NODE }))
		Input[i]->Left->Size = Parent->Find(Input[i]->Left, Parent)->Size;

	if (Input[i]->is(ASSIGN_OPERATOR_NODE) && Input[i]->Left->Size > _SYSTEM_BIT_SIZE_) {
		Parse_Cloning(i);
		return;
	}
	//If this operator is handling with pointters we cant use general operator handles
	int Level_Difference = (int)labs(Get_Amount("ptr", Input[i]->Left) - Get_Amount("ptr", Input[i]->Right));
	if (Level_Difference != 0)
		return;

	Token* Left = nullptr;
	Token* Right = nullptr;

	IRGenerator g(Parent, { Input[i]->Left }, Output, Input[i]->is(ASSIGN_OPERATOR_NODE) || Is_In_Left_Side_Of_Operator);

	vector<IR*> tmp;
	IRGenerator g2(Parent, { Input[i]->Right }, &tmp);

	if (Input[i]->Generated)
		return;

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
				Left = new Token(TOKEN::MEMORY | F, { Left }, Input[i]->Find(Input[i]->Left, Input[i]->Left->Scope)->Get_Size(), Left->Get_Name());
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

	Input[i]->Generated = true;
}

void IRGenerator::Parse_Pointers(int i)
{
	//int a = 0
	//int ptr b = a + f - e / g get the address of memory
	//int ptr c = b pass memory address of a to c
	//int d = c		load value of a into c

	if (!Input[i]->is(OPERATOR_NODE) && !Input[i]->is(CONDITION_OPERATOR_NODE) && !Input[i]->is(BIT_OPERATOR_NODE) && !Input[i]->is(ASSIGN_OPERATOR_NODE))
		return;
	if (Parent->Name == "GLOBAL_SCOPE")
		return;
	if (Input[i]->Name == ".")
		return;


	Update_Operator(Input[i]);
	if (!Input[i]->Left->Has({ ARRAY_NODE, OPERATOR_NODE, ASSIGN_OPERATOR_NODE, CONDITION_OPERATOR_NODE, BIT_OPERATOR_NODE }))
		Input[i]->Left->Size = Parent->Find(Input[i]->Left, Parent)->Size;
	if (Input[i]->is(ASSIGN_OPERATOR_NODE) && Input[i]->Left->Get_Size() > _SYSTEM_BIT_SIZE_) {
		//this has been already made in cloning objects
		return;
	}

	int Level_Difference = (int)labs(Get_Amount("ptr", Input[i]->Left) - Get_Amount("ptr", Input[i]->Right));
	if (Level_Difference == 0)
		return;

	Token* Right = nullptr;
	Token* Left = nullptr;

	if (Input[i]->Generated)
		return;
	
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
			Token* reg = new Token(TOKEN::REGISTER, Right->Get_Name() + "_REG" + to_string(Reg_Random_ID_Addon++), _SYSTEM_BIT_SIZE_);

			Token* Right_Mem = new Token(TOKEN::MEMORY, { Right }, _SYSTEM_BIT_SIZE_, Right->Get_Name());

			Output->push_back(new IR(new Token(TOKEN::OPERATOR, "evaluate"), { new Token(*reg), Right_Mem }, Input[i]->Location));
			Right = reg;
		}
		else {
			int Keep_Last_Address = 0;
			if (Input[i]->is(ASSIGN_OPERATOR_NODE))
				Keep_Last_Address = 1;
			Left = Operate_Pointter(Left, Level_Difference - Keep_Last_Address, false, Left->is(TOKEN::MEMORY));
			if (Input[i]->is(ASSIGN_OPERATOR_NODE))
				Left = new Token(TOKEN::MEMORY, { Left }, _SYSTEM_BIT_SIZE_);
		}

		if (Right->is(TOKEN::CONTENT)) {
			//handle the other side into a usable register
			Right = new Token(TOKEN::MEMORY, { Right }, Input[i]->Find(Right->Get_Name(), Right->Get_Parent())->Get_Size());
		}
	}
	else if (Left_Level < Right_Level) {
		Right = Operate_Pointter(Right, Level_Difference, false, Right->is(TOKEN::MEMORY), Input[i]->Right->Inheritted);
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

	if (Left->is(TOKEN::CONTENT))
		Left = new Token(TOKEN::MEMORY, { Left }, Left->Get_Size(), Left->Get_Name());
	Output->push_back(new IR(new Token(TOKEN::OPERATOR, Operator), { Left, Right }, Input[i]->Location));

	Input[i]->Generated = true;
}

void IRGenerator::Parse_Arrays(int i)
{
	if (!Input[i]->is(ARRAY_NODE))
		return;
	if (Parent->Name == "GLOBAL_SCOPE")
		return;
	if (Input[i]->Generated)
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
		vector<string> Type_Trace = Input[i]->Find(Input[i]->Left, Input[i]->Left->Scope)->Inheritted;
		//reverse(Type_Trace.begin(), Type_Trace.end());
		//int,[ptr, ptr]
		//x	  [123, 123]
		Token* handle = new Token(TOKEN::MEMORY, { Left}, _SYSTEM_BIT_SIZE_, Left->Get_Name());

		//the array is a ptr and it is in a memory then load the actual address the pointter points to
		if (Input[i]->Left->is("ptr") != -1)
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
					Scale += Global_Scope->Find(Type_Trace[tmp], Global_Scope)->Get_Size();
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
						Next_Register_Size += Global_Scope->Find(Type_Trace[tmp], Global_Scope)->Get_Size();
				}

			int Next_Scaler_Size = 0;
			for (int tmp = (int)Type_Trace.size() - 2 - o; tmp >= 0; tmp--) {
				if (Type_Trace[tmp] == "ptr") {
					Next_Scaler_Size = _SYSTEM_BIT_SIZE_;
					break;
				}
				else
					Next_Scaler_Size += Global_Scope->Find(Type_Trace[tmp], Global_Scope)->Get_Size();
			}

			reg = new Token(TOKEN::REGISTER, handle->Get_Name() + "_REG" + to_string(Reg_Random_ID_Addon++), Next_Register_Size);

			//parse through the Right childs for something complex.
			g.Generate({ Input[i]->Right->Childs[o] }, false);

			if (g.Handle != nullptr)
				Right = g.Handle;
			else
				Right = new Token(Input[i]->Right->Childs[o]);

			if (Input[i]->Right->Childs[o]->is("ptr") != -1)
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
				Reg_Size += Global_Scope->Find(Type_Trace[tmp], Global_Scope)->Get_Size();
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
		if (Input[i]->Left->is("ptr") != -1)
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
				Scale += Global_Scope->Find(Type_Trace[tmp], Global_Scope)->Get_Size();
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
					Next_Register_Size += Global_Scope->Find(Type_Trace[tmp], Global_Scope)->Get_Size();
			}

		int Next_Scaler_Size = 0;
		for (int tmp = (int)Type_Trace.size() - 2; tmp >= 0; tmp--) {
			if (Type_Trace[tmp] == "ptr") {
				Next_Scaler_Size = _SYSTEM_BIT_SIZE_;
				break;
			}
			else
				Next_Scaler_Size += Global_Scope->Find(Type_Trace[tmp], Global_Scope)->Get_Size();
		}

		reg = new Token(TOKEN::REGISTER, handle->Get_Name() + "_REG" + to_string(Reg_Random_ID_Addon++), Next_Register_Size);

		//parse through the Right childs for something complex.
		g.Generate({ Input[i]->Right }, false);

		if (g.Handle != nullptr)
			Right = g.Handle;
		else
			Right = new Token(Input[i]->Right);

		if (Input[i]->Right->is("ptr") != -1)
			//								//unload all ptr layers
			Right = Operate_Pointter(Right, Get_Amount("ptr", Input[i]->Right), true, Right->is(TOKEN::MEMORY));
		else if (Right->is(TOKEN::CONTENT)) {
			//load variable into a register
			Output->push_back(new IR(new Token(TOKEN::OPERATOR, "="), {
				new Token(TOKEN::REGISTER, Right->Get_Name() + "_REG" + to_string(Reg_Random_ID_Addon++), _SYSTEM_BIT_SIZE_),
				new Token(TOKEN::MEMORY, {Right}, _SYSTEM_BIT_SIZE_, Right->Get_Name())
				}, Input[i]->Location));
			Right = new Token(TOKEN::REGISTER, Right->Get_Name() + "_REG" + to_string(Reg_Random_ID_Addon++), _SYSTEM_BIT_SIZE_);
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
				Reg_Size += Global_Scope->Find(Type_Trace[tmp], Global_Scope)->Get_Size();
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

	Input[i]->Generated = true;
}

void IRGenerator::Parse_PreFixes(int i)
{
	if (!Input[i]->is(PREFIX_NODE))
		return;
	if (Input[i]->Generated)
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

	IR* ir = new IR(opc, { Right, num }, Input[i]->Location);
	Output->push_back(ir);

	Handle = Right;
	Input[i]->Generated = true;
}

void IRGenerator::Parse_PostFixes(int i)
{
	if (!Input[i]->is(POSTFIX_NODE))
		return;
	if (Input[i]->Generated)
		return;

	//i++
	IRGenerator g(Parent, { Input[i]->Left }, Output, true);

	Token* Left = nullptr;

	if (g.Handle != nullptr)
		Left = g.Handle;
	else
		Left = new Token(Input[i]->Left);

	if (Left->is(TOKEN::CONTENT))
		Left = new Token(TOKEN::MEMORY, { Left }, Input[i]->Find(Left->Get_Name(), Left->Get_Parent())->Get_Size());

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

	Token* add = new Token(TOKEN::OPERATOR, "+");

	IR* ir = new IR(add, { Left, num }, Input[i]->Location);
	Output->push_back(ir);
	if (Input[i]->Context == nullptr)
		Handle = Left;
	Input[i]->Generated = true;
}

void IRGenerator::Parse_Jump(int i)
{
	if (Input[i]->Name != "jump")
		return;
	if (Input[i]->Generated)
		return;


	Output->push_back(Make_Jump("jump", Input[i]->Right->Name));
	Input[i]->Generated = true;
}

void IRGenerator::Parse_Parenthesis(int i)
{
	if (!Input[i]->is(CONTENT_NODE))
		return;
	if (Input[i]->Paranthesis_Type != '(')
		return;
	if (Input[i]->Generated)
		return;


	//b++ + (b++ + 1)
	IRGenerator g(Parent, Input[i]->Childs, Output);

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
	Input[i]->Generated = true;
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

void IRGenerator::Generate_Global_Variable(string Variable_Name, Node* Value)
{
	Output->push_back(Make_Label(Variable_Name));

	Token* value = new Token(Value);

	string Init_Type = "init";
	if (value->is(TOKEN::STRING))
		Init_Type = "ascii";
	Output->push_back(new IR(new Token(TOKEN::SET_DATA, Init_Type), { value }, nullptr));
	if (value->is(TOKEN::STRING))
		Output->push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::STRING, "0", 1) }, nullptr));
}

void IRGenerator::Generate_Global_Variable(string Variable_Name, int Size)
{
	Node* Value = new Node(NUMBER_NODE, nullptr);
	Value->Name = "0";
	Value->Size = Size;
	Generate_Global_Variable(Variable_Name, Value);
}

void IRGenerator::Parse_Global_Variables(Node* n)
{
	if (Parent->Name != "GLOBAL_SCOPE")
		return;

	if (!n->is(ASSIGN_OPERATOR_NODE))
		return;

	n->Right->Size = n->Find(n->Left, n)->Size;
	Generate_Global_Variable(n->Left->Name, n->Right);
}

void IRGenerator::Parse_Static_Variables(Node* n)
{
	if (n->is(CLASS_NODE)) {
		if (n->is("static") != -1)
			for (auto i : n->Childs)
				Parse_Static_Variables(i);
		else
			for (auto i : n->Header)
				Parse_Static_Variables(i);
		return;
	}

	if (n->Has({ OPERATOR_NODE, ASSIGN_OPERATOR_NODE, CONDITION_OPERATOR_NODE, BIT_OPERATOR_NODE })) {
		//{[Namespace name] + [Static variable name]} d[size] [Value]
		Generate_Global_Variable(n->Scope->Name + "_" + n->Left->Name, n->Right);
	}
	else if (n->Has({ OBJECT_DEFINTION_NODE, OBJECT_NODE })) {
		//{[Namespace name] + [Static variable name]} d[size] 0
		Generate_Global_Variable(n->Scope->Name + "_" + n->Name, n->Size);
	}
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
	if (n->Generated)
		return;


	if (n->is("static") != -1 || n->Fetcher->is("static") != -1) {
		if (Parent->is(FUNCTION_NODE)) {
			//this now namespace if the condition above yelds true.
			bool Load_To_Reg = true;

			if (n->Context->Name == "=" && n->Context->Left == n)
				Load_To_Reg = false;	//the label data is going to be rewritten by set operator.

			if (!n->Fetcher->is(CLASS_NODE))
				n->Fetcher = n->Find(n->Fetcher->Inheritted[0]);

			Token* Result = new Token(TOKEN::MEMORY, { new Token(n) }, n->Size, n->Name);

			if (Load_To_Reg) {
				Token* Reg = new Token(TOKEN::REGISTER, n->Fetcher->Name + "_" + n->Name + "_REGISTER", n->Size);
				Output->push_back(new IR(new Token(TOKEN::OPERATOR, "="),
					{
						Reg, Result
					}, nullptr));
				Result = Reg;
			}

			n->Generated = true;
			Handle = Result;
			return;
		}
		n->Generated = true;
		Handle = new Token(n);
		return;
	}

	Token* Fecher;
	IRGenerator g(n->Scope, { n->Fetcher }, Output, true);
	if (g.Handle != nullptr)
		Fecher = g.Handle;
	else
		Fecher = new Token(n->Fetcher);

	if (Fecher->is(TOKEN::MEMORY)) {
		Fecher = Fecher->Childs.back();
	}

	//if the fetcher is a memory we need to load it first to a register and that register is our handle for the member offset
	if (Fecher->is(TOKEN::CONTENT) && !n->Fetcher->Has({OPERATOR_NODE, CONDITION_OPERATOR_NODE, ASSIGN_OPERATOR_NODE, BIT_OPERATOR_NODE, ARRAY_NODE}) && n->Fetcher->is("ptr") != -1) {
		//call the pointter handle system to do our job here :D
		//															 - 1 because the fecher being memory 
		//															the pointter operator alrerady because of that does one unwrap
		Fecher = Operate_Pointter(Fecher, n->Fetcher->Get_All("ptr"), false, false, n->Fetcher->Inheritted);

	}
	
	//make the member offset
	Token* Member_Offset = new Token(TOKEN::NUM, to_string(n->Find(n->Fetcher, n->Fetcher->Scope)->Find(n->Name)->Memory_Offset));

	Token* Member_Offsetter = new Token(TOKEN::OFFSETTER, "+");
	Member_Offsetter->Left = Fecher;
	Member_Offsetter->Right = Member_Offset;

	long long Type = 0;
	if (n->Format == "decimal")
		Type = TOKEN::DECIMAL;

	Member_Offsetter = new Token(Type | TOKEN::MEMORY, { Member_Offsetter }, n->Find(n->Fetcher, n->Fetcher->Scope)->Find(n->Name)->Size, n->Fetcher->Name + "_" + n->Name);

	if (Is_In_Left_Side_Of_Operator) {
		Handle = Member_Offsetter;
		n->Generated = true;
		return;
	}
	
	//if not then load this into register
	Token* r = new Token(Type | TOKEN::REGISTER, Member_Offsetter->Get_Name() + "_REG" + to_string(Reg_Random_ID_Addon++), n->Get_Size());

	Output->push_back(new IR(new Token(TOKEN::OPERATOR, "="), { r, Member_Offsetter }, n->Location));

	Handle = new Token(*r);
	n->Generated = true;
}

void IRGenerator::Switch_To_Correct_Places(Node* o)
{
	if (!o->is(OPERATOR_NODE) && !o->is(ASSIGN_OPERATOR_NODE) && !o->is(CONDITION_OPERATOR_NODE) && !o->is(BIT_OPERATOR_NODE))
		return;

	if (o->Left->is(OPERATOR_NODE) || o->Left->is(ASSIGN_OPERATOR_NODE) || o->Left->is(CONDITION_OPERATOR_NODE) || o->Left->is(BIT_OPERATOR_NODE))
		Switch_To_Correct_Places(o->Left);
	if (o->Right->is(OPERATOR_NODE) || o->Right->is(ASSIGN_OPERATOR_NODE) || o->Right->is(CONDITION_OPERATOR_NODE) || o->Right->is(BIT_OPERATOR_NODE))
		Switch_To_Correct_Places(o->Right);

	if (o->Left->is(NUMBER_NODE) && !o->Right->is(NUMBER_NODE)) {
		//switch the left side with right side, what could possibly go wrong?
		Node* tmp = o->Left;
		o->Left = o->Right;
		o->Right = tmp;
	}
}

void IRGenerator::Parse_Static_Casting(Node* n)
{
	//first check is the n has a casting request, and its format casting, no other!
	//int a
	//return a->float
	if (n->Cast_Type == "")
		return;
	if (n->Cast_Type == "address")
		return;
	if (n->Generated)
		return;

	n->Update_Format();

	Node* Caster = n->Find(n->Cast_Type, n, CLASS_NODE);


	//parse calls, arrays etc..
	string cast_Type = n->Cast_Type;
	n->Cast_Type = "";

	int Last_Output_Size = Output->size();

	IRGenerator g(n, { n }, Output);
	Token* Old_Format = nullptr;

	if (Output->size() > Last_Output_Size)
		Handle = g.Handle;

	n->Generated = true;

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

	Token* r = new Token(Type | TOKEN::REGISTER, "REG_" + n->Name + to_string(Reg_Random_ID_Addon++), n->Find(cast_Type, n, CLASS_NODE)->Get_Size());
	
	Output->push_back(new IR(new Token(TOKEN::OPERATOR, "convert"), {
		r, Old_Format
	}, n->Location));

	Handle = r;
	n->Cast_Type = cast_Type;
}

void IRGenerator::Parse_Dynamic_Casting(Node* n)
{
	if (n->Cast_Type == "")
		return;
	if (n->Cast_Type != "address")
		return;
	if (n->Generated)
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

	n->Generated = true;
}

void IRGenerator::Parse_Loops(int i)
{
	if (!Input[i]->is(WHILE_NODE))
		return;
	if (Input[i]->Generated)
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
	Output->push_back(Make_Label(Input[i], false));

	int start_Index = (int)Output->size();

	//make ir tokens from the code inside the loop
	g.Generate(Input[i]->Childs, false);

	//make the Footter IR
	g.Generate(Footer, false);
	//now do the condition again
	//get the location of the condition
	vector<Node*> Conditions = Node::Get_all(CONDITION_OPERATOR_NODE, Header);
	g.Generate(Conditions, false);

	//now make the _END addon at the end of loop for the false condition to fall
	Output->push_back(Make_Jump("jump", Input[i]->Name));

	Output->push_back(new IR(new Token(TOKEN::LABEL, Input[i]->Name + "_END"), {}, Input[i]->Location));

	//make here IR that states that every variable that is extern to this while define list must last the same end.
	Output->push_back(new IR(new Token(TOKEN::END_OF_LOOP), Get_All_Extern_Variables((int)Output->size(), start_Index, Input[i]), Input[i]->Location));

	Input[i]->Generated = true;
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
						Reg_Size += Global_Scope->Find(Type_Trace[s], Parent)->Size;
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

IR* IRGenerator::Make_Label(Node* n, bool Mangle = false)
{
	string name = n->Name;
	if (Mangle)
		name = MANGLER::Mangle(n);
	Token* label_name = new Token(TOKEN::LABEL, name);

	Node* Scope_Path = Parent;
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
	if (Input[i]->Generated)
		return;


	if (Input[i]->Right) {
		bool Can_Modify_Last_Variable_Value = true;
		for (auto j : Input[i]->Right->Has(Input[i]->Right, OBJECT_NODE)) {
			if (j->Has({ OBJECT_DEFINTION_NODE, OBJECT_NODE }) && j->Find(j, j->Scope)->Scope == Global_Scope)
				Can_Modify_Last_Variable_Value = false;
			if (j->is("ptr") != -1)
				Can_Modify_Last_Variable_Value = false;
		}

		IRGenerator g(Parent, { Input[i]->Right }, Output, Can_Modify_Last_Variable_Value);

		Token* Return_Val = nullptr;
		if (g.Handle != nullptr)
			Return_Val = g.Handle;
		else
			Return_Val = new Token(Input[i]->Right);

		Node* p = Input[i]->Get_Parent_As(FUNCTION_NODE, Input[i]);

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
		if (Level_Difference != 0) {
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
	ret->Set_Parent(Parent);
	Output->push_back(new IR(ret, vector<Token*>{}, Input[i]->Location));

	Input[i]->Generated = true;
}