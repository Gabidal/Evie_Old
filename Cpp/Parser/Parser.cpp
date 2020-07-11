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
	//foo ptr a = ...
	//<summary>
	//list all previusly defined and find the last as an text to define a new object
	//put that result object into parents defined list and also into the INPUT[i + object index] the newly created object
	//</summary>
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

	//for later AST use
	Input[i + New_Defined_Object.Inheritted.Childs.size() + 1].node = new Object_Node(New_Defined_Object);

	Input.erase(Input.begin() + i, Input.begin() + i + New_Defined_Object.Inheritted.Childs.size());
	return;
}

void Parser::Object_Pattern(int i)
{
	//<summary>
	//Find defined text components and implant-
	//the node repective of that component into the input[i]
	//</summary>
	if (!Input[i].is(Flags::TEXT_COMPONENT))
		return;
	if (Is_Defined(Input[i].Value, Parent) == nullptr)
		return;
	if (Input[i].node != nullptr)
		return;	//we dont want to rewrite the content
	Input[i].node = new Node(*Is_Defined(Input[i].Value, Parent));
	return;
}

void Parser::Paranthesis_Pattern(int i)
{
	// a = (a + b) * c
	//<summary>
	//go the content of the paranthesis and resurn an object
	//put that result object into the INPUT[i + object index] the newly created paranthesis
	//</summary>
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
	Input[i].node = new Content_Node(Paranthesis);

	return;
}

void Parser::Math_Pattern(int i, vector<string> Operators)
{
	//<summary>
	//This function paternises the math order.
	//Before this function the variables/functioncalls/parenthesis/ need to be-
	//already made into Nodes and saved into the Components node member.
	//</summary>
	//a = b + c * d
	if (!Input[i].is(Flags::OPERATOR_COMPONENT))
		return;
	if (i - 1 < 0)
		return;
	if (((size_t)i + 1) > Input.size())
		return;
	bool op_Pass = false;
	for (string s : Operators)
		if (Input[i].Value == s)
			op_Pass = true;
	if (!op_Pass)
		return;

	Operator_Node Operator;
	Operator.Name = Input[i].Value;

	if (Input[(size_t)i - 1].node != nullptr)
		Operator.Left_Side_Nodes = Input[(size_t)i - 1].node;
	else
		cout << "Error: Left side Of operator " << Input[i].Value << " is not Initialized!" << endl;

	if (Input[(size_t)i + 1].node != nullptr)
		Operator.Right_Side_Nodes = Input[(size_t)i + 1].node;
	else
		cout << "Error: Right side Of operator " << Input[i].Value << " is Initialized!" << endl;

	Input[i].node = new Operator_Node(Operator);
	Input.erase(Input.begin() + i - 1);
	Input.erase(Input.begin() + i + 1);

	if (Input[i].is(Flags::OPERATOR_COMPONENT))
		Math_Pattern(i, Operators);
	return;
}

void Parser::Number_Pattern(int i)
{
	//<summary>
	//Make component numbers into real number_node.
	//</summary>
	if (!Input[i].is(Flags::NUMBER_COMPONENT))
		return;
	Number_Node Num;
	Num.Value = Input[i].Value;
	Input[i].node = new Number_Node(Num);
	return;
}

void Parser::Operator_PreFix(int i, vector<string> Prefixes)
{
	//<summary>
	//-123/-a/-b()
	//++a/++b()
	//Adds the Operator_Prefix into the next object
	//</summary>
	if (!Input[i].is(Flags::OPERATOR_COMPONENT))
		return;
	if (Input[i - 1].is(Flags::TEXT_COMPONENT))		//a -b
		return;
	if (Input[i - 1].is(Flags::PAREHTHESIS_COMPONENT))		//(a+b) -a
		return;
	if (((size_t)i + 1) > Input.size())
		return;
	bool op_Pass = false;
	for (string s : Prefixes)
		if (Input[i].Value == s)
			op_Pass = true;
	if (!op_Pass)
		return;
	PreFix_Node PreFix;
	PreFix.Fix = Input[i].Value;
	PreFix.node = Input[i + 1].node;
	
	//Operator_Node PreFix;	//++a/-a/--a
	//Operator_Node PostFix;	//a++/a--
	Input[i].node = new PreFix_Node(PreFix);

	Input.erase(Input.begin() + i + 1);
}

void Parser::Factory() {

}