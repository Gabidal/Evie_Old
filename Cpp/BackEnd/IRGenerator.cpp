#include "../../H/BackEnd/BackEnd.h"
#include "..\..\H\BackEnd\IRGenerator.h"

void IRGenerator::Factory()
{
}

void IRGenerator::Parse_Function(int i)
{
	if (!Input[i]->is(FUNCTION_NODE))
		return;

	//label
	IR* Label = Make_Label(Input[i]);
	Output.push_back(Label);

	//go through the childs of the function
	IRGenerator g(Input[i], Input[i]->Childs, Output);

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

}

IR* IRGenerator::Make_Label(Node* n)
{
	Token* label_name = new Token(TOKEN::LABEL, n->Name);
	IR* label = new IR();
	label->OPCODE = label_name;
	return label;
}
