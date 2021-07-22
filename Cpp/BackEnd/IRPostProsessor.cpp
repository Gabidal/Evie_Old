#include "../../H/BackEnd/IRPostProsessor.h"
#include "../../H/Nodes/Node.h"
#include "../../H/Docker/Mangler.h"

extern Selector* selector;
extern Node* Global_Scope;

void IRPostProsessor::Scale_To_Same_Size(int i)
{
	if (!Input->at(i)->is(TOKEN::OPERATOR))
		return;

	if (Input->at(i)->Arguments.size() < 2)
		return;

	if (!selector->Get_Opcode(Input->at(i))->is(TOKEN::ALL_ARGS_SAME_SIZE))
		return;

	//numbers seem to be exeptions to this particular rule...
	for (auto j : Input->at(i)->Arguments)
		if (j->is(TOKEN::NUM))
			return;

	//there IR's are still universal so dont worry about, if there is more than 2 arguments with the operator.
	//convert always the smaller into the bigger size
	Token* Scalable = nullptr;
	int Destination_Size = 0;
	int ArgIndex = 0;

	if (Input->at(i)->Arguments[0]->Get_Size() > Input->at(i)->Arguments[1]->Get_Size()) {
		//this means that right side is smaller, scale.
		Scalable = Input->at(i)->Arguments[1];
		ArgIndex = 1;	//tell later that were the scalable originates from.
		Destination_Size = Input->at(i)->Arguments[0]->Get_Size();
	}
	else if (Input->at(i)->Arguments[0]->Get_Size() < Input->at(i)->Arguments[1]->Get_Size()) {
		//this means thatthe left side is smaller, scale.
		Scalable = Input->at(i)->Arguments[0];
		ArgIndex = 0; //tell later where scalable originates from.
		Destination_Size = Input->at(i)->Arguments[1]->Get_Size();
	}
	else {
		//this means that theyre same size
		return;
	}

	Token* NewReg = new Token(TOKEN::REGISTER, Scalable->Get_Name() + "_converted", Destination_Size);

	Token* Convert = new Token(TOKEN::OPERATOR, "convert");
	IR* CONV = new IR(Convert, { NewReg, new Token(*Scalable) }, Input->at(i)->Location);

	//now put the newreg where the scalable was.
	Input->at(i)->Arguments[ArgIndex] = NewReg;

	//now insert the new converter before the operator
	Input->insert(Input->begin() + i, CONV);
}

void IRPostProsessor::Registerize(Token* t, int i)
{
	//mov eax, ebx
	if (t->is(TOKEN::REGISTER)) {
		Give_New_Register(t, i);
	}
	else if (t->is(TOKEN::MEMORY) || t->is(TOKEN::CONTENT))
		for (auto c : t->Childs)
			Registerize(c, i);
	else if (t->is(TOKEN::OFFSETTER) || t->is(TOKEN::DEOFFSETTER) || t->is(TOKEN::SCALER)) {
		Registerize(t->Left, i);
		Registerize(t->Right, i);
	}
}

void IRPostProsessor::Give_New_Register(Token* t, int i)
{
	if (!t->is(TOKEN::REGISTER) || t->is(TOKEN::ALREADY_GIVEN_REGISTER_NAME))
		return;
	//if (t->Get_Name() == ".RIP") {
	//	cout << ".";
	//}
	if (selector->Get_Memory_Location(t) == nullptr || !t->is(TOKEN::REGISTER_SAVE_SPACE)) {
		if (selector->Get_Register(t) == nullptr)
			if (selector->Get_New_Reg(Input, i, t) == nullptr) {
				selector->Allocate_Register(Input, i, t);
				goto Use_Memory_Instead_Of_Register;
			}
		t->ID = selector->Get_Register(t)->Get_Name();
	}
	else {
	Use_Memory_Instead_Of_Register:;
		*t = *selector->Get_Memory_Location(t);
		Handle_Stack_Usages(t);
	}
	//if (t->Get_Name() == "REG_2") {
	//	cout << ".";
	//}
}

void IRPostProsessor::Handle_Global_Labels()
{
	for (auto i : Global_Scope->Header) {
		//if (i->is(IMPORT))
		//	Input->insert(Input->begin(), new IR(new Token(TOKEN::GLOBAL_LABEL, "extern"), { new Token(TOKEN::LABEL, MANGLER::Mangle(i)) }, nullptr));
		/*else*/ if (i->is("export") != -1)
			Input->insert(Input->begin(), new IR(new Token(TOKEN::GLOBAL_LABEL, "global"), { new Token(TOKEN::LABEL,  MANGLER::Mangle(i, "")) }, nullptr));

	}
}

void IRPostProsessor::Clean_Selector(int& i)
{
	if (!Input->at(i)->is(TOKEN::END_OF_FUNCTION))
		return;
	if (Input->at(i)->OPCODE->Is_Initted)
		return;
	Input->at(i)->OPCODE->Is_Initted = true;
	//get the start of function index
	int Start_Of_Function = 0;
	for (int j = i; j > 0; j--)
		if (Input->at(j)->is(TOKEN::START_OF_FUNCTION)) {
			Start_Of_Function = j;
			break;
		}
	Start_Of_Function += 1; //Skip the label
	//now we know what non-volatiles are in use
	vector<Token*> Push_Amount;
	int Additional_Changes = 0;
	int Return_Amount = 0;
	for (auto r : selector->Get_Register_Type(TOKEN::NONVOLATILE)) {
		if (r.first == nullptr)
			continue;

		Token* reg;

		//if the same nonvolatile is in other size used
		for (auto p : Push_Amount) {
			for (auto s : p->Get_Connected_Registers(p)) {
				if (s->Get_Name() == r.second->Get_Name()) {
					goto Already_Pushed;
				}
			}
		}

		reg = new Token(*r.second->Get_Size_Parent(_SYSTEM_BIT_SIZE_, r.second));
		reg->ID = reg->Get_Name();
		Input->insert(Input->begin() + Start_Of_Function, new IR(new Token(TOKEN::OPERATOR, "push"), { reg }, Input->at(i)->Location));
		Additional_Changes += Parse_Complex(Input->at(Start_Of_Function), Start_Of_Function, true);
		Push_Amount.push_back(reg);
	Already_Pushed:;
	}

	//Compute here the needed re-location of the function parameters
	int New_Stack_Offset = 0;
	for (auto r : Push_Amount)
		New_Stack_Offset += r->Get_Size();
	//start from the bottom of the function and rise up until hit function start label.
	for (int j = i + (int)Push_Amount.size() + Additional_Changes; j > Start_Of_Function; j--) {
		for (auto& arg : Input->at(j)->Arguments)
			for (auto& Child : arg->Get_All(TOKEN::ADD_NON_VOLATILE_SPACE_NEEDS_HERE)) {
				int Current_Offset = atoi(Child->Get_Name().c_str());
				Current_Offset += New_Stack_Offset;
				Child->Set_Name(to_string(Current_Offset));

			}
	}

	reverse(Push_Amount.begin(), Push_Amount.end());

	//now do same but for the end of funciton
	for (int j = i + (int)Push_Amount.size() + Additional_Changes; j > Start_Of_Function; j -= 1) {
		if (Input->at(j)->OPCODE->Get_Name() != "return")
			continue;
		Return_Amount++;
		Token* ret = Input->at(j)->OPCODE;
		for (auto r : Push_Amount) {
			Token* reg = new Token(*r->Get_Size_Parent(_SYSTEM_BIT_SIZE_, r));
			reg->ID = reg->Get_Name();


			Input->insert(Input->begin() + j, new IR(new Token(TOKEN::OPERATOR, "pop"), { reg }, Input->at(i)->Location));
			Parse_Complex(Input->at(j), j, true);
		}
		Node* Parent = Global_Scope->Get_Parent_As(FUNCTION_NODE, ret->Get_Parent());
		if (Parent->Size_of_Call_Space + Parent->Local_Allocation_Space > 0) {
			selector->DeAllocate_Stack(Parent->Size_of_Call_Space + Parent->Local_Allocation_Space, Input, j);
			for (auto k : Input->at(j)->Arguments)
				Registerize(k, j);
		}
	}

	for (int j = i + (int)Push_Amount.size() + Additional_Changes; j > Start_Of_Function; j--) {
		for (auto& arg : Input->at(j)->Arguments)
			for (auto& Child : arg->Get_All(TOKEN::LOCAL_VARIABLE_SCOPE)) {
				int Current_Offset = atoi(Child->Get_Name().c_str());
				Current_Offset += selector->Calculate_Memory_Address(TOKEN::LOCAL_VARIABLE_SCOPE);
				Child->Set_Name(to_string(Current_Offset));

			}
	}

	selector->Clean_Register_Holders();
	selector->Clean_Stack();
	//find the current end of function location.
	for (; !Input->at(i)->is(TOKEN::END_OF_FUNCTION); i++);
}

void IRPostProsessor::Prepare_Function(int& i)
{
	if (!Input->at(i)->is(TOKEN::START_OF_FUNCTION))
		return;

	//selector->Allocate_Stack(Global_Scope->Find(Input->at(i)->OPCODE->Get_Name(), Global_Scope)->Max_Allocation_Space, Input, i + 1);
	
	Node* Scope = Input->at(i)->OPCODE->Get_Parent();

	Node* Func = Scope->Find(Input->at(i)->OPCODE->OG);

	int Before_OpCode_Additions = Input->size();
	for (auto p : Func->Defined) {
		if (!p->is(PARAMETER_NODE))
			continue;
		Token* tmp = new Token(p);
		if (tmp->is(TOKEN::REGISTER))
			selector->Get_New_Reg(Input, i+1, new Token(p));
	}

	i += (Input->size() - Before_OpCode_Additions) + (Input->size() > Before_OpCode_Additions);
}

void IRPostProsessor::Handle_Labels(int i)
{
	if (!Input->at(i)->is(TOKEN::LABEL))
		return;

	if (!Input->at(i)->is(TOKEN::START_OF_FUNCTION))
		return;

	Node* Scope = Input->at(i)->OPCODE->Get_Parent();

	Node* Func = Scope->Find(Input->at(i)->OPCODE->OG, Scope, FUNCTION_NODE);

	if (Func->Size_of_Call_Space == 0 && Func->Local_Allocation_Space == 0)
		return;

	selector->Allocate_Stack(Func->Size_of_Call_Space + Func->Local_Allocation_Space, Input, i + 1);

	selector->Init_Stack(Func);
}

void IRPostProsessor::Handle_Stack_Usages(Token* t)
{
	if (t->is(TOKEN::MEMORY))
		for (auto& i : t->Childs)
			Handle_Stack_Usages(i);
	if (t->is(TOKEN::OFFSETTER) || t->is(TOKEN::DEOFFSETTER) || t->is(TOKEN::SCALER)) {
		Handle_Stack_Usages(t->Left);
		Handle_Stack_Usages(t->Right);
	}
	if (!t->is(TOKEN::CONTENT))
		return;

	if (t->is(TOKEN::GLOBAL_VARIABLE)) {
		*t = Token(TOKEN::OFFSETTER, "+", new Token(TOKEN::POSITION_INDEPENDENT_REGISTER | TOKEN::REGISTER, ".RIP", _SYSTEM_BIT_SIZE_), new Token(TOKEN::GLOBAL_VARIABLE, t->Get_Name(), t->Get_Size()));
	}
	else {
		if (t->Has({ TOKEN::REGISTER_SAVE_SPACE })) {
			*t = Token(TOKEN::OFFSETTER, "+", new Token(TOKEN::STACK_POINTTER | TOKEN::REGISTER, ".STACK", _SYSTEM_BIT_SIZE_), new Token(TOKEN::NUM, to_string(selector->Calculate_Memory_Address(t))));
		}
		else {
			//first update the stack offset.
			Node* Function = t->Get_Parent();

			/*Function->Update_Defined_Stack_Offsets();*/

			Node* og = Function->Find(t->Get_Name());

			//this is for memory usage parameters
			long long Pushes_Also_Determine_The_Parameter_Location = TOKEN::NUM;
			if (og->is(PARAMETER_NODE) && !Token(og, true).is(TOKEN::REGISTER))
				Pushes_Also_Determine_The_Parameter_Location |= TOKEN::ADD_NON_VOLATILE_SPACE_NEEDS_HERE;
			else
				Pushes_Also_Determine_The_Parameter_Location |= TOKEN::LOCAL_VARIABLE_SCOPE;


			long long Offset = 0;// = selector->Calculate_Memory_Address(TOKEN::LOCAL_VARIABLE_SCOPE);

			//Maybe we need to add the parameters addresses here?
			if (og->Memory_Offset >= 0 || og->is(PARAMETER_NODE))
				*t = Token(TOKEN::OFFSETTER, "+", new Token(TOKEN::STACK_POINTTER | TOKEN::REGISTER, ".STACK", _SYSTEM_BIT_SIZE_), new Token(Pushes_Also_Determine_The_Parameter_Location, to_string(og->Memory_Offset + Offset)));
			/*else if (og->Memory_Offset + Offset == 0)
				*t = Token(TOKEN::STACK_POINTTER | TOKEN::REGISTER, ".STACK", _SYSTEM_BIT_SIZE_);*/
			else if (og->Memory_Offset < 0)
				*t = Token(TOKEN::DEOFFSETTER, "-", new Token(TOKEN::STACK_POINTTER | TOKEN::REGISTER, ".STACK", _SYSTEM_BIT_SIZE_), new Token(Pushes_Also_Determine_The_Parameter_Location, to_string(og->Memory_Offset + Offset)));
		}
	}
}

int IRPostProsessor::Parse_Complex(IR* ir, int i, bool Registry)
{
	if (!ir->is(TOKEN::OPERATOR))
		return 0;
	if (selector->Get_Opcode(ir)->Complex != nullptr) {
		vector<IR*> r = selector->Get_Opcode(ir)->Complex(ir->Arguments);
		if (r.size() == 0)
			return 0;
		int Changes = r.size() - 1;
		if (Registry)
			for (int opc = 0; opc < r.size(); opc++)
				for (auto arg : r[opc]->Arguments) {
					Registerize(arg, i + opc);
				}
		Input->erase(Input->begin() + i);
		Input->insert(Input->begin() + i, r.begin(), r.end());
		//go through the added complex content and iterate them into complex again, 
		//this feature is made for recursive complex usage.
		for (int j = 0; j < r.size(); j++)
			Changes += Parse_Complex(Input->at(i + j), i + j, Registry);
		return Changes;
	}
	return 0;
}

void IRPostProsessor::Factory()
{
	Handle_Global_Labels();
	for (int i = 0; i < Input->size(); i++)
		Parse_Complex(Input->at(i), i, false);
	for (int i = 0; i < Input->size(); i++)
		Scale_To_Same_Size(i);
	for (int i = 0; i < Input->size(); i++) {
		selector->Reset_Parameter_Register_Count(Input->at(i));
		Prepare_Function(i);
		Handle_Labels(i);
		IR* Holder = Input->at(i);
		reverse(Holder->Arguments.begin(), Holder->Arguments.end());
		for (auto a : Holder->Arguments) {
			Handle_Stack_Usages(a);
			Registerize(a, i);
		}
		reverse(Holder->Arguments.begin(), Holder->Arguments.end());
		Clean_Selector(i);
	}
}
