#include "../../H/Parser/Parser.h"

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
		if (Input[i].is(Flags::KEYWORD_COMPONENT) || (Parent->Find(Input[i].Value, Parent, false) != nullptr) || Input[i].Value == ".")
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

	Node* New_Defined_Object = new Node(OBJECT_DEFINTION_NODE);
	New_Defined_Object->Inheritted = Inheritted;
	New_Defined_Object->Name = Input[i + Get_Inheritting_Components(i).size() - 1 + 1].Value;
	New_Defined_Object->Parent = Parent;
	Parent->Defined.push_back(New_Defined_Object);

	//for later AST use
	Input[i + New_Defined_Object->Inheritted.size() -1 + 1].node = New_Defined_Object;

	Input.erase(Input.begin() + i, Input.begin() + i + New_Defined_Object->Inheritted.size());
	return;
}

void Parser::Duplicated_Prototype_Handler(int i)
{	
	//foo ptr a = ...
	//<summary>
	//list all previusly defined and find the last as an text to define a new object
	//put that result object into parents defined list and also into-
	//the INPUT[i + object index] the newly created object
	//</summary>
	if (Input[i].node != nullptr)
		return;
	if (!(Get_Inheritting_Components(i).size() > 0))
		return;
	if (i + Get_Inheritting_Components(i).size() + 1 > Input.size())
		return;
	if (!(Input[i + Get_Inheritting_Components(i).size() - 1 + 1].is(Flags::PAREHTHESIS_COMPONENT)))
		return;
	if (!Input[i + Get_Inheritting_Components(i).size() - 1].is(Flags::TEXT_COMPONENT))
		//if this is is true that means the case is a duplicate prototypes.
		return;
	if (Get_Inheritting_Components(i)[0].Value == ".")
		return;
	//type a
	vector<string> Inheritted;


	for (int j = 0; j < Get_Inheritting_Components(i).size() -1; j++) {
		if (Input[(size_t)i + j].is(Flags::KEYWORD_COMPONENT)) {
			Node keyword(KEYWORD_NODE);
			keyword.Name = Input[(size_t)i + j].Value;
			keyword.Parent = Parent;
			Inheritted.push_back(keyword.Name);
		}
		else {
			Inheritted.push_back(Input[(size_t)i + j].Value);
		}
	}

	Node* New_Defined_Object = new Node(OBJECT_DEFINTION_NODE);
	New_Defined_Object->Inheritted = Inheritted;
	New_Defined_Object->Name = Input[i + Get_Inheritting_Components(i).size() - 1].Value;
	New_Defined_Object->Parent = Parent;
	Parent->Defined.push_back(New_Defined_Object);

	//for later AST use
	Input[i + New_Defined_Object->Inheritted.size() - 1 + 1].node = New_Defined_Object;

	Input.erase(Input.begin() + i, Input.begin() + i + New_Defined_Object->Inheritted.size());
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
	if (Parent->Find(Input[i].Value, Parent, true) == nullptr)
		return;
	if (Input[i].node != nullptr)
		return;	//we dont want to rewrite the content
	Input[i].node = new Node(*Parent->Find(Input[i].Value, Parent, true));
	Input[i].node->Type = OBJECT_NODE;
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
	Node* Paranthesis = new Node(CONTENT_NODE);
	Paranthesis->Parent = Parent;
	
	Parser TMP_Parser(Parent);
	TMP_Parser.Input = Input[i].Components;
	TMP_Parser.Factory();

	for (Component j : TMP_Parser.Input)
		if (j.node != nullptr)
			Paranthesis->Childs.push_back(new Node(*j.node));

	Paranthesis->Paranthesis_Type = Input[i].Value[0];
	Input[i].Components = TMP_Parser.Input;
	Input[i].node = Paranthesis;

	return;
}

void Parser::Math_Pattern(int i, vector<string> Operators, int F)
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

	Node* Operator = new Node(F);
	Operator->Name = Input[i].Value;

	if (Input[(size_t)i - 1].node != nullptr)
		Operator->Left = Input[(size_t)i - 1].node;
	else {
		//Dont worry about function calls
		Node* new_member = new Node(OBJECT_DEFINTION_NODE);
		new_member->Name = Input[(size_t)i - 1].Value;

		Operator->Left = new_member;
	}

	if (Input[(size_t)i + 1].node != nullptr)
		Operator->Right = Input[(size_t)i + 1].node;
	else {
		//test.a.m //these a.m are in different localscope.
		//the right side does not need to be determined as well the left.
		//Dont worry about function calls
		Node* new_member = new Node(OBJECT_DEFINTION_NODE);
		new_member->Name = Input[(size_t)i + 1].Value;

		Operator->Right = new_member;
	}

	//this is for advanced only!!
	if (Input[i].Value == "-")
		Operator->Right->Coefficient *= -1;

	Input[i].node = Operator;
	Input.erase(Input.begin() + i + 1);
	Input.erase(Input.begin() + i - 1);

	if ((size_t)i + 1 > Input.size() - 1)
		return;
	if (Input[i].is(Flags::OPERATOR_COMPONENT))
		Math_Pattern(i, Operators, F);
	return;
}

void Parser::Number_Pattern(int i)
{
	//<summary>
	//Make component numbers into real number_node.
	//</summary>
	if (!Input[i].is(Flags::NUMBER_COMPONENT))
		return;
	Node* Num = new Node(NUMBER_NODE);
	Num->Name = Input[i].Value;
	Num->Parent = Parent;
	Input[i].node = Num;
	return;
}

void Parser::String_Pattern(int i)
{
	//<summary>
	//Make component string into real string_node.
	//</summary>
	if (!Input[i].is(Flags::STRING_COMPONENT))
		return;
	Node* String = new Node(STRING_NODE);
	String->Name = Input[i].Value;
	Input[i].node = String;
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
	if (Input[(size_t)i - 1].is(Flags::TEXT_COMPONENT))		//a -b
		return;
	if (Input[(size_t)i - 1].is(Flags::NUMBER_COMPONENT))		//1 -b
		return;
	if (Input[(size_t)i - 1].is(Flags::PAREHTHESIS_COMPONENT))		//(a+b) -a
		return;
	if (((size_t)i + 1) > Input.size())
		return;
	bool op_Pass = false;
	for (string s : Prefixes)
		if (Input[i].Value == s)
			op_Pass = true;
	if (!op_Pass)
		return;
	Node* PreFix = new Node(PREFIX_NODE);
	//name
	PreFix->Name = Input[i].Value;
	//for more complex casting
	PreFix->Left = Input[i].node;
	PreFix->Right = Input[(size_t)i + 1].node;
	
	//Operator_Node PreFix;	//++a/-a/--a
	//Operator_Node PostFix;	//a++/a--
	Input[i].node = PreFix;

	Input.erase(Input.begin() + i + 1);
}

void Parser::Operator_PostFix_Pattern(int i, vector<string> Postfix)
{	
	//<summary>
	//a--/b()--
	//a++/b()++
	//Adds the Operator_Postfix into the previus object
	//</summary>
	if (!Input[i].is(Flags::OPERATOR_COMPONENT))
		return;		//++
	if ((size_t)i + 1 < Input.size() - 1) {
		if (Input[(size_t)i + 1].is(Flags::TEXT_COMPONENT))
			return;		//++ abc
		if (Input[(size_t)i + 1].is(Flags::PAREHTHESIS_COMPONENT))
			return;		//++ (..)
	}

	bool op_Pass = false;
	for (string s : Postfix)
		if (Input[i].Value == s)
			op_Pass = true;
	if (!op_Pass)
		return;

	Node* post = new Node(POSTFIX_NODE);
	post->Name = Input[i].Value;
	
	//set the node to postfix as left
	post->Left = Input[(size_t)i - 1].node;
	//for casting
	post->Right = Input[i].node;

	Input[i].node = post;

	Input.erase(Input.begin() + i - 1);

	return;
}

void Parser::Variable_Negate_Pattern(int i)
{
	if (Input[i].Value != "-")
		return;
	if (Input[(size_t)i - 1].is(Flags::TEXT_COMPONENT))		//a -b
		return;
	if (Input[(size_t)i - 1].is(Flags::NUMBER_COMPONENT))		//1 -b
		return;
	if (Input[(size_t)i - 1].is(Flags::PAREHTHESIS_COMPONENT))		//(a+b) -a
		return;
	if (((size_t)i + 1) > Input.size())
		return;

	Input[(size_t)i+1].node->Coefficient *= -1;

	//remove the negettor operator
	Input.erase(Input.begin() + i);

	return;
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
	if (Input[(size_t)i + 1].Value[0] != '(')
		return;

	Node* call;

	if (Input[i].node != nullptr) {
		if (Input[i].node->Inheritted.size() > 0) {
			//this is how prototypes are made!
			call = new Node(PROTOTYPE);
			call->Inheritted = Input[i].node->Inheritted;
		}
		else
			call = new Node(CALL_NODE);
	}
	else
		call = new Node(CALL_NODE);
	call->Name = Input[i].Value;
	call->Parent = Parent;

	//initialize the parenthesis that contains the parameters
	Parenthesis_Pattern(i + 1);

	call->Parameters = Input[(size_t)i + 1].node->Childs;
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
	if (Input[(size_t)i + 1].node->Paranthesis_Type != '[')
		return;

	Node* arr = new Node(ARRAY_NODE);

	//TODO:
	//Needs more testing with more complex array usage like: a[x][y][z]
	arr->Left = new Node(*Input[i].node);
	arr->Right = new Node(*Input[(size_t)i + 1].node->Childs[0]);
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
	Node* func = nullptr;
	if (Input[i].node->Type == OBJECT_DEFINTION_NODE)
		func = Input[i].node;
	else
		func = Parent->Find(Input[i].Value, Parent, true);
	if (func == nullptr)
		cout << "Error: Parser didnt find " << Input[i].node->Name << " constructor!" << endl;
	//override the object definition node flag
	func->Type = FUNCTION_NODE;
	//set the other values
	func->Name = Input[i].Value;
	func->Parent = Parent;

	Parser p(func);
	p.Input.push_back(Input[Parenthesis_Indexes[0]]);
	p.Factory();
	func->Parameters = p.Input[0].node->Childs;
	p.Input.clear();

	p.Input.push_back(Input[Parenthesis_Indexes[1]]);
	p.Factory();
	func->Childs = p.Input[0].node->Childs;
	p.Input.clear();

	func->Mangled_Name = func->Get_Mangled_Name();

	Input[i].node = func;

	Input.erase(Input.begin() + Parenthesis_Indexes[1]);
	Input.erase(Input.begin() + Parenthesis_Indexes[0]);

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
	if (Parent->Find(Input[i].Value, Parent, false) == nullptr)
		return;
	vector<int> Parenthesis_Indexes = Get_Amount_Of(i + 1, Flags::PAREHTHESIS_COMPONENT);
	if (Parenthesis_Indexes.size() != 1)
		return;
	if (Input[Parenthesis_Indexes[0]].Value[0] != '{')
		return;


	//This works because there is only one constructor named by this type class
	Node* Type = nullptr;
	if (i < Input.size())
		Type = Parent->Find(Input[i].Value, Parent, true);
	if (Type == nullptr)
		cout << "Error: Type definition was not found!" << endl;
	//reset the value
	Type->Type = CLASS_NODE;

	Parser p(Type);
	p.Input.push_back(Input[Parenthesis_Indexes[0]]);
	p.Factory();
	Type->Childs = p.Input[0].node->Childs;
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
	//if ((size_t)i + 2 > Input.size() - 1)
	//	return;
	//if (Parent->Find(Input[i].Value, Parent) == nullptr)
	//	return;
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
	vector<int> Parenthesis_Indexes = Get_Amount_Of(i + 1, Flags::PAREHTHESIS_COMPONENT);
	if (Parenthesis_Indexes.size() != 2)
		return;				

	//if (){..}
	//else (){..}		//this works as 'else if'
	//else {..}			//and this as normal 'else'
	//while (..){..}	//loop
	Node* con;
	if (Input[i].Value == "if")
		con = new Node(IF_NODE);
	else if (Input[i].Value == "while")
		con = new Node(WHILE_NODE);
	else if (Input[i].Value == "else")
		con = new Node(ELSE_NODE);		//this works for only else if because it requers 2 paranthesis
	else
		return;

	Parser p(con);
	con->Name = Input[i].Value;
	con->Parent = Parent;

	p.Input.push_back(Input[Parenthesis_Indexes[0]]);
	p.Factory();

	con->Parameters = p.Input[0].node->Childs;

	p.Input.clear();

	p.Input.push_back(Input[Parenthesis_Indexes[1]]);
	p.Factory();

	con->Childs = p.Input[0].node->Childs;

	Input[i].node = con;

	Input.erase(Input.begin() + Parenthesis_Indexes[0]);
	Input.erase(Input.begin() + Parenthesis_Indexes[1] - 1);

	return;
}

void Parser::Else_Pattern(int i)
{
	//here we patternise the alse without a condition
	if (!Input[i].is(Flags::KEYWORD_COMPONENT))
		return;
	vector<int> Parenthesis_Indexes = Get_Amount_Of(i + 1, Flags::PAREHTHESIS_COMPONENT);
	if (Parenthesis_Indexes.size() != 1)
		return;

	if (Input[i].Value != "else")
		return;

	Node* Else = new Node(ELSE_NODE);

	Parser p(Else);
	Else->Name = Input[i].Value;
	Else->Parent = Parent;

	p.Input.push_back(Input[Parenthesis_Indexes[0]]);
	p.Factory();

	Else->Childs = p.Input[0].node->Childs;

	Input[i].node = Else;

	Input.erase(Input.begin() + Parenthesis_Indexes[0]);

	return;
}

void Parser::Operator_Order()
{
	for (int i = 0; i < Input.size(); i++)
		Array_Pattern(i);
	for (int i = 0; i < Input.size(); i++)
		Variable_Negate_Pattern(i);
	for (int i = 0; i < Input.size(); i++)
		Operator_PreFix_Pattern(i, { "++", "--" });
	for (int i = 0; i < Input.size(); i++)
		Operator_PostFix_Pattern(i, { "++", "--" });
	//the combination and multilayering of operations.
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { ":" }, OPERATOR_NODE);
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "." }, OPERATOR_NODE);
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "*", "/" , "%" }, OPERATOR_NODE);
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "<<", ">>" }, BIT_OPERATOR_NODE);
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "&", "!&" }, BIT_OPERATOR_NODE);
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "?" }, BIT_OPERATOR_NODE);
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "|", "!|" }, BIT_OPERATOR_NODE);
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "+", "-" }, OPERATOR_NODE);
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "<", ">" }, CONDITION_OPERATOR_NODE);
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "==", "!=", "<=", ">=", "!<", "!>" , "|=", "&=" }, CONDITION_OPERATOR_NODE);
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "=", "+=", "-=", "*=", "/=" }, OPERATOR_NODE);
}

void Parser::Return_Pattern(int i)
{
	if (Input[i].Value != "return")
		return;
	bool No_Return_Value = (((size_t)i + 1 > Input.size() - 1) || (Input[i + 1].Value == ";"));

	//return a + b
	//return;
	Node* ret = new Node(FLOW_NODE);
	ret->Name = "return";
	if (!No_Return_Value) {
		ret->Right = Input[(size_t)i + 1].node;
		Input.erase(Input.begin() + i + 1);
	}
	Input[i].node = ret;
	return;
}

void Parser::Size_Pattern(int i)
{
	//size 4
	if (Input[i].Value != "size")
		return;
	if (!Input[(size_t)i + 1].is(Flags::NUMBER_COMPONENT))
		return;
	Node* size = new Node(OBJECT_DEFINTION_NODE);

	size->Size = atoi((Input[(size_t)i + 1].node)->Name.c_str());

	size->Name = "_SIZE_";
	size->Inheritted.push_back("type");
	size->Parent = Parent;

	Parent->Defined.push_back(size);

	Input[i].node = size;
	return;
}

void Parser::Factory() {
	for (int i = 0; i < Input.size(); i++) {
		//variable/objects definator.
		Definition_Pattern(i);
		Duplicated_Prototype_Handler(i);
	}
	for (int i = 0; i < Input.size(); i++) {
		//multiline AST stuff
		Function_Pattern(i);
		Type_Pattern(i);
		If_Pattern(i);
		Else_Pattern(i);
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
	for (int i = 0; i < Input.size(); i++) {
		Return_Pattern(i);
		Size_Pattern(i);
	}
}