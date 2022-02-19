#include "../../H/Parser/Parser.h"
#include "../../H/UI/Safe.h"
#include "../../H/Docker/Mangler.h"
#include "../../H/UI/Usr.h"
//this is for unamed parameters.
int arg_count = 0;
extern Usr* sys;

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
		if (Input[i].is(Flags::KEYWORD_COMPONENT) || (Scope->Find(Input[i].Value, Scope, false) != nullptr))
			Result.push_back(Input[i]);
		else 
			break;
	}
	return Result;
}

void Parser::Combine_Dot_In_Member_Functions(int& i)
{
	if (!Scope->is(CLASS_NODE) || !Scope->is("static"))
		return;
	if (Input[i].Value != ".")
		return;

	Math_Pattern(i, { "." }, OPERATOR_NODE, true);
}

void Parser::Template_Pattern(int& i)
{
	if (Input[i].Value != "<")
		return;
	//if (s < 1 && s > 0)
	int j = i;
	int This_Scopes_Open_Template_Operators = 1;
	while (Input[j].Value != ">" || This_Scopes_Open_Template_Operators > 0) {
		j++;
		if (j > Input.size() - 1)
			break;
		if (Input[j].Value == "<")
			This_Scopes_Open_Template_Operators++;
		if (Input[j].Value == ">")
			This_Scopes_Open_Template_Operators--;
																																			
		else if (Input[j].Value != ">" && Input[j].Value != "<" && !Input[j].is(Flags::TEXT_COMPONENT) && !Input[j].is(Flags::KEYWORD_COMPONENT) )
			break;
	}

	//this is not a template holding operator.
	if (This_Scopes_Open_Template_Operators > 0)
		return;
	if (Input[j].Value != ">")
		return;

	Input[i].Flags = Flags::TEMPLATE_COMPONENT;
	Input[i].Value = "<>";
	for (int k = i + 1; k < j; k++) {
		Input[i].Components.push_back(Input[k]);
	}

	Input.erase(Input.begin() + i + 1, Input.begin() + j + 1);

	Parser p(Scope);
	p.Input = { Input[i].Components };
	p.Factory();

	Input[i].Components = p.Input;

	//for difinition pattern.
	i--;
}

void Parser::Construct_Virtual_Class_To_Represent_Multiple_Template_Inputs(Component& i)
{
	if (!i.is(Flags::TEMPLATE_COMPONENT))
		return;

	//<int ptr, char>
	vector<vector<string>> Template_Pairs;
	vector<pair<string, bool>> Output;

	//first sort template pair type by comma.
	vector<string> Current_Template_Pair;
	for (auto T : i.Components) {
		if (T.Value == ",") {
			Template_Pairs.push_back(Current_Template_Pair);
			Current_Template_Pair.clear();
		}
		else {
			if (T.is(Flags::TEMPLATE_COMPONENT)) {
				//<int ptr, List<T ptr>>
				Construct_Virtual_Class_To_Represent_Multiple_Template_Inputs(T);
			}
			Current_Template_Pair.push_back(T.Value);
		}
	}
	if (Current_Template_Pair.size() > 0) {
		Template_Pairs.push_back(Current_Template_Pair);
		Current_Template_Pair.clear();
	}

	//Now create a class for every template pair.
	for (auto& Template_Pair : Template_Pairs) {
		//ofcourse avoid same class redefinition.
		if (Template_Pair.size() == 1) {
			Output.push_back({ Template_Pair[0], false });
			continue;
		}
		string Template_Pair_Class_Name = "____";
		for (auto T : Template_Pair) {
			Template_Pair_Class_Name += T + "_";
		}
		if (Scope->Find(Template_Pair_Class_Name, Scope, CLASS_NODE) != nullptr) {
			Output.push_back({ Template_Pair_Class_Name, true });
		}
		else {
			Node* New_Template_Pair_Class = new Node(CLASS_NODE, (new Position(i.Location)));
			New_Template_Pair_Class->Inheritted = Template_Pair;
			New_Template_Pair_Class->Name = Template_Pair_Class_Name;
			New_Template_Pair_Class->Scope = Global_Scope;
			Global_Scope->Defined.push_back(New_Template_Pair_Class);
			Output.push_back({ Template_Pair_Class_Name, true });
		}
	}

	i.Components.clear();
	for (auto j : Output) {
		Component C = Component(j.first, i.Location, Flags::TEXT_COMPONENT);
		i.Components.push_back(C);
	}

	Parser p(Global_Scope);
	p.Input = i.Components;
	p.Factory();
	i.Components = p.Input;

}

void Parser::Operator_Combinator(int i)
{
	if (Input[i].Value != ">")
		return;

	string All_Combined_Operators = ">";
	for (int j = i + 1; j < Input.size() && Input[j].Value == ">"; j++)
		All_Combined_Operators += ">";

	if (All_Combined_Operators.size() == 1)
		return;

	Input.erase(Input.begin() + i + 1, Input.begin() + i + All_Combined_Operators.size() - 1);

	Input[i].Value = All_Combined_Operators;

}

void Parser::Nodize_Template_Pattern(int i)
{
	if (!Input[i].is(Flags::TEMPLATE_COMPONENT))
		return;
	if (Input[i].node != nullptr)
		return;

	Input[i].node = new Node(TEMPLATE_NODE, "<>", &Input[i].Location);

	//List<List<int>, List<int>>
	for (auto& T : Input[i].Components) {
		//check that the value is defined not as a template but as a class.
		//Or. If the current scope is a namespace (for template class definitions)

		if (Scope->Find(T.Value)) {
			Parser p(Scope);
			p.Input = { T };
			p.Factory();
			Input[i].node->Templates.push_back(p.Input.back().node);
		}
		else if (Scope->Find_Template(T.Value) || (Scope->is("static") && Scope->is(CLASS_NODE))) {
			return;
		}
		else {
			Report(Observation(ERROR, "Uknown template type '" + T.Value + "'", T.Location, ""));
		}

	}

}

void Parser::Template_Type_Constructor(int i)
{
	if (Input[i].node == nullptr)
		return;
	if (Input[i].node->Templates.size() == 0)
		return;
	if (!Scope->Find(Input[i].Value, Scope, CLASS_NODE))
		return;

	string New_Name = Input[i].node->Construct_Template_Type_Name();
	if (Scope->Find(New_Name) != nullptr) {
		Input[i].Value = New_Name;

		Node* Constructed_Template_Class = Scope->Find(New_Name, Scope, CLASS_NODE);

		if (Constructed_Template_Class)
			Input[i].node->Inheritable_templates = Constructed_Template_Class->Inheritable_templates;
		return;
	}
	//Search the original template class
	Node* Og_Type = Input[i].node->Find(Input[i].node, Scope, CLASS_NODE);
	//copy this template class to be non template
	Node* Type;
	Scope->Copy_Node(Type, Og_Type, Og_Type->Scope);
	Type->Parsed_By = 0;	//reset the parsed flags

	//copy all functions becuase the copy_node by default skips function copying
	for (auto &j : Type->Defined) {
		if (j->is(FUNCTION_NODE))
			Scope->Copy_Node(j, new Node(*j), Type);
	}

	//give the templates back to this new template class for template type refilling
	Type->Templates = Input[i].node->Templates;

	//turns List<T> into List<int>
	for (int T = 0; T < Input[i].node->Templates.size(); T++) {
		string T_Arg = Og_Type->Templates[T]->Name;
		string T_Type = Type->Templates[T]->Name;

		for (auto& Defined : Type->Template_Children) {
			for (auto n : Defined.Get_all())
				if (n->Value == T_Arg)
					n->Value = T_Type;
		}
		/*for (auto& Inheritted : Type->Un_Initialized_Template_Inheritance) {
			for (auto n : Inheritted.first.Get_all())
				if (n->Value == T_Arg)
					n->Value = T_Type;
		}*/
	}

	vector<Component> New_Constructed_Template_Class_Code;

	vector<Component> New_Constructed_Template_Code;

	//re-Construct the class
	/*for (auto j : Type->Un_Initialized_Template_Inheritance)
		New_Constructed_Template_Code.push_back(j.first);*/

	for (auto j : Type->Inheritted)
		New_Constructed_Template_Class_Code.push_back(Component(j, *Type->Location, Lexer::GetComponent(j).Flags));
	
	New_Constructed_Template_Class_Code.push_back(Component(New_Name, *Type->Location, Flags::TEXT_COMPONENT));
	Component Content = Component("{", *Type->Location, Flags::PAREHTHESIS_COMPONENT);
	Content.Components = Type->Template_Children;
	New_Constructed_Template_Class_Code.push_back(Content);
	New_Constructed_Template_Class_Code.push_back(Lexer::GetComponent("\n"));

	//now Construct all member funcitons as well.
	for (auto& Func : Type->Defined) {
		for (int T = 0; T < Func->Templates.size(); T++) {
			string T_Arg = Func->Templates[T]->Name;
			string T_Type = Type->Templates[T]->Name;

			if (Func->Templates[T]->Name == T_Arg)
				Func->Templates[T]->Name = T_Type;
		}
		if (Func->Fetcher == nullptr)
			continue;	//inside type defined functions dont need to be rewritten again.
		//if (Func->Templates.size() == 0)
			Func->Fetcher = Type;

		vector<Component> tmp = Template_Function_Constructor(Func, Og_Type->Templates, Type->Templates);
		New_Constructed_Template_Code.insert(New_Constructed_Template_Code.end(), tmp.begin(), tmp.end());
	}

	Type->Name = New_Name;
	Type->Defined.clear();
	Type->Childs.clear();

	//the constructed template class members are pushed to the old namespace altough the namespace has vbeen inlined

	Node* Closest_Namespace = Scope->Get_Scope_As(CLASS_NODE, {"static"}, Scope);

	Parser p(Closest_Namespace);
	p.Input = New_Constructed_Template_Class_Code;
	p.Factory();

	Type->Scope->Find(Type->Name)->Inheritable_templates = Input[i].node->Templates;
	Input[i].node->Inheritable_templates = Input[i].node->Templates;
	Input[i].node->Templates.clear();

	p = Parser(Closest_Namespace);
	p.Input = New_Constructed_Template_Code;
	p.Factory();
	

	//for erasing the <>
	//Input.erase(Input.begin() + i + 1);

	Input[i].Value = Type->Name;
}

vector<Component> Parser::Template_Function_Constructor(Node* Func, vector<Node*> T_Args, vector<Node*> T_Types)
{
	vector<Component> New_Constructed_Template_Code;
	string New_Name = Func->Construct_Template_Type_Name();

	if (Scope->Find(New_Name) != nullptr) {
		if (Func->Compare_Fetchers(Scope->Find(New_Name))) {
			Func->Name = New_Name;
			return New_Constructed_Template_Code;
		}
	}
	if (!Func->is(FUNCTION_NODE))
		return New_Constructed_Template_Code;

	vector<Component> Return_Type;
	for (auto& Inheritted : Func->Inheritted) {
		for (int T = 0; T < T_Args.size(); T++) {
			string T_Arg = T_Args[T]->Name;
			string T_Type = T_Types[T]->Name;

			if (Inheritted == T_Arg) {
				Inheritted = T_Type;
				Func->Is_Template_Object = true;
			}
		}
		Return_Type.push_back(Lexer::GetComponent(Inheritted));
	}

	for (auto& Inheritted : Func->Un_Initialized_Template_Inheritance) {
		for (int T = 0; T < T_Args.size(); T++) {
			string T_Arg = T_Args[T]->Name;
			string T_Type = T_Types[T]->Name;
			for (auto& j : Inheritted.first.Get_all())
				if (j->Value == T_Arg) {
					j->Value = T_Type;
					Func->Is_Template_Object = true;
				}
		}
		Return_Type.insert(Return_Type.begin() + Inheritted.second, Inheritted.first);
		Return_Type.insert(Return_Type.begin() + Inheritted.second + 1, Inheritted.first.Components[0]);
	}

	vector<Component> Fetchers;
	if (Func->Fetcher) {
		//How TF can there be more than one fetcher Gabe?
		//for (auto* Fetcher : Func->Get_All_Fetchers()) {
		Node* Fetcher = Func->Fetcher;

		Node* New_Fetcher;
		Fetcher->Copy_Node(New_Fetcher, Fetcher, Fetcher->Scope);

		for (int T = 0; T < T_Args.size(); T++) {
			string T_Arg = T_Args[T]->Name;
			string T_Type = T_Types[T]->Name;

			for (auto& t : New_Fetcher->Templates)
				if (t->Name == T_Arg)
					t->Name = T_Type;

		}
		Component Fetcher_Component = Lexer::GetComponent(New_Fetcher->Construct_Template_Type_Name());
		Fetchers.push_back(Fetcher_Component);
		Fetchers.push_back(Lexer::GetComponent("."));
	}

	for (int T = 0; T < T_Args.size(); T++)
		for (auto& Defined : Func->Template_Children)
			for (auto n : Defined.Get_all())
				if (n->Value == T_Args[T]->Name) {
					n->Value = T_Types[T]->Name;
				}

	Component Name = Lexer::GetComponent(New_Name);
	Name.Value = New_Name;

	New_Constructed_Template_Code.insert(New_Constructed_Template_Code.end(), Return_Type.begin(), Return_Type.end());
	New_Constructed_Template_Code.insert(New_Constructed_Template_Code.end(), Fetchers.begin(), Fetchers.end());
	New_Constructed_Template_Code.insert(New_Constructed_Template_Code.end(), Name);
	New_Constructed_Template_Code.insert(New_Constructed_Template_Code.end(), Func->Template_Children.begin(), Func->Template_Children.end());
	New_Constructed_Template_Code.push_back(Lexer::GetComponent("\n"));

	return New_Constructed_Template_Code;
}

void Parser::Inject_Template_Into_Member_Function_Fetcher(int& i)
{
	// i-1 should have the class fetcher that feches the member.
	if (i - 1 < 0)
		return;
	if (!Input[i - 1].is(Flags::TEXT_COMPONENT))
		return;
	if (Input[i - 1].node == nullptr)
		return;
	if (Scope->Find(Input[i - 1].Value, Scope, CLASS_NODE) == nullptr)
		return;

	// i should have the template <>
	if (!Input[i].is(Flags::TEMPLATE_COMPONENT))
		return;

	for (auto T : Input[i].Components) {
		Node* Template = new Node(TEMPLATE_NODE, T.Value, &T.Location);

		Template->Inheritted.push_back("type");

		Input[i - 1].node->Templates.push_back(Template);
	}

	Input.erase(Input.begin() + i--);
}

void Parser::Combine_Comment(int i)
{
	if (!Input[i].is(Flags::COMMENT_COMPONENT))
		return;
	if (i + 1 >= Input.size() || !Input[i+1].is(Flags::COMMENT_COMPONENT))
		return;

	Input[i].Value += "\n" + Input[i + 1].Value;

	Input.erase(Input.begin() + i + 1);

	Combine_Comment(i);
}

void Parser::Remove_All_Excess_Comments(int i)
{
	if (!Input[i].is(Flags::COMMENT_COMPONENT))
		return;

	Input.erase(Input.begin() + i--);

	if (i >= 0)
		Remove_All_Excess_Comments(i);
}

void Parser::Definition_Pattern(int i)
{
	//foo ptr a = ...|bool is(int f) | bool is(string f)
	//<summary>
	//list all previusly defined and find the last as an text to define a new object
	//put that result object into parents defined list and also into-
	//the INPUT[i + object index] the newly created object
	//</summary>
	vector<int> Words = Get_Amount_Of(i, { Flags::KEYWORD_COMPONENT, Flags::TEXT_COMPONENT, Flags::TEMPLATE_COMPONENT });
	//object definition needs atleast one type and one raw text
	if (Words.size() > 0 && Input[Words.back()].is(Flags::TEMPLATE_COMPONENT))
		Words.pop_back();
	if (Words.size() < 2)
		return;
	//the last word must be a raw text not a keyword to be defined as a new object
	if (Input[Words.back()].is(Flags::KEYWORD_COMPONENT))
		return;
	//this is because of the syntax of label jumping exmp: "jump somewhere" is same as a variable declaration exmp: "int somename".
	for (auto j : Words)
		//import keywords have theyre own function to parse theyre own patterns.
		if (Input[j].Value == "jump" || Input[j].Value == "return" || Input[j].Value == "use")
			return;

	//int ptr a
	Node* New_Defined_Object = new Node(OBJECT_DEFINTION_NODE, new Position(Input[Words[0]].Location));

	if (i - 1 >= 0 && Input[i - 1].is(Flags::COMMENT_COMPONENT)) {
		New_Defined_Object->Comment.Deprication_Information = Input[i - 1].Value;

		replace(New_Defined_Object->Comment.Deprication_Information.begin(), New_Defined_Object->Comment.Deprication_Information.end(), '#', ' ');
	}

	New_Defined_Object->Name = Input[Words.back()].Value;
	New_Defined_Object->Scope = Scope;

	//transform the indecies into strings, and the -1 means that we want to skip the last element in the list (the name)
	for (int j = 0; j < Words.size() - 1; j++) {
		//the define is something like tihs:
		//T a
		//then there would be no problem because the T would have been found by the Find function
		//The issue here is if there is template construction like:
		//List<T> a
		//that will construct a new List class that type is T, and that is wrong.
		if (Input[Words[j]].is(Flags::TEMPLATE_COMPONENT)) {
			//insure that this isn't a template parameter
			//<int, T, R>

			//check that all the templates are defined as a classes
			bool All_Templates_Are_Defined_As_Classes = true;
			for (auto T : Input[Words[j]].Components)
				if (Scope->Find(T.Value) == nullptr)
					All_Templates_Are_Defined_As_Classes = false;

			//insire that all of the templates are from scopes templates and not classes
			for (auto T : Input[Words[j]].Components)
				if (Scope->Find_Template(T.Value))
					//this means that the template type is not a class
					All_Templates_Are_Defined_As_Classes = false;
			
			if (All_Templates_Are_Defined_As_Classes == false) {
				//normal 'T a' will not trigger this code because the T is not wrapped into a <>
				Input[Words[j - 1]].Components.push_back(Input[Words[j]]);
				
				New_Defined_Object->Un_Initialized_Template_Inheritance.push_back({ Input[Words[j - 1]] , j - 1 });
			}
			else {
				//List<List<int>> a
				//-> .List_List_int a 
				Parser p(Scope);
				p.Input = { Input[Words[j - 1]],  Input[Words[j]] };
				p.Factory();
				
				if ((!Scope->is("static") || !Scope->is(CLASS_NODE)) || All_Templates_Are_Defined_As_Classes) {
					New_Defined_Object->Inheritted.push_back(p.Input.back().Value);
					New_Defined_Object->Inheritable_templates = p.Input.back().node->Inheritable_templates;
				}
				else {
					//This is for if the function return a templated return type like:
					//List<T> a
					//because the upper scope is not same as the function that this return type belongs to the upper code will not work
					//and thats why this is here.
					New_Defined_Object->Un_Initialized_Template_Inheritance.push_back({ p.Input.back(), j});
				}
			}
		}
		else if (j + 1 < Words.size() && !Input[Words[j + 1]].is(Flags::TEMPLATE_COMPONENT))
			New_Defined_Object->Inheritted.push_back(Input[Words[j]].Value);
	}

	//Almost Namespace combination system 2000 (:
	// The rest is made in the Type_Pattern dude
	//if the current made object already exists
	Node* Namespace = Scope->Find(New_Defined_Object, Scope, {CLASS_NODE, OBJECT_DEFINTION_NODE}, false);
	//if the namespace is already a static class type and this one too then combine
	//int std._Max_int_(int a, int b)
	if (Namespace && Namespace->is("static") && Input[Words.back() + 1].Value == ".") {
		//the operator below will erase the int inheritance of the namespace!!!
		vector<string> Inheritted = New_Defined_Object->Inheritted;

		New_Defined_Object->Inheritted = Namespace->Inheritted;
		New_Defined_Object->Fetching_Inheritance = Inheritted;
	}
	else if (Namespace && (Namespace->is(CLASS_NODE) || ((Get_Amount_Of(Words.back() + 1, { Flags::PAREHTHESIS_COMPONENT }, false).size() == 1) && (Input[Words.back() + 1].Value[0] == '{'))) && Namespace->is("static")) {
		New_Defined_Object = Namespace;
	}
	//if the object is static and the namespace is not
	else if (Namespace != nullptr && New_Defined_Object->is("static") && !Namespace->is("static")) {
		Report({
			Observation(ERROR, "'" + New_Defined_Object->Name + "'", *New_Defined_Object->Location, "Colliding definitions of"),
			Observation(ERROR, "'" + Namespace->Name + "'", *Namespace->Location, "Colliding definitions of")
		});
	}
	//if the namespace is already a static class but this is not a static class or both are non static.
	else if (Namespace != nullptr && Namespace->is(CLASS_NODE) && !Namespace->is("static")) {
		bool Skip_Templates = false;
		if (Words.back() + 1 < Input.size() && Input[Words.back() + 1].is(Flags::TEMPLATE_COMPONENT))
			Skip_Templates = true;

		vector<int> Parenthesises = Get_Amount_Of(Words.back() + 1 + Skip_Templates, { Flags::PAREHTHESIS_COMPONENT }, false);
		if ((Parenthesises.size() == 1) && (Input[Parenthesises[0]].Value[0] == '{')) {
			//check if the other one is namespace and the other not
			if (New_Defined_Object->is("static")) {
				Report(Observation(ERROR, "Cannot combine non static classes as namespaces!", *Namespace->Location, ""));
			}
			else {
				Report({ 
					Observation(ERROR, "'" + New_Defined_Object->Name + "'", *New_Defined_Object->Location, "Colliding definitions of"),
					Observation(ERROR, "'" + Namespace->Name + "'", *Namespace->Location, "Colliding definitions of")
					});
			}
		}
		else
			Scope->Defined.push_back(New_Defined_Object);
	}
	else if (Namespace != nullptr && !Namespace->Has({ IMPORT, EXPORT, FUNCTION_NODE }) && !Input[Words.back() + 1].is(CONTENT_NODE)) {
		if (!Input[Words.back() + 1].is(CONTENT_NODE))
			Report(Observation(ERROR, "'" + New_Defined_Object->Name + "' is already defined at '" + Namespace->Location->ToString() + "'", *New_Defined_Object->Location, "Colliding definitions of"));
	}
	else
		Scope->Defined.push_back(New_Defined_Object);

	//for later AST use:int ptr a = 123
	Input[Words.back()].node = New_Defined_Object;

	Input.erase(Input.begin() + i, Input.begin() + Words.back());
}

void Parser::Constructor_Pattern(int i)
{
	vector<Component> ReturnType = Get_Inheritting_Components(i);
	if (!(ReturnType.size() > 1))
		return;
	if (ReturnType[ReturnType.size() - 1].is(Flags::KEYWORD_COMPONENT))
		return;	//the last list index is the name and thus cannot be a keyword

	if (!Scope->Find(ReturnType[ReturnType.size() - 1].Value, Scope)->is(CLASS_NODE))
		return;	//the name must be same as some class name to represent as the constructor of that class

	for (auto j : ReturnType) {
		if (j.Value == "return" || j.Value == "jump" || j.Value == "use")
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
	if (!Scope->is("static"))
		return;
	//int abc = banana()
	//if ()
	//func banana(int, short)\n
	vector<int> Words = Get_Amount_Of(i, { Flags::TEXT_COMPONENT, Flags::KEYWORD_COMPONENT, Flags::TEMPLATE_COMPONENT });
	//Words list must be a at leat two size for the type and for the name to be inside it
	if (Words.size() == 0)
		return;
	//Banana<abc>() <- NO | int Banana<abc>() <- YES
	if (Words.size() - Input[Words.back()].is(Flags::TEMPLATE_COMPONENT) < 2)
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
		if (Input[c].Value == "jump" || Input[c].Value == "return" || Input[c].Value == "import" || Input[c].Value == "use")
			return;

	Node* New_Defined_Object = new Node(PROTOTYPE, new Position(Input[Words.back()].Location));

	if (Input[Words.back()].is(Flags::TEMPLATE_COMPONENT)) {
		if (Input[Words.back()].is(Flags::TEMPLATE_COMPONENT)) {
			for (auto T : Input[Words.back()].Components) {
				Node* Template = new Node(TEMPLATE_NODE, T.Value, &T.Location);

				Template->Inheritted.push_back("type");

				New_Defined_Object->Templates.push_back(Template);
			}
		}
		Words.pop_back();
		New_Defined_Object->Is_Template_Object = true;
	}
	//type a
	vector<string> Inheritted;

	//skip the last that is the name index.
	for (int j = 0; j < Words.size() - 1; j++) {
		Inheritted.push_back(Input[Words[j]].Value);
	}

	New_Defined_Object->Inheritted = Inheritted;
	New_Defined_Object->Name = Input[Words.back()].Value;
	New_Defined_Object->Scope = Scope;

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

			if (p->is("type"))
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

		if (p->is("type"))
			p->Is_Template_Object = true;

		New_Defined_Object->Parameters.push_back(p);
	}

	//erase inherittes as well the name as well the pearameters from the input list
	Input.erase(Input.begin() + Words[0], Input.begin() + Paranthesis[0] + 1);

	Scope->Defined.push_back(New_Defined_Object);

	if (i < Input.size())
		Prototype_Pattern(i);

	return;
}

void Parser::Combine_Import_Shattered_Return_Info(int i)
{
	//import func 4 integer banana(4 integer)
	//import func 8 decimal banana(4 integer)
	if (i + 1 >= Input.size())
		return;
	if (!Input[i].is(Flags::NUMBER_COMPONENT) || !Input[i + 1].is(Flags::TEXT_COMPONENT))
		return;

	Node* Numerical_Type = new Node(NUMBER_NODE, &Input[i].Location);
	Numerical_Type->Name = Input[i].Value;
	Numerical_Type->Format = Input[i + 1].Value;

	Input[i].Flags = Flags::NUMERICAL_TYPE_COMPONENT;
	Input[i].node = Numerical_Type;
	Input.erase(Input.begin() + i + 1);
}

void Parser::Import_Pattern(int i)
{
	//func banana(int, short)\n
	vector<int> Words = Get_Amount_Of(i, { Flags::TEXT_COMPONENT, Flags::KEYWORD_COMPONENT, Flags::TEMPLATE_COMPONENT, Flags::NUMERICAL_TYPE_COMPONENT });
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

	Node* New_Defined_Object = new Node(IMPORT, new Position(Input[Words.back()].Location));


	if (Input[Words.back()].is(Flags::TEMPLATE_COMPONENT)) {
		for (auto T : Input[Words.back()].Components) {
			Node* Template = new Node(TEMPLATE_NODE, T.Value, new Position(T.Location));

			Template->Inheritted.push_back("type");

			New_Defined_Object->Templates.push_back(Template);
		}
		Words.pop_back();
		New_Defined_Object->Is_Template_Object = true;
	}

	//type a
	vector<string> Inheritted;

	//skip the last that is the name index.
	for (int j = 0; j < Words.size() - 1; j++) {
		if (Input[Words[j]].is(Flags::NUMERICAL_TYPE_COMPONENT)) {
			New_Defined_Object->Numerical_Return_Types.push_back(Input[Words[j]].node);
		}
		else
			Inheritted.push_back(Input[Words[j]].Value);
	}

	New_Defined_Object->Inheritted = Inheritted;
	New_Defined_Object->Name = Input[Words.back()].Value;
	New_Defined_Object->Scope = Scope;

	vector<Component> Types;
	for (auto j : Input[Paranthesis[0]].Components) {
		if (j.Value == ",") {
			string Format = "";
			for (int j = 0; j < Types.size(); j++) {
				if (Types[j].Value == "decimal" || Types[j].Value == "integer") {
					Format = Types[j].Value;
					Types.erase(Types.begin() + j);
				}
			}
			Node* p;
			if (Types.back().is(Flags::NUMBER_COMPONENT))
				p = new Node(NUMBER_NODE, new Position(j.Location), Format);
			else
				p = new Node(OBJECT_DEFINTION_NODE, new Position(j.Location), Format);

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

			if (p->is("type"))
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
			p = new Node(NUMBER_NODE, new Position(Types.back().Location), Format);
		else
			p = new Node(OBJECT_DEFINTION_NODE, new Position(Types.back().Location));

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

		if (p->is("type"))
			p->Is_Template_Object = true;

		New_Defined_Object->Parameters.push_back(p);
	}

	//erase inherittes as well the name as well the pearameters from the input list
	Input.erase(Input.begin() + Words[0], Input.begin() + Paranthesis[0] + 1);

	Scope->Defined.push_back(New_Defined_Object);

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
	if (!Scope->Find(Input[i].Value, Scope, { PARAMETER_NODE, OBJECT_DEFINTION_NODE, OBJECT_NODE, TEMPLATE_NODE, CLASS_NODE }, false))
		return;
	if (Input[i].node != nullptr)
		return;	//we dont want to rewrite the content

	Scope->Copy_Node(Input[i].node, new Node(*Scope->Find(Input[i].Value, Scope, {PARAMETER_NODE, OBJECT_DEFINTION_NODE, OBJECT_NODE, TEMPLATE_NODE, CLASS_NODE }, false)), Scope);
	Input[i].node->Location = new Position(Input[i].Location);
	Input[i].node->Defined.clear();

	//List<int> a -> __List_int a
	if (Input[i].node->Templates.size() > 0) {
		//this means that the next element is a template
		if (i+1 >= Input.size() || !Input[i + 1].is(Flags::TEMPLATE_COMPONENT))
			Report(Observation(ERROR, Input[i].Value, Input[i].Location, "Missing template arguments"));

		Input[i].node->Templates = Input[i + 1].node->Templates;

		Input.erase(Input.begin() + i + 1);
	}
	else if (i + 1 < Input.size() && Input[i + 1].is(Flags::TEMPLATE_COMPONENT)) {
		//check if the current scope is a namespace or global scope
		if (!Scope->is("static") || !Scope->is(CLASS_NODE)) {
			for (auto T : Input[i + 1].Components)
				Input[i].node->Templates.push_back(T.node);

			if (Scope->Find(Input[i].node, Scope) == nullptr) {
				Report(Observation(ERROR, "This object does not take template arguments '" + Input[i].Value + "'", Input[i].Location, ""));
			}

			Input[i].node = Scope->Find(Input[i].node, Scope);
			Input[i].node->Templates = Input[i + 1].node->Templates;
			Input.erase(Input.begin() + i + 1);
		}
		else {
			//List<T> a -> List<T> a
			//this will conserve the template as source code for the template manifestation
			//Input[i] = Component("Un_initialized", Flags::UN_INITIALIZED_TEMPLATES, { Input[i], Input[i + 1] });
			Input[i].Components.push_back(Input[i + 1]);
			Input.erase(Input.begin() + i + 1);
			return;
		}
	}

	if (Input[i].node->is(OBJECT_DEFINTION_NODE))
		Input[i].node->Type = OBJECT_NODE;
	else if (Input[i].node->is(PARAMETER_NODE))
		Input[i].node->Type = PARAMETER_NODE;
	else if (Input[i].node->is(LABEL_NODE))
		Input[i].node->Type = LABEL_NODE;
	else if (Input[i].node->is(FUNCTION_NODE)) //this happends for function pointer adress geting prosess
		Input[i].node->Type = OBJECT_NODE;

	Input[i].node->Scope = Scope;
	return;
}

void Parser::This_Pattern(int i)
{
}

void Parser::Complex_Cast(int i)
{
	//this needs to be called before any paranthesis parser
	//x->(T ptr ptr)
	//this function creates a new virtual class that repesents the cast types
	if (i - 1 < 0)
		return;
	if (!Input[i].is(Flags::PAREHTHESIS_COMPONENT))
		return;
	if (Input[i - 1].Value != "->")
		return;

	Input[i] = *Construct_Virtual_Class_For_Complex_Cast(Input[i]);
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

	//if (Input[i].Value[0] == '{')
	//	if (Scope->is(CLASS_NODE) && Scope->is("static") != -1)
	//		return;		//this is for member functions

	//create an content Node and output will be in the same input.
	Node* Paranthesis = new Node(CONTENT_NODE, new Position(Input[i].Location));
	Paranthesis->Scope = Scope;
	
	Parser TMP_Parser(Scope);
	TMP_Parser.Input = Input[i].Components;
	TMP_Parser.Factory();

	for (Component j : TMP_Parser.Input)
		if (j.node != nullptr) {
			//j.node->Context = Paranthesis;
			//j.node->Parent = Paranthesis;
			Node* New_j;
			j.node->Copy_Node(New_j, j.node, Scope);
			Paranthesis->Childs.push_back(New_j);
		}

	Paranthesis->Paranthesis_Type = Input[i].Value[0];
	Input[i].Components = TMP_Parser.Input;
	Input[i].node = Paranthesis;

	return;
}

void Parser::Math_Pattern(int& i, vector<string> Operators, int F, bool Change_Index)
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
	Operator->Scope = Scope;

	if (Input[(size_t)i - 1].node != nullptr)
		Operator->Left = Input[(size_t)i - 1].node;
	else {
		//Dont worry about function calls
		Node* new_member = new Node(OBJECT_DEFINTION_NODE, new Position(Input[(size_t)i + 1].Location));
		new_member->Name = Input[(size_t)i - 1].Value;
		new_member->Scope = Operator->Scope;


		Operator->Left = new_member;
	}

	if (Input[(size_t)i + 1].node != nullptr)
		Operator->Right = Input[(size_t)i + 1].node;
	else {
		//test.a.m //these a.m are in different localscope.
		//the right side does not need to be determined as well the left.
		//Dont worry about function calls
		Node* new_member = new Node(OBJECT_DEFINTION_NODE, new Position(Input[(size_t)i + 1].Location));
		new_member->Name = Input[(size_t)i + 1].Value;
		new_member->Scope = Operator->Scope;

		Operator->Right = new_member;
	}

	//this is for algebra only!!
	if (Input[i].Value == "-"){
		Node* Coefficient = new Node(NUMBER_NODE, new Position(Input[i].Location));
		Coefficient->Name = "-1";
		Operator->Right->Coefficient = Coefficient;
	}

	if (Operator->Name == "=")
		if (Scope->Name == "GLOBAL_SCOPE")
			Scope->Find(Operator->Left->Name)->Inheritted.push_back("const");

	//give the left and right operators the right holder information
	Operator->Left->Context = Operator;
	Operator->Right->Context = Operator;

	Input[i].node = Operator;
	Input.erase(Input.begin() + i + 1);
	if (Change_Index)
		i--;
	Input.erase(Input.begin() + i - !Change_Index);

	if ((size_t)i + 1 + Change_Index > Input.size() - 1)
		return;
	if (Input[i + Change_Index].is(Flags::OPERATOR_COMPONENT))
		Math_Pattern(i += Change_Index, Operators, F, Change_Index);
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
	Num->Scope = Scope;

	for (int j = 0; j < Num->Name.size(); j++)
		if (Num->Name[j] == '.') {
			Num->Format = "decimal";
			break;
		}

	if (Num->Format == "decimal") {
		int Dot_Index = Num->Name.find_first_of('.');

		int Decimal_Precission = Num->Name.substr(Dot_Index, Num->Name.size() - 1).size();

		if (Decimal_Precission > 8) {
			Num->Size = 8;
		}
		else {
			Num->Size = 4;
		}
	}
	else {
		if (atoll(Num->Name.c_str()) > INT32_MAX)
			Num->Size = 8;
		else
			Num->Size = 4;
	}

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
	if (i + 1 > Input.size() - 1)
		return;
	if (Input[i + 1].is(Flags::END_COMPONENT))
		return;
	if (Input[i].node != nullptr)
		return;
	if (!Input[i].is(Flags::OPERATOR_COMPONENT))
		return;
	//return if the left side of the operator is a computable oject.
	if (Input[(size_t)i - 1].Has({ Flags::TEXT_COMPONENT, Flags::NUMBER_COMPONENT, Flags::PAREHTHESIS_COMPONENT }))		//a -b
		return;

	bool op_Pass = false;
	for (string s : Prefixes)
		if (Input[i].Value == s)
			op_Pass = true;
	if (!op_Pass)
		return;

	Node* PreFix = new Node(PREFIX_NODE, new Position(Input[i].Location));
	PreFix->Scope = Scope;
	//name
	PreFix->Name = Input[i].Value;
	PreFix->Right = Input[(size_t)i + 1].node;

	PreFix->Right->Context = PreFix;
	PreFix->Right->Scope = PreFix->Scope;
	
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
	if (i -1 < 0)
		return;
	if (Input[i].node != nullptr)
		return;
	if (!Input[i].is(Flags::OPERATOR_COMPONENT))
		return;

	//check if this operator is meant to be a prefix, not postfix.
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

	Node* post = new Node(POSTFIX_NODE, new Position(Input[i].Location));
	post->Name = Input[i].Value;
	post->Scope = Scope;
	
	//set the node to postfix as left
	post->Left = Input[(size_t)i - 1].node;
	post->Left->Context = post;
	post->Left->Scope = post->Scope;

	Input[i].node = post;

	Input.erase(Input.begin() + i - 1);

	return;
}

void Parser::Variable_Negate_Pattern(int i)
{
	if (Input[i].Value != "-")
		return;
	if (i - 1 >= 0) {
		if (Input[(size_t)i - 1].Has({ Flags::PAREHTHESIS_COMPONENT, Flags::NUMBER_COMPONENT, Flags::TEXT_COMPONENT, Flags::OPERATOR_COMPONENT}))
			return;
	}
	if (((size_t)i + 1) > Input.size())
		return;

	Node* Coefficient = new Node(NUMBER_NODE, new Position(Input[i].Location));
	Coefficient->Name = "-1";

	Node* Coefficient_Operator = new Node(OPERATOR_NODE, new Position(Input[i].Location));
	Coefficient_Operator->Name = "*";
	Coefficient_Operator->Left = Input[(size_t)i + 1].node->Coefficient;
	Coefficient_Operator->Right = Coefficient;

	Input[(size_t)i+1].node->Coefficient = Coefficient_Operator;

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

	int Paranthesis_Offset = 1;
	if (i + 1 < Input.size() && Input[i + 1].is(Flags::TEMPLATE_COMPONENT))
		Paranthesis_Offset = 2;

	vector<int> Paranthesis = Get_Amount_Of(i + Paranthesis_Offset, Flags::PAREHTHESIS_COMPONENT);

	if (Paranthesis.size() == 0)
		return;
	if (Paranthesis.size() > 1 && Input[Paranthesis[1]].Value[0] != '[')
		return;
	if (Input[(size_t)i + Paranthesis_Offset].Value[0] != '(')
		return;

	Node* call = new Node(CALL_NODE, new Position(Input[i].Location));
	call->Name = Input[i].Value;

	if (Input[i + 1].is(Flags::TEMPLATE_COMPONENT)) {
		//Nodize the template type 'int' for example.
		Parser p(Scope);
		p.Input = {Input[i + 1]};
		p.Factory();

		//save all the template types into the call node, for postprosessor to handle this.
		for (auto T : p.Input.back().node->Templates)
			call->Templates.push_back(T);

		Input.erase(Input.begin() + i + 1);
	}
	//give the normal call the inheritance for future operator type determining


	call->Scope = Scope;

	if (Scope->is(CALL_NODE))
		call->Context = Scope;

	//initialize the parenthesis that contains the parameters
	Parser p(Scope);
	p.Input = {Input[(size_t)i + 1]};
	p.Factory();

	call->Parameters = p.Input.back().node->Childs;

	for (auto P : call->Parameters) {
		P->Context = call;
	}

	Input[i].node = call;
	Input[i].Value = call->Name;

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
	arr->Scope = Scope;

	if (Input[(size_t)i].node != nullptr)
		arr->Left = Input[(size_t)i].node;
	else {
		//Dont worry about function calls
		Node* new_member = new Node(OBJECT_DEFINTION_NODE, new Position(Input[i].Location));
		new_member->Name = Input[(size_t)i].Value;

		arr->Left = new_member;
		arr->Left->Scope = Scope;
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
		arr->Right->Scope = Scope;
	}

	//TODO:
	//Needs more testing with more complex array usage like: a[x][y][z]
	arr->Name = "[]";

	Input[i].node = arr;

	Input.erase(Input.begin() + i + 1);
	Array_Pattern(i);
	return;
}

void Parser::Function_Pattern(int i, Node* Class)
{
	//import int func main() [\n] {..}
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

	int Paranthesis_Offset = 1;
	if (i + 1 < Input.size() && Input[i + 1].is(Flags::TEMPLATE_COMPONENT))
		Paranthesis_Offset = 2;

	vector<int> Parenthesis_Indexes = Get_Amount_Of(i + Paranthesis_Offset, Flags::PAREHTHESIS_COMPONENT, false);
	if (Parenthesis_Indexes.size() != 2)
		return;
	if (Input[Parenthesis_Indexes[0]].Value[0] != '(')
		return;

	//first try to get the behaviour
	Node* func = nullptr;
	if (Input[i].node->Type == OBJECT_DEFINTION_NODE)
		func = Input[i].node;
	else if (Input[i].node->Name == ".") {
		Member_Function_Pattern(i);
		return;
	}
	else
		func = Scope->Find(Input[i].Value, Scope, true);
	if (func == nullptr) {
		Report(Observation(ERROR, "Parser didnt find " + Input[i].node->Name + " constructor!", Input[i].Location));
	}
	//override the object definition node flag
	func->Type = FUNCTION_NODE;
	//set the other values
	func->Name = Input[i].Value;
	func->Scope = Scope;

	if (Class == nullptr) {
		Class = func->Get_Scope_As({ CLASS_NODE }, func, false);
		if (Class->is("static"))
			Class = nullptr;
	}

	func->Template_Children = { Input[Parenthesis_Indexes[0]], Input[Parenthesis_Indexes[1]] };

	//Template Fucntions.
	for (auto T : func->Inheritted)
		if (func->Find_Template(T)) {
			func->Is_Template_Object = true;
			break;
		}
	//construct nodes from the component templates.
	if (Paranthesis_Offset == 2) {
		for (auto T : Input[i + 1].Components) {
			Node* Template = new Node(TEMPLATE_NODE, T.Value, &T.Location);

			Template->Inheritted.push_back("type");

			func->Templates.push_back(Template);
		}
		func->Is_Template_Object = true;
	}

	if (Class) {
		//Make the returning type to follow the template returning protocols.
		Component* Uninitialized_Templates;
		if (Class->Is_Template_Object) {
			string Result = Class->Get_Uninitialized_Templates();
			vector<Component> tmp = Lexer::GetComponents(Result);

			Node* tmp_Class = new Node(CLASS_NODE, new Position());
			tmp_Class->Templates = Class->Templates;

			Parser p(tmp_Class);
			p.Input = tmp;
			p.Factory();

			Uninitialized_Templates = new Component(Class->Generate_Uninitialized_Template_Component(p.Input));

		}

		//Add the this pointter to the function parameters
		Node* This = new Node(PARAMETER_NODE, "this", func->Location);
		if (Class->Is_Template_Object) {
			This->Inheritted = { "ptr" };
			This->Un_Initialized_Template_Inheritance = { { *Uninitialized_Templates, 0 } };
		}
		else {
			This->Inheritted = { Class->Name, "ptr" };
		}
		This->Scope = func;
		This->Size = _SYSTEM_BIT_SIZE_;
		//This->Defined = Class->Defined;
		This->Inheritable_templates = Class->Inheritable_templates;

		func->Defined.push_back(This);
	}

	//if the functoin is a template typed, then we must be carefull with the parameters that use the template too
	Parser p(func);
	p.Input.push_back(Input[Parenthesis_Indexes[0]]);
	p.Factory();

	for (auto& j : func->Defined) {
		j->Type = PARAMETER_NODE;
	}

	func->Parameters = func->Defined;
	if (!func->Is_Template_Object) {
		p.Input.clear();

		p.Input.push_back(Input[Parenthesis_Indexes[1]]);
		p.Factory();
		func->Childs = p.Input[0].node->Childs;
		p.Input.clear();

		for (auto j : func->Defined) {
			Safe s;
			s.Check_For_Undefined_Inheritance(j);
		}

		func->Mangled_Name = MANGLER::Mangle(func, "");
	}

	Input[i].node = func;

	Input.erase(Input.begin() + Parenthesis_Indexes[1]);
	Input.erase(Input.begin() + Parenthesis_Indexes[0]);

	if (func->Templates.size() > 0) {
		Input.erase(Input.begin() + i + 1);
	}

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
	if (Scope->Find(Input[i].Value, Scope, false) == nullptr)
		return;

	int Paranthesis_Offset = 1;
	if (i+1 < Input.size() && Input[i + 1].is(Flags::TEMPLATE_COMPONENT))
		Paranthesis_Offset = 2;

	vector<int> Parenthesis_Indexes = Get_Amount_Of(i + Paranthesis_Offset, Flags::PAREHTHESIS_COMPONENT, false);
	
	if (Parenthesis_Indexes.size() != 1)
		return;
	if (Input[Parenthesis_Indexes[0]].Value[0] != '{')
		return;

	Node* Type = nullptr;
	if (Input[i].node != nullptr)
		//dont worry this has same pointter as the one that is in the Defined list, so this point to it
		Type = Input[i].node;
	else
		Type = Scope->Find(Input[i].Value, Scope, OBJECT_DEFINTION_NODE);
	if (Type == nullptr) {
		Report(Observation(ERROR, "Type definition was not found!", Input[i].Location));
		throw::runtime_error("ERROR!");
	}
	//reset the value
	Type->Type = CLASS_NODE;

	//combine inheritted memebrs
	Type->Get_Inheritted_Class_Members();

	if (Input[i + 1].is(Flags::TEMPLATE_COMPONENT)) {
		for (auto T : Input[i + 1].Components) {
			Node* Template = new Node(TEMPLATE_NODE, T.Value, &T.Location);

			Template->Inheritted.push_back("type");

			Type->Templates.push_back(Template);
		}
		Type->Template_Children = Input[Parenthesis_Indexes[0]].Components;
		Type->Is_Template_Object = true;
	}

	if (!Type->Is_Template_Object) {
		Parser p(Type);
		p.Input.push_back(Input[Parenthesis_Indexes[0]]);
		p.Factory();

		for (auto j : Type->Defined) {
			Safe s;
			s.Check_For_Undefined_Inheritance(j);
		}

		Type->Append(Type->Childs, p.Input[0].node->Childs);
		p.Input.clear();
	}

	//This means that the class is a namespace
	//Namespace Combination system 5000
	if (Type->is("static")) {

		for (auto& j : Type->Defined) {
			if (j->is("static"))
				continue;
			if (j->Has({ FUNCTION_NODE, CLASS_NODE }))
				continue;

			j->Inheritted.insert(j->Inheritted.begin(), "static");
		}
	}

	//infiltrate the class type and inject this behemoth
	/*if (MANGLER::Is_Base_Type(Type) == false && sys->Info.Reference_Count_Size > 0) {
		Node* Reference_Count = new Node(OBJECT_DEFINTION_NODE, Type->Location);
		Reference_Count->Name = "Reference_Count";
		Reference_Count->Scope = Type;

		Node* Size_Representer = Type->Find(sys->Info.Reference_Count_Size, Type, CLASS_NODE, "integer");

		if (Size_Representer == nullptr) {
			Report(Observation(WARNING, "Cannot find suitable size type for the reference countter", *Type->Location));
			//we can still save this!
			Node* Size = new Node(OBJECT_DEFINTION_NODE, Type->Location);
			Size->Name = "size";
			Size->Size = sys->Info.Reference_Count_Size;
			Size->Inheritted.push_back("const");

			Reference_Count->Defined.push_back(Size);
			Reference_Count->Inheritted.push_back("type");
		}
		else
			Reference_Count->Inheritted.push_back(Size_Representer->Name);
	}*/

	Input.erase(Input.begin() + Parenthesis_Indexes[0]);

	if (i+1 < Input.size() && Input[i + 1].is(Flags::TEMPLATE_COMPONENT))
		Input.erase(Input.begin() + i + 1);

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
	con->Scope = Scope;

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
	Else->Scope = Scope;

	p.Input.push_back(Input[Parenthesis_Indexes[0]]);
	p.Factory();

	Else->Childs = p.Input[0].node->Childs;

	Input[i].node = Else;

	Input.erase(Input.begin() + Parenthesis_Indexes[0]);

	return;
}

void Parser::Operator_Order()
{
	if (Input.size() < 2)
		return;
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "." }, OPERATOR_NODE);
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
		Math_Pattern(i, { "^" }, OPERATOR_NODE);
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "*", "/" , "%" }, OPERATOR_NODE);
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "+", "-" }, OPERATOR_NODE);
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "<<", ">>" }, BIT_OPERATOR_NODE);
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "==", "!=", "<=", ">=", "!<", "!>" , "|=", "&=" }, CONDITION_OPERATOR_NODE);
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "&", "!&" }, BIT_OPERATOR_NODE);
	//for (int i = 0; i < Input.size(); i++)
	//	Math_Pattern(i, { "?" }, BIT_OPERATOR_NODE);	
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "¤" }, BIT_OPERATOR_NODE);
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "|", "!|" }, BIT_OPERATOR_NODE);
	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "<", ">" }, CONDITION_OPERATOR_NODE);

	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "&&", "||" }, LOGICAL_OPERATOR_NODE);

	for (int i = 0; i < Input.size(); i++)
		Math_Pattern(i, { "=", "+=", "-=", "*=", "/=" }, ASSIGN_OPERATOR_NODE);
}

void Parser::Return_Pattern(int i)
{
	if (Input[i].Value != "return")
		return;
	if (Input[i].node != nullptr)
		return;
	bool No_Return_Value = (((size_t)i + 1 > Input.size() - 1) || (Input[i+1].node == nullptr));

	//return a + b
	//return;
	Node* ret = new Node(FLOW_NODE, new Position(Input[i].Location));
	ret->Name = "return";
	ret->Scope = Scope;
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
	Node* l = Scope->Find(Input[i].Value, Scope);
	if (l == nullptr)
		return;
	if (!l->is(LABEL_NODE))
		return;
	Node* L = new Node(LABEL_NODE, new Position(Input[i].Location));
	L->Name = Input[i].Value;
	L->Scope = Scope;
	
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
	if (Scope->Find(Input[i].Value, Scope) != nullptr)
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
	label->Scope = Scope;

	Input[i].node = label;

	Scope->Defined.push_back(label);
}

void Parser::Break_Pattern(int i)
{
	if (Input[i].Value != "break")
		return;

	Node* While = Scope->Get_Scope_As({ WHILE_NODE }, Scope, false);

	if (!While) {
		Report(Observation(ERROR, "Use of 'break' outside of 'while'.", Input[i].Location, SYNTAX_ERROR));
	}

	Node* Break = new Node(FLOW_NODE, &Input[i].Location);
	//This will point straight to the while loop for conveniences.
	Break->Scope = While;
	Break->Name = "break";

	Input[i].node = Break;
}

void Parser::Continue_Pattern(int i)
{
	if (Input[i].Value != "continue")
		return;

	Node* While = Scope->Get_Scope_As({ WHILE_NODE }, Scope, false);

	if (!While) {
		Report(Observation(ERROR, "Use of 'continue' outside of 'while'.", Input[i].Location, SYNTAX_ERROR));
	}

	Node* Continue = new Node(FLOW_NODE, &Input[i].Location);
	//This will point straight to the while loop for conveniences.
	Continue->Scope = While;
	Continue->Name = "continue";

	Input[i].node = Continue;
}

void Parser::Size_Pattern(int i)
{
	//size = 4
	if (Input[i].Value != "size")
		return;
	if (!Scope->is(CLASS_NODE))
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
	size->Scope = Scope;

	Scope->Defined.push_back(size);

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
	if (!Scope->is(CLASS_NODE))
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
	format->Scope = Scope;

	Scope->Defined.push_back(format);

	Input[i].node = format;

	Input.erase(Input.begin() + i + 1);
	Input.erase(Input.begin() + i + 1);
	return;
}

void Parser::Member_Function_Pattern(int i)
{
	//return_type class_name.funcname(){}
	if (Scope->is(FUNCTION_NODE))
		return;
	if (Input[i].Value != ".")
		return;

	//the name must be connected with the fethcer already by the dot operator.

	int Paranthesis_Offset = 1;
	if (i + Paranthesis_Offset < Input.size() && Input[i + Paranthesis_Offset].is(Flags::TEMPLATE_COMPONENT))
		Paranthesis_Offset = 2;

	vector<int> Parenthesis_Indexes = Get_Amount_Of(i + Paranthesis_Offset, Flags::PAREHTHESIS_COMPONENT, false);
	if (Parenthesis_Indexes.size() != 2)
		return;
	if (Input[Parenthesis_Indexes[1]].Value[0] != '{')
		return;
	if (Input[Parenthesis_Indexes[0]].Value[0] != '(')
		return;
	//set all the left sided of operators as the fetchers
	Input[i].node->Left->Transform_Dot_To_Fechering(Input[i].node->Right);

	//Find the scope that this function is set to as a member to.
	Node* Class = Scope->Find(Input[i].node->Right->Fetcher, Scope, CLASS_NODE);
	if (Class == nullptr)
		Report(Observation(ERROR, Input[i].node->Right->Fetcher->Name + " was not found when creating " + Input[i].node->Right->Name, Input[i].Location));

	//delete the tmp fecher defined in the parent scope.
	Node* Ghost_Definition = Input[i].node->Left;

	for (int j = 0; j < Scope->Defined.size(); j++)
		if (Ghost_Definition == Scope->Defined[j])
			Scope->Defined.erase(Scope->Defined.begin() + j);

	//unwrap the . operator
	Input[i].node->Right->Context = Input[i].node->Context;
	Input[i].node->Right->Scope = Input[i].node->Scope;
	Input[i].node = Input[i].node->Right;
	Input[i].Value = Input[i].node->Name;

	//port foward the fetcher magnetized inheritance to this function
	if (!Input[i].node->Fetcher->is("static")) {
		Input[i].node->Inheritted = Input[i].node->Fetcher->Inheritted;
	}
	else {
		Input[i].node->Inheritted = Input[i].node->Fetcher->Fetching_Inheritance;
	}

	Input[i].node->Un_Initialized_Template_Inheritance = Input[i].node->Fetcher->Un_Initialized_Template_Inheritance;
	//clear exess stuff
	Input[i].node->Fetcher->Inheritted.clear();
	Input[i].node->Fetcher->Un_Initialized_Template_Inheritance.clear();
	Input[i].node->Is_Template_Object = Class->Is_Template_Object;

	//replace all the class named fetchers by the Class node for future referencing.
	//this code break c++ XD
	/*vector<Node*> Fethcers = Input[i].node->Get_All_Fetchers();

	for (auto& Fetcher : Fethcers) {
		if (Fetcher->Name == Class->Name)
			*Fetcher = *Class;
	}*/

	Function_Pattern(i, Class);

	Class->Defined.push_back(Input[i].node);

	//Node* Fethcer = Input[i].node->Fetcher;
	//Input[i].node->Fetcher = nullptr;

	//if (Class->Scope->Find(Input[i].node, Class->Scope, FUNCTION_NODE) == nullptr) {
	//	Class->Scope->Defined.push_back(Input[i].node);
	//	Input[i].node->Fetcher = Fethcer;
	//}
	////Input[i].node->Fetcher = Fethcer;
	//else if (Input[i].node->Fetcher = Fethcer; !Input[i].node->Compare_Fetchers(Class->Scope->Find(Input[i].node, Class->Scope, FUNCTION_NODE)))
	//	Class->Scope->Defined.push_back(Input[i].node);

	Input.erase(Input.begin() + i);

}

void Parser::Use_Pattern(int i)
{
	//use foo
	if ((size_t)i + 1 >= Input.size())
		return;
	if (Input[i].Value != "use")
		return;
	if (!Input[(size_t)i + 1].is(Flags::TEXT_COMPONENT))
		return;

	Node* Namespace = Scope->Find(Input[(size_t)i + 1].Value);

	if (Namespace == nullptr)
		return;

	if (!Namespace->is("static") || !Namespace->is(CLASS_NODE))
		return;

	vector<Node*> Inlined = Namespace->Defined;

	Scope->Append(Inlined, Namespace->Inlined_Items);

	Node* Closest_Namespace = Scope->Get_Scope_As(CLASS_NODE, Scope);

	//check if the same namespace is already inlined to this exact scope.
	for (auto n : Closest_Namespace->Inlined_Namespaces)
		if (n == Namespace || n->Name == Namespace->Name)
			return;

	Closest_Namespace->Inlined_Namespaces.push_back(Namespace);

	for (auto &j : Inlined) {
		Node* n = j;
		if (j->is(FUNCTION_NODE)) {
			continue;
			//n = new Node(*n);
		}

		//j = j->Copy_Node(n, Closest_Namespace);
	}

	for (auto &j : Inlined) {
		if (j->Fetcher)
			continue;

		j->Fetcher = Namespace;
	}

	for (auto &j : Inlined) {
		if (j->Is_Template_Object)
			continue;
		if (j->Has({ FUNCTION_NODE, CLASS_NODE })) 
			continue;

		j->Update_Size();
	}

	Closest_Namespace->Append(Closest_Namespace->Inlined_Items, Inlined);

	Input.erase(Input.begin() + i, Input.begin() + i + 2);
}

Component* Parser::Construct_Virtual_Class_For_Complex_Cast(Component Parenthesis)
{
	Node* Virtual_Class = new Node(CLASS_NODE, new Position(Parenthesis.Location));

	for (auto i : Parenthesis.Components) {
		Virtual_Class->Inheritted.push_back(i.Value);
	}

	string Virtual_Class_Name = "____VIRTUAL_CLASS";

	for (auto i : Virtual_Class->Get_Inheritted())
		Virtual_Class_Name += "_" + i;

	Component *Cast = new Component(Virtual_Class_Name, Flags::TEXT_COMPONENT);

	if (Scope->Find(Virtual_Class_Name)) {
		Scope->Copy_Node(Cast->node, Scope->Find(Virtual_Class_Name), Scope->Find(Virtual_Class_Name)->Scope);
		return Cast;
	}

	Virtual_Class->Name = Virtual_Class_Name;
	Virtual_Class->Scope = Scope->Get_Scope_As(CLASS_NODE, {"static"}, Scope);

	Virtual_Class->Update_Size();

	Node* New_Virtual_Class;
	Scope->Copy_Node(New_Virtual_Class, Virtual_Class, Virtual_Class->Scope);
	Virtual_Class->Scope->Defined.push_back(New_Virtual_Class);

	Cast->node = Virtual_Class;

	return Cast;
}

void Parser::Factory() {
	for (int i = 0; i < Input.size(); i++)
		Combine_Comment(i);
	for (int i = 0; i < Input.size(); i++)
		Combine_Import_Shattered_Return_Info(i);
	for (int i = 0; i < Input.size(); i++)
		Template_Pattern(i);
	for (auto& i : Input)
		Construct_Virtual_Class_To_Represent_Multiple_Template_Inputs(i);
	for (int i = 0; i < Input.size(); i++) {
		//variable/objects definator.		
		Prototype_Pattern(i);	//Definition_pattern stoles this import functions, so this goes first
		Import_Pattern(i);
		//Template_Pattern(i);
		Definition_Pattern(i);
		Label_Definition(i);
	}
	for (int i = 0; i < Input.size(); i++)
		Remove_All_Excess_Comments(i);
	for (int i = 0; i < Input.size(); i++) {
		//multiline AST stuff
		Combine_Dot_In_Member_Functions(i);
		Type_Pattern(i);		//class constructor
		Use_Pattern(i);
		Inject_Template_Into_Member_Function_Fetcher(i);
		if (Input.size() == 0 || i >= Input.size())
			break;
		Nodize_Template_Pattern(i);
		Constructor_Pattern(i);	//constructor needs the type to be defined as a class 
		Member_Function_Pattern(i);
		Function_Pattern(i);
		If_Pattern(i);
		Else_Pattern(i);
		Callation_Pattern(i);
		Jump_Pattern(i);
		Break_Pattern(i);
		Continue_Pattern(i);
	}
	for (int i = 0; i < Input.size(); i++) {
		//prepreattor for math operator AST combinator.
		Object_Pattern(i);
		Template_Type_Constructor(i);
		Complex_Cast(i);
		Parenthesis_Pattern(i);
		String_Pattern(i);
		Number_Pattern(i);
		Label_Pattern(i);
	}
	for (int i = 0; i < Input.size(); i++) {
		Size_Pattern(i);
		Format_Pattern(i);
	}
	for (int i = 0; i < Input.size(); i++) {
		Operator_Combinator(i);
	}
	//AST operator combinator.
	Operator_Order();
	for (int i = 0; i < Input.size(); i++) {
		Return_Pattern(i);
	}

}

