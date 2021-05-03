#include "../../H/Parser/PostProsessor.h"
#include "../../H/Docker/Mangler.h"
#include "../../H/Parser/Parser.h"
#include "../../H/Lexer/Lexer.h"
#include "../../H/UI/Safe.h"
#include "../../H/UI/Usr.h"

extern Node* Global_Scope;
long long LNumber = 0;
extern bool Optimized;
extern Usr* sys;

void PostProsessor::Factory() {
	Transform_Component_Into_Node(); 
	for (int i = 0; i < Parent->Defined.size(); i++) {
		//the prototypes needs the types to have sizes to determine the number parameters assosiative type.
		Type_Size_Definer(i);
	}
	for (int i = 0; i < Parent->Defined.size(); i++) {
		//the prototypes needs the types to have sizes to determine the number parameters assosiative type.
		Handle_Imports(i);
	}
	for (int i = 0; i < Parent->Defined.size(); i++) {
		Type_Definer(i);
	}
	for (int i = 0; i < Parent->Defined.size(); i++) {
		//the prototypes needs the types to have sizes to determine the number parameters assosiative type.
		Member_Function_Defined_Outside(i);
		Member_Function_Defined_Inside(i);
		Open_Function_For_Prosessing(i);
	}
	//Define_Sizes(Parent);
	for (int i = 0; i < Input.size(); i++) {
		Cast(Input[i]);
		Open_Paranthesis(i);
		Operator_Overload(i);
		Open_Condition_For_Prosessing(i);
		Open_Loop_For_Prosessing(i);
		//Combine_Conditions(i);
		Combine_Member_Fetching(Input[i]);
		Determine_Return_Type(i);
		Determine_Array_Type(i);
		Open_Call_Parameters_For_Prosessing(i);
		Find_Call_Owner(Input[i]);
		Analyze_Global_Variable_Changes(i);
		Change_Local_Strings_To_Global_Pointters(i);
		Update_Operator_Inheritance(Input[i]);
		Analyze_Return_Value(Input[i]);
		Increase_Calling_Number_For_Function_Address_Givers(Input[i]);
		Open_PreFix_Operator(i);
		Open_PostFix_Operator(i);
	}
	Open_Safe(Input);
	for (int i = 0; i < Input.size(); i++)
		Combine_Condition(i);
	for (int i = 0; i < Input.size(); i++)
		Move_Global_Varibles_To_Header(i);
	for (int i = 0; i < Input.size(); i++)
		Algebra_Laucher(i);
}

void PostProsessor::Transform_Component_Into_Node()
{
	//<summary>
	//Extracts the Node ptr's from the component tokens
	//</summary>
	for (auto i : Components) {
		if (i.node == nullptr)
			continue;
		Node* n = i.node;
		Input.push_back(n);
	}
	return;
}

void PostProsessor::Type_Definer(int i)
{
	//<summary>
	//stack type info
	//</summary>
	if (Parent->Defined[i]->Type != CLASS_NODE)
		return;
	if (Parent->Defined[i]->Templates.size() > 0)	//template types are constructed elsewhere.
		return;
	/*//update members sizes
	Parent->Defined[i]->Update_Size();

	//update the member stack offsets
	Parent->Defined[i]->Update_Members_Mem_Offset();

	//update format
	Parent->Defined[i]->Update_Format();

	//update all member formats as well
	for (auto& i : Parent->Defined[i]->Defined)
		i->Update_Format();
	*/

	//If this is a namespace skip the default constructor builder
	if (Parent->Defined[i]->is("static") != -1)
		return;

	for (auto& j : Parent->Defined[i]->Defined)
		if (j->is(FUNCTION_NODE) && (j->Parameters.size() == 0 || j->Parameters[0]->Inheritted[0] != Parent->Defined[i]->Name)) {
			PostProsessor p(Parent->Defined[i], { j });
			//p.Input = { j };
			//p.Member_Function_Defined_Inside(0);
			//j = p.Output[0];
		}

	//check for static members and move them into Header section to be labelazed
	for (auto& j : Parent->Defined[i]->Childs)
		if (j->Has({ OPERATOR_NODE, ASSIGN_OPERATOR_NODE, CONDITION_OPERATOR_NODE, BIT_OPERATOR_NODE })) {
			if (j->Left->is("static") != -1 && Node::Has(Parent->Defined[i]->Header, j->Left) == false)
				Parent->Defined[i]->Header.push_back(j);
		}
		else if (j->is("static") != -1 && Node::Has(Parent->Defined[i]->Header, j) == false)
				Parent->Defined[i]->Header.push_back(j);

	//DISABLE default constructor if user has already defined one.
	for (auto j : Parent->Defined) {
		if (!j->is(FUNCTION_NODE))
			continue;
		if (j->Name != Parent->Defined[i]->Name)
			continue;

		if (j->is("ptr") == -1)
			continue;	//constructor must return a ptr
		if (j->is(Parent->Defined[i]->Name) == -1)
			continue;	//constructor must return its self typed class type ptr.

		if (j->Parameters.size() != 1)
			continue;
		if (j->Parameters[0]->is(Parent->Defined[i]->Name) == -1)
			continue;
		if (j->Parameters[0]->is("ptr") == -1)
			continue;	//constructor must take itself as a ptr.
		return;	//the user has already defined the default constructor for us.
	}

	//make a default constructor.
	//insert the constructor into global scopes funciton list.
	Node* Function = new Node(FUNCTION_NODE, Parent->Defined[i]->Location);
	Function->Name = Parent->Defined[i]->Name;
	Function->Inheritted = { Parent->Defined[i]->Name, "ptr" };
	Function->Scope = Global_Scope;

	Node* This = new Node(PARAMETER_NODE, Parent->Defined[i]->Location);
	This->Inheritted = {Parent->Defined[i]->Name, "ptr"};
	This->Name = "this";
	This->Defined = Parent->Defined[i]->Defined;
	This->Scope = Function;
	This->Update_Size();

	Function->Parameters.push_back(This);
	Function->Defined.push_back(This);

	Function->Update_Size();

	Node* p = Parent->Defined[i];
	if (p->Has({ "cpp", "evie", "vivid" }) != -1)
		Function->Inheritted.push_back(p->Inheritted[p->Has({ "cpp", "evie", "vivid" })]);

	Function->Childs = Insert_Dot(Parent->Defined[i]->Childs, Function, This);

	//call all the inheritted default or overrided constructor calls.
	vector<Node*> tmp = Dottize_Inheritanse(Parent->Defined[i], This, Function);

	Function->Childs.insert(Function->Childs.begin(), tmp.begin(), tmp.end());

	//make the return of this pointter
	Node* ret = new Node(FLOW_NODE, Parent->Defined[i]->Location);
	ret->Name = "return";
	ret->Right = new Node(*This);
	ret->Scope = Function;
	Function->Childs.push_back(ret);

	PostProsessor P(Function, Function->Childs);

	Global_Scope->Defined.push_back(Function);
	Global_Scope->Childs.push_back(Function);

	return;
}

vector<Node*> PostProsessor::Insert_Dot(vector<Node*> Childs, Node* Function, Node* This)
{
	vector<Node*> Result;
	for (auto c : Childs) {
		Update_Operator_Inheritance(c);
		if (c->is("const") != -1)
			continue;
		if (c->is("static") != -1)
			continue;
		if (c->is(FUNCTION_NODE))
			continue;
		Node* c_copy = c->Copy_Node(c, Function);
		//insert this. infront of every member
		for (auto& linear_n : Linearise(c_copy)) {
			if (linear_n->is(NUMBER_NODE) || linear_n->is(FUNCTION_NODE) || (linear_n->is("const") != -1) || MANGLER::Is_Base_Type(linear_n))
				continue;
			if ((linear_n->is(OBJECT_DEFINTION_NODE) || linear_n->is(OBJECT_NODE)) && This->Find(linear_n, This) != nullptr) {
				//Node* define = c->Find(linear_n, Function);
				Node* Dot = new Node(OPERATOR_NODE, Function->Location);
				Dot->Name = ".";
				Dot->Scope = linear_n->Scope;

				Dot->Left = new Node(*This);

				Dot->Right = new Node(*linear_n);

				Dot->Context = linear_n->Context;

				*linear_n = *Dot;
			}
			else if (linear_n->is(CALL_NODE)) {
				linear_n->Parameters = Insert_Dot(linear_n->Parameters, Function, This);
			}
		}
		Result.push_back(c_copy);
	}
	return Result;
}

vector<Node*> PostProsessor::Dottize_Inheritanse(Node* Class, Node* This, Node* Funciton)
{
	vector<Node*> Result;
	for (auto i : Class->Inheritted) {
		if (Lexer::GetComponents(i)[0].is(Flags::KEYWORD_COMPONENT))
			continue;

		Node* Call = new Node(CALL_NODE, Class->Location);
		Call->Parameters.push_back(This->Copy_Node(This, Funciton));
		Call->Name = i;
		Call->Scope = Funciton;

		Result.push_back(Call);
	}
	return Result;
}

void PostProsessor::Cast(Node* n)
{
	if (!n->is(NODE_CASTER))
		return;

	n->Left->Cast_Type = n->Right->Name;
	n->Left->Context = n->Context;
	*n = *n->Left;
}

void PostProsessor::Increase_Calling_Number_For_Function_Address_Givers(Node* n)
{
	if (!n->is(OBJECT_NODE))
		return;

	Node* f;
	if (!n->Find(n->Name, n->Scope, FUNCTION_NODE)) {
		if (!n->Find(n->Name, n->Scope, IMPORT)) {
			if (!n->Find(n->Name, n->Scope, PROTOTYPE))
				return;
			else
				f = n->Find(n->Name, n->Scope, PROTOTYPE);
		}
		else
			f = n->Find(n->Name, n->Scope, IMPORT);
	}
	else
		f = n->Find(n->Name, n->Scope, FUNCTION_NODE);

	f->Calling_Count++;
}

void PostProsessor::Member_Function_Defined_Outside(int i)
{
	//<summary>
	//	The function is in global scope's childs list-
	//	but it can be found in the respective scope that the fetchers describe.
	//	The Find function in Node.cpp can handle complex AST search to find the respective function.
	//	
	//	If the function in question is not a static type then we need to apply this pointters and other cool stuf.
	//</summary>
	if (Parent->Defined[i]->Type != FUNCTION_NODE)
		return;
	if (Parent->Defined[i]->Fetcher == nullptr)
		return;
	if (Parent->Defined[i]->is("static") != -1)
		return;
	if (Parent->Defined[i]->Parameters.size() > 0 && Parent->Defined[i]->Parameters[0]->Name == "this")
		return;

	Node* func = Parent->Defined[i];

	Node* This = new Node(PARAMETER_NODE, "this", func->Location);
	This->Inheritted = { func->Fetcher->Name, "ptr" };
	This->Scope = func;
	This->Size = _SYSTEM_BIT_SIZE_;
	This->Defined = func->Find(func->Fetcher->Name, func, CLASS_NODE)->Defined;

	func->Defined.push_back(This);

	func->Parameters.insert(func->Parameters.begin(), This);

	func->Childs = Insert_Dot(func->Childs, func, This);

	Node* Scope = func->Find_Scope(func);

	func->Fetcher = Scope;

	*func->Fetcher->Find(func, Scope, FUNCTION_NODE) = *func;

	return;
}

void PostProsessor::Member_Function_Defined_Inside(int i)
{
	if (!Parent->Defined[i]->is(FUNCTION_NODE))
		return;
	if (Parent->Defined[i]->is("static") != -1)
		return;
	if (Parent->Name == "GLOBAL_SCOPE")
		return;
	if (Parent->Defined[i]->Fetcher != nullptr)
		return;

	Node* func = Parent->Defined[i];

	Node* This = new Node(PARAMETER_NODE, "this", nullptr);
	This->Inheritted = { Parent->Name, "ptr" };
	This->Scope = func;
	This->Size = _SYSTEM_BIT_SIZE_;

	func->Defined.push_back(This);

	func->Parameters.insert(func->Parameters.begin(), This);

	func->Childs = Insert_Dot(func->Childs, func, This);

	Node* Scope = Parent->Find(Parent->Name, Parent, CLASS_NODE);

	*Parent->Find(func, Scope, FUNCTION_NODE) = *func;

	return;
}

void PostProsessor::Open_Function_For_Prosessing(int i)
{
	//here we just go trugh the insides of the function
	//for optimization and other cool stuff :D
	if (!Parent->Defined[i]->is(FUNCTION_NODE))
		return;
	if (Parent->Defined[i]->Is_Template_Object)
		return;
	for (auto j : Parent->Defined[i]->Get_All_Fetchers())
		if (j->Is_Template_Object)
			return;
	/*for (auto j : Input[i]->Parameters)
		if (j->is("type") != -1)
			return;
	*/



	PostProsessor p(Parent->Defined[i]);
	p.Input = Parent->Defined[i]->Childs;

	//prepare the local variables
	p.Define_Sizes(Parent->Defined[i]);

	Parent->Defined[i]->Update_Format();

	Parent->Defined[i]->Update_Size();

	p.Factory();

	Parent->Defined[i]->Childs = p.Input;

	for (auto& v : Parent->Defined[i]->Defined)
		for (auto j : Parent->Defined[i]->Childs) {
			Analyze_Variable_Address_Pointing(v, j);
			if (v->Requires_Address)
				break;
		}

	//DEBUG
	//if (sys->Info.Debug)
		for (auto& v : Parent->Defined[i]->Defined) {
			if (v->is(PARAMETER_NODE) && !sys->Info.Debug)
				continue;
			else if (v->Size <= _SYSTEM_BIT_SIZE_ && !v->Requires_Address)
				continue;
			v->Memory_Offset = v->Scope->Local_Allocation_Space;
			v->Scope->Local_Allocation_Space += v->Get_Size();
			v->Requires_Address = true;
		}

	//Parent->Defined[i]->Update_Defined_Stack_Offsets();

	return;
}

void PostProsessor::Open_Condition_For_Prosessing(int i)
{
	if (!Input[i]->is(IF_NODE) && !Input[i]->is(ELSE_IF_NODE) && !Input[i]->is(ELSE_NODE))
		return;
	//this add the L number to it
	Input[i]->Name += to_string(LNumber++);

	//preprare the local variables
	Define_Sizes(Input[i]);

	if (!Input[i]->is(ELSE_NODE)) {
		PostProsessor p(Input[i], Input[i]->Parameters);
	}

	//here we now postprosess also the insides of the condition
	PostProsessor p(Input[i], Input[i]->Childs);

	return;
}

void PostProsessor::Open_Paranthesis(int i)
{
	if (!Input[i]->is(CONTENT_NODE))
		return;

	PostProsessor p(Input[i], Input[i]->Childs);
}

void PostProsessor::Find_Call_Owner(Node* n)
{
	if (!n->is(CALL_NODE))
		return;
	if (n->Function_Implementation != nullptr)
		return;
	//<summary>
	//this function tryes to find the function to call
	//</summary>
	//first try to find if this fucntion is a virtual function
	//Node* defition = Parent->Find(n->Name, Parent);
	//other wise we have normal functions
	//now lets check for template arguments-
	//as parameters on the function this callation calls

	Node* Scope = Global_Scope;
	if (n->Fetcher != nullptr) {
		if (n->Fetcher->is(CLASS_NODE))
			Scope = n->Fetcher->Find(n->Fetcher->Name, n, CLASS_NODE);
		else
			Scope = n->Fetcher->Find(n->Fetcher->Inheritted[0], n, CLASS_NODE);
	}

	//now that the scope is resolved we can finaly construct the template functions inners properly.
	if (n->Templates.size() > 0) {
		string New_Name = "." + n->Construct_Template_Type_Name();
		Parser P(Scope->Get_Parent_As(CLASS_NODE, Scope));

		if (Scope->Find(New_Name, Scope, { FUNCTION_NODE, PROTOTYPE, IMPORT, EXPORT }) != nullptr && n->Compare_Fetchers(Scope->Find(New_Name, Scope, { FUNCTION_NODE, PROTOTYPE, IMPORT, EXPORT }))) {
			n->Name = New_Name;
			n->Templates.clear();
		}
		else if (Scope->Find(n, Scope, { FUNCTION_NODE, PROTOTYPE, IMPORT, EXPORT })) {
			Node* Func = Scope->Copy_Node(Scope->Find(n, Scope, { FUNCTION_NODE, PROTOTYPE, IMPORT, EXPORT }), Scope->Find(n, Scope, { FUNCTION_NODE, PROTOTYPE, IMPORT, EXPORT })->Scope);
			vector<Node*> Args = Func->Templates;
			Func->Templates = n->Templates;

			Parser P(Scope->Get_Parent_As(CLASS_NODE, Scope));
			P.Input = P.Template_Function_Constructor(Func, Args, n->Templates);
			P.Factory();

			n->Name = New_Name;
			n->Templates.clear();
		}
		else if (Scope->Find(n, Scope, CLASS_NODE)) {
			//Constructors
			n->Name = New_Name;
			n->Templates.clear();
		}
	}

	Node* OgFunc = nullptr;
	//also the returning type of this callation is not made,
	//we can determine it by the operations other side objects type.
	//this prosess is made for operator in Determine_Return_Type().
	//but it wont work if the call is inside another call
	if (n->Context != nullptr && n->Context->is(CALL_NODE)) {
		int Parameter_Index = 0;
		for (auto p : n->Context->Parameters)
			if (p == n)//check the pointer address
				break;
			else
				Parameter_Index++;
		//the holder callation does not have template function.
		//this posible to make only this way:
		//if there are only one funciton named as the holder,
		//if not the this function return type must NOT be a Base type.
		if (MANGLER::Is_Based_On_Base_Type(n)) {
			//this happends when the n return a template type.
			//there can be only one template function.
			vector<int> callation;
			for (int c = 0; c < Scope->Defined.size(); c++) {
				if (Scope->Defined[c]->is(FUNCTION_NODE) && (Scope->Defined[c]->Name == n->Context->Name)) {
					if (Scope->Defined[c]->Parameters.size() == n->Context->Parameters.size())
						callation.push_back(c);
				}
			}
			if (callation.size() > 1){
				Report({
					Observation(ERROR, "Cannot decide, " + n->Context->Name + " has too many similar overloads.", *n->Context->Location),
					Observation(SOLUTION, "Solution: Please cast " + n->Name + " into desired type.", *n->Location)
					});
				throw::runtime_error("Error!");
			}
			n->Inheritted = Scope->Defined[callation[0]]->Parameters[Parameter_Index]->Inheritted;
		}

	}

	
	bool Skip_Name_Checking_For_Func_Ptr = false;
Try_Again:;
	//first ignore the template parameters for now
	for (int f = 0; f < Scope->Defined.size(); f++) {
		if (!Skip_Name_Checking_For_Func_Ptr)
			if (Scope->Defined[f]->Name != n->Name)
				continue;
		if (Scope->Defined[f]->is(CLASS_NODE))
			continue;	//this is for constructors
		//check for template return types.
		if (!Check_If_Template_Function_Is_Right_One(Scope->Defined[f], n))
			continue;
		if (Scope->Defined[f]->Parameters.size() != n->Parameters.size())
			continue;
		int g_i = -1;
		bool Has_Template_Parameters = false;
		for (auto g : Scope->Defined[f]->Parameters) {
			g_i++;

			if (g->Is_Template_Object) {
				Has_Template_Parameters = true;
				if (!Check_If_Template_Function_Is_Right_One(g, n->Parameters[g_i]))
					goto Wrong_Template_Function;
				else
					continue;
			}
			else if (n->Parameters[g_i]->is("type") != -1) {
				if (!Check_If_Template_Function_Is_Right_One(n->Parameters[g_i], g))
					goto Wrong_Template_Function;
				else
					continue;
			}
			else if (g->Get_Inheritted("_", true, false) == n->Parameters[g_i]->Get_Inheritted("_", true, false))
				continue;
			
			for (auto g_h : g->Get_Inheritted(true, false)) {
				//banana --> fruit
				if (Find_Castable_Inheritance(n->Parameters[g_i]->Get_Inheritted(true, false), g_h))
					continue;
				//fruit <-- banana
				for (auto n_h : n->Parameters[g_i]->Get_Inheritted(true, false)) {
					if (Find_Castable_Inheritance(g->Get_Inheritted(true, false), n_h))
						goto Right_Type;
				}
				goto Wrong_Template_Function;
			Right_Type:;
			}
		}
		if (Has_Template_Parameters && !Scope->Defined[f]->is(IMPORT)) {
			OgFunc = Scope->Defined[f];
			goto Non_Imported_Template_Function_Usage;
		}
		if (Skip_Name_Checking_For_Func_Ptr) {
			n->Function_Ptr = true;	//this caller is a function pointter.
			n->Inheritted = n->Find(n, n->Scope)->Inheritted;
			//remove one pointter
			vector<string> New_Inheritance;
			bool Removed_Ptr = false;
			for (auto inherit : n->Inheritted) {
				if (inherit == "ptr" && !Removed_Ptr) {
					Removed_Ptr = true;
					continue;
				}
				New_Inheritance.push_back(inherit);
			}
			n->Inheritted = New_Inheritance;
		}
		n->Function_Implementation = Scope->Defined[f];
		if (!Skip_Name_Checking_For_Func_Ptr) {
			n->Function_Implementation->Calling_Count++;

			if ((MANGLER::Is_Based_On_Base_Type(n->Function_Implementation) == false) || n->Inheritted.size() == 0)
				n->Inheritted = n->Function_Implementation->Inheritted;
		}
		return;
		Wrong_Template_Function:;
	}
	Non_Imported_Template_Function_Usage:;
	//if the code gets here it means the og-function has template paramters!
	//and its not external fucntion.
	/*for (auto f : Global_Scope->Defined) {
		if (!f->is(FUNCTION_NODE) && !f->is(PROTOTYPE) && !f->is(IMPORT))
			continue;
		if (n->is("ptr") == -1)
			if (f->Name != n->Name)
				continue;
		bool Direct_Type = false;
		if (f->is(IMPORT))
			Direct_Type = true;
		if (f->Parameters.size() != n->Parameters.size())
			continue;
		if (f->Get_Inheritted("", false, true) != n->Get_Inheritted("", false, true))
			continue;
		for (int p = 0; p < f->Parameters.size(); p++) {
			if (Direct_Type && f->Parameters[p]->Name == "type")
				continue;
			else if (!Direct_Type && f->Parameters[p]->is("type") != -1)
				continue;	//just ignore the template parameters for now.
			//here we will determine if this function is the og-fucntion or not.
			else if (Direct_Type && (f->Parameters[p]->Name != n->Parameters[p]->Get_Inheritted((string)"")))
				goto Next_Function;
			else if (!Direct_Type && f->Parameters[p]->Get_Inheritted("") != n->Parameters[p]->Get_Inheritted("")) {
				goto Next_Function;
			}
		}
		//here if we get this function is the og-function.
		OgFunc = f;
		break;
	Next_Function:;
	}*/
	if (OgFunc == nullptr && n->Scope->Find(n, n->Scope)->is("ptr") != -1)
		if (Skip_Name_Checking_For_Func_Ptr == false) {
			Skip_Name_Checking_For_Func_Ptr = true;
			goto Try_Again;
	}

	if (OgFunc == nullptr && Scope != Global_Scope) {
		Scope = Global_Scope;
		goto Try_Again;
	}

	if (OgFunc == nullptr) {
		string s = "";
		for (int j = 0; j < n->Parameters.size(); j++) {
			s += "  " + n->Parameters[j]->Name + "\n";
		}
		Report(Observation(ERROR, "Can't find suitable funciton to call " + n->Name + " with parameters:" + s, *n->Location));
		throw::runtime_error("Error!");
	}

	if (OgFunc->is(PROTOTYPE))
		for (auto j : OgFunc->Parameters)
			if (j->Name == "type") {		//REMEBER THE DIRECT TYPING!!	
				Report(Observation(ERROR, "Can't copy a foreingh function " + OgFunc->Name + ".", *OgFunc->Location));
				throw::runtime_error("Error!");
			}

	Node* func = nullptr;
	if (!OgFunc->is(PROTOTYPE)) {
		//now we want to copy that function again but this time we will put the called parameter types
		func = OgFunc->Copy_Node(OgFunc, Parent);

		//now we want to through the templates and put on them the right parameter infos
		for (int p = 0; p < func->Parameters.size(); p++) {
			vector<string> tmp = func->Parameters[p]->Inheritted;
			//update the parent
			func->Parameters[p]->Scope = func;

			func->Parameters[p]->Inheritted = n->Parameters[p]->Inheritted;
			//now iterate the leftover types like ptr
			for (string s : tmp) {
				if (s == "type")
					continue;
				if (func->Parameters[p]->is(s) == -1)
					func->Parameters[p]->Inheritted.push_back(s);
			}
			//alsoset the defined types into right inheritance.
			func->Find(func->Parameters[p]->Name, func)->Inheritted = func->Parameters[p]->Inheritted;
		}
	}
	else {
		func = OgFunc;
	}
	n->Function_Implementation = func;
	func->Mangled_Name = func->Get_Mangled_Name();
	
	PostProsessor p(func);
	p.Input = func->Childs;
	p.Factory();

	Update_Used_Object_Info(func);

	//now we want to inject it to global scope to be reached next time.
	Scope->Childs.push_back(func);
	Scope->Defined.push_back(func);

	return;
}

bool PostProsessor::Find_Castable_Inheritance(vector<string> types, string target)
{
	for (auto type : types) {
		if (Lexer::GetComponents(type)[0].is(Flags::KEYWORD_COMPONENT))
			continue;
		if (type == target)
			return true;
		if (Find_Castable_Inheritance(Parent->Find(type, Parent, CLASS_NODE)->Get_Inheritted(true), target))
			return true;
	}
	return false;
}

void PostProsessor::Open_Call_Parameters_For_Prosessing(int i)
{
	if (!Input[i]->is(CALL_NODE))
		return;

	//give the post prosessor a way to reach the parameters that might have member fetching/ math
	PostProsessor p(Parent, Input[i]->Parameters);

	//use optimization into the parameters.
	//Algebra a(Input[i], &Input[i]->Parameters);	//Algebra has already optimized this!

	for (auto j : Input[i]->Parameters)
		if (j->is(OPERATOR_NODE)) {
			Update_Operator_Inheritance(j);
			j->Update_Size();
		}
}

void PostProsessor::Algebra_Laucher(int i)
{
	if (!Input[i]->is(FUNCTION_NODE))
		return;
	while (true) {
		Algebra a(Input[i], &Input[i]->Childs);
		if (!Optimized)
			break;
		Optimized = false;
	}
}

void PostProsessor::Combine_Member_Fetching(Node* n)
{
	if (n->Name != ".")
		return;
	if (n->Right->is(CALL_NODE)) {
		n->Right->Parameters.insert(n->Right->Parameters.begin(), n->Left);
		n->Right->Context = n->Context;
		n->Right->Fetcher = n->Left;
		*n = *n->Right;
	}
	else {
		//Remember: Dot is constructed as any normal operator.
		//((((a.b).c[..]).d()).e) = 123
		//We have to go first to the most left sided operator.
		Cast(n->Left);
		Cast(n->Right);
		Combine_Member_Fetching(n->Left);
		//set the left side
		Node* Left = Parent->Find(Get_From_AST(n->Left), Parent);
		//we must also update the current left side to inherit the members from the inherit list

		//get the left side of the dot operator, this is getted from most left because it can be also an AST.
		Node* Right = n->Get_Most_Left(n->Right);

		if (Right->Name == "size") {
			Node* num = Right->Find("size", Left);
			if (num == nullptr || (num->is("const") != -1)) {
				//this means it is definetly a size get request
				Right->Name = to_string(Left->Get_Size());
				Right->Type = NUMBER_NODE;	
				if (atoll(Right->Name.c_str()) > INT32_MAX)
					Right->Size = 8;
				else
					Right->Size = 4;
			}
			else
				//load the needed information from the parent
				*Right = *n->Find(Right, Left);
		}
		else
			//load the needed information from the parent
			*Right = *n->Find(Right, Left);

		//set the parent as a fechable
		Right->Fetcher = Left;

		//now remove the current dot operator and replace it with the new fetched member
		Right->Context = n->Context;
		Right->Scope = n->Scope;

		//a.Array[1]
		//put the a.Array as the left side of the array operator
		if (n->Right->is(ARRAY_NODE)) {
			*n->Right->Left = *Right;
			*n = *n->Right;
		}
		else
			*n = *Right;
	}
}

Node* PostProsessor::Get_From_AST(Node* n)
{
	//((((a.b).c[..]).d()).e) = 123
	if (n->is(CONTENT_NODE)) {
		//childs can have only one start node for the AST because that is how math just works :/
		//(a.b + a.c) 
		//				n is parent because of the local scope
		PostProsessor p(n, n->Childs);
		return Get_From_AST(n->Childs[0]);
	}
	else if (n->is(OPERATOR_NODE)) {
		PostProsessor p(Parent, { n });
		return Get_From_AST(n);	//this call the same funciton again because the structure of the AST might have been changed.
	}
	else if (n->is(ARRAY_NODE)) {
		PostProsessor p(Parent, { n });
		return n->Get_Most_Left();
	}
	else if (n->is(CALL_NODE)) {
		PostProsessor p(Parent, n->Parameters);	//prosess the parameters.
		//update the return type of the funciton call
		//if (n->Holder->Name == "return")
		//	Analyze_Return_Value(n->Holder);
		Find_Call_Owner(n);
		return n;
	}
	else  {
		return n;
	}
}

void PostProsessor::Define_Sizes(Node* p)
{
	//here we set the defined size of the variable
	for (Node* d : p->Defined) {
		d->Get_Inheritted_Class_Members();
		d->Update_Size();
		d->Update_Members_Mem_Offset();
		d->Update_Format();
	}
}

void PostProsessor::Combine_Condition(int i)
{
	if (!Input[i]->is(IF_NODE))
		return;

	Node* current_condition = Input[i];
	int j;
	//loop through the next nodes if theyre else ifs
	for (j = i + 1; j < Input.size(); j++) {
		if (Input[j]->is(ELSE_IF_NODE) || Input[j]->is(ELSE_NODE)) {
			//give the else if the parent as the if
			Input[j]->Predecessor = current_condition;
			//give the if the child as successor else if
			current_condition->Succsessor = Input[j];
			//give the successor as the current pointter
			current_condition = Input[j];
		}
		else {
			break;
		}
	}

	//now remove the elses
	Input.erase(Input.begin() + i + 1, Input.begin() + j);
}

void PostProsessor::Determine_Return_Type(int i)
{
	if (!Input[i]->is(OPERATOR_NODE) && !Input[i]->is(CONDITION_OPERATOR_NODE) && !Input[i]->is(ASSIGN_OPERATOR_NODE) && !Input[i]->is(BIT_OPERATOR_NODE))
		return;

	if (Input[i]->Right->is(CALL_NODE) && MANGLER::Is_Based_On_Base_Type(Input[i]->Right)) {
		PostProsessor l(Parent, vector<Node*>{Input[i]->Left });
		Input[i]->Right->Inheritted = Input[i]->Left->Inheritted;
		PostProsessor r(Parent, vector<Node*>{ Input[i]->Right});
	}
	else if (Input[i]->Left->is(CALL_NODE) && MANGLER::Is_Based_On_Base_Type(Input[i]->Left)) {
		PostProsessor r(Parent, vector<Node*>{ Input[i]->Right});
		Input[i]->Left->Inheritted = Input[i]->Right->Inheritted;
		PostProsessor l(Parent, vector<Node*>{Input[i]->Left });
	}
	else {
		PostProsessor r(Parent, vector<Node*>{ Input[i]->Right, Input[i]->Left });
	}


	//try to find a suitable operator overload if there is one
	for (auto& overload : Input[i]->Left->Operator_Overloads) {
		//the syntax still needs to be done!

		//the operator overloads return type is the same as the operator type for this.
		Input[i]->Inheritted = overload->Inheritted;
		return;
	}	

	int Left_Size = 0;
	int Right_Size = 0;

	for (auto j : Input[i]->Left->Get_Inheritted(false, false)) {
		if (Lexer::GetComponents(j)[0].is(Flags::KEYWORD_COMPONENT))
			continue;
		Left_Size += Parent->Find(j, Parent)->Get_Size();
	}	
	if (Input[i]->Left->Cast_Type != "" && Input[i]->Left->Cast_Type != "address")
		Left_Size = Parent->Find(Input[i]->Left->Cast_Type, Parent)->Get_Size();
	if (Input[i]->Left->is("ptr") != -1)
		Left_Size = _SYSTEM_BIT_SIZE_;

	for (auto j : Input[i]->Right->Get_Inheritted(false, false)) {
		if (Lexer::GetComponents(j)[0].is(Flags::KEYWORD_COMPONENT))
			continue;
		Right_Size += Parent->Find(j, Parent)->Get_Size();
	}
	if (Input[i]->Right->Cast_Type != "" && Input[i]->Right->Cast_Type != "address")
		Right_Size = Parent->Find(Input[i]->Right->Cast_Type, Parent)->Get_Size();
	if (Input[i]->Right->is("ptr") != -1)
		Right_Size = _SYSTEM_BIT_SIZE_;

	if (Left_Size >= Right_Size)
		Input[i]->Inheritted = Input[i]->Left->Get_Inheritted(false, false);
	else
		Input[i]->Inheritted = Input[i]->Right->Get_Inheritted(false, false);
}

void PostProsessor::Determine_Array_Type(int i)
{
	if (!Input[i]->is(ARRAY_NODE))
		return;

	PostProsessor r(Parent, vector<Node*>{ Input[i]->Right, Input[i]->Left });

	//Who is gay and does not pay taxes also farts in public 
	for (auto& overload : Input[i]->Left->Operator_Overloads) {
		//the syntax still needs to be done!

		//the operator overloads return type is the same as the operator type for this.
		Input[i]->Inheritted = overload->Inheritted;
		return;
	}

	//give the type inheritance to this array operator so that the upper function can check the do-ability
	Input[i]->Inheritted = Input[i]->Left->Inheritted;
}

void PostProsessor::Open_PreFix_Operator(int i)
{
	if (!Input[i]->is(PREFIX_NODE))
		return;

	PostProsessor p(Parent, { Input[i]->Right });
}

void PostProsessor::Open_PostFix_Operator(int i)
{
	if (!Input[i]->is(POSTFIX_NODE))
		return;


	PostProsessor p(Parent, { Input[i]->Left });
}

void PostProsessor::Type_Size_Definer(int i)
{
	if (Parent->Defined[i]->Type != CLASS_NODE)
		return;
	if (Parent->Defined[i]->Templates.size() > 0)	//template types are constructed elsewhere.
		return;
	//update members sizes
	Parent->Defined[i]->Update_Size();

	//update the member stack offsets
	Parent->Defined[i]->Update_Members_Mem_Offset();

	//update format
	Parent->Defined[i]->Update_Format();

	//update all member formats as well
	for (auto& i : Parent->Defined[i]->Defined)
		i->Update_Format();
}

void PostProsessor::Handle_Imports(int i)
{
	if (!Parent->Defined[i]->is(IMPORT))
		return;
	//import func new (4, ABC)
	//all numbers need to be redefined by type size.
	//and all other text is already classes.
	//pointters are inside the parameter as inheritance.
	bool Parse_Returning_Numerical_Types = false;
	vector<Node*> Numerical_Types = Parent->Defined[i]->Parameters;
Again:;
	for (int j = 0; j < Numerical_Types.size(); j++) {
		vector<string> Inheritted = Numerical_Types[j]->Inheritted;
		if (Numerical_Types[j]->is(NUMBER_NODE)) {
			*Numerical_Types[j] = *Global_Scope->Find(atoi(Numerical_Types[j]->Name.c_str()), Global_Scope, CLASS_NODE, Numerical_Types[j]->Format);
			Numerical_Types[j]->Inheritted.insert(Numerical_Types[j]->Inheritted.end(), Inheritted.begin(), Inheritted.end());
		}
		else if (!MANGLER::Is_Base_Type(Numerical_Types[j]))
			continue;
		else if (Numerical_Types[j]->is(OBJECT_DEFINTION_NODE)) {
			if ((Numerical_Types[j]->Name == "type") || Numerical_Types[j]->is("type") != -1)
				continue;
			*Numerical_Types[j] = *Global_Scope->Find(Numerical_Types[j]->Name, Global_Scope, CLASS_NODE);
			Numerical_Types[j]->Inheritted.insert(Numerical_Types[j]->Inheritted.end(), Inheritted.begin(), Inheritted.end());
		}
	}
	if (Parse_Returning_Numerical_Types == false && Parent->Defined[i]->Numerical_Return_Types.size() > 0) {
		Parse_Returning_Numerical_Types = true;
		Numerical_Types = Parent->Defined[i]->Numerical_Return_Types;
		goto Again;
	}
	else if (Parse_Returning_Numerical_Types) {
		for (auto j : Numerical_Types) {
			Parent->Defined[i]->Inheritted.push_back(j->Name);
		}
		Parent->Defined[i]->Numerical_Return_Types.clear();
	}
	//TODO: Re-order all return types and parameter types into a logical order.
	//now all types are good to go.
	//although function calling might get tricky with just types as the parameters.
}

void PostProsessor::Open_Loop_For_Prosessing(int i)
{
	if (!Input[i]->is(WHILE_NODE))
		return;
	//this add the L number to it
	Input[i]->Name += to_string(LNumber++);

	//while (a + 1 < a * 2){..}
	//while (int i = 0, a + i < a * i*2, i++){..}
	//we dont necessarily need to seperate the condition operator.
	Algebra Alg(Input[i], &Input[i]->Parameters);

	//now just prosess the child tokens of while node as well.
	PostProsessor post(Input[i]);
	post.Input = Input[i]->Childs;

	//NOTE: this defined sizes might be reduntant!
	post.Define_Sizes(Input[i]);

	//haha brain go brr
	post.Factory();
}

void PostProsessor::Update_Used_Object_Info(Node* n)
{
	if (!n->is(FUNCTION_NODE))
		return;
	for (auto i : n->Get_all(OBJECT_NODE)) {
		i->Inheritted = n->Find(i->Name, i->Scope)->Inheritted;
		i->Update_Size();
	}
	//do the same for parameters
	for (auto i : n->Get_all(PARAMETER_NODE)) {
		i->Inheritted = n->Find(i->Name, i->Scope)->Inheritted;
		i->Update_Size();
	}
}

void PostProsessor::Operator_Overload(int i)
{
	//todo: make the override syntax
}

void PostProsessor::Template_Parameter(int i)
{
}

void PostProsessor::Templates(int i)
{
}

void PostProsessor::Analyze_Variable_Address_Pointing(Node* v, Node* n)
{
	if (!v->is(OBJECT_DEFINTION_NODE) && !v->is(OBJECT_NODE) && !v->is(PARAMETER_NODE))
		return;

	//if a variable is pointed to via a pointter or a function parameter address loader, use stack.
	//Other than that use registers.
	if (n->is(ASSIGN_OPERATOR_NODE) || n->is(OPERATOR_NODE) || n->is(CONDITION_OPERATOR_NODE) || n->is(BIT_OPERATOR_NODE)) {
		Analyze_Variable_Address_Pointing(v, n->Left);
		if (v->Requires_Address)
			return;
		Analyze_Variable_Address_Pointing(v, n->Right);
		if (v->Requires_Address)
			return;

		int Right_ptr = Get_Amount("ptr", n->Right);
		int Left_ptr = Get_Amount("ptr", n->Left);
		//TODO!! need better contex idea for what is the result be as ptr amount?!!
		if (Right_ptr > Left_ptr && n->Left->Name == v->Name) {
			v->Requires_Address = true;
		}
		if (Left_ptr > Right_ptr && n->Right->Name == v->Name) {
			v->Requires_Address = true;
		}
	}
	else if (n->is(CONTENT_NODE))
		for (auto i : n->Childs) {
			Analyze_Variable_Address_Pointing(v, i);
			if (v->Requires_Address)
				return;
		}
	else if (n->is(CALL_NODE)) {
		vector<int> v_index;
		for (int i = 0; i < n->Parameters.size(); i++)
			if (n->Parameters[i]->Name == v->Name)
				v_index.push_back(i);
		for (auto i : v_index) {
			int Template_ptr = Get_Amount("ptr", n->Function_Implementation->Parameters[i]);
			int V_ptr = Get_Amount("ptr", v);
			if (Template_ptr > V_ptr)
				v->Requires_Address = true;
		}
	}
	else if (n->Name == "return" && n->Right != nullptr) {
		Analyze_Variable_Address_Pointing(v, n->Right);
		if (v->Requires_Address)
			return;
		Node* func = n->Get_Parent_As(FUNCTION_NODE, n);
		int Func_ptr = Get_Amount("ptr", func);
		int V_ptr = Get_Amount("ptr", v);
		if (Func_ptr > V_ptr)
			v->Requires_Address = true;
	}
	
	
	if (v->is(PARAMETER_NODE) && sys->Info.Debug)
		v->Requires_Address = true;

	/*if (v->Requires_Address) {
		v->Memory_Offset = v->Scope->Local_Allocation_Space;
		v->Scope->Local_Allocation_Space += v->Get_Size();
	}*/
}

int PostProsessor::Get_Amount(string t, Node* n)
{
	int result = 0;
	for (string s : n->Inheritted)
		if (s == t)
			result++;

	return result;
}

void PostProsessor::Analyze_Global_Variable_Changes(int i)
{
	if (!Input[i]->is(ASSIGN_OPERATOR_NODE))
		return;

	//check if the parent is global scope.
	if (Input[i]->Left->Scope->Name != "GLOBAL_SCOPE")
		return;

	Node* og = Parent->Find(Input[i]->Left->Name);

	if (Parent->Name == "GLOBAL_SCOPE") {
		//We are in global scope area.
		if (!Input[i]->Right->Get_Most_Left()->is(NUMBER_NODE) && !Input[i]->Right->Get_Most_Left()->is(STRING_NODE)) {
			Node* Right = Parent->Find(Input[i]->Right->Get_Most_Left()->Name);
			if (Right->is("const") == -1)
				if (og->is("const") != -1) {
					og->Inheritted.erase(og->Inheritted.begin() + og->is("const"));
				}
		}
	}
	else {
		//we are in a fucntion of some sort.
		//if this is the case the global variable cannot be a constant anymore.
		if (og->is("const") != -1) {
			og->Inheritted.erase(og->Inheritted.begin() + og->is("const"));
		}
	}
}

void PostProsessor::Change_Local_Strings_To_Global_Pointters(int i)
{
	if (!Input[i]->is(STRING_NODE))
		return;
	if (Parent->Name == "GLOBAL_SCOPE")
		return;
	//a = "123" to a = S0
	int Current_S_Count = 0;
	for (auto c : Global_Scope->Defined) {
		if (!c->is(LABEL_NODE))
			continue;
		Current_S_Count++;
		if (c->String == Input[i]->Name) {
			*Input[i] = *c;
			if (Input[i]->is("ptr") == -1)
				Input[i]->Inheritted.push_back("ptr");
			return;
		}
	}
	//if there is no string Sx make a new one.
	Node* s = new Node(LABEL_NODE, Input[i]->Location);
	s->String = Input[i]->Name;
	s->Name = "S" + to_string(Current_S_Count);
	s->Inheritted = { Global_Scope->Find(1, Global_Scope, CLASS_NODE, "integer")->Name };
	if (s->is("ptr") == -1)
		s->Inheritted.push_back("ptr");
	s->Scope = Global_Scope;

	Node* init = new Node(ASSIGN_OPERATOR_NODE, Input[i]->Location);
	init->Name = "=";
	init->Scope = Global_Scope;

	Node* value = new Node(STRING_NODE, Input[i]->Location);
	value->Name = s->String;
	value->Scope = Global_Scope;
	value->Size = 1;	//byte

	init->Left = s;
	init->Right = value;

	Global_Scope->Header.push_back(init);
	Global_Scope->Defined.push_back(s);

	Change_Local_Strings_To_Global_Pointters(i);
}

void PostProsessor::Move_Global_Varibles_To_Header(int i)
{
	if (!Input[i]->is(ASSIGN_OPERATOR_NODE))
		return;
	if (Parent->Name != "GLOBAL_SCOPE" && Parent->is("static") == -1)
		return;

	Node* Globl_Var = Parent->Find(Input[i]->Left->Name);
	Globl_Var->Type = OBJECT_NODE;

	Globl_Var->Update_Size();

	Parent->Header.push_back(Input[i]);

	Input.erase(Input.begin() + i);

	Move_Global_Varibles_To_Header(i);
}

bool PostProsessor::Check_If_Template_Function_Is_Right_One(Node* t, Node* c)
{
	//t = template
	//c = call
	//how many times we can skip a type
	int Type_Amount = Get_Amount("type", t);

	if (c->is("type") != -1) {
		//this means this funciton call is in template usage or this is a void calling convension.
		return true;
	}

	for (auto i : c->Inheritted) {
		if (Lexer::GetComponents(i)[0].is(Flags::KEYWORD_COMPONENT)) {
			if (t->is(i) == -1) {
				return false;	//teplate function must contain same keywords.
			}
		}
		else if (t->is(i) == -1) {
			if (Type_Amount > 0) {
				Type_Amount--;
				continue;
			}
			else
				return false;
		}
	}
	return true;
}

vector<Node*> PostProsessor::Linearise(Node* ast)
{
	vector<Node*> Result;
	if (ast->is(OPERATOR_NODE) || ast->is(CONDITION_OPERATOR_NODE) || ast->is(BIT_OPERATOR_NODE) || ast->is(ASSIGN_OPERATOR_NODE) || ast->is(ARRAY_NODE)) {
		vector<Node*> left = Linearise(ast->Left);
		Result.insert(Result.end(), left.begin(), left.end());

		vector<Node*> right = Linearise(ast->Right);
		Result.insert(Result.end(), right.begin(), right.end());
	}
	else if (ast->is(PREFIX_NODE)) {
		vector<Node*> right = Linearise(ast->Right);
		Result.insert(Result.end(), right.begin(), right.end());
	}
	else if (ast->is(POSTFIX_NODE) || ast->is(NODE_CASTER)) {
		vector<Node*> left = Linearise(ast->Left);
		Result.insert(Result.end(), left.begin(), left.end());
	}
	else if (ast->is(CONTENT_NODE)) {
		vector<Node*> childs;
		for (auto c : ast->Childs) {
			vector<Node*> tmp = Linearise(c);
			childs.insert(childs.end(), tmp.begin(), tmp.end());
		}
		Result.insert(Result.end(), childs.begin(), childs.end());
	}
	else if (ast->Has({IF_NODE, ELSE_IF_NODE, ELSE_NODE, WHILE_NODE})) {
		vector<Node*> childs;
		for (auto c : ast->Parameters) {
			vector<Node*> tmp = Linearise(c);
			childs.insert(childs.end(), tmp.begin(), tmp.end());
		}
		for (auto c : ast->Childs) {
			vector<Node*> tmp = Linearise(c);
			childs.insert(childs.end(), tmp.begin(), tmp.end());
		}
		Result.insert(Result.end(), childs.begin(), childs.end());
	}
	else if (ast->is(CALL_NODE)) {
		vector<Node*> childs;
		for (auto c : ast->Parameters) {
			vector<Node*> tmp = Linearise(c);
			childs.insert(childs.end(), tmp.begin(), tmp.end());
		}
		Result.insert(Result.end(), childs.begin(), childs.end());
	}
	else if (ast->Name == "return" && ast->Right != nullptr) {
		for (auto c : Linearise(ast->Right))
			Result.push_back(c);
	}
	else
		Result.push_back(ast);

	return Result;

}

void PostProsessor::Open_Safe(vector<Node*> n)
{
	Safe s(n);
}

void PostProsessor::Update_Operator_Inheritance(Node* n)
{
	if (n->is(CONTENT_NODE))
		Update_Operator_Inheritance(n->Childs[0]);
	if (!n->is(ASSIGN_OPERATOR_NODE) && !n->is(CONDITION_OPERATOR_NODE) && !n->is(OPERATOR_NODE) && !n->is(BIT_OPERATOR_NODE) && !n->is(ARRAY_NODE))
		return;

	Update_Operator_Inheritance(n->Left);
	Update_Operator_Inheritance(n->Right);

	//check for operator overrides.
	n->Inheritted.clear();

	if (n->is(ARRAY_NODE)) {
		int Pointter_UnWrapping_Count = 1;	//default
		if (n->Right->Childs.size() > 1)
			Pointter_UnWrapping_Count = (int)n->Right->Childs.size();

		for (auto i : n->Find(n->Left, n->Scope)->Inheritted) {
			if (i == "ptr") {
				if (Pointter_UnWrapping_Count < 1) {
					n->Inheritted.push_back(i);
					continue;
				}
				else
					Pointter_UnWrapping_Count--;
			}
			else
				n->Inheritted.push_back(i);
		}
	}
	else {
		if (n->Left->is(OPERATOR_NODE) || n->Left->is(ASSIGN_OPERATOR_NODE) || n->Left->is(CONDITION_OPERATOR_NODE) || n->Left->is(BIT_OPERATOR_NODE) || n->Left->is(ARRAY_NODE))
			n->Inheritted = n->Left->Inheritted;
		else if (!n->Left->is(NUMBER_NODE) && !n->Left->is(CONTENT_NODE))
			n->Inheritted = n->Left->Scope->Find(n->Left, n->Left->Scope)->Inheritted;
		else if (n->Left->is(NUMBER_NODE))
			n->Inheritted = n->Left->Get_Inheritted(false, false);
		else {
			if (n->Right->is(OPERATOR_NODE) || n->Right->is(ASSIGN_OPERATOR_NODE) || n->Right->is(CONDITION_OPERATOR_NODE) || n->Right->is(BIT_OPERATOR_NODE) || n->Right->is(ARRAY_NODE))
				n->Inheritted = n->Right->Inheritted;
			else
				//both cannot be numbers, because otherwise algebra would have optimized it away.
				n->Inheritted = n->Right->Scope->Find(n->Right, n->Right->Scope)->Inheritted;
		}
	}
}

void PostProsessor::Analyze_Return_Value(Node* n)
{
	if (n->Name != "return")
		return;
	if (n->Right == nullptr)
		return;

	PostProsessor p(n, { n->Right });

	Update_Operator_Inheritance(n->Right);
}