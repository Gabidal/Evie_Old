#include "../../H/BackEnd/IRPostProsessor.h"

extern Selector* selector;

void IRPostProsessor::Scale_To_Same_Size(int i)
{
	if (!Input->at(i)->is(TOKEN::OPERATOR))
		return;

	if (!selector->Get_Opcode(Input->at(i))->is(TOKEN::ALL_ARGS_SAME_SIZE))
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
	IR* CONV = new IR(Convert, { NewReg, new Token(*Scalable) });

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
	if (!t->is(TOKEN::REGISTER))
		return;
	if (selector->Get_Register(t) == nullptr)
		if (selector->Get_New_Reg(Input, i, t) == nullptr)
			selector->Allocate_Register(Input, i, t);
	t->ID = selector->Get_Register(t)->Get_Name();
}

void IRPostProsessor::Handle_Calls(int i)
{
	if (!Input->at(i)->is(TOKEN::CALL))
		return;

	//handle the given registers
	//hmm i think the registerizer can handle these too, 
	//the parameters in OPCODE emeber are just for information for the selector.

}

void IRPostProsessor::Clean_Selector(int i)
{
	if (!Input->at(i)->is(TOKEN::END_OF_FUNCTION))
		return;
	//get the start of function index
	int Start_Of_Function = 0;
	for (int j = i; j > 0; j--)
		if (Input->at(j)->is(TOKEN::START_OF_FUNCTION)) {
			Start_Of_Function = j;
			break;
		}
	Start_Of_Function += 2; //Skip the label
	//now we know what non-volatiles are in use
	int Push_Amount = 0;
	for (auto r : selector->Get_Register_Type(TOKEN::NONVOLATILE)) {
		if (r.first == nullptr)
			continue;
		Token* reg = new Token(*r.second->Get_Size_Parent(_SYSTEM_BIT_SIZE_, r.second));
		reg->ID = reg->Get_Name();
		Input->insert(Input->begin() + Start_Of_Function, new IR(new Token(TOKEN::OPERATOR, "push"), { reg }));
		Push_Amount++;
	}
	//now do same but for the end of funciton
	for (int j = i+Push_Amount; j > Start_Of_Function; j--) {
		if (Input->at(j)->OPCODE->Get_Name() != "return")
			continue;
		for (auto r : selector->Get_Register_Type(TOKEN::NONVOLATILE)) {
			if (r.first == nullptr)
				continue;
			Token* reg = new Token(*r.second->Get_Size_Parent(_SYSTEM_BIT_SIZE_, r.second));
			reg->ID = reg->Get_Name();
			Input->insert(Input->begin() + j, new IR(new Token(TOKEN::OPERATOR, "pop"), { reg }));
		}
	}

	selector->Clean_Register_Holders();
}

void IRPostProsessor::Prepare_Function(int i)
{
	if (!Input->at(i)->is(TOKEN::START_OF_FUNCTION))
		return;

	for (auto p : Global_Scope->Find(Input->at(i)->OPCODE->Get_Name(), Global_Scope)->Defined) {
		if (!p->is(PARAMETER_NODE))
			continue;
		Token* tmp = new Token(p);
		if (tmp->is(TOKEN::REGISTER))
			selector->Get_New_Reg(Input, i, new Token(p));
	}
}

void IRPostProsessor::Factory()
{
	for (int i = 0; i < Input->size(); i++)
		Scale_To_Same_Size(i);
	for (int i = 0; i < Input->size(); i++) {
		Prepare_Function(i);
		for (auto a : Input->at(i)->Arguments)
			Registerize(a, i);
		Clean_Selector(i);
	}
}
