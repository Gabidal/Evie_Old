#include "../../H/BackEnd/BackEnd.h"

extern Node* Global_Scope;
extern Usr* sys;
extern x86_64 X86_64;
extern ARM_64 _ARM_64;
extern Selector* selector;

void BackEnd::Init()
{
	if (sys->Info.Architecture == "x86") {
		if (sys->Info.Bytes_Mode == "8") {
			Seperator = X86_64.Seperator;
			Register_Pre_Fix = X86_64.Register_Pre_Fix;
			Number_Pre_Fix = X86_64.Number_Pre_Fix;
			Label_Post_Fix = X86_64.Label_Post_Fix;
		}

	}	
	else if (sys->Info.Architecture == "arm") {
		if (sys->Info.Bytes_Mode == "8") {
			if (sys->Info.OS == "win" || sys->Info.OS == "unix") {
				Seperator = _ARM_64.Seperator;
				Register_Pre_Fix = _ARM_64.Register_Pre_Fix;
				Number_Pre_Fix = _ARM_64.Number_Pre_Fix;
				Label_Post_Fix = _ARM_64.Label_Post_Fix;
			}
		}

	}
}

void BackEnd::Factory()
{
	int j = 0;
	for (auto i : Input) {
		Label_Builder(i);
		Global_Builder(i);
		Operator_Builder(i);
		End_Of_Function_Builder(i);
		Call_Builder(i);
		j++;
	}
}

void BackEnd::Operator_Builder(IR* i)
{
	//leave data handling into other algorithm
	if (!i->is(TOKEN::OPERATOR) && !i->is(TOKEN::FLOW) && !i->is(TOKEN::SET_DATA))
		return;
	//get the needed opcode
	IR* opc = selector->Get_Opcode(i);
	*Output += opc->OPCODE->Get_Name() + " ";

	//set up the parameters
	for (int p = 0; p < i->Arguments.size(); p++) {
		*Output += Token_Builder(i->Arguments[p], i->is(TOKEN::SET_DATA));
		if ((size_t)p + 1 < i->Arguments.size()) {
			*Output += Seperator + " ";
		}
	}
	//set up the next line

	string Comment = "\t\t#";

	for (int j = 0; j < i->Arguments.size(); j++) {
		Comment += i->Arguments[j]->Get_Name();
		if (j != i->Arguments.size() - 1)
			Comment += ", ";
	}

	*Output += Comment + "\n";
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

void BackEnd::Call_Builder(IR* i)
{
	if (!i->is(TOKEN::CALL))
		return;

	IR* call_opc = selector->Get_Opcode(i);
	*Output += call_opc->OPCODE->Get_Name();

	*Output += " " + Token_Builder(i->Arguments[0]) + "\n";
}

void BackEnd::Global_Builder(IR* i)
{
	if (!i->is(TOKEN::GLOBAL_LABEL))
		return;

	IR* glob = selector->Get_Opcode(i);
	*Output += glob->OPCODE->Get_Name();

	*Output += " " + Token_Builder(i->Arguments[0]) + "\n";
}

string BackEnd::Token_Builder(Token* t, bool Inside_Content)
{
	string PreFix = "";
	string PostFix = "";
	string Result = "";
	string Name = "";
	if (t->is(TOKEN::REGISTER) || t->is(TOKEN::NONVOLATILE) || t->is(TOKEN::RETURNING) || t->is(TOKEN::QUOTIENT) || t->is(TOKEN::REMAINDER) || t->is(TOKEN::PARAMETER)) {
		Name = t->ID->Name;
	}
	else if (t->is(TOKEN::NUM) || (t->is(TOKEN::DECIMAL) && !t->is(TOKEN::MEMORY))) {
		//if (Inside_Content)
		Name = t->Get_Name();
		//else
		//	Name = selector->Get_Size_Identifier(t->Get_Size()) + " " + t->Get_Name();
	}
	else if (t->is(TOKEN::STRING))
		Name = "\"" + t->Get_Name() + "\"";
	else if (t->is(TOKEN::GLOBAL_VARIABLE))
		//Name = selector->Get_Size_Identifier(t->Get_Size()) + "[" + t->Get_Name() + "]";
		Name = t->Get_Name();
	else if (t->is(TOKEN::MEMORY)) {
		if (Inside_Content)
			PreFix = t->Get_Name();
		else
			PreFix = selector->Get_Size_Identifier(t->Get_Size()) + " [";
		for (auto i : t->Childs)
			Name += Token_Builder(i, true) + " ";
		PostFix = "]";
	}
	else if (t->is(TOKEN::CONTENT)) {
		PreFix = "(";
		for (auto i : t->Childs)
			Name += Token_Builder(i, true);
		PostFix = ")";
	}
	else if (t->is(TOKEN::OFFSETTER) || t->is(TOKEN::SCALER) || t->is(TOKEN::DEOFFSETTER)) {
		Name += Token_Builder(t->Left, true) + " " + t->Get_Name() + " " + Token_Builder(t->Right, true);
	}
	else if (t->is(TOKEN::LABEL))
		Name = t->Get_Name();

	Result = PreFix + Name + PostFix;
	return Result;
}
