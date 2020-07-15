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

vector<int> Parser::Get_Amount_Of(int i, long Flag)
{
	//<summary>
	//check from the index to next and counts-
	//how many componets match the flag given
	//</summary>
	vector<int> Indexes;
	for (; i < Input.size(); i++) {
		if (Input[i].is(Flag))
			Indexes.push_back(i);
		else
			if  (Input[i].is(Flags::END_COMPONENT) || 
				(Input[i].is(Flags::COMMENT_COMPONENT)))
				continue;
			else
				break;
	}
	return Indexes;
}

vector<Component> Parser::Get_Inheritting_Components(int i)
{
	//import int ptr func a
	vector<Component> Result;
	for (; i < Input.size(); i++) {
		if (Input[i].is(Flags::KEYWORD_COMPONENT) || (Is_Defined(Input[i].Value, Parent) != nullptr) || Input[i].Value == ".")
			Result.push_back(Input[i]);
		else 
			break;
	}
	return Result;
}

void Parser::Definition_Pattern(int i)
{
	//foo ptr a = ...
	//<summary>
	//list all previusly defined and find the last as an text to define a new object
	//put that result object into parents defined list and also into-
	//the INPUT[i + object index] the newly created object
	//</summary>
	if (!(Get_Inheritting_Components(i).size() > 0))
		return;
	if (i + Get_Inheritting_Components(i).size() + 1 > Input.size())
		return;
	if (!(Input[i + Get_Inheritting_Components(i).size() - 1 + 1].is(Flags::TEXT_COMPONENT)))
		return;
	if (Get_Inheritting_Components(i)[0].Value == ".")
		return;
	//type a
	vector<string> Inheritted;


	for (int j = 0; j < Get_Inheritting_Components(i).size(); j++) {
		if (Input[(size_t)i + j].is(Flags::KEYWORD_COMPONENT)) {
			Node keyword(KEYWORD_NODE);
			keyword.Name	= Input[(size_t)i + j].Value;
			keyword.Parent	= Parent;
			Inheritted.push_back(keyword.Name);
		}
		else {
			Inheritted.push_back(Input[(size_t)i + j].Value);
		}
	}

	Object_Definition_Node New_Defined_Object;
	New_Defined_Object.Inheritted = Inheritted;
	New_Defined_Object.Name = Input[i + Get_Inheritting_Components(i).size() - 1 + 1].Value;
	Parent->Defined.push_back(new Object_Definition_Node(New_Defined_Object));

	//for later AST use
	Input[i + New_Defined_Object.Inheritted.size() -1 + 1].node = new Object_Definition_Node(New_Defined_Object);

	Input.erase(Input.begin() + i, Input.begin() + i + New_Defined_Object.Inheritted.size());
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

void Parser::Parenthesis_Pattern(int i)
{
	// a = (a + b) * c
	//<summary>
	//go the content of the paranthesis and resurn an object
	//put that result object into the INPUT[i + object index] the newly created paranthesis
	//</summary>
	if (!Input[i].is(Flags::PAREHTHESIS_COMPONENT))
		return;
	//create an content Node and output will be in the same input.
	Content_Node Paranthesis;
	Paranthesis.Parent = Parent;
	
	Parser TMP_Parser(Parent);
	TMP_Parser.Input = Input[i].Components;
	TMP_Parser.Factory();

	for (Component j : TMP_Parser.Input)
		if (j.node != nullptr)
			Paranthesis.Childs.push_back(new Node(*j.node));

	Paranthesis.Paranthesis_Type = Input[i].Value[0];
	Input[i].Components = TMP_Parser.Input;
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
	if (Input[i].node != nullptr)
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
	Input.erase(Input.begin() + i + 1);
	Input.erase(Input.begin() + i - 1);

	if (i + 1 > Input.size() - 1)
		return;
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

void Parser::String_Pattern(int i)
{
	//<summary>
	//Make component string into real string_node.
	//</summary>
	if (!Input[i].is(Flags::STRING_COMPONENT))
		return;
	String_Node String;
	String.Value = Input[i].Value;
	Input[i].node = new String_Node(String);
	return;
}

void Parser::Operator_PreFix_Pattern(int i, vector<string> Prefixes)
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

void Parser::Callation_Pattern(int i)
{
	//<summary>
	//Notice!!! the Parameter Paranthesis must be before this defined!!!
	//Also the callation as an object should be already be in the node member
	//</summary>
	if (!Input[i].is(Flags::TEXT_COMPONENT))
		return;
	if (Get_Amount_Of(i + 1, Flags::PAREHTHESIS_COMPONENT).size() != 1)
		return;
	if (Input[i + 1].Value[0] != '(')
		return;

	Call_Node* call = new Call_Node;

	//initialize the parenthesis that contains the parameters
	Parenthesis_Pattern(i + 1);

	call->Paranthesis = *(Content_Node*)Input[(size_t)i + 1].node;
	Input[i].node = call;

	Input.erase(Input.begin() + i + 1);
	return;
}

void Parser::Array_Pattern(int i)
{
	//<summary>
	//find paranthesis with signature of '[' and put it into Input[i]
	//Notice!!! The paranthesis must be initialized before this unition of array operation!!!
	//</summary>
	if (!Input[i].is(Flags::TEXT_COMPONENT))
		return;
	if (i + 1 > Input.size() - 1)
		return;
	if (!Input[(size_t)i + 1].is(Flags::PAREHTHESIS_COMPONENT))
		return;
	if (((Content_Node*)Input[(size_t)i + 1].node)->Paranthesis_Type != '[')
		return;

	Operator_Node* arr = new Operator_Node;

	//TODO:
	//Needs more testing with more complex array usage like: a[x][y][z]
	arr->Left_Side_Nodes = new Node(*Input[i].node);
	arr->Right_Side_Nodes = new Node(*((Content_Node*)Input[(size_t)i + 1].node)->Childs[0]);
	arr->Name = "[]";

	Input[i].node = arr;

	Input.erase(Input.begin() + i + 1);
	return;
}

void Parser::Function_Pattern(int i)
{
	//import loyal int func main() [\n] {..}
	//<summary>
	//Notice!!! The parameter parenthesis & Childs parenthesis must be already initialized!!!
	//Notice!!! The construction of function must be done before this!!!
	//Notice!!! The Including must be done before this!!!
	//Notice!!! This must be done before Object_Pattern & after Defintitin_Pattern!!!
	//Build the function as 
	//</summary>
	if (Input[i].node == nullptr)
		return;
	if (Input[i].is(Flags::KEYWORD_COMPONENT))
		return;
	vector<int> Parenthesis_Indexes = Get_Amount_Of(i + 1, Flags::PAREHTHESIS_COMPONENT);
	if (Parenthesis_Indexes.size() != 2)
		return;
	if (Input[Parenthesis_Indexes[0]].Value[0] != '(')
		return;

	/*
	Object_Definition_Node* Function_Definition = nullptr;
	if ((size_t)i - 1 < Input.size())
		Function_Definition = (Object_Definition_Node*)Is_Defined(Input[i].Value, Parent);
	if (Function_Definition == nullptr)
		cout << "Error: Function definition wasnt found!" << endl;
	*/

	//first try to get the behavior
	Function_Node* func = new Function_Node;
	func->Constructor = Input[i].node;
	func->Name = Input[i].Value;
	func->Parent = Parent;

	Parser p((Scope_Node*)func);
	p.Input.push_back(Input[Parenthesis_Indexes[0]]);
	p.Factory();
	func->Parameters = *(Content_Node*)p.Input[0].node;
	p.Input.clear();

	p.Input.push_back(Input[Parenthesis_Indexes[1]]);
	p.Factory();
	func->Childs = *(Content_Node*)p.Input[0].node;
	p.Input.clear();

	Input[i].node = func;

	Input.erase(Input.begin() + Parenthesis_Indexes[0]);
	Input.erase(Input.begin() + Parenthesis_Indexes[1] - 1);

	return;
}

void Parser::Type_Pattern(int i)
{
	//type int{ size 4}
	//<summary>
	//Notice!!! The Parenthesis that contains the members needs to be initialized before this!!!
	//Does same as the Function_Pattern but just one less parenthesis to worrie about.
	//</summary>
	if (!Input[i].is(Flags::TEXT_COMPONENT))
		return;
	if (Is_Defined(Input[i].Value, Parent) == nullptr)
		return;
	vector<int> Parenthesis_Indexes = Get_Amount_Of(i, Flags::PAREHTHESIS_COMPONENT);
	if (Parenthesis_Indexes.size() != 1)
		return;
	if (Input[Parenthesis_Indexes[0]].Value[0] != '{')
		return;


	//This works because there is only one constructor named by this type class
	Object_Definition_Node* Type_Definition = nullptr;
	if ((size_t)i - 1 < Input.size())
		Type_Definition = (Object_Definition_Node*)Is_Defined(Input[i].Value, Parent);
	if (Type_Definition == nullptr)
		cout << "Error: Type definition was not found!" << endl;

	Type_Node* Type = new Type_Node;
	Type->Inheritted = Type_Definition->Inheritted;
	Type->Name = Input[i].Value;
	Type->Parent = Parent;

	Parser p((Scope_Node*)Type);
	p.Input.push_back(Input[Parenthesis_Indexes[0]]);
	p.Factory();
	Type->Childs = *(Content_Node*)p.Input[0].node;
	p.Input.clear();

	Input[i].node = Type;

	Input.erase(Input.begin() + Parenthesis_Indexes[0]);

	return;
}

void Parser::Member_Pattern(int i)
{
	//foo.a = 1
	//<summary>
	//
	//
	//</summary>
	if ((size_t)i + 2 > Input.size() - 1)
		return;
	if (Is_Defined(Input[i].Value, Parent) == nullptr)
		return;
	//use operator token to capture the members int o a AST like tree
	//IF LEXER ALREADY USES DOT COMPONENT AS OPERATOR THEN WE DONT NEED TO DO ENYTHING HERE :D.
}

void Parser::If_Pattern(int i)
{
	//<summary>
	//make the AST of condition as IF
	//if <condition/(condition)> <code-single-line/(multiline-code)>
	//Notice!!! The two next components need to be initialized before this!!!
	//</summary>
	if (!Input[i].is(Flags::KEYWORD_COMPONENT))
		return;
	vector<int> Parenthesis_Indexes = Get_Amount_Of(i+1, Flags::PAREHTHESIS_COMPONENT);
	if (Parenthesis_Indexes.size() != 2)
		return;				

	//if (){..}
	//else (){..}		//this works as 'else if'
	//else {..}			//and this as normal 'else'
	//while (..){..}	//loop
	Condition_Node* con;
	if (Input[i].Value == "if")
		con = new Condition_Node(IF_NODE);
	else if (Input[i].Value == "else")
		con = new Condition_Node(ELSE_NODE);
	else
		return;

	Parser p((Scope_Node*)con);
	con->Name = Input[i].Value;
	con->Parent = Parent;

	p.Input.push_back(Input[Parenthesis_Indexes[0]]);
	p.Factory();
	Content_Node Condition(*(Content_Node*)p.Input[0].node);
	p.Input.clear();

	p.Input.push_back(Input[Parenthesis_Indexes[1]]);
	p.Factory();
	Content_Node Child(*(Content_Node*)p.Input[0].node);

	con->Condition_Initializer(Condition, Child);

	Input[i].node = con;

	Input.erase(Input.begin() + Parenthesis_Indexes[0]);
	Input.erase(Input.begin() + Parenthesis_Indexes[1] - 1);

	return;
}

void Parser::Operator_Order()
{
	for (int i = 0; i < Input.size(); i++)
		Array_Pattern(i);
	for (int i = 0; i < Input.size(); i++)
		Operator_PreFix_Pattern(i, { "++", "--", "-" });
	//the combination and multilayering of operations.
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { ":" });
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "." });
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "*", "/" , "%" });
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "<<", ">>" });
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "&", "!&" });
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "?" });
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "|", "!|" });
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "+", "-" });
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "<", ">" });
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "==", "!=", "<=", ">=", "!<", "!>" , "|=", "&=" });
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "=", "+=", "-=", "*=", "/=" });
}

void Parser::Factory() {
	for (int i = 0; i < Input.size(); i++)
		//variable/objects definator.
		Definition_Pattern(i);
	for (int i = 0; i < Input.size(); i++) {
		//multiline AST stuff
		Function_Pattern(i);
		Type_Pattern(i);
		If_Pattern(i);
		Callation_Pattern(i);
	}
	for (int i = 0; i < Input.size(); i++) {
		//prepreattor for math operator AST combinator.
		Object_Pattern(i);
		Parenthesis_Pattern(i);
		String_Pattern(i);
		Number_Pattern(i);
	}
	//AST operator combinator.
	Operator_Order();
}