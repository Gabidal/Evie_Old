#include "../../H/Parser/Parser.h"
#include "../../H/UI/Safe.h"
//this is for unamed parameters.
int arg_count = 0;

vector<int> Parser::Get_Amount_Of(int i, long Flag, bool All_in_Same_Line)
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
			if (Input[i].is(Flags::END_COMPONENT) ||
				(Input[i].is(Flags::COMMENT_COMPONENT))) {
				if (All_in_Same_Line)
					break;
				continue;
			}
			else
				break;
	}
	return Indexes;
}

vector<int> Parser::Get_Amount_Of(int i, vector<int> Flags, bool All_in_Same_Line)
{
	vector<int> Indexes;
	for (; i < Input.size(); i++) {
		for (auto f : Flags) {
			if (Input[i].is(f)) {
				Indexes.push_back(i);
				goto Success;
			}
		}
		//this happends if there was no correlatoin between the flags and the input at i
		if (Input[i].is(Flags::END_COMPONENT) ||
			(Input[i].is(Flags::COMMENT_COMPONENT))) {
			if (All_in_Same_Line)
				break;
			continue;
		}
		else
			break;
	Success:;
	}
	return Indexes;
}

vector<Component> Parser::Get_Inheritting_Components(int i)
{
	//import int ptr func a
	vector<Component> Result;
	for (; i < Input.size(); i++) {
		if (Input[i].is(Flags::KEYWORD_COMPONENT) || (Parent->Find(Input[i].Value, Parent, false) != nullptr))
			Result.push_back(Input[i]);
		else 
			break;
	}
	return Result;
}

void Parser::Definition_Pattern(int i)
{
	//foo ptr a = ...|bool is(int f) | bool is(string f)
	//<summary>
	//list all previusly defined and find the last as an text to define a new object
	//put that result object into parents defined list and also into-
	//the INPUT[i + object index] the newly created object
	//</summary>
	vector<int> Words = Get_Amount_Of(i, { Flags::KEYWORD_COMPONENT, Flags::TEXT_COMPONENT });
	//object definition needs atleast one type and one raw text
	if (Words.size() < 2)
		return;
	//the last word must be a raw text not a keyword to be defined as a new object
	if (Input[Words.back()].is(Flags::KEYWORD_COMPONENT))
		return;
	//this is because of the syntax of label jumping exmp: "jump somewhere" is same as a variable declaration exmp: "int somename".
	for (auto j : Words)
		//import keywords have theyre own function to parse theyr patterns.
		if (Input[j].Value == "jump" || Input[j].Value == "return")
			return;

	//type a
	vector<string> Inheritted;

	//transform the indecies into strings, and the -1 means that we want to skip the last element in the list (the name)
	for (int j = 0; j < Words.size() -1; j++) {
		Inheritted.push_back(Input[Words[j]].Value);
	}

	Node* New_Defined_Object = new Node(OBJECT_DEFINTION_NODE, new Position(Input[Words[0]].Location));
	New_Defined_Object->Inheritted = Inheritted;

	New_Defined_Object->Name = Input[Words.back()].Value;
	New_Defined_Object->Scope = Parent;
	Parent->Defined.push_back(New_Defined_Object);

	//for later AST use
	Input[Words.back()].node = New_Defined_Object;

	Input.erase(Input.begin() + i, Input.begin() + Words.back());
	return;
}

void Parser::Constructor_Pattern(int i)
{
	vector<Component> ReturnType = Get_Inheritting_Components(i);
	if (!(ReturnType.size() > 1))
		return;
	if (ReturnType[ReturnType.size() - 1].is(Flags::KEYWORD_COMPONENT))
		return;	//the last list index is the name and thus cannot be a keyword

	if (!Parent->Find(ReturnType[ReturnType.size() - 1].Value, Parent)->is(CLASS_NODE))
		return;	//the name must be same as some class name to represent as the constructor of that class

	for (auto j : ReturnType) {
		if (j.Value == "return" || j.Value == "jump")
			return;
	}


	Node* Constructor = new Node(OBJECT_DEFINTION_NODE, new Position(ReturnType.back().Location));
	Constructor->Name = ReturnType.back().Value;
	for (int j = 0; j < ReturnType.size() - 1; j++)
		Constructor->Inheritted.push_back(ReturnType[j].Value);

	Input[i + Constructor->Inheritted.size() - 1 + 1].node = Constructor;

	Input.erase(Input.begin() + i, Input.begin() + i + Constructor->Inheritted.size());
	return;
}

void Parser::Prototype_Pattern(int i)
{
	//func banana(int, short)\n
	vector<int> Words = Get_Amount_Of(i, { Flags::TEXT_COMPONENT, Flags::KEYWORD_COMPONENT });
	//Words list must be a at leat two size for the type and for the name to be inside it
	if (Words.size() < 2)
		return;
	vector<int> Paranthesis = Get_Amount_Of(Words.back() + 1, Flags::PAREHTHESIS_COMPONENT);
	if (Paranthesis.size() != 1)
		return;
	if (Input[Paranthesis[0]].Value[0] != '(')
		return;

	//this is here because the jump can have a function call
	//label get_jump(int x)
	//jump get_jump(123);
	for (auto c : Words)
		if (Input[c].Value == "jump" || Input[c].Value == "return" || Input[c].Value == "import")
			return;

	//type a
	vector<string> Inheritted;

	//skip the last that is the name index.
	for (int j = 0; j < Words.size() - 1; j++) {
		Inheritted.push_back(Input[Words[j]].Value);
	}

	Node* New_Defined_Object = new Node(PROTOTYPE, new Position(Input[Words.back()].Location));
	New_Defined_Object->Inheritted = Inheritted;
	New_Defined_Object->Name = Input[Words.back()].Value;
	New_Defined_Object->Scope = Parent;

	vector<Component> Types;
	for (auto j : Input[Paranthesis[0]].Components) {
		if (j.Value == ",") {
			Node* p = new Node(OBJECT_DEFINTION_NODE, &j.Location);

			if (Types.back().is(Flags::KEYWORD_COMPONENT)) {
				p->Name = "ARG" + to_string(arg_count++);
				p->Is_Template_Object = true;
			}
			else {
				p->Name = Types.back().Value;
				Types.pop_back();
			}
			p->Scope = New_Defined_Object;
			for (auto k : Types)
				p->Inheritted.push_back(k.Value);

			if (p->is("type") != -1)
				p->Is_Template_Object = true;

			New_Defined_Object->Parameters.push_back(p);
			Types.clear();
		}
		else {
			Types.push_back(j);
		}
	}
	if (Types.size() > 0) {
		//for the last parameter
		Node* p = new Node(OBJECT_DEFINTION_NODE, &Types.back().Location);

		if (Types.back().is(Flags::KEYWORD_COMPONENT)) {
			p->Name = "ARG" + to_string(arg_count++);
			p->Is_Template_Object = true;
		}
		else {
			p->Name = Types.back().Value;
			Types.pop_back();
		}
		p->Scope = New_Defined_Object;
		for (auto k : Types)
			p->Inheritted.push_back(k.Value);

		if (p->is("type") != -1)
			p->Is_Template_Object = true;

		New_Defined_Object->Parameters.push_back(p);
	}

	//erase inherittes as well the name as well the pearameters from the input list
	Input.erase(Input.begin() + Words[0], Input.begin() + i + Paranthesis[0] + 1);

	Parent->Defined.push_back(New_Defined_Object);

	if (i < Input.size())
		Prototype_Pattern(i);

	return;
}

void Parser::Import_Pattern(int i)
{
	//func banana(int, short)\n
	vector<int> Words = Get_Amount_Of(i, { Flags::TEXT_COMPONENT, Flags::KEYWORD_COMPONENT });
	//Words list must be a at leat two size for the type and for the name to be inside it
	if (Words.size() < 2)
		return;
	vector<int> Paranthesis = Get_Amount_Of(Words.back() + 1, Flags::PAREHTHESIS_COMPONENT);
	if (Paranthesis.size() != 1)
		return;
	if (Input[Paranthesis[0]].Value[0] != '(')
		return;

	bool Has_Import_Keyword = false;
	for (auto c : Words)
		if (Input[c].Value == "import")
			Has_Import_Keyword = true;

	if (!Has_Import_Keyword)
		return;

	//type a
	vector<string> Inheritted;

	//skip the last that is the name index.
	for (int j = 0; j < Words.size() - 1; j++) {
		Inheritted.push_back(Input[Words[j]].Value);
	}

	Node* New_Defined_Object = new Node(IMPORT, new Position(Input[Words.back()].Location));
	New_Defined_Object->Inheritted = Inheritted;
	New_Defined_Object->Name = Input[Words.back()].Value;
	New_Defined_Object->Scope = Parent;

	vector<Component> Types;
	for (auto j : Input[Paranthesis[0]].Components) {
		if (j.Value == ",") {
			Node* p;
			if (Types.back().is(Flags::NUMBER_COMPONENT))
				p = new Node(NUMBER_NODE, &j.Location);
			else
				p = new Node(OBJECT_DEFINTION_NODE, &j.Location);

			if (Types.back().is(Flags::KEYWORD_COMPONENT)) {
				p->Name = "ARG" + to_string(arg_count++);
				p->Is_Template_Object = true;
			}
			else {
				p->Name = Types.back().Value;
				Types.pop_back();
			}
			p->Scope = New_Defined_Object;
			for (auto k : Types)
				p->Inheritted.push_back(k.Value);

			if (p->is("type") != -1)
				p->Is_Template_Object = true;

			New_Defined_Object->Parameters.push_back(p);
			Types.clear();
		}
		else {
			Types.push_back(j);
		}
	}
	if (Types.size() > 0) {
		//for the last parameter
		string Format = "";
		for (int j = 0; j < Types.size(); j++) {
			if (Types[j].Value == "decimal" || Types[j].Value == "integer") {
				Format = Types[j].Value;
				Types.erase(Types.begin() + j);
			}
		}
		Node* p = nullptr;
		if (Types.back().is(Flags::NUMBER_COMPONENT))
			p = new Node(NUMBER_NODE, &Types.back().Location, Format);
		else
			p = new Node(OBJECT_DEFINTION_NODE, &Types.back().Location);

		if (Types.back().is(Flags::KEYWORD_COMPONENT)) {
			p->Name = "ARG" + to_string(arg_count++);
			p->Is_Template_Object = true;
		}
		else {
			p->Name = Types.back().Value;
			Types.pop_back();
		}
		p->Scope = New_Defined_Object;
		for (auto k : Types)
			p->Inheritted.push_back(k.Value);

		if (p->is("type") != -1)
			p->Is_Template_Object = true;

		New_Defined_Object->Parameters.push_back(p);
	}

	//erase inherittes as well the name as well the pearameters from the input list
	Input.erase(Input.begin() + Words[0], Input.begin() + Paranthesis[0] + 1);

	Parent->Defined.push_back(New_Defined_Object);

	if (i < Input.size())
		Import_Pattern(i);

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
	if (Input[i].node->is(OBJECT_DEFINTION_NODE))
		Input[i].node->Type = OBJECT_NODE;
	else if (Input[i].node->is(PARAMETER_NODE))
		Input[i].node->Type = PARAMETER_NODE;
	else if (Input[i].node->is(LABEL_NODE))
		Input[i].node->Type = LABEL_NODE;
	else if (Input[i].node->is(FUNCTION_NODE)) //this happends for function pointer adress geting prosess
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
	Node* Paranthesis = new Node(CONTENT_NODE, new Position(Input[i].Location));
	Paranthesis->Scope = Parent;
	
	Parser TMP_Parser(Parent);
	TMP_Parser.Input = Input[i].Components;
	TMP_Parser.Factory();

	for (Component j : TMP_Parser.Input)
		if (j.node != nullptr) {
			j.node->Context = Paranthesis;
			//j.node->Parent = Paranthesis;
			Paranthesis->Childs.push_back(new Node(*j.node));
		}

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

	Node* Operator = new Node(F, new Position(Input[i].Location));
	Operator->Name = Input[i].Value;
	Operator->Scope = Parent;

	if (Input[(size_t)i - 1].node != nullptr)
		Operator->Left = Input[(size_t)i - 1].node;
	else {
		//Dont worry about function calls
		Node* new_member = new Node(OBJECT_DEFINTION_NODE, new Position(Input[i].Location));
		new_member->Name = Input[(size_t)i - 1].Value;

		Operator->Left = new_member;
	}

	if (Input[(size_t)i + 1].node != nullptr)
		Operator->Right = Input[(size_t)i + 1].node;
	else {
		//test.a.m //these a.m are in different localscope.
		//the right side does not need to be determined as well the left.
		//Dont worry about function calls
		Node* new_member = new Node(OBJECT_DEFINTION_NODE, new Position(Input[i].Location));
		new_member->Name = Input[(size_t)i + 1].Value;

		Operator->Right = new_member;
	}

	//this is for algebra only!!
	if (Input[i].Value == "-")
		Operator->Right->Coefficient *= -1;

	if (Operator->Name == "=")
		if (Parent->Name == "GLOBAL_SCOPE")
			Parent->Find(Operator->Left->Name)->Inheritted.push_back("const");

	//give the left and right operators the right holder information
	Operator->Left->Context = Operator;
	Operator->Right->Context = Operator;

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
	Node* Num = new Node(NUMBER_NODE, new Position(Input[i].Location));
	Num->Name = Input[i].Value;
	Num->Scope = Parent;

	for (int j = 0; j < Num->Name.size(); j++)
		if (Num->Name[j] == '.') {
			Num->Format = "decimal";
			break;
		}

	if (atoll(Num->Name.c_str()) > INT32_MAX)
		Num->Size = 8;
	else
		Num->Size = 4;

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
	Node* String = new Node(STRING_NODE, new Position(Input[i].Location));
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
	Node* PreFix = new Node(PREFIX_NODE, new Position(Input[i].Location));
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
	if (Input[(size_t)i - 1].is(Flags::OPERATOR_COMPONENT))
		return; // b = ++<a>

	bool op_Pass = false;
	for (string s : Postfix)
		if (Input[i].Value == s)
			op_Pass = true;
	if (!op_Pass)
		return;

	Node* post = new Node(POSTFIX_NODE, new Position(Input[i].Location));
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

	Node* call = new Node(CALL_NODE, new Position(Input[i].Location));

	//give the normal call the inheritance for future operator type determining
	/*Node* Function = nullptr;
	Function = Parent->Find(Input[i].Value, Parent, FUNCTION_NODE);
	if (Function == nullptr)
		Function = Parent->Find(Input[i].Value, Parent, IMPORT);
	if (Function == nullptr)
		Function = Parent->Find(Input[i].Value, Parent, EXPORT);
	if (Function == nullptr)
		Function = Parent->Find(Input[i].Value, Parent, PROTOTYPE);
	if (Function == nullptr)
		Function = Parent->Find(Input[i].Value, Parent, OBJECT_DEFINTION_NODE);
	call->Inheritted = Function->Inheritted;*/

	call->Name = Input[i].Value;
	call->Scope = Parent;

	if (Parent->is(CALL_NODE))
		call->Context = Parent;

	//initialize the parenthesis that contains the parameters
	Parser p(call);
	p.Input = {Input[(size_t)i + 1]};
	p.Factory();

	call->Parameters = p.Input.back().node->Childs;
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
	if ((size_t)i + 1 > Input.size() - 1)
		return;
	if (!Input[(size_t)i + 1].is(Flags::PAREHTHESIS_COMPONENT))
		return;
	if (Input[(size_t)i + 1].node->Paranthesis_Type != '[')
		return;

	Node* arr = new Node(ARRAY_NODE, new Position(Input[i].Location));
	arr->Scope = Parent;

	if (Input[(size_t)i].node != nullptr)
		arr->Left = Input[(size_t)i].node;
	else {
		//Dont worry about function calls
		Node* new_member = new Node(OBJECT_DEFINTION_NODE, new Position(Input[i].Location));
		new_member->Name = Input[(size_t)i].Value;

		arr->Left = new_member;
		arr->Left->Scope = Parent;
	}

	if (Input[(size_t)i + 1].node->Childs.size() > 1) {
		arr->Right = new Node(CONTENT_NODE, new Position(Input[(size_t)i+1].Location));
		arr->Right->Childs = Input[(size_t)i + 1].node->Childs;
	}
	else if (Input[(size_t)i + 1].node->Childs[0] != nullptr)
		arr->Right = Input[(size_t)i + 1].node->Childs[0];
	else {
		//test.a.m //these a.m are in different localscope.
		//the right side does not need to be determined as well the left.
		//Dont worry about function calls
		Node* new_member = new Node(OBJECT_DEFINTION_NODE, new Position(Input[(size_t)i+1].Location));
		new_member->Name = Input[(size_t)i + 1].Components[0].Value;

		arr->Right = new_member;
		arr->Right->Scope = Parent;
	}

	//TODO:
	//Needs more testing with more complex array usage like: a[x][y][z]
	arr->Name = "[]";

	Input[i].node = arr;

	Input.erase(Input.begin() + i + 1);
	Array_Pattern(i);
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
	vector<int> Parenthesis_Indexes = Get_Amount_Of(i + 1, Flags::PAREHTHESIS_COMPONENT, false);
	if (Parenthesis_Indexes.size() != 2)
		return;
	if (Input[Parenthesis_Indexes[0]].Value[0] != '(')
		return;

	//first try to get the behavior
	Node* func = nullptr;
	if (Input[i].node->Type == OBJECT_DEFINTION_NODE)
		func = Input[i].node;
	else
		func = Parent->Find(Input[i].Value, Parent, true);
	if (func == nullptr) {
		Report(Observation(ERROR, "Parser didnt find " + Input[i].node->Name + " constructor!", Input[i].Location));
		throw::runtime_error("ERROR!");
	}
		//override the object definition node flag
	func->Type = FUNCTION_NODE;
	//set the other values
	func->Name = Input[i].Value;
	func->Scope = Parent;

	Parser p(func);
	p.Input.push_back(Input[Parenthesis_Indexes[0]]);
	p.Factory();

	for (auto& j : func->Defined) {
		j->Type = PARAMETER_NODE;
		if (j->is("type") != -1)
			j->Is_Template_Object = true;
	}

	func->Parameters = func->Defined;
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
	vector<int> Parenthesis_Indexes = Get_Amount_Of(i + 1, Flags::PAREHTHESIS_COMPONENT, false);
	if (Parenthesis_Indexes.size() != 1)
		return;
	if (Input[Parenthesis_Indexes[0]].Value[0] != '{')
		return;

	Node* Type = nullptr;
	if (Input[i].node != nullptr)
		//dont worry this has same pointter as the one that is in the Defined list, so this point to it
		Type = Input[i].node;
	else
		Type = Parent->Find(Input[i].Value, Parent, OBJECT_DEFINTION_NODE);
	if (Type == nullptr) {
		Report(Observation(ERROR, "Type definition was not found!", Input[i].Location));
		throw::runtime_error("ERROR!");
	}
	//reset the value
	Type->Type = CLASS_NODE;

	//combine inheritted memebrs
	Type->Get_Inheritted_Class_Members();

	Parser p(Type);
	p.Input.push_back(Input[Parenthesis_Indexes[0]]);
	p.Factory();

	Type->Childs = p.Input[0].node->Childs;
	p.Input.clear();

	Input.erase(Input.begin() + Parenthesis_Indexes[0]);
	Input.erase(Input.begin() + i);

	if (i < Input.size())
		Type_Pattern(i);

	return;
}

void Parser::Member_Pattern(int i)
{
	//foo.a = 1
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
	vector<int> Parenthesis_Indexes = Get_Amount_Of(i + 1, Flags::PAREHTHESIS_COMPONENT, false);
	if (Parenthesis_Indexes.size() != 2)
		return;				

	//if (){..}
	//else (){..}		//this works as 'else if'
	//else {..}			//and this as normal 'else'
	//while (..){..}	//loop
	Node* con; 
	if (Input[i].Value == "if")
		con = new Node(IF_NODE, new Position(Input[i].Location)); 
	else if (Input[i].Value == "else")
		con = new Node(ELSE_IF_NODE, new Position(Input[i].Location));		//this works for only else if because it requers 2 paranthesis
	else if (Input[i].Value == "while")
		con = new Node(WHILE_NODE, new Position(Input[i].Location));
	else
		return;

	Parser p(con);
	con->Name = Input[i].Value;
	con->Scope = Parent;

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
	//here we patternise the else without a condition
	if (!Input[i].is(Flags::KEYWORD_COMPONENT))
		return;
	vector<int> Parenthesis_Indexes = Get_Amount_Of(i + 1, Flags::PAREHTHESIS_COMPONENT, false);
	if (Parenthesis_Indexes.size() != 1)
		return;

	if (Input[i].Value != "else")
		return;

	Node* Else = new Node(ELSE_NODE, new Position(Input[i].Location));

	Parser p(Else);
	Else->Name = Input[i].Value;
	Else->Scope = Parent;

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
		Math_Pattern(i, { "->" }, NODE_CASTER);
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
		Math_Pattern(i, { "¤"}, BIT_OPERATOR_NODE);
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "=", "+=", "-=", "*=", "/=" }, ASSIGN_OPERATOR_NODE);
}

void Parser::Return_Pattern(int i)
{
	if (Input[i].Value != "return")
		return;
	bool No_Return_Value = (((size_t)i + 1 > Input.size() - 1) || (Input[i+1].node == nullptr));

	//return a + b
	//return;
	Node* ret = new Node(FLOW_NODE, new Position(Input[i].Location));
	ret->Name = "return";
	ret->Scope = Parent;
	if (!No_Return_Value) {
		ret->Right = Input[(size_t)i + 1].node;
		ret->Right->Context = ret;
		Input.erase(Input.begin() + i + 1);
	}
	Input[i].node = ret;
	return;
}

void Parser::Jump_Pattern(int i)
{
	//jump banana
	if (Input[i].Value != "jump")
		return;
	if (Input.size() < (size_t)i + 1)
		return;

	Node* jmp = new Node(FLOW_NODE, new Position(Input[i].Location));
	jmp->Name = "jump";
	
	Node* label = new Node(LABEL_NODE, new Position(Input[i].Location));
	label->Name = Input[(size_t)i + 1].Value;

	jmp->Right = label;

	Input[i].node = jmp;
	Input.erase(Input.begin() + i + 1);
}

void Parser::Label_Pattern(int i)
{
	if (Input[i].node != nullptr)
		return;
	//test
	//..
	//labels are tricy because they are just one word
	//so check that it isnt connectd to enythign
	Node* l = Parent->Find(Input[i].Value, Parent);
	if (l == nullptr)
		return;
	if (!l->is(LABEL_NODE))
		return;
	Node* L = new Node(LABEL_NODE, new Position(Input[i].Location));
	L->Name = Input[i].Value;
	L->Scope = Parent;
	
	Input[i].node = L;
}

void Parser::Label_Definition(int i)
{
	if (i - 1 <= 0)
		return;
	if ((size_t)i + 1 > Input.size()-1)
		return;
	if (Input[(size_t)i - 1].is(Flags::KEYWORD_COMPONENT))
		return;	//return label_name
	if (Input[(size_t)i + 1].is(Flags::TEXT_COMPONENT))
		return;	//label_name obj_name(int)
	if (Parent->Find(Input[i].Value, Parent) != nullptr)
		return;	//label_name(int), label_name = ..
	if (!Input[i].is(Flags::TEXT_COMPONENT))
		return;	//only text name allowed
	if (Input[i].Value == "\n")
		return;
	if (Input[(size_t)i - 1].is(Flags::OPERATOR_COMPONENT))
		return;
	if (Input[(size_t)i + 1].is(Flags::OPERATOR_COMPONENT))
		return;
	if (Input[i].Value == "size" || Input[i].Value == "format")
		return;
	//passes: label_name if (..)..
	//passes: label_name (..)
	//passes: label_name {..}
	Node* label = new Node(LABEL_NODE, new Position(Input[i].Location));
	label->Name = Input[i].Value;
	label->Scope = Parent;

	Input[i].node = label;

	Parent->Defined.push_back(label);
}

void Parser::Size_Pattern(int i)
{
	//size = 4
	if (Input[i].Value != "size")
		return;
	if (!Parent->is(CLASS_NODE))
		return;
	if (Input[i].node != nullptr)
		return;
	if (i - 1 >= 0)
		if (Input[(size_t)i - 1].is(Flags::OPERATOR_COMPONENT) || Input[(size_t)i - 1].is(Flags::TEXT_COMPONENT))
			return;
	if (Input[(size_t)i + 1].Value != "=")
		return;
	if (!Input[(size_t)i + 2].is(Flags::NUMBER_COMPONENT))
		return;
	Node* size = new Node(OBJECT_DEFINTION_NODE, new Position(Input[i].Location));

	size->Size = atoi((Input[(size_t)i + 2].node)->Name.c_str());

	size->Name = "size";
	size->Inheritted.push_back("const");	//NOTICE:!!! this might be wrong type!!!
	size->Scope = Parent;

	Parent->Defined.push_back(size);

	Input[i].node = size;

	Input.erase(Input.begin() + i + 1);
	Input.erase(Input.begin() + i + 1);
	return;
}

void Parser::Format_Pattern(int i)
{
	//format = decimal
	if (Input[i].Value != "format")
		return;
	if (!Parent->is(CLASS_NODE))
		return;
	if (i - 1 >= 0)
		if (Input[(size_t)i - 1].is(Flags::OPERATOR_COMPONENT) || Input[(size_t)i - 1].is(Flags::TEXT_COMPONENT) || Input[(size_t)i-1].is(Flags::KEYWORD_COMPONENT))
			return;
	if (Input[(size_t)i + 1].Value != "=")
		return;
	if (!Input[(size_t)i + 2].is(Flags::TEXT_COMPONENT))
		return;
	Node* format = new Node(OBJECT_DEFINTION_NODE, new Position(Input[i].Location));

	format->Format = Input[(size_t)i + 2].Value;

	format->Name = "format";
	format->Inheritted.push_back("const");	//NOTICE:!!! this might be wrong type!!!
	format->Scope = Parent;

	Parent->Defined.push_back(format);

	Input[i].node = format;

	Input.erase(Input.begin() + i + 1);
	Input.erase(Input.begin() + i + 1);
	return;
}

void Parser::Member_Function_Pattern(int i)
{
	//return_type class_name.funcname(){}
	if (Parent->Name != "GLOBAL_SCOPE")
		return;
	if (Input[i].node == nullptr)
		return;
	if (Input[i].Value != ".")
		return;

	vector<int> Parenthesis_Indexes = Get_Amount_Of(i + 1, Flags::PAREHTHESIS_COMPONENT, false);
	if (Parenthesis_Indexes.size() != 2)
		return;
	if (Input[Parenthesis_Indexes[1]].Value[0] != '{')
		return;
	if (Input[Parenthesis_Indexes[0]].Value[0] != '(')
		return;
	//set all the left sided of operators as the fetchers
	Input[i].node->Left->Transform_Dot_To_Fechering(Input[i].node->Right);

	//Find the scope that this function is set to as a member to.
	Node* Class = Parent->Find(Input[i].node->Right->Fetcher, Parent, CLASS_NODE);
	if (Class == nullptr)
		Report(Observation(ERROR, Input[i].node->Right->Fetcher->Name + " was not found when creating " + Input[i].node->Right->Name, Input[i].Location));

	Input[i].node->Right->Context = Input[i].node->Context;
	Input[i].node->Right->Scope = Input[i].node->Scope;
	Input[i].node = Input[i].node->Right;
	Input[i].Value = Input[i].node->Name;

	Input[i].node->Inheritted = Input[i].node->Fetcher->Inheritted;
	Input[i].node->Fetcher->Inheritted.clear();

	Function_Pattern(i);

	Class->Defined.push_back(Input[i].node);
}

void Parser::Factory() {
	for (int i = 0; i < Input.size(); i++) {
		//variable/objects definator.		
		Prototype_Pattern(i);	//Definition_pattern stoles this import functions, so this goes first
		Import_Pattern(i);
		Definition_Pattern(i);
		Label_Definition(i);
	}
	for (int i = 0; i < Input.size(); i++) {
		//multiline AST stuff
		Type_Pattern(i);		//class constructor
		Constructor_Pattern(i);	//constructor needs the type to be defined as a class 
		Function_Pattern(i);
		If_Pattern(i);
		Else_Pattern(i);
		Callation_Pattern(i);
		Jump_Pattern(i);
	}
	for (int i = 0; i < Input.size(); i++) {
		//prepreattor for math operator AST combinator.
		Object_Pattern(i);
		Parenthesis_Pattern(i);
		String_Pattern(i);
		Number_Pattern(i);
		Label_Pattern(i);
	}
	for (int i = 0; i < Input.size(); i++) {
		Size_Pattern(i);
		Format_Pattern(i);
	}
	//AST operator combinator.
	Operator_Order();
	for (int i = 0; i < Input.size(); i++) {
		Member_Function_Pattern(i);
		Return_Pattern(i);
	}
}