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
	Output->push_back(new IR(new Token(TOKEN::FLOW, "return"), {}));

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

	for (Node* n : Input[i]->Parameters) {
		g.Generate({ n });

		Token* p;
		//handle complex instructions
		if (g.Handle != nullptr)
			p = g.Handle;
		else
			p = new Token(n);

		if (n->Has_Floating_Point_Value) {
			if (Float_Register_Count <= MAX_Floating_Register_Count) {
				//use a parameter register
				Token* reg = new Token(TOKEN::PARAMETER | TOKEN::REGISTER | TOKEN::DECIMAL, "REG_" + p->Get_Name() + "_Parameter", p->Get_Size());
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
			if (Number_Register_Count <= MAX_Number_Register_Count) {
				//use a parameter register
				Token* reg = new Token(TOKEN::PARAMETER | TOKEN::REGISTER, "REG_" + p->Get_Name() + "_Parameter", p->Get_Size());
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
	}

	reverse(Reversable_Pushes.begin(), Reversable_Pushes.end());

	//now all the push needing parameters are reversed, and ready to go push.
	for (auto p : Reversable_Pushes)
		Output->push_back(new IR(new Token(TOKEN::OPERATOR, "push"), { p }));

	Token* call = new Token(TOKEN::CALL, Input[i]->Name, All_Parameters);
	IR* ir = new IR(call, {});

	Output->push_back(ir);

	Token* returningReg = new Token(TOKEN::REGISTER | TOKEN::RETURNING, "RetREG_" + call->Get_Name(), Input[i]->Size);

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
	if (!Input[i]->is(OPERATOR_NODE) && !Input[i]->is(BIT_OPERATOR_NODE) && !Input[i]->is(ASSIGN_OPERATOR_NODE))
		return;
	//If this operator is handling with pointters we cant use general operator handles
	int Level_Difference = (int)labs(Get_Amount("ptr", Input[i]->Left) - Get_Amount("ptr", Input[i]->Right));
	if (Level_Difference != 0)
		return;

	Token* Left = nullptr;
	Token* Right = nullptr;

	IRGenerator g(Parent, { Input[i]->Right }, Output);

	if (g.Handle != nullptr)
		Right = g.Handle;
	else if (!Input[i]->Right->is(NUMBER_NODE)) {
		Token* R = new Token(Input[i]->Right->Find(Input[i]->Right, Input[i]->Right->Parent));
		if (R->is(TOKEN::CONTENT))
			R = new Token(TOKEN::MEMORY, { R }, R->Get_Size());

		Token* Reg = new Token(TOKEN::REGISTER, "REG_" + R->Get_Name(), R->Get_Size());
		//create the IR
		Token* Opc = new Token(TOKEN::OPERATOR, "move");
		IR* ir = new IR(Opc, { Reg, R });

		Right = Reg;
		Output->push_back(ir);
	}
	else {
		Right = new Token(TOKEN::NUM, Input[i]->Right->Name, 4);
	}
	
	g.Generate({ Input[i]->Left });

	if (g.Handle != nullptr)
		Left = g.Handle;
	else {
		if (Input[i]->Name == "=") {
			//dont load the value into a register
			Left = new Token(Input[i]->Left);
			if (Left->is(TOKEN::CONTENT))
				Left = new Token(TOKEN::MEMORY, { Left }, Input[i]->Find(Input[i]->Left, Input[i]->Left->Parent)->Get_Size());
		}
		else {
			Token* L = new Token(Input[i]->Left->Find(Input[i]->Left, Input[i]->Left->Parent));
			if (L->is(TOKEN::CONTENT))
				L = new Token(TOKEN::MEMORY, { L }, L->Get_Size());

			Token* Reg = new Token(TOKEN::REGISTER, "REG_" + L->Get_Name(), L->Get_Size());
			//create the IR
			Token* Opc = new Token(TOKEN::OPERATOR, "move");
			IR* ir = new IR(Opc, { Reg, L });

			Left = Reg;
			Output->push_back(ir);
		}
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

	int Level_Difference = (int)labs(Get_Amount("ptr", Input[i]->Left) - Get_Amount("ptr", Input[i]->Right));
	if (Level_Difference == 0)
		return;

	int Left_Level = Get_Amount("ptr", Input[i]->Left);
	int Right_Level = Get_Amount("ptr", Input[i]->Right);


	Token* Right = nullptr;
	Token* Left = nullptr;
	
	//handle complex Right
	IRGenerator g(Parent, { Input[i]->Right }, Output);
	if (g.Handle != nullptr)
		Right = g.Handle;
	else
		Right = new Token(Input[i]->Right);

	//handle complex Left
	g.Generate({ Input[i]->Left });
	if (g.Handle != nullptr)
		Left = g.Handle;
	else
		Left = new Token(Input[i]->Left);

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
			vector<string> Type_Trace = Input[i]->Find(Left->Get_Name(), Left->Get_Parent())->Inheritted;
			//reverse(Type_Trace.begin(), Type_Trace.end());

			//load the Left to right level
			//mov reg1, [(esp+123)]
			//mov reg2, [reg1]
			//give Left [reg2]
			//set the Left size into right system bit size
			Left->Set_Size(_SYSTEM_BIT_SIZE_);
			Token* handle = new Token(TOKEN::MEMORY, { Left }, _SYSTEM_BIT_SIZE_, Left->Get_Name());	//start from the pointter 
			Token* Reg = nullptr;
			int Keep_Last_Address = 0;
			if (Input[i]->is(ASSIGN_OPERATOR_NODE))
				Keep_Last_Address = 1;
			for (int j = 0; j <= Level_Difference - Keep_Last_Address; j++) {
				int Reg_Size = _SYSTEM_BIT_SIZE_;
				if (j + 1 >= Level_Difference) {
					Reg_Size = 0;
													//	 -j because we need to remove the current ptr to see what is inside it
					for (int s = Type_Trace.size()-1 - j; s >= 0; s--) {
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
				Left = handle;	//handle already has the 
			else
				Left = Reg;
		}

		if (Right->is(TOKEN::CONTENT)) {
			//handle the other side into a usable register
			Right = new Token(TOKEN::MEMORY, { Right }, Input[i]->Find(Right->Get_Name(), Right->Get_Parent())->Get_Size());
		}
	}
	else if (Left_Level < Right_Level) {

		vector<string> Type_Trace = Input[i]->Find(Right->Get_Name(), Right->Get_Parent())->Inheritted;
		//reverse(Type_Trace.begin(), Type_Trace.end());

		//load the Left to right level
		//mov reg1, [(esp+123)]
		//mov reg2, [reg1]
		//give Left [reg2]
		Right->Set_Size(_SYSTEM_BIT_SIZE_);
		Token* handle = new Token(TOKEN::MEMORY, { Right }, _SYSTEM_BIT_SIZE_, Right->Get_Name());	//start from the pointter 
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
			Right = handle;	//handle already has the 
		else
			Right = Reg;

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
	else {
		Token* Source = new Token(Input[i]->Left);

		Left = new Token(TOKEN::REGISTER, Input[i]->Left->Name + to_string(rand()), Input[i]->Left->Find(Input[i]->Left, Input[i]->Left->Parent)->Size);

		Token* opc = new Token(TOKEN::OPERATOR, "move");

		IR* ir = new IR(opc, { Left, Source });
		Output->push_back(ir);
	}

	g.Generate({ Input[i]->Right });

	//a[x][y]
	//the right side can have the [x] inside.
	if (g.Handle != nullptr)
		Right = g.Handle;	
	else {
		Token* Source = new Token(Input[i]->Right);

		Right = new Token(TOKEN::REGISTER, Input[i]->Right->Name + to_string(rand()), Input[i]->Right->Find(Input[i]->Right, Input[i]->Right->Parent)->Size);

		Token* opc = new Token(TOKEN::OPERATOR, "move");

		IR* ir = new IR(opc, { Right, Source });
		Output->push_back(ir);
	}

	//int a[100][2] //2D array
	//int ptr b //when the brakets are used after variable name, it moves all the types inheritted into the list members
	//a[0] = 1

	Token* offset_operator = new Token(TOKEN::OFFSETTER, "+");
	offset_operator->Left = Left;
	offset_operator->Right = Right;

	Token* Mem = new Token(TOKEN::MEMORY, {offset_operator}, _SYSTEM_BIT_SIZE_);

																	//TODO: Left->Size maybe?
	Token* Result = new Token(TOKEN::REGISTER, "MEMREG_" + to_string(rand()), Input[i]->Left->Find(Input[i]->Left->Name, Input[i]->Left->Parent)->Scaler);

	//TODO: make address passing for this Gab!
	Token* opc = new Token(TOKEN::OPERATOR, "move");

	IR* ir = new IR(opc, { Result, Mem });

	Output->push_back(ir);

	Handle = Result;
	
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
	Token* CR = new Token(TOKEN::REGISTER, "CLONEREG_" + Left->Get_Name(), Left->Get_Size());
	Token* copc = new Token(TOKEN::OPERATOR, "move");

	IR* cir = new IR(copc, { CR, Left });
	Output->push_back(cir);
	Handle = CR;

	//add to the original variable
	Token* num = new Token(TOKEN::NUM, "1", 4);

	Token* add = new Token(TOKEN::OPERATOR, "+");

	IR* ir = new IR(add, { Left, num });
	Output->push_back(ir);
}

void IRGenerator::Parse_Jump(int i)
{
	if (Input[i]->Name != "jump")
		return;

	Output->push_back(Make_Jump("jump", Input[i]->Right->Name));
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
	}

	int Returning_Reg_Size = 0;
	for (auto j : p->Inheritted) {
		if (j == "ptr") {
			Returning_Reg_Size = _SYSTEM_BIT_SIZE_;
			break;
		}
		Returning_Reg_Size += Global_Scope->Find(j, Global_Scope)->Size;
	}

	Output->push_back(new IR(new Token(TOKEN::OPERATOR, "move"), {
		new Token(TOKEN::REGISTER | TOKEN::RETURNING, "Returning_REG", Returning_Reg_Size),
		Return_Val }));

	//let the postprosessor to handle stack emptying!

	Output->push_back(new IR(new Token(TOKEN::FLOW, "return"), vector<Token*>{}));
}