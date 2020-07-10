#include "../../H/Parser/Parser.h"

Node* Parser::Is_Defined(string name, Scope_Node* p)
{
	for (Node* s : p->Defined)
		if (name == s->Name)
			return s;
	if (p->Parent != nullptr)
		return Is_Defined(name, p->Parent);
	return nullptr;
}

vector<Component> Parser::Get_Inheritting_Components(int i)
{
	//import int ptr func a
	vector<Component> Result;
	for (; i < Input.size(); i++) {
		if (Input[i].is(Flags::KEYWORD_COMPONENT) || !(Is_Defined(Input[i].Value, Parent) != nullptr))
			Result.push_back(Input[i]);
	}
	return Result;
}

void Parser::Definition_Pattern(int i)
{
	//this pattern just goes and looks for type/object/variable definition and tryes to put em into an list
	if (!(Get_Inheritting_Components(i).size() > 0))
		return;
	if (i + Get_Inheritting_Components(i).size() + 1 > Input.size())
		return;
	if (!(Input[i + Get_Inheritting_Components(i).size() + 1].is(Flags::TEXT_COMPONENT)))
		return;
	//type a
	Content_Node Inheritted;

	for (int j = 0; j < Get_Inheritting_Components(i).size(); j++) {
		if (Input[(size_t)i + j].is(Flags::KEYWORD_COMPONENT)) {
			Node keyword(KEYWORD_NODE);
			keyword.Name	= Input[(size_t)i + j].Value;
			keyword.Parent	= Parent;
			Inheritted.Childs.push_back(new Node(keyword));
		}
		else {
			Inheritted.Childs.push_back(Is_Defined(Input[(size_t)i + j].Value, Parent));
		}
	}

	Object_Node New_Defined_Object;
	New_Defined_Object.Inheritted = Inheritted;
	New_Defined_Object.Name = Input[i + Get_Inheritting_Components(i).size() + 1].Value;
	Parent->Defined.push_back(new Object_Node(New_Defined_Object));

	Input.erase(Input.begin() + i, Input.begin() + i + New_Defined_Object.Inheritted.Childs.size() + 1);
	return;
}

void Parser::Paranthesis_Pattern(int i)
{
	if (!Input[i].is(Flags::PAREHTHESIS_COMPONENT))
		return;
	//create an content Node and output it into Parent's childs list.
	Content_Node Paranthesis;
	
	Scope_Node TMP_Parent;
	Parser TMP_Parser(&TMP_Parent);
	TMP_Parser.Input = Input[i].Components;
	TMP_Parser.Factory();

	Paranthesis = TMP_Parent.Childs;
	Paranthesis.Paranthesis_Type = Input[i].Value[0];
	Parent->Childs.Childs.push_back(new Content_Node(Paranthesis));

	Input.erase(Input.begin() + i);
	return;
}

void Parser::Factory() {

}