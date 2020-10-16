#include "../../H/BackEnd/BackEnd.h"
#include "..\..\H\BackEnd\IRGenerator.h"

void IRGenerator::Factory()
{
	for (int i = 0; i < Input.size(); i++)
		Un_Wrap_Inline(i);
	for (int i = 0; i < Input.size(); i++) {
		Parse_Function(i);
		Parse_If(i);
		Parse_Loops(i);
	}
	for (int i = 0; i < Input.size(); i++) {
		Parse_Arrays(i);
		Parse_Calls(i);
		Parse_Condition(i);
		Parse_Operators(i);
		Parse_Pointers(i);
		Parse_PostFixes(i);
		Parse_PreFixes(i);
	}
}

void IRGenerator::Parse_Function(int i)
{
	if (!Input[i]->is(FUNCTION_NODE))
		return;

	//label
	IR* Label = Make_Label(Input[i]);
	Output->push_back(Label);

	//go through the childs of the function
	IRGenerator g(Input[i], Input[i]->Childs, Output);

	//TODO: Make the return IR here
}

void IRGenerator::Parse_Calls(int i)
{
	if (!Input[i]->is(CALL_NODE))
		return;

	IRGenerator g(Parent, Output);
	//do the parameters
	for (Node* n : Input[i]->Parameters) {
		g.Generate({ n });

		Token* p;
		//handle complex instructions
		if (g.Handle != nullptr)
			p = g.Handle;
		else
			p = new Token(n);

		Token* reg = new Token(TOKEN::PARAMETER, "REG_" + p->Get_Name() + "_Parameter", p->Get_Size());
		Token* opc = new Token(TOKEN::OPERATOR, "move");
		//make the parameter move
		IR* ir = new IR(opc, { reg, p });
		Output->push_back(ir);
	}

	Token* call = new Token(TOKEN::CALL, Input[i]->Name);
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
	Node* current = Input[i];
	while (true) {
		if (current == nullptr)
			break;
		//do an subfunction that can handle coditions and gets the label data for the condition data from the Parent given.
		IRGenerator p(Input[i], Input[i]->Parameters, Output);
		//then do childs
		IRGenerator c(Input[i], Input[i]->Childs, Output);

		current = current->Succsessor;
	}
	//the end of every conditon to false fall to
	Output->push_back(Make_Jump("jump", Input[i]->Name + "_END"));
}

void IRGenerator::Parse_Condition(int i)
{
	//NOTICE: this must happen after all operator is created as IR!!!
	if (!Input[i]->is(CONDITION_OPERATOR_NODE))
		return;
	if (!Parent->is(IF_NODE) && !Parent->is(ELSE_IF_NODE) && !Parent->is(WHILE_NODE)) {
		// a = b * c < d
		//...
		return;
	}
	// if (a == 1)
	//give the right side as left side to IRGenerator
	IRGenerator g(Parent, { Input[i]->Right }, Output);

	Token* Right = nullptr;
	Token* Left = nullptr;

	if (g.Handle != nullptr)
		Right = g.Handle;
	else {
		//move to register
		Token* R = new Token(Input[i]->Right);
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
		Token* L = new Token(Input[i]->Left);
		Token* Reg = new Token(TOKEN::REGISTER, "REG_" + L->Get_Name(), L->Get_Size());

		Token* opc = new Token(TOKEN::OPERATOR, "move");

		IR* ir = new IR(opc, { Reg, L });
		Output->push_back(ir);

		Right = Reg;
	}

	Token* cmp = new Token(TOKEN::OPERATOR, "compare");

	IR* ir = new IR(cmp, { Left, Right });
	Output->push_back(ir);

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
	if (!Input[i]->is(OPERATOR_NODE) && !Input[i]->is(CONDITION_OPERATOR_NODE) && !Input[i]->is(BIT_OPERATOR_NODE))
		return;
	//If this operator is handling with pointters we cant use general operator handles
	if (Input[i]->Left->is("ptr") != -1)
		return;
	if (Input[i]->Right->is("ptr") != -1)
		return;

	Token* Left = nullptr;
	Token* Right = nullptr;

	IRGenerator g(Parent, { Input[i]->Right }, Output);

	if (g.Handle != nullptr)
		Right = g.Handle;
	else {
		//create the register
		Token* Reg = new Token(TOKEN::REGISTER, "REG_" + Input[i]->Right->Name, Input[i]->Right->Size);
		//create a Token version out of the right side
		Token* Value = new Token(Input[i]->Right);
		//create the IR
		Token* Opc = new Token(TOKEN::OPERATOR, "move");
		IR* ir = new IR(Opc, { Reg, Value });

		Right = Reg;
		Output->push_back(ir);
	}
	
	g.Generate({ Input[i]->Left });

	if (g.Handle != nullptr)
		Left = g.Handle;
	else {
		if (Input[i]->Name == "=") {
			//dont load the value into a register
			Left = new Token(Input[i]->Left);
		}
		else {
			//create the register
			Token* Reg = new Token(TOKEN::REGISTER, "REG_" + Input[i]->Left->Name, Input[i]->Left->Size);
			//create a Token version out of the right side
			Token* Value = new Token(Input[i]->Left);
			//create the IR
			Token* Opc = new Token(TOKEN::OPERATOR, "move");
			IR* ir = new IR(Opc, { Reg, Value });

			Left = Reg;
			Output->push_back(ir);
		}
	}

	Token* Opcode = new Token(TOKEN::OPERATOR, Input[i]->Name);

	IR* ir = new IR(Opcode, {Left, Right});

	Handle = Left;
	Output->push_back(ir);
}

void IRGenerator::Parse_Pointers(int i)
{
	if (!Input[i]->is(OPERATOR_NODE) && !Input[i]->is(CONDITION_OPERATOR_NODE) && !Input[i]->is(BIT_OPERATOR_NODE))
		return;
	if ((Input[i]->Left->is("ptr") == -1) && Input[i]->Right->is("ptr") == -1)
		return;

	//int a = 0
	//int ptr b = a + f - e / g get the address of memory
	//int ptr c = b pass memory address of a to c
	//int d = c		load value of a into c

	//if true load the pointing value or move the inside value
	bool Load_Value = Get_Amount("ptr", Input[i]->Left) < Get_Amount("ptr", Input[i]->Right);
	bool Point_To_Value = Get_Amount("ptr", Input[i]->Left) > Get_Amount("ptr", Input[i]->Right);


	int Pointer_Depth = labs(Get_Amount("ptr", Input[i]->Left) - Get_Amount("ptr", Input[i]->Right));

	Token* Left = nullptr;
	Token* Right = nullptr;
	Token* Source = nullptr;
	
	IRGenerator g(Parent, { Input[i]->Left }, Output);

	if (g.Handle != nullptr)
		Left = g.Handle;
	else
		Left = new Token(Input[i]->Left);

	g.Generate({ Input[i]->Right });

	if (g.Handle != nullptr)
		Source = g.Handle;
	else
		Source = new Token(Input[i]->Right);

	if (Load_Value) {
		int Register_Count = 0;
		for (int j = 0; j < Pointer_Depth; j++) {
			//load reg1, right
			//make an register to load into
			Right = new Token(TOKEN::REGISTER, "REG_" + to_string(Register_Count++) + Source->Get_Name(), Source->Get_Size());

			Token* Load = new Token(TOKEN::OPERATOR, "load");

			IR* ir = new IR(Load, { Right, Source });
			Output->push_back(ir);

			Source = Right;
		}
	}
	else if (Point_To_Value) {
		if (Pointer_Depth > 1) {
			cout << "Error: Could not get temporary memory allocated for pointter depth more than 1 " << Input[i]->Left->Name << Input[i]->Name << Input[i]->Right->Name << endl;
			exit(1);
		}
		//save reg1, right		
		//make an register to save right into
		Right = new Token(TOKEN::REGISTER, "REG_" + Source->Get_Name(), Source->Get_Size());
		Token* Save = new Token(TOKEN::OPERATOR, "save");
		IR* ir = new IR(Save, { Right, Source });
		Output->push_back(ir);
	}
	Token* Opc = new Token(TOKEN::OPERATOR, Input[i]->Name);
	IR* Opcode = new IR(Opc, {Left, Right});
	Output->push_back(Opcode);

	Handle = Left;
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

		Left = new Token(TOKEN::REGISTER, Input[i]->Left->Name + to_string(rand()), Input[i]->Left->Size);

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

		Right = new Token(TOKEN::REGISTER, Input[i]->Right->Name + to_string(rand()), Input[i]->Right->Size);

		Token* opc = new Token(TOKEN::OPERATOR, "move");

		IR* ir = new IR(opc, { Right, Source });
		Output->push_back(ir);
	}

	//int a[100][2] //2D array
	//int ptr b //when the brakets are used after variable name, it moves all the types inheritted into the list members
	//a[0] = 1

	Token* offset_operator = new Token(TOKEN::OFFSETTER, "+");

	Token* Mem = new Token(TOKEN::MEMORY, "memory");
	Mem->add({ Left, offset_operator, Right });
																	//TODO: Left->Size maybe?
	Token* Result = new Token(TOKEN::REGISTER, "MEMREG_" + to_string(rand()), Input[i]->Left->Scaler);

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

	Token* opc = new Token(TOKEN::OPERATOR, "add");
	Token* num = new Token(TOKEN::NUM, "1");

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

	//make a copy
	Token* CR = new Token(TOKEN::REGISTER, "CLONEREG_" + Left->Get_Name(), Left->Get_Size());
	Token* copc = new Token(TOKEN::OPERATOR, "move");

	IR* cir = new IR(copc, { CR, Left });
	Output->push_back(cir);
	Handle = CR;

	//add to the original variable
	Token* num = new Token(TOKEN::NUM, "1");

	Token* add = new Token(TOKEN::OPERATOR, "add");

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
	if (Input[i]->Parameters[0]->is(OPERATOR_NODE))
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
	Output->push_back(Make_Jump("jump", Input[i]->Name + "_END"));
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
