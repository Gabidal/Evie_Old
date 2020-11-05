#include "../../H/BackEnd/BackEnd.h"

extern Node* Global_Scope;
extern Usr* sys;
extern x86_64_Win X86_64_WIN;
extern Selector* selector;

void BackEnd::Init()
{
	if (sys->Info.Architecture == "x86") {
		if (sys->Info.Bits_Mode == "8") {
			if (sys->Info.OS == "win32") {
				X86_64_WIN.Init();
				Seperator = X86_64_WIN.Seperator;
				Register_Pre_Fix = X86_64_WIN.Register_Pre_Fix;
				Number_Pre_Fix = X86_64_WIN.Number_Pre_Fix;
				Label_Post_Fix = X86_64_WIN.Label_Post_Fix;

				Opcodes = X86_64_WIN.Opcodes;
			}
		}

	}
}

void BackEnd::Factory()
{
	for (auto i : Input) {
		Label_Builder(i);
		Operator_Builder(i);
		End_Of_Function_Builder(i);
	}
}

void BackEnd::Operator_Builder(IR* i)
{
	//leave data handling into other algorithm
	if (!i->is(TOKEN::OPERATOR) && !i->is(TOKEN::FLOW))
		return;
	//get the needed opcode
	IR* opc = selector->Get_Opcode(i);
	*Output += opc->OPCODE->Get_Name() + " ";

	//set up the parameters
	for (int p = 0; p < i->Arguments.size(); p++) {
		*Output += Token_Builder(i->Arguments[p]);
		if ((size_t)p + 1 < i->Arguments.size()) {
			*Output += Seperator + " ";
		}
	}
	//set up the next line
	*Output += "\n";
}

void BackEnd::Label_Builder(IR* i)
{
	if (!i->is(TOKEN::LABEL))
		return;

	*Output += i->OPCODE->Get_Name() + Label_Post_Fix + "\n";
}

void BackEnd::End_Of_Function_Builder(IR* i)
{
	if (!i->is(TOKEN::END_OF_FUNCTION))
		return;

	*Output += "\n\n";
}

string BackEnd::Token_Builder(Token* t)
{
	string PreFix = "";
	string PostFix = "";
	string Result = "";
	string Name = "";
	if (t->is(TOKEN::REGISTER)) {
		Name = t->ID;
	}
	else if (t->is(TOKEN::NUM) || t->is(TOKEN::DECIMAL))
		Name = t->Get_Name();
	else if (t->is(TOKEN::MEMORY)) {
		PreFix = "[";
		for (auto i : t->Childs)
			Name += Token_Builder(i) + " ";
		PostFix = "]";
	}
	else if (t->is(TOKEN::CONTENT)) {
		PreFix = "(";
		for (auto i : t->Childs)
			Name += Token_Builder(i);
		PostFix = ")";
	}
	else if (t->is(TOKEN::OFFSETTER) || t->is(TOKEN::SCALER) || t->is(TOKEN::DEOFFSETTER)) {
		Name += Token_Builder(t->Left) + " " + t->Get_Name() + " " + Token_Builder(t->Right);
	}

	Result = PreFix + Name + PostFix;
	return Result;
}
