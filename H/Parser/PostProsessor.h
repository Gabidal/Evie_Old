#ifndef _POSTPROSESSOR_H_
#define _POSTPROSESSOR_H_

#include "../Lexer/Component.h"
#include "../Flags.h"
#include "../Nodes/Node.h"
#include "Algebra.h"

#include <vector>
#include <iostream>

using namespace std;

class PostProsessor
{
public:
	vector<Component> Components;
	vector<Node*> Input;
	vector<Node*> Output;
	Node* Parent = nullptr;

	PostProsessor(Node* p) : Parent(p){}
	PostProsessor(Node* p, vector<Node*> in) : Parent(p), Input(in) { Factory(); }
	PostProsessor(Node* p, vector<Component> in) : Parent(p), Components(in) { Factory(); }
	PostProsessor(){}
	~PostProsessor(){}

	void Factory();
	void Transform_Component_Into_Node();			//transfer the components into pure nodes
	void Type_Definer(int i);						//defines all the members of type
	void Member_Function(int i);					//puts the func into parenting type class
	//void Combine_Conditions(int i);					//combines the if and else
	void Open_Function_For_Prosessing(int i);		//just opens the functions insides for post prosessor.
	void Open_Condition_For_Prosessing(int i);		//just opens the condition insides for post prosessor.
	void Find_Call_Owner(Node* n);					//justifyes the fucntion to call
	void Open_Call_Parameters_For_Prosessing(int i);//open the calls parameters to do postprosessing
	void Algebra_Laucher(int i);					//utilisez algebra to optimize the code in the function.
	void Combine_Member_Fetching(Node* n);			//combines the fether into the fetching member
	void Define_Sizes(Node* p);						//defines sizes of every type that the parent has init.
	void Combine_Condition(int i);					//combines the ifs and elses
	void Determine_Return_Type(int i);				//open the operator and determined the types basen on the left and right side
	void Determine_Array_Type(int i);				//
													//opens an operator for callation purposes.
	void Operator_Type_Definer(Node* n);			//gives the operator its left and the right sided types for more abstract.
	void Handle_Imports(int i);					//here we can redefine the types given to parameters.
	void Open_Loop_For_Prosessing(int i);
	void Update_Used_Object_Info(Node* n);

	Node* Get_From_AST(Node* n);
		
	void Operator_Overload(int i);					//makes new instance of using different operators
	void Template_Parameter(int i);					//dynamic parameters
	void Templates(int i);

	void Analyze_Variable_Address_Pointing(Node* n);
	int Get_Amount(string t, Node* n);

	void Analyze_Global_Variable_Changes(int i);
	void Change_Local_Strings_To_Global_Pointters(int i);

	void Move_Global_Varibles_To_Header(int i);

	bool Check_If_Template_Function_Is_Right_One(Node* t, Node* c);

	void Open_Safe(vector<Node*> n);

	vector<Node*> Linearise(Node*);
	string To_String(Node*);
private:
};

#endif