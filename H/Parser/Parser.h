#ifndef _PARSER_H_
#define _PARSER_H_

#include "../../H/Flags.h"
#include "../Lexer/Component.h"
#include "../Nodes/Node.h"

#include <vector>
#include <iostream>

using namespace std;

class Parser
{
public:
	Parser(Node* p) : Parent(p){}
	~Parser(){}
	Node* Parent = nullptr;
	vector<Component> Input;
	vector<Component> Get_Inheritting_Components(int i);
	vector<int> Get_Amount_Of(int i, long Flag, bool All_in_Same_Line = true);
	vector<int> Get_Amount_Of(int i, vector<int> Flags, bool All_in_Same_Line = true);

	//POST-PREPROSESSOR PATTERNS
	//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	void Combine_Dot_In_Member_Functions(int& i);

	void Template_Pattern(int& i);
	void Operator_Combinator(int i);
	void Nodize_Template_Pattern(int i); 
	void Template_Type_Constructor(int i);
	vector<Component> Template_Function_Constructor(Node* Func, vector<Node*> T_Arg, vector<Node*> T_Type);
	void Inject_Template_Into_Member_Function_Fetcher(int& i);

	//Comment hazard
	//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	void Combine_Comment(int i);
	void Remove_All_Excess_Comments(int i);

	//PATTERNS
	//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	void Definition_Pattern(int i);								//test ptr a
	void Constructor_Pattern(int i);							//foo ptr foo(foo ptr){..}
	void Prototype_Pattern(int i);								//int main()\n
	void Import_Pattern(int i);									//import func new(int amount)\n
	void Object_Pattern(int i);									//a
	void Parenthesis_Pattern(int i);							//(a + a) * b
	void Math_Pattern(int& i, vector<string> Operator, int Flag, bool Change_Index = false);			//a = b + c * d, a.b.c.d()
	void Number_Pattern(int i);									//123
	void String_Pattern(int i);									//"abc"
	void Operator_PreFix_Pattern(int i, vector<string> Prefix);	//++a/--b()
	void Operator_PostFix_Pattern(int i, vector<string> Postfix);//a++/b()--
	void Variable_Negate_Pattern(int i);						//-a, -b()
	void Callation_Pattern(int i);								//b(a, b, c, d)
	void Array_Pattern(int i);									//a[1]/b[a]
	void Function_Pattern(int i);								//func int ptr f(int x) {..}
	void Type_Pattern(int i);									//type [inheritted] foo{member 1,}
	void Member_Pattern(int i);									//Dot operator is in Operator_Pattern()
	void If_Pattern(int i);										//patternises the condition nodes
	void Else_Pattern(int i);
	void Return_Pattern(int i);									//return 1/ return;
	void Jump_Pattern(int i);									//jump test
	void Label_Pattern(int i);
	void Label_Definition(int i);
	void Size_Pattern(int i);									//if (contidion){..}
	void Format_Pattern(int i);									//format = decimal
	void Member_Function_Pattern(int i);						//return_type class_name.funcname(){}
	//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	//Pattern Users
	void Operator_Order();
	void Factory();
private:
};

#endif
