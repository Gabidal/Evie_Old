#include "../../H/BackEnd/IRPostProsessor.h"

void IRPostProsessor::Scale_To_Same_Size(int i)
{
	if (!Input->at(i)->is(TOKEN::OPERATOR))
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

	//now inser the new converter before the operator
	Input->insert(Input->begin() + i, CONV);
}

void IRPostProsessor::Factory()
{
}
