#ifndef _POSTPROSESSOR_H_
#define _POSTPROSESSOR_H_

#include "../Lexer/Component.h"
#include "../Flags.h"
#include "../Nodes/Node.h"
#include "Algebra.h"

#include <vector>
#include <iostream>
#include <map>

using namespace std;

class PostProsessor
{
public:
	vector<Component> Components;
	vector<Node*> Input;
	vector<Node*> Output;
	Node* Scope = nullptr;

	PostProsessor(Node* p) : Scope(p){}
	PostProsessor(Node* p, vector<Node*> in) : Scope(p), Input(in) { Factory(); }
	PostProsessor(Node* p, vector<Component> in) : Scope(p), Components(in) { Factory(); }
	PostProsessor(){}
	~PostProsessor(){}

	void Factory();
	void Transform_Component_Into_Node();			//transfer the components into pure nodes
	
	//Import handlers
	//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	void Type_Size_Definer(int i);
	void Handle_Imports(int i);					//here we can redefine the types given to parameters.

	//Class handlers
	//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	void Type_Definer(int i);						//defines all the members of type
	void Destructor_Generator(Node* Type);			//creates the destructor pipeline
	void Destructor_Caller(Node* v, vector<Node*>& childs);
	void Member_Function_Defined_Outside(Node* f);	//puts the func into parenting type class
	void Member_Function_Defined_Inside(Node* f);		//


	//void Combine_Conditions(int i);				//combines the if and else
	void Open_Function_For_Prosessing(Node* f);		//just opens the functions insides for post prosessor.
	void Open_Condition_For_Prosessing(int i);		//just opens the condition insides for post prosessor.
	void Open_Paranthesis(int i);					//(..)

	//Callation handlers
	//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	void Open_Call_Parameters_For_Prosessing(int i);//open the calls parameters to do postprosessing
	vector<pair<Node*, Node*>> Find_Suitable_Function_Candidates(Node* caller, bool Skip_Name_Comparison);
	map<int, vector<pair<pair<Node*, Node*>, Node*>>> Order_By_Accuracy(vector<pair<Node*, Node*>> Candidates, Node* Caller);
	int Choose_Most_Suited_Function_Candidate(map<int, vector<pair<pair<Node*, Node*>, Node*>>> Candidates, Node* Caller, bool Is_Func_Ptr);
	int Get_Casting_Distance(Node* a, Node* b, bool Layer = false);
	bool Find_Castable_Inheritance(vector<string> types, string target);
	void Find_Call_Owner(Node* n);					//justifyes the fucntion to call



	void Algebra_Laucher(Node* Scope, vector<Node*> &List);					//utilisez algebra to optimize the code in the function.
	void Combine_Member_Fetching(Node* n);			//combines the fether into the fetching member
	void Define_Sizes(Node* p);						//defines sizes of every type that the parent has init.
	void Combine_Condition(int i);					//combines the ifs and elses
	void Determine_Return_Type(int i);				//open the operator and determined the types basen on the left and right side
	void Determine_Array_Type(int i);				//
	void Open_PreFix_Operator(int i);
	void Open_PostFix_Operator(int i);
										
	void Open_Loop_For_Prosessing(int i);
	void Update_Used_Object_Info(Node* n);

	Node* Get_From_AST(Node* n);
		
	void Operator_Overload(int i);					//makes new instance of using different operators
	void Template_Parameter(int i);					//dynamic parameters
	void Templates(int i);

	void Analyze_Variable_Address_Pointing(Node* v, Node* n);
	int Get_Amount(string t, Node* n);

	void Analyze_Global_Variable_Changes(int i);
	void Change_Local_Strings_To_Global_Pointters(int i);

	void Move_Global_Varibles_To_Header(int i);

	bool Check_If_Template_Function_Is_Right_One(Node* t, Node* c);

	void Open_Safe(vector<Node*> n);

	void Update_Operator_Inheritance(Node* n);
	void Analyze_Return_Value(Node* n);

	vector<Node*> Insert_Dot(vector<Node*> Childs, Node* Function, Node* This);
	vector<Node*> Dottize_Inheritanse(Node* Class, Node* This, Node* Function);

	void Cast(Node* n);
	void Increase_Calling_Number_For_Function_Address_Givers(Node* n);

	//Namespace inlining properties
	//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	//void Handle_Namespace_Inlining(int i);
private:
};

#endif