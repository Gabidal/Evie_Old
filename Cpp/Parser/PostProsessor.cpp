#include "../../H/Parser/PostProsessor.h"
#include "../../H/Docker/Mangler.h"
#include "../../H/Parser/Parser.h"
#include "../../H/Lexer/Lexer.h"
#include "../../H/UI/Safe.h"
#include "../../H/UI/Usr.h"

extern Node* Global_Scope;
extern bool Optimized;
extern Usr* sys;

void PostProsessor::Factory() {
	Transform_Component_Into_Node(); 
	for (int i = 0; i < Scope->Defined.size(); i++) {
		//the prototypes needs the types to have sizes to determine the number parameters assosiative type.
		Type_Size_Definer(i);
	}
	for (int i = 0; i < Scope->Defined.size(); i++) {
		//the prototypes needs the types to have sizes to determine the number parameters assosiative type.
		Handle_Imports(i);
	}
	for (int i = 0; i < Scope->Defined.size(); i++) {
		Type_Definer(i);
	}
	for (auto& i : Scope->Defined) {
		//the prototypes needs the types to have sizes to determine the number parameters assosiative type.
		Member_Function_Defined_Outside(i);
		Member_Function_Defined_Inside(i);
		Open_Function_For_Prosessing(i);
	}
	//Define_Sizes(Parent);
	for (int i = 0; i < Input.size(); i++) {
		//Handle_Namespace_Inlining(i);
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
	//Open_Safe(Input);
	for (int i = 0; i < Input.size(); i++)
		Combine_Condition(i);
	for (int i = 0; i < Input.size(); i++)
		Move_Global_Varibles_To_Header(i);
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
	if (Scope->Defined[i]->Type != CLASS_NODE)
		return;
	if (Scope->Defined[i]->Templates.size() > 0)	//template types are constructed elsewhere.
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
	if (Scope->Defined[i]->is("static") != -1) {

		/*for (auto& j : Scope->Defined[i]->Defined) {
			if (j->is("static") != -1)
				continue;

			j->Inheritted.insert(j->Inheritted.begin(), "static");
		}*/

		return;
	}

	/*for (auto& j : Scope->Defined[i]->Defined)
		if (j->is(FUNCTION_NODE) && (j->Parameters.size() == 0 || j->Parameters[0]->Inheritted[0] != Scope->Defined[i]->Name)) {
			PostProsessor p(Scope->Defined[i], { j });
			//p.Input = { j };
			//p.Member_Function_Defined_Inside(0);
			//j = p.Output[0];
		}*/

	//check for static members and move them into Header section to be labelazed
	for (auto& j : Scope->Defined[i]->Childs)
		if (j->Has({ OPERATOR_NODE, ASSIGN_OPERATOR_NODE, CONDITION_OPERATOR_NODE, BIT_OPERATOR_NODE })) {
			if (j->Left->is("static") != -1 && Node::Has(Scope->Defined[i]->Header, j->Left) == false)
				Scope->Defined[i]->Header.push_back(j);
		}
		else if (j->is("static") != -1 && Node::Has(Scope->Defined[i]->Header, j) == false)
				Scope->Defined[i]->Header.push_back(j);

	//infiltrate the class type and inject this behemoth
	Node* Type = Scope->Defined[i];
	if ((MANGLER::Is_Base_Type(Type) == false) && (!MANGLER::Is_Based_On_Base_Type(Type) || Type->Defined.size() > 0) && sys->Info.Reference_Count_Size > 0) {
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

		Type->Defined.insert(Type->Defined.begin(), Reference_Count);
	}

	Destructor_Generator(Scope->Defined[i]);

	//DISABLE default constructor if user has already defined one.
	for (auto j : Scope->Defined) {
		if (!j->is(FUNCTION_NODE))
			continue;
		if (j->Name != Scope->Defined[i]->Name)
			continue;

		if (j->is("ptr") == -1)
			continue;	//constructor must return a ptr
		if (j->is(Scope->Defined[i]->Name) == -1)
			continue;	//constructor must return its self typed class type ptr.

		if (j->Parameters.size() != 1)
			continue;
		if (j->Parameters[0]->is(Scope->Defined[i]->Name) == -1)
			continue;
		if (j->Parameters[0]->is("ptr") == -1)
			continue;	//constructor must take itself as a ptr.
		return;	//the user has already defined the default constructor for us.
	}

	//make a default constructor.
	//insert the constructor into global scopes funciton list.
	Node* Function = new Node(FUNCTION_NODE, Scope->Defined[i]->Location);
	Function->Name = Scope->Defined[i]->Name;
	Function->Inheritted = { Scope->Defined[i]->Name, "ptr" };
	Function->Scope = Global_Scope;

	Node* This = new Node(PARAMETER_NODE, Scope->Defined[i]->Location);
	This->Inheritted = {Scope->Defined[i]->Name, "ptr"};
	This->Name = "this";
	This->Defined = Scope->Defined[i]->Defined;
	This->Scope = Function;
	This->Update_Size();

	Function->Parameters.push_back(This);
	Function->Defined.push_back(This);

	Function->Update_Size();

	Node* p = Scope->Defined[i];
	if (p->Has({ "cpp", "evie", "vivid" }) != -1)
		Function->Inheritted.push_back(p->Inheritted[p->Has({ "cpp", "evie", "vivid" })]);

	Function->Childs = Insert_Dot(Scope->Defined[i]->Childs, Function, This);

	//call all the inheritted default or overrided constructor calls.
	vector<Node*> tmp = Dottize_Inheritanse(Scope->Defined[i], This, Function);

	Function->Childs.insert(Function->Childs.begin(), tmp.begin(), tmp.end());

	//make the return of this pointter
	Node* ret = new Node(FLOW_NODE, Scope->Defined[i]->Location);
	ret->Name = "return";
	ret->Right = new Node(*This);
	ret->Scope = Function;
	Function->Childs.push_back(ret);

	PostProsessor P(Function, Function->Childs);

	Function->Childs = P.Input;

	Scope->Append(Function->Childs, P.Output);

	Global_Scope->Defined.push_back(Function);
	Global_Scope->Childs.push_back(Function);


	for (auto& j : Scope->Defined[i]->Defined)
		if (j->is(FUNCTION_NODE) /* && (j->Parameters.size() == 0 || j->Parameters[0]->Inheritted[0] == Scope->Defined[i]->Name) */ ) {
			PostProsessor p(Scope->Defined[i]);
			p.Member_Function_Defined_Inside(j);
			p.Member_Function_Defined_Outside(j);
			p.Open_Function_For_Prosessing(j);
		}

	return;
}

void PostProsessor::Destructor_Generator(Node* Type)
{
	if (sys->Info.Reference_Count_Size < 1)
		return;

	if (MANGLER::Is_Base_Type(Type) || (MANGLER::Is_Based_On_Base_Type(Type) && Type->Defined.size() == 0))
		return;
	//[type].Destructor(){
	//	if ([member] != 0->address && --[member].Reference_Count < 1){
	//		[member].Destructor()
	//		Deallocate<[member type]>([member])
	// 	}
	//}

	string Ifs = "";
	//if (Type->is("ptr") != -1) {
		Ifs +=
			"if (this != 0->address && --Reference_Count < 1){\n";
	//}

	for (auto Member : Type->Defined) {
		if ((Member->is("ptr") == -1) || MANGLER::Is_Base_Type(Member) || MANGLER::Is_Based_On_Base_Type(Member))
			continue;

		string Member_Types = "";
		for (auto I : Member->Inheritted) {
			Member_Types += " " + I;
		}

		Ifs += 
			"if (" + Member->Name + " != 0->address && --" + Member->Name + ".Reference_Count < 1){\n" +
				Member->Name + ".Destructor()\n" +
				"Deallocate<" + Member_Types + ">(" + Member->Name + ")\n" +
			"}\n";
	}

	Ifs += "Deallocate<" + Type->Name + ">(this)\n}";
	//}
	//The function itself needs to be constructed with a this pointter.
	Node* Func = new Node(FUNCTION_NODE, Type->Location);
	Func->Name = "Destructor";
	Func->Inheritted.push_back("func");
	Func->Scope = Type;

	Node* This = new Node(PARAMETER_NODE, Type->Location);
	This->Name = "this";
	This->Inheritted = { Type->Name, "ptr" };
	This->Scope = Func;

	Func->Parameters.push_back(This);
	Func->Defined.push_back(This);

	Parser p(Func);
	p.Input = Lexer::GetComponents(Ifs);
	p.Factory();
	Func->Childs.push_back(p.Input[0].node);

	Func->Childs = Insert_Dot(Func->Childs, Func, This);

	/*for (int i = 0; i < Func->Parameters.size(); i++)
		if (Func->Parameters[i] == This)
			Func->Parameters.erase(Func->Parameters.begin() + i);

	for (int i = 0; i < Func->Defined.size(); i++)
		if (Func->Defined[i] == This)
			Func->Defined.erase(Func->Defined.begin() + i);*/

	Func->Parsed_By |= PARSED_BY::MEMBER_FUNCTION_DEFINED_INSIDE;

	Type->Defined.push_back(Func);
}

void PostProsessor::Destructor_Caller(Node* v, vector<Node*> &childs)
{
	if (!v->is(OBJECT_DEFINTION_NODE))
		return;
	if (MANGLER::Is_Based_On_Base_Type(v))
		return;
	if (v->is("ptr") == -1)
		return;
	if (v->is(PARSED_BY::DESTRUCTOR_CALLER))
		return;

	Parser p(v->Scope);
	p.Input = Lexer::GetComponents(v->Name + ".Destructor()");
	p.Factory();

	v->Parsed_By |= PARSED_BY::DESTRUCTOR_CALLER;

	PostProsessor P(v->Scope, p.Input);
	//v->Append(Output, P.Input);

	bool There_Is_No_User_Defined_Return = true;
	for (int i = childs.size()-1; i >= 0; i--) {
		if (childs[i]->Name == "return") {
			childs.insert(childs.begin() + i, P.Input.begin(), P.Input.end());
			There_Is_No_User_Defined_Return = false;
		}
	}

	if (There_Is_No_User_Defined_Return) {
		childs.insert(childs.end(), P.Input.begin(), P.Input.end());
	}
}

vector<Node*> PostProsessor::Insert_Dot(vector<Node*> Childs, Node* Function, Node* This)
{
	vector<Node*> Result;
	for (auto Child : Childs) {
		Update_Operator_Inheritance(Child);
		//this is for the size and format to not be included in the default constructor.
		if (Child->is("const") != -1)
			continue;
		/*if (Child->is("static") != -1)
			continue;*/

		//this is for the class constructor to not include functions as a dottize operation.
		if (Child->is(FUNCTION_NODE))
			continue;

		//Because the child in question is the highest in the ast towards tyhe function as a child.
		Node* Child_Copy = Child->Copy_Node(Child, Function);

		//insert this. infront of every member
			for (auto& Object : Child_Copy->Get_all({ OBJECT_DEFINTION_NODE, OBJECT_NODE, CALL_NODE })) {
				if (Object->is(NUMBER_NODE) || Object->is(FUNCTION_NODE) || (Object->is("const") != -1) || MANGLER::Is_Base_Type(Object))
					continue;
				if ((Object->is(OBJECT_DEFINTION_NODE) || Object->is(OBJECT_NODE)) && This->Find(Object, This) != nullptr && !Object->is(PARSED_BY::THIS_AND_DOT_INSERTER)) {
					//Node* define = c->Find(linear_n, Function);

					Node* Dot = new Node(OPERATOR_NODE, Function->Location);
					Dot->Name = ".";
					Dot->Scope = Object->Scope;

					Dot->Left = This->Copy_Node(This, This->Scope);

					Dot->Right = new Node(*Object);
					Dot->Right->Parsed_By |= PARSED_BY::THIS_AND_DOT_INSERTER;

					Dot->Context = Object->Context;

					*Object = *Dot;
				}
				else if (Object->is(CALL_NODE)) {
					//because this insert_dot is called upon a non hight AST member it needs to use the dynamic scope above.
					Object->Parameters = Insert_Dot(Object->Parameters, Object->Scope, This);
				}
			}
		Result.push_back(Child_Copy);
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

		Call->Parameters.back()->Context = Call;

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

	n->Left->Cast_Type = n->Right;
	n->Left->Cast_Type->Type = OBJECT_NODE;
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

	n->Function_Address_Giver = true;
}

void PostProsessor::Process_Function_Pointters(Node* scope)
{
	//first we need to identify all function pointters
	//the identification of a function pointter is:
	//func ptr X
	for (auto& Defined : scope->Defined) {
		if (!Defined->is(vector<string>{"func", "ptr"}))
			return;

			Defined->Function_Ptr = true;	
			
			//letus find the function adress giver
			for (int Line = 0; Line < scope->Childs.size(); Line++) {
				for (auto& Operator : scope->Childs[Line]->Get_all()) {//we dont want to filter the get all beacuse the get all will sort the returned items
					if (Operator->is(ASSIGN_OPERATOR_NODE) && Operator->Left->Name == Defined->Name && Operator->Right->is(OBJECT_NODE)) {
						if (Operator->Find(Operator->Right, Operator->Right)->Has({ IMPORT, FUNCTION_NODE })) {
							string Function_Name = Operator->Right->Name;
							Node* First_Call_Type = nullptr;
							//Now that we know the function name we need to know what function 
							//overload we want to call.
							for (int i = Line + 1; i < scope->Childs.size(); i++) {
								for (auto& j : scope->Childs[i]->Get_all()) {
									if (j->is(ASSIGN_OPERATOR_NODE) && j->Left->Name == Defined->Name)
										goto quit;

									if (j->is(CALL_NODE)) {
										Node* Call = new Node(CALL_NODE, j->Location);
										Call->Name = Function_Name;
										Call->Parameters = j->Parameters;
										Call->Scope = j->Scope;

										Update_Inheritance(j);
										Call->Inheritted = j->Inheritted;

										Find_Call_Owner(Call);

										j->Function_Implementation = Call->Function_Implementation;
										 
										if (First_Call_Type == nullptr)
											First_Call_Type = Call;
										else if (First_Call_Type->Function_Implementation != Call->Function_Implementation) {
											Node* Assing = new Node(ASSIGN_OPERATOR_NODE, j->Location);
											Assing->Name = "=";
											Assing->Scope = j->Scope;

											Assing->Left = new Node(*Defined);
											Assing->Right = new Node(OBJECT_NODE, j->Location);
											Assing->Right->Name = Function_Name;

											Assing->Left->Context = Assing;
											Assing->Right->Context = Assing;

											j->Header.push_back(Assing);
											goto quit;
										}

									}
								}
							}
						quit:;

							if (First_Call_Type) {
								Operator->Right->Function_Implementation = First_Call_Type->Function_Implementation;
							}
						}
						else {
							//this happends when a function pointter is passed to another one
							Report(Observation(ERROR, "YEET"));
						}
					}

				}
			}
	}


}

void PostProsessor::Member_Function_Defined_Outside(Node* f)
{
	//<summary>
	//	The function is in global scope's childs list-
	//	but it can be found in the respective scope that the fetchers describe.
	//	The Find function in Node.cpp can handle complex AST search to find the respective function.
	//	
	//	If the function in question is not a static type then we need to apply this pointters and other cool stuf.
	//</summary>
	if (f->Type != FUNCTION_NODE)
		return;
	if (f->Fetcher == nullptr)
		return;
	if (f->is("static") != -1)
		return;
	if (f->Parameters.size() > 0 && f->Parameters[0]->Name == "this")
		return;

	Node* func = f;

	Node* This = new Node(PARAMETER_NODE, "this", func->Location);
	This->Inheritted = { func->Fetcher->Name, "ptr" };
	This->Scope = func;
	This->Size = _SYSTEM_BIT_SIZE_;
	This->Defined = func->Find(func->Fetcher->Name, func, CLASS_NODE)->Defined;

	func->Defined.push_back(This);

	func->Parameters.insert(func->Parameters.begin(), This);

	func->Childs = Insert_Dot(func->Childs, func, This);

	Node* Class = func->Find_Scope(func);

	func->Fetcher = Class;

	*func->Fetcher->Find(func, Class, FUNCTION_NODE) = *func;
	
	func->Parsed_By |= PARSED_BY::POSTPROSESSOR;

	return;
}

void PostProsessor::Member_Function_Defined_Inside(Node* f)
{
	if (!f->is(FUNCTION_NODE))
		return;
	if (f->is("static") != -1)
		return;
	if (Scope->Name == "GLOBAL_SCOPE")
		return;
	if (f->Fetcher != nullptr)
		return;
	if (f->is(PARSED_BY::MEMBER_FUNCTION_DEFINED_INSIDE))
		return;

	Node* func = f;

	Node* This = new Node(PARAMETER_NODE, "this", func->Location);
	This->Inheritted = { Scope->Name, "ptr" };
	This->Scope = func;
	This->Size = _SYSTEM_BIT_SIZE_;

	func->Defined.push_back(This);

	func->Parameters.insert(func->Parameters.begin(), This);

	func->Childs = Insert_Dot(func->Childs, func, This);

	Node* Class = Scope->Find(Scope->Name, Scope, CLASS_NODE);

	*Scope->Find(func, Class, FUNCTION_NODE) = *func;

	func->Parsed_By |= PARSED_BY::POSTPROSESSOR;
	func->Parsed_By |= PARSED_BY::MEMBER_FUNCTION_DEFINED_INSIDE;

	return;
}

void PostProsessor::Open_Function_For_Prosessing(Node* f)
{
	//here we just go trugh the insides of the function
	//for optimization and other cool stuff :D
	if (!f->is(FUNCTION_NODE))
		return;
	if (f->Is_Template_Object)
		return;
	if (f->is(PARSED_BY::FUNCTION_PROSESSOR))
		return;
	for (auto j : f->Get_All_Fetchers())
		if (j->Is_Template_Object)
			return;

	f->Parsed_By |= PARSED_BY::FUNCTION_PROSESSOR;
	/*for (auto j : Input[i]->Parameters)
		if (j->is("type") != -1)
			return;
	*/
	
	PostProsessor p(f);
	p.Input = f->Childs;

	//prepare the local variables
	p.Define_Sizes(f);

	f->Update_Format();

	f->Update_Size();

	Open_Safe({ f });

	Process_Function_Pointters(f);

	p.Factory();

	f->Childs = p.Input;

	//clear from nested scopes current value.
	for (auto &i : f->Childs)
		for (auto &j : i->Get_all({IF_NODE, ELSE_IF_NODE, ELSE_NODE, WHILE_NODE}))
			for (auto& k : j->Defined)
				k->Current_Value = nullptr;

	for (auto& v : f->Defined)
		p.Destructor_Caller(v, f->Childs);

	while (true) {
		Algebra a(f, &f->Childs);
		if (!Optimized)
			break;
		Optimized = false;
	}

	for (auto& v : f->Defined) {
		for (auto j : f->Childs) {
			Analyze_Variable_Address_Pointing(v, j);
			if (v->Requires_Address)
				break;
		}
	}

	Define_Sizes(f);

	//Parent->Defined[i]->Update_Defined_Stack_Offsets();
	Scope->Append(f->Childs, p.Output);

	f->Parsed_By |= PARSED_BY::POSTPROSESSOR;
	return;
}

void PostProsessor::Open_Condition_For_Prosessing(int i)
{
	if (!Input[i]->is(IF_NODE) && !Input[i]->is(ELSE_IF_NODE) && !Input[i]->is(ELSE_NODE))
		return;
	//this add the L number to it
	//Input[i]->Name += to_string(LNumber++);

	//preprare the local variables
	Define_Sizes(Input[i]);

	if (!Input[i]->is(ELSE_NODE)) {
		PostProsessor p(Input[i], Input[i]->Parameters);

		Input[i]->Parameters = p.Input;
	}

	Process_Function_Pointters(Input[i]);

	//here we now postprosess also the insides of the condition
	PostProsessor p(Input[i], Input[i]->Childs);

	Input[i]->Childs = p.Input;

	Algebra_Laucher(Input[i], Input[i]->Childs);

	for (auto& v : Input[i]->Defined)
		p.Destructor_Caller(v, Input[i]->Childs);

	Scope->Append(Input[i]->Childs, p.Output);

	return;
}

void PostProsessor::Open_Paranthesis(int i)
{
	if (!Input[i]->is(CONTENT_NODE))
		return;

	PostProsessor p(Input[i], Input[i]->Childs);

	Input[i]->Childs = p.Input;

	for (auto& v : Input[i]->Defined)
		p.Destructor_Caller(v, Input[i]->Childs);

	Scope->Append(Input[i]->Childs, p.Output);

	if (Input[i]->Childs.back()->Cast_Type)
		Input[i]->Inheritted.push_back(Input[i]->Childs.back()->Cast_Type->Name);

	if (Input[i]->Inheritted.size() == 0)
		Input[i]->Inheritted = Input[i]->Childs.back()->Inheritted;
}

void PostProsessor::Find_Call_Owner(Node* n)
{
	if (!n->is(CALL_NODE))
		return;
	if (n->Function_Implementation != nullptr)
		return;
	//this function tryes to find the function to call
	//first try to find if this fucntion is a virtual function
	//Node* defition = Parent->Find(n->Name, Parent);
	//other wise we have normal functions
	//now lets check for template arguments-
	//as parameters on the function this callation calls

	vector<pair<Node*, Node*>> Candidates;
	bool It_Is_A_Function_Pointter = false;
	while (n->Function_Implementation == nullptr) {
		Candidates = Find_Suitable_Function_Candidates(n, It_Is_A_Function_Pointter);
		int Note = Choose_Most_Suited_Function_Candidate(Order_By_Accuracy(Candidates, n), n, It_Is_A_Function_Pointter);

		// returns 0 if found caller's function implemitation.
		if (Note == 0) {
			break;
		}
		// returns 1 if constructed a new function implemitation based on the template types
		else if (Note == 1) {
			continue;
		}
		// returns -1 if nothing found
		else if (Note == -1) {
			if (It_Is_A_Function_Pointter == false)
				It_Is_A_Function_Pointter = true;
			else
				Report(Observation(ERROR, "Cannot find function to call!", *n->Location));
		}
		// returns 2 if there is more than one suitable functions to call.
		else if (Note == 2) {
			Report(Observation(ERROR, "Cannot decide which function overload to call!", *n->Location));
		}
	}
	//the incerement of all func ptr candidates calling count happends at Choose_Most_Suited_Function_Candidate()
	if (It_Is_A_Function_Pointter == false) {
		n->Function_Implementation->Calling_Count++;
		n->Inheritted = n->Function_Implementation->Inheritted;
	}
	else {
		n->Size = n->Find(n, n)->Size;
		n->Inheritted = n->Find(n, n)->Inheritted;
	}



	/*Node* Scope = Global_Scope;
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

		Node* tmp_Current_Func = n->Copy_Node(n, n->Scope);
		tmp_Current_Func->Name = New_Name;

		if (Scope->Find(New_Name, Scope, { FUNCTION_NODE, PROTOTYPE, IMPORT, EXPORT }) != nullptr && tmp_Current_Func->Compare_Fetchers(Scope->Find(New_Name, Scope, { FUNCTION_NODE, PROTOTYPE, IMPORT, EXPORT }))) {
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
	}
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

	return;*/
}

vector<pair<Node*, Node*>> PostProsessor::Find_Suitable_Function_Candidates(Node* caller, bool Skip_Name_Comparison)
{
	vector<pair<Node*, Node*>> Result;

	//first try to find the scope, by checking fetchers
	vector<Node*> Scopes;

	if (caller->Fetcher) {
		/*if (caller->Fetcher->Defined.size() == 0) {
			caller->Fetcher->Defined = caller->Find(caller->Fetcher, caller->Scope)->Defined;
		}*/
		Scopes.push_back(caller->Find(caller->Fetcher, caller->Scope));
	}
	else if (caller->Get_Scope_As(CLASS_NODE, caller) != Global_Scope) {
		Scopes.push_back(caller->Get_Scope_As(CLASS_NODE, caller));
	}
	//Get_Scope_Path() doesnt give us Global_Scope, so lets add it manually.
	Scopes.push_back(Global_Scope);

	string New_Name = "";
	bool Inherit_Templates = false;
	if (caller->Templates.size() > 0) {
		New_Name = caller->Construct_Template_Type_Name();
	}
	else {
		Inherit_Templates = true;
	}

	bool Can_Remove_Templates = false;

	//now that our scopes are ready to go, we can loop through them and find suitable candidates.
	for (auto Scope : Scopes) {
		if (Inherit_Templates && Scope->Inheritable_templates.size() > 0) {
			caller->Templates = Scope->Inheritable_templates;
			New_Name = caller->Construct_Template_Type_Name();
			Can_Remove_Templates = true;
		}

		for (auto Func : Scope->Defined) {
			bool Is_Similiar_To_Existing_Template_Func_That_Has_Been_Constructed = false;
			if (!Func->Has({ FUNCTION_NODE, PROTOTYPE, IMPORT, EXPORT }))
				continue;

			if (Scope == caller->Fetcher) {
				if (Func->Fetcher != nullptr) {
					//this function has been declared at global scope
					continue;
				}
			}

			//this part is skipped if the function is a fuinction pointer.
			if (!Skip_Name_Comparison) {
				//check if the names are smae
				if (Func->Name != caller->Name)
					//if there is a mangled template name
					if (New_Name != "") {
						//check the mangled template name
						if (New_Name != Func->Name)
							continue;
						else
							Is_Similiar_To_Existing_Template_Func_That_Has_Been_Constructed = true;
					}
					else
						continue;
				//Check if the templates are temporarly made for just this instance.
				else if (Func->Templates.size() == 0 && Can_Remove_Templates) {
					caller->Templates.clear();
				}
			}
			if (Func->Parameters.size() != caller->Parameters.size())
				continue;
			if (Func->Templates.size() != caller->Templates.size() && !Is_Similiar_To_Existing_Template_Func_That_Has_Been_Constructed)
				continue;

			Result.push_back({ Func, Scope });
		}
	}
	return Result;
}

map<int, vector<pair<pair<Node*, Node*>, Node*>>> PostProsessor::Order_By_Accuracy(vector<pair<Node*, Node*>> Candidates, Node* Caller)
{
	//save the candidatea by int accuracity
	map<int, vector<pair<pair<Node*, Node*>, Node*>>> Result;

	for (auto Candidate : Candidates) {
		//for every point the accuracity increases.
		int Accuracity = 0;

		Node* Func = Candidate.first;

		//make the template ready for comparison.
		if (Candidate.first->Is_Template_Object) {
			Func = Candidate.first->Copy_Node(new Node(*Candidate.first), Candidate.second);

			//this part is going to be really slow :/
			for (int T = 0; T < Caller->Templates.size(); T++) {
				//find and replace the template arg with the callers template type.
				for (auto& I : Func->Inheritted)
					if (I == Candidate.first->Templates[T]->Name)
						I = Caller->Templates[T]->Name;

				for (auto& P : Func->Parameters) {
					for (auto& I : P->Inheritted)
						if (I == Candidate.first->Templates[T]->Name)
							I = Caller->Templates[T]->Name;
				}
			}
		}

		//dont worry about pointter amount, we will check them in another function-
		//that is to run after this function.
		if (Func->Get_Inheritted("_", true, false, true) == Caller->Get_Inheritted("_", true, false, true))
			Accuracity++;

		bool All_Parameters_Match = true;
		for (int i = 0; i < Func->Parameters.size(); i++) {
			if (Func->Parameters[i]->Get_Inheritted("_", true, false, true) != Caller->Parameters[i]->Get_Inheritted("_", true, false, true))
				for (int j = 0; j < Func->Parameters[i]->Inheritted.size(); j++)
					if (!Lexer::GetComponent(Func->Parameters[i]->Inheritted[j]).is(Flags::KEYWORD_COMPONENT))
						//banana --> fruit
						if (!Find_Castable_Inheritance(Caller->Parameters[i]->Get_Inheritted(true, false), Func->Parameters[i]->Inheritted[j]))
							//fruit --> banana
							for (int Caller_i = 0; Caller_i < Caller->Parameters[i]->Get_Inheritted(true, false).size(); Caller_i++)
								if (!Lexer::GetComponent(Caller->Parameters[i]->Get_Inheritted(true, false)[Caller_i]).is(Flags::KEYWORD_COMPONENT))
									if (!Find_Castable_Inheritance(Func->Parameters[i]->Get_Inheritted(true, false), Caller->Parameters[i]->Get_Inheritted(true, false)[Caller_i]))
										All_Parameters_Match = false;
		}

		if (All_Parameters_Match)
			Accuracity++;

		//check if the function is already constructed for this caller.
		if (Caller->Templates.size() > 0) {
			string New_Name = Caller->Construct_Template_Type_Name();
			if (New_Name == Func->Name)
				Accuracity++;
		}

		Result[Accuracity].push_back({ {Candidate.first, Func}, Candidate.second });

	}
	return Result;
}

// returns 0 if found caller's function implemitation.
// returns 1 if constructed a new function implemitation based on the template types
// returns -1 if nothing found
// returns 2 if there is more than one suitable functions to call.
int PostProsessor::Choose_Most_Suited_Function_Candidate(map<int, vector<pair<pair<Node*, Node*>, Node*>>> Candidates, Node* Caller, bool Is_Func_Ptr)
{
	//Max accuracity is currently capped out at 3
	int Max_Accuracity = 3;

	Node* Best_Candidate = nullptr;
	Node* Best_Candidate_Copy;
	Node* Scope = Caller->Scope;

	string New_Name = Caller->Construct_Template_Type_Name();

	//	  Candidate, Distance
	vector<pair<pair<pair<Node*, Node*>, Node*>, int>> Candidate_Distance;
	for (int Current_Accuracy = Max_Accuracity; Current_Accuracy >= 0; Current_Accuracy--) {
		for (auto Func : Candidates[Current_Accuracy]) {
			//Check whoose closer if the return type or parameters need to be casted
			int Current_Candidate_Distance = 0;
			//the more casting is made the further the candidate is from the caller
			vector<string> Callers_Return_Types = Caller->Get_Inheritted(true, false, true);
			vector<string> Func_Return_Types = Func.first.second->Get_Inheritted(true, false, true);

			for (int P = 0; P < Func.first.second->Parameters.size(); P++) {
				//calculate the casting distance
				Current_Candidate_Distance += Get_Casting_Distance(Caller->Parameters[P], Func.first.second->Parameters[P]);
				//calculate the ptr distance
				Current_Candidate_Distance += Caller->Parameters[P]->Calculate_Inheritted_Distance(Func.first.second->Parameters[P], "ptr");
			}

			if (Callers_Return_Types.size() == Func_Return_Types.size())
				for (int P = 0; P < Callers_Return_Types.size(); P++)
					Current_Candidate_Distance += Get_Casting_Distance(Scope->Find(Callers_Return_Types[P]), Scope->Find(Func_Return_Types[P]));
			else {
				//if the caller has return type but is not same as the func the distance grows.
				if (Callers_Return_Types.size() > 0)
					Current_Candidate_Distance += Caller->Calculate_Inheritted_Distance(Func.first.second, "ptr");
				//but if the call's return type is empty it means that the context is hard to read.
				//so the distance won be affected.
			}

			//if the function is already defined for this caller the distance should be smaller.
			if (Caller->Templates.size() > 0) {
				if (New_Name == Func.first.first->Name) {
					Current_Candidate_Distance--;
				}
			}

			Candidate_Distance.push_back({ {{Func.first.first, Func.first.second}, Func.second}, Current_Candidate_Distance });
		}
	}

	if (Is_Func_Ptr) {
		for (auto& I : Candidate_Distance) {
			I.first.first.first->Calling_Count++;
		}
		Caller->Function_Ptr = true;
		return 0;
	}

	//now determine the best candidate
	pair<pair<pair<Node*, Node*>, Node*>, int>* Closest = nullptr;
	for (auto& I : Candidate_Distance) {
		if (Closest == nullptr || Closest->second > I.second)
			Closest = &I;
	}

	int Identical_Function_Candidate_Count = 0;
	for (auto& I : Candidate_Distance) {
		if (I.second == Closest->second)
			if (Closest != &I)
				if (Closest->first.first != I.first.first)
					Identical_Function_Candidate_Count++;
	}

	if (Identical_Function_Candidate_Count > 0)
		return 2;

	if (Closest == nullptr) {
		return -1;
	}

	Best_Candidate = Closest->first.first.first;
	Best_Candidate_Copy = Closest->first.first.second;
	Scope = Closest->first.second;

	if (Best_Candidate->Is_Template_Object) {
		//check if the template function is already generated for this caller.
		Best_Candidate_Copy->Name = New_Name;

		Node* Function = Scope->Find(New_Name, Scope, { FUNCTION_NODE, PROTOTYPE, IMPORT, EXPORT });
		if (Function != nullptr && Best_Candidate_Copy->Compare_Fetchers(Function) && (Function->Template_Children[1].Components.size() > 0 && Function->Childs.size() > 0)) {
			
			/*if (Function->Template_Children[1].Components.size() > 0 && Function->Childs.size() == 0) {
				Parser parser(Function);
				parser.Input = Function->Template_Children[1].Components;

				for (auto component : parser.Input) {

				}

				parser.Factory();

				for (auto I : parser.Input)
					if (I.node)
						Function->Childs.push_back(I.node);

				Function->Is_Template_Object = false;

				PostProsessor postprosessor(Function);
				postprosessor.Open_Function_For_Prosessing(Function);
			}*/
			
			Caller->Function_Implementation = Function;
			Caller->Name = New_Name;
			Caller->Templates.clear();
			Function->Calling_Count++;
			return 0;
		}

		//reset the name to normal
		Best_Candidate_Copy->Name = Best_Candidate->Name;
		Best_Candidate_Copy->Templates = Caller->Templates;

		//here we generate the template function from the template types
		Parser P(Scope);
		P.Input = P.Template_Function_Constructor(Best_Candidate_Copy, Best_Candidate->Templates, Caller->Templates);
		P.Factory();

		for (int i = Scope->Defined.size() - 1; i >= 0; i--) {
			if (Scope->Defined[i]->is(FUNCTION_NODE) && Scope->Defined[i]->Name == New_Name){
				Caller->Function_Implementation = Scope->Defined[i];
				break;
			}
		}

		Caller->Name = New_Name;
		Caller->Templates.clear();

		if (!Caller->Function_Implementation->is(PARSED_BY::POSTPROSESSOR)) {
			if (Caller->Function_Implementation->Fetcher != nullptr || Caller->Function_Implementation->Get_Scope_As(CLASS_NODE, Caller->Function_Implementation) != Global_Scope) {
				Member_Function_Defined_Inside(Caller->Function_Implementation);
				Member_Function_Defined_Outside(Caller->Function_Implementation);
			}
			Open_Function_For_Prosessing(Caller->Function_Implementation);
		}

		return 1;
	}
	else {
		Caller->Function_Implementation = Best_Candidate;
		Caller->Name = Caller->Function_Implementation->Name;
		Caller->Templates.clear();
		return 0;
	}
}

int PostProsessor::Get_Casting_Distance(Node* a, Node* b, bool Layer)
{
	int Result = 0;
	//banana -> fruit
	Node* Current = a;
	Node* Goal = b;

	if (Current->Get_Inheritted("_", true, false, true) == Goal->Get_Inheritted("_", true, false, true))
		return Result + Layer;

	if (!MANGLER::Is_Base_Type(Current))
		for (auto I : Current->Get_Inheritted(true, false, true)) {
			//try to chack if this inheritted is connected to the goal type.
			int Distance = Get_Casting_Distance(Current->Find(I), Goal, true);
			if (Distance > 0)
				Result += Distance;
		}

	if (Result == 0) {
		//fruit -> banana
		if (!MANGLER::Is_Base_Type(Goal))
			for (auto I : Goal->Get_Inheritted(true, false, true)) {
				//try to chack if this inheritted is connected to the goal type.
				int Distance = Get_Casting_Distance(Goal->Find(I), Current, true);
				if (Distance > 0)
					Result += Distance;
			}
	}
	return Result + Layer;
}

bool PostProsessor::Find_Castable_Inheritance(vector<string> types, string target)
{
	for (auto type : types) {
		if (Lexer::GetComponents(type)[0].is(Flags::KEYWORD_COMPONENT))
			continue;
		if (type == target)
			return true;
		if (!MANGLER::Is_Base_Type(Scope->Find(type, Scope, CLASS_NODE)))
			if (Find_Castable_Inheritance(Scope->Find(type, Scope, CLASS_NODE)->Get_Inheritted(true), target))
				return true;
	}
	return false;
}

void PostProsessor::Open_Call_Parameters_For_Prosessing(int i)
{
	if (!Input[i]->is(CALL_NODE))
		return;

	vector<Node*> Own_Defined = Input[i]->Defined;

	//give the post prosessor a way to reach the parameters that might have member fetching/ math
	PostProsessor p(Scope, Input[i]->Parameters);

	Input[i]->Parameters = p.Input;

	Algebra_Laucher(Input[i], Input[i]->Parameters);

	//see what outside defined has been injected to this call.
	for (int j = 0; j < Input[i]->Defined.size(); j++) {
		bool Is_Own_Defined = false;
		for (auto k : Own_Defined) {
			if (Input[i]->Defined[j] == k) {
				Is_Own_Defined = true;
			}
		}
		if (!Is_Own_Defined) {
			Input[i]->Scope->Defined.push_back(Input[i]->Defined[j]);
			Input[i]->Defined[j]->Scope = Input[i]->Scope;
			Input[i]->Defined.erase(Input[i]->Defined.begin() + j);
		}
	}

	//for (auto& v : Input[i]->Defined)
	//	p.Destructor_Caller(v, Input);

	Scope->Append(Output, p.Output);

	for (auto j : Input[i]->Parameters) {
		if (j->Header.size() > 0) {
			Input[i]->Header.insert(Input[i]->Header.end(), j->Header.begin(), j->Header.end());
			j->Header.clear();
		}
	}

	if (Input[i]->Context == nullptr || !Input[i]->Context->Has({ CALL_NODE, OPERATOR_NODE, ASSIGN_OPERATOR_NODE, CONDITION_OPERATOR_NODE, BIT_OPERATOR_NODE, LOGICAL_OPERATOR_NODE, ARRAY_NODE, FLOW_NODE })) {
		Input.insert(Input.begin() + i, Input[i]->Header.begin(), Input[i]->Header.end());
		Input[i]->Header.clear();
	}
	else if (Input[i]->Context) {
		Input[i]->Context->Header.insert(Input[i]->Context->Header.end(), Input[i]->Header.begin(), Input[i]->Header.end());
		Input[i]->Header.clear();
	}
	//use optimization into the parameters.
	//Algebra a(Input[i], &Input[i]->Parameters);	//Algebra has already optimized this!

	for (auto j : Input[i]->Parameters)
		if (j->is(OPERATOR_NODE)) {
			Update_Operator_Inheritance(j);
			j->Update_Size();
		}
}

void PostProsessor::Algebra_Laucher(Node* Scope, vector<Node*> &List)
{
	while (true) {
		Algebra a(Scope, &List);
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
		Node* Left = Scope->Find(Get_From_AST(n->Left), Scope);
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

		n->Childs = p.Input;

		return Get_From_AST(n->Childs[0]);
	}
	else if (n->is(OPERATOR_NODE)) {
		vector<Node*> Change = { n };
		PostProsessor p(Scope, Change);

		if (Change.size() > 1)
			Report(Observation(ERROR, "Un handled situation!", *n->Location));

		return Get_From_AST(n);	//this call the same funciton again because the structure of the AST might have been changed.
	}
	else if (n->is(ARRAY_NODE)) {

		vector<Node*> Change = { n };

		PostProsessor p(Scope, Change);

		if (Change.size() > 1)
			Report(Observation(ERROR, "Un handled situation!", *n->Location));

		return n->Get_Most_Left();
	}
	else if (n->is(CALL_NODE)) {
		PostProsessor p(Scope, n->Parameters);

		n->Parameters = p.Input;

		Find_Call_Owner(n);
		return n;
	}
	else  {
		return n;
	}
}

//this is not called upon type initializations because this is called on function memebers
//so that unused classe's members size wont need to be calculated.
void PostProsessor::Define_Sizes(Node* p)
{
	//here we set the defined size of the variable
	for (Node* d : p->Defined) {
		d->Get_Inheritted_Class_Members();
		d->Update_Size();
		d->Update_Format();
	}

	p->Update_Local_Variable_Mem_Offsets();
	p->Update_Member_Variable_Offsets(p);

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
	if (!Input[i]->Has({ASSIGN_OPERATOR_NODE, OPERATOR_NODE, BIT_OPERATOR_NODE, CONDITION_OPERATOR_NODE, LOGICAL_OPERATOR_NODE, PREFIX_NODE, POSTFIX_NODE}))
		return;

	if (Input[i]->is(PREFIX_NODE)) {
		PostProsessor r(Scope, vector<Node*>{ Input[i]->Right});
	}
	else if (Input[i]->is(POSTFIX_NODE)) {
		PostProsessor r(Scope, vector<Node*>{ Input[i]->Left});
	}
	else if (Input[i]->Right->is(CALL_NODE) && MANGLER::Is_Based_On_Base_Type(Input[i]->Right)) {
		PostProsessor l(Scope, vector<Node*>{Input[i]->Left });
		Input[i]->Right->Inheritted = Input[i]->Left->Inheritted;
		PostProsessor r(Scope, vector<Node*>{ Input[i]->Right});
	}
	else if (Input[i]->Left->is(CALL_NODE) && MANGLER::Is_Based_On_Base_Type(Input[i]->Left)) {
		PostProsessor r(Scope, vector<Node*>{ Input[i]->Right});
		Input[i]->Left->Inheritted = Input[i]->Right->Inheritted;
		PostProsessor l(Scope, vector<Node*>{Input[i]->Left });
	}
	else {
		PostProsessor r(Scope, vector<Node*>{ Input[i]->Right, Input[i]->Left });
	}

	vector<Node*> Tmp;

	if (!Input[i]->is(PREFIX_NODE))
		Tmp.push_back(Input[i]->Left);
	if (!Input[i]->is(POSTFIX_NODE))
		Tmp.push_back(Input[i]->Right);

	Algebra_Laucher(Input[i], Tmp);

	if (!Input[i]->Has({ PREFIX_NODE, POSTFIX_NODE })) {
		//try to find a suitable operator overload if there is one
		for (auto& overload : Input[i]->Left->Operator_Overloads) {
			//the syntax still needs to be done!

			//the operator overloads return type is the same as the operator type for this.
			Input[i]->Inheritted = overload->Inheritted;
			return;
		}

		if (Input[i]->Left->is(NUMBER_NODE)) {
			if (Input[i]->Name == "-" || Input[i]->Name == "/" || Input[i]->Name == "<" || Input[i]->Name == ">" || Input[i]->Name == "!<" || Input[i]->Name == "!>" || Input[i]->Name == "<=" || Input[i]->Name == ">=") {
				//make a tmp variable and set the number constant into it
				string Constant_Name = Input[i]->Left->Name + "_TMP";

				Node* Constant_Tmp;

				if (Input[i]->Find(Constant_Name)) {
					Constant_Tmp = Input[i]->Find(Constant_Name);
				}
				else {
					Constant_Tmp = new Node(OBJECT_DEFINTION_NODE, new Position());
					Constant_Tmp->Name = Constant_Name;
					Constant_Tmp->Scope = Input[i]->Scope;
				}

				//move the constant here.
				Node* Move = new Node(ASSIGN_OPERATOR_NODE, new Position());
				Move->Name = "=";
				Move->Scope = Input[i]->Scope;

				Move->Left = new Node(*Constant_Tmp);
				Move->Left->Context = Move;

				Move->Right = new Node(*Input[i]->Left);
				Move->Right->Context = Move;

				Input[i]->Header.insert(Input[i]->Header.begin(), Move);
				*Input[i]->Left = *Move;
			}
			else {
				Node* tmp = Input[i]->Left;
				Input[i]->Left = Input[i]->Right;
				Input[i]->Right = tmp;
			}
		}
	}

	int Left_Size = 0;
	int Right_Size = 0;

	if (!Input[i]->is(PREFIX_NODE)) {
		for (auto j : Input[i]->Left->Get_Inheritted(false, false)) {
			if (Lexer::GetComponents(j)[0].is(Flags::KEYWORD_COMPONENT))
				continue;
			Left_Size += Scope->Find(j, Scope)->Get_Size();
		}
		if (Input[i]->Left->Cast_Type != nullptr && Input[i]->Left->Cast_Type->Name != "address")
			Left_Size = Scope->Find(Input[i]->Left->Cast_Type, Scope)->Get_Size();
		if (Input[i]->Left->is("ptr") != -1)
			Left_Size = _SYSTEM_BIT_SIZE_;
	}

	if (!Input[i]->is(POSTFIX_NODE)) {
		for (auto j : Input[i]->Right->Get_Inheritted(false, false)) {
			if (Lexer::GetComponents(j)[0].is(Flags::KEYWORD_COMPONENT))
				continue;
			Right_Size += Scope->Find(j, Scope)->Get_Size();
		}
		if (Input[i]->Right->Cast_Type != nullptr && Input[i]->Right->Cast_Type->Name != "address")
			Right_Size = Scope->Find(Input[i]->Right->Cast_Type, Scope)->Get_Size();
		if (Input[i]->Right->is("ptr") != -1)
			Right_Size = _SYSTEM_BIT_SIZE_;
	}


	if (Left_Size >= Right_Size)
		Input[i]->Inheritted = Input[i]->Left->Get_Inheritted(false, false);
	else
		Input[i]->Inheritted = Input[i]->Right->Get_Inheritted(false, false);

	if (!Input[i]->is(PREFIX_NODE)) {
		if (Input[i]->Left->Function_Address_Giver)
			Input[i]->Left->Size = Left_Size;
		if (Input[i]->Left->Header.size() > 0) {
			int Header_Size = Input[i]->Left->Header.size();

			if (Input[i]->Context == nullptr)
				Input.insert(Input.begin() + i, Input[i]->Left->Header.begin(), Input[i]->Left->Header.end());
			else
				Input[i]->Context->Header.insert(Input[i]->Context->Header.end(), Input[i]->Left->Header.begin(), Input[i]->Left->Header.end());

			Input[i + Header_Size]->Left->Header.clear();
		}
	}
	if (!Input[i]->is(POSTFIX_NODE)) {
		if (Input[i]->Right->Header.size() > 0) {
			int Header_Size = Input[i]->Right->Header.size();

			if (Input[i]->Context == nullptr)
				Input.insert(Input.begin() + i, Input[i]->Right->Header.begin(), Input[i]->Right->Header.end());
			else
				Input[i]->Context->Header.insert(Input[i]->Context->Header.end(), Input[i]->Right->Header.begin(), Input[i]->Right->Header.end());

			Input[i + Header_Size]->Right->Header.clear();
		}
		if (Input[i]->Right->Function_Address_Giver)
			Input[i]->Right->Size = Right_Size;
	}

	if ((Input[i]->Header.size() > 0) && (Input[i]->Context == nullptr)) {
		int Header_Size = Input[i]->Header.size();
		Input.insert(Input.begin() + i, Input[i]->Header.begin(), Input[i]->Header.end());

		Input[i + Header_Size]->Header.clear();
	}
}

void PostProsessor::Determine_Array_Type(int i)
{
	if (!Input[i]->is(ARRAY_NODE))
		return;

	PostProsessor r(Scope, vector<Node*>{ Input[i]->Right, Input[i]->Left });

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

	PostProsessor p(Scope, { Input[i]->Right });
}

void PostProsessor::Open_PostFix_Operator(int i)
{
	if (!Input[i]->is(POSTFIX_NODE))
		return;


	PostProsessor p(Scope, { Input[i]->Left });
}

void PostProsessor::Type_Size_Definer(int i)
{
	if (Scope->Defined[i]->Type != CLASS_NODE)
		return;
	if (Scope->Defined[i]->Templates.size() > 0)	//template types are constructed elsewhere.
		return;
	//update members sizes
	Scope->Defined[i]->Update_Size();

	//update the member stack offsets
	Scope->Defined[i]->Update_Local_Variable_Mem_Offsets();

	//update format
	Scope->Defined[i]->Update_Format();

	//update all member formats as well
	for (auto& i : Scope->Defined[i]->Defined)
		i->Update_Format();
}

void PostProsessor::Handle_Imports(int i)
{
	if (!Scope->Defined[i]->is(IMPORT))
		return;
	//import func new (4, ABC)
	//all numbers need to be redefined by type size.
	//and all other text is already classes.
	//pointters are inside the parameter as inheritance.
	bool Parse_Returning_Numerical_Types = false;
	vector<Node*> Numerical_Types = Scope->Defined[i]->Parameters;
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
	if (Parse_Returning_Numerical_Types == false && Scope->Defined[i]->Numerical_Return_Types.size() > 0) {
		Parse_Returning_Numerical_Types = true;
		Numerical_Types = Scope->Defined[i]->Numerical_Return_Types;
		goto Again;
	}
	else if (Parse_Returning_Numerical_Types) {
		for (auto j : Numerical_Types) {
			Scope->Defined[i]->Inheritted.push_back(j->Name);
		}
		Scope->Defined[i]->Numerical_Return_Types.clear();
	}
	//TODO: Re-order all return types and parameter types into a logical order.
	//now all types are good to go.
	//although function calling might get tricky with just types as the parameters.
}

void PostProsessor::Open_Loop_For_Prosessing(int i)
{
	if (!Input[i]->is(WHILE_NODE))
		return;

	//while (a + 1 < a * 2){..}
	//while (int i = 0, a + i < a * i*2, i++){..}
	//we dont necessarily need to seperate the condition operator.
	Algebra Alg(Input[i], &Input[i]->Parameters);

	//now just prosess the child tokens of while node as well.
	PostProsessor post(Input[i]);
	post.Input = Input[i]->Childs;

	Algebra_Laucher(Input[i], Input[i]->Childs);

	//NOTE: this defined sizes might be reduntant!
	post.Define_Sizes(Input[i]);

	Process_Function_Pointters(Input[i]);

	//haha brain go brr
	post.Factory();

	for (auto& v : Input[i]->Defined)
		post.Destructor_Caller(v, Input[i]->Childs);

	Scope->Append(Input[i]->Childs, post.Output);
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
	if (!v->Has({ OBJECT_DEFINTION_NODE, OBJECT_NODE, PARAMETER_NODE }))
		return;

	//if a variable is pointed to via a pointter or a function parameter address loader, use stack.
	//Other than that use registers.
	if (n->Has({ASSIGN_OPERATOR_NODE, OPERATOR_NODE, CONDITION_OPERATOR_NODE, BIT_OPERATOR_NODE, LOGICAL_OPERATOR_NODE})) {
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
			for (auto j : n->Parameters[i]->Get_all({ OBJECT_NODE, PARAMETER_NODE, OBJECT_DEFINTION_NODE }))
				if (j->Name == v->Name)
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

		//check if the return returs this v node
		for (auto i : n->Get_all({ OBJECT_DEFINTION_NODE, OBJECT_NODE, PARAMETER_NODE })) {
			if (i->Name == v->Name)
				if (i->Context == n) {
					Node* func = n->Get_Scope_As(FUNCTION_NODE, n);
					int Func_ptr = Get_Amount("ptr", func);
					int V_ptr = Get_Amount("ptr", i);
					if (Func_ptr > V_ptr)
						v->Requires_Address = true;
				}
		}

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

	if (n->Cast_Type != nullptr && n->Cast_Type->Name != "address")
		for (auto i : n->Find(n->Cast_Type, n)->Inheritted)
			if (i == t)
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

	Node* og = Scope->Find(Input[i]->Left->Name);

	if (Scope->Name == "GLOBAL_SCOPE") {
		//We are in global scope area.
		if (!Input[i]->Right->Get_Most_Left()->is(NUMBER_NODE) && !Input[i]->Right->Get_Most_Left()->is(STRING_NODE)) {
			Node* Right = Scope->Find(Input[i]->Right->Get_Most_Left()->Name);
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
	if (Scope->Name == "GLOBAL_SCOPE")
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
	if (Scope->Name != "GLOBAL_SCOPE" && Scope->is("static") == -1)
		return;

	Node* Globl_Var = Scope->Find(Input[i]->Left->Name);
	Globl_Var->Type = OBJECT_NODE;

	Globl_Var->Update_Size();

	Scope->Header.push_back(Input[i]);

	Input.erase(Input.begin() + i);

	Move_Global_Varibles_To_Header(i);
}

bool PostProsessor::Check_If_Template_Function_Is_Right_One(Node* t, Node* c)
{
	//t = template
	//c = call
	int Type_Amount = 0;
	if (t->Templates.size() > 0) {
		for (auto T : t->Templates)
			for (auto i : t->Inheritted)
				if (i == T->Name)
					Type_Amount++;
	}
	else {
		//how many times we can skip a type
		int Type_Amount = Get_Amount("type", t);

	}

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
		if (n->Left->Has({OPERATOR_NODE, CONDITION_OPERATOR_NODE, BIT_OPERATOR_NODE, ARRAY_NODE, LOGICAL_OPERATOR_NODE, PREFIX_NODE, POSTFIX_NODE}))
			n->Inheritted = n->Left->Inheritted;
		else if (!n->Left->is(NUMBER_NODE) && !n->Left->is(CONTENT_NODE))
			n->Inheritted = n->Left->Scope->Find(n->Left, n->Left->Scope)->Inheritted;
		else if (n->Left->is(NUMBER_NODE))
			n->Inheritted = n->Left->Get_Inheritted(false, false);
		else {
			if (n->Right->Has({ OPERATOR_NODE, CONDITION_OPERATOR_NODE, BIT_OPERATOR_NODE, ARRAY_NODE, LOGICAL_OPERATOR_NODE, PREFIX_NODE, POSTFIX_NODE }))
				n->Inheritted = n->Right->Inheritted;
			else
				//both cannot be numbers, because otherwise algebra would have optimized it away.
				n->Inheritted = n->Right->Scope->Find(n->Right, n->Right->Scope)->Inheritted;
		}
	}
}

void PostProsessor::Update_Inheritance(Node* n)
{
	if (n->Context->Name == "return") {
		n->Inheritted = n->Get_Scope_As(FUNCTION_NODE, n)->Inheritted;
	}
	else {
		Update_Operator_Inheritance(n->Context);
		n->Inheritted = n->Context->Inheritted;
	}
}

void PostProsessor::Analyze_Return_Value(Node* n)
{
	if (n->Name != "return")
		return;
	if (n->Right == nullptr)
		return;

	PostProsessor p(n, { n->Right });

	for (auto& v : n->Right->Defined)
		p.Destructor_Caller(v, Input);
		
	Scope->Append(Output, p.Output);

	Update_Operator_Inheritance(n->Right);
}