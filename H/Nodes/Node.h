#ifndef _NODE_H_
#define _NODE_H_

extern int _SYSTEM_BIT_SIZE_;

#include <string>
#include <vector>
#include <iostream>
#include <regex>

#include "../Lexer/Lexer.h"

using namespace std;

class Node {
public:
	Node(int flag) : Type(flag){}
	//Node(){}
	//Normal features
	string Name = "";
	int Type = 0;
	int Size = 0;
	int Memory_Offset = 0;
	vector<string> Inheritted;
	Node* Parent = nullptr;
	//funciton inlining features
	vector<Node*> Header;
	//Scope features
	vector<Node*> Defined;
	vector<Node*> Childs;
	vector<Node*> Member_Functions;
	vector<Node*> Operator_Overloads;
	//function features
	vector<Node*> Parameters;
	string Mangled_Name = "";
	//operator features
	Node* Left = nullptr;
	Node* Right = nullptr;
	//pointter features
	int Scaler = 0;
	//content features
	char Paranthesis_Type = 0;
	//condition features
	Node* Succsessor = nullptr;
	Node* Predecessor = nullptr;
	//algebra optimizer features
	int Order = 0;
	int Coefficient = 1;
	Node* Current_Value = nullptr;
	bool Inlined = false;
	//fetching features
	Node* Fetcher = nullptr;
	//calling features
	Node* Template_Function = nullptr;
	string Calling_Convention = "";
	//function prototype features
	//the import has the flag to prototyping
	//and the paramters are Named as the size needed. thx!

	bool is(int F) {
		return Type == F;
	}
	
	int is(string t) {
		for (int i = 0; i < Inheritted.size(); i++)
			if (t == Inheritted[i])
				return i;
		return -1;
	}
	
	string Get_Inheritted(string seperator, bool Dirent_Type = false, bool Skip_Prefixes = false) {
		if (Dirent_Type) {
			return Name;
		}
		else if (is(NUMBER_NODE)) {
			//1.29348
			if (find(Name.begin(), Name.end(), '.') != Name.end()) {
				if ((Name.end() - find(Name.begin(), Name.end(), '.')) <= 7)
					return Find(4, Parent)->Get_Inheritted(seperator);
				else 
					return Find(8, Parent)->Get_Inheritted(seperator);
			}
			else {
				if (atoll(Name.c_str()) > INT_MAX) {
					return Find(8, Parent)->Get_Inheritted(seperator);
				}
				return Find(4, Parent)->Get_Inheritted(seperator);
			}
		}
		else {
			string result = "";
			for (int i = 0; i < Inheritted.size(); i++) {
				if (Skip_Prefixes && ((Inheritted[i] == "ptr") || (Inheritted[i] == "ref")))
					continue;
				result += seperator + Inheritted[i] ;
			}
			return result;
		}
	}

	string Get_Mangled_Name(bool Skip_Prefixes = false, bool Skip_Return_Type = false) {
		//_int_ptr_Z6banana_int_int_short
		string mname = "";
		//add the returning type
		if (!Skip_Return_Type)
			for (auto i : Inheritted)
				mname += "_" + i;
		mname += "_" + Name;
		for (auto i : Parameters)
			mname += "_" + i->Get_Inheritted("_", is(PROTOTYPE), Skip_Prefixes);
		return mname;
	}

	string Un_Mangle(Node* n) {
		string Result;
		for (string s : n->Inheritted)
			Result += s + " ";
		Result += n->Name + "(";
		for (Node* p : n->Parameters)
			for (string s : p->Inheritted)
				Result += s + ", ";
		Result += ")\n";
		return Result;
	}
	
	//returns atm: Cpp, Evie
	string Get_Calling_Convention_Type(string raw) {
		if (raw[0] == '_') {
			if (raw[1] == 'Z')
				return "Cpp";
			if (raw[1] == 'E')
				return "Evie";
		}
		return "UNKNOWN";
	}

	vector<Component> Un_Mangle(string raw) {
		Component Function = Component("", Flags::TEXT_COMPONENT);
		Component Parenthesis = Component("()", Flags::PAREHTHESIS_COMPONENT);
		bool Func_Name = true;
		string Current;
		vector<Component> Current_Parameter_Inheritted;
		//type ptr new  type
		if (raw[0] == '_' && raw[1] == 'Z') {
			//C++ unmangler
			//_Z3NEWi3ABC
			for (int i = 2; i < raw.size(); i++) {
				if		(raw[i] == 'P') {
					Component ptr = Component("ptr", Flags::KEYWORD_COMPONENT);
					Current_Parameter_Inheritted.push_back(ptr);
					continue;
				}
				else if (raw[i] == 'R') {
					Component ref = Component("ref", Flags::KEYWORD_COMPONENT);
					Current_Parameter_Inheritted.push_back(ref);
					continue;
				}
				else if (raw[i] == 'c') {
					//because there is nothign defined yet we want to preserve these datas for later definition.
					Component p = Component("1", Flags::NUMBER_COMPONENT);
					p.Components = Current_Parameter_Inheritted;
					Current_Parameter_Inheritted.clear();
					Parenthesis.Components.push_back(p);
				}
				else if (raw[i] == 's') {
					Component p = Component("2", Flags::NUMBER_COMPONENT);
					p.Components = Current_Parameter_Inheritted;
					Current_Parameter_Inheritted.clear();
					Parenthesis.Components.push_back(p);
				}
				else if (raw[i] == 'f') {
					Component p = Component("4", Flags::NUMBER_COMPONENT);
					p.Components = Current_Parameter_Inheritted;
					Current_Parameter_Inheritted.clear();
					Parenthesis.Components.push_back(p);
				}
				else if (raw[i] == 'i') {
					Component p = Component("4", Flags::NUMBER_COMPONENT);
					p.Components = Current_Parameter_Inheritted;
					Current_Parameter_Inheritted.clear();
					Parenthesis.Components.push_back(p);
				}
				else if (raw[i] == 'd') {
					Component p = Component("8", Flags::NUMBER_COMPONENT);
					p.Components = Current_Parameter_Inheritted;
					Current_Parameter_Inheritted.clear();
					Parenthesis.Components.push_back(p);
				}

				else if (((raw[i] >= 48) && (raw[i] <= 57))) {
					string tmp = "";
					tmp += raw[i];
					for (int j = i + 1; j < raw.size(); j++) {
						if (((raw[j] >= 48) && (raw[j] <= 57)))
							tmp += (char)raw[j];
						else
							break;
					}
					int size = atoi(tmp.c_str());
					string name = "";
					for (int j = i + tmp.size(); (j < (size + i + 1)) && j < raw.size(); j++) {
						name += (char)raw[j];
					}
					if (Func_Name) {
						Function.Value = name;
						Func_Name = false;
					}
					else {
						//class based parameters.
						Component p = Component(name, Flags::TEXT_COMPONENT);
						p.Components = Current_Parameter_Inheritted;
						Current_Parameter_Inheritted.clear();
						Parenthesis.Components.push_back(p);
					}
					i += size;
				}
			}
		}
		//else if (raw[0] == '_' && raw[1] == 'E') {

		//}
		else {
			//this lauches when no call type is identifyed.
			Function.Value = raw;
		}
		vector<Component> Result = { Function, Parenthesis };
		return Result;
	}
	
	Node* Find(string name, Node* parent, bool Need_Parent_existance = true) {
		if (name == "\n")
			return nullptr;
		if (parent == nullptr && Need_Parent_existance) {
			cout << "Critical Error: parent is null!" << endl;
			return nullptr;
		}
		for (Node* i : parent->Defined)
			if (i->Name == name)
				return i;
		if (parent->Parent != nullptr)
			return Find(name, parent->Parent, Need_Parent_existance);
		return nullptr;
	}
	
	Node* Find(int size, Node* parent) {
		for (Node* i : parent->Defined)
			if (i->Size == size)
				return i;
		if (parent->Parent != nullptr)
			return Find(size, parent->Parent);
		return nullptr;
	}

	Node* Get_Right_Parent() {
		if (Fetcher != nullptr) {
			return Get_Final_Fetcher(this , 1);
		}
		else {
			return Parent;
		}
	}

	vector<string> Tree;
	//a.x.b.y
	Node* Get_Final_Fetcher(Node* n, int offset) {
		Tree.push_back(n->Name);
		if (n->Fetcher != nullptr) {
			return Get_Final_Fetcher(n->Fetcher, offset);
		}

		//now got though the tree and find the right defined in the last that is inside of node* n.
		reverse(Tree.begin(), Tree.end());
		//a.x.b.y
		Node* Result = Find(Tree[0], n->Parent);

		for (int i = 1; i < Tree.size() - offset; i++) {
			Result = Find(Tree[i], Result);
		}
		Tree.clear();
		return Result;
	}

	Node* Get_Most_Left(Node* n) {
		if (n->is(ARRAY_NODE) || n->is(OPERATOR_NODE))
			return Get_Most_Left(n->Left);
		return n;
	}	
	Node* Get_Most_Left() {
		if (this->is(ARRAY_NODE) || this->is(OPERATOR_NODE))
			return this->Left->Get_Most_Left();
		return this;
	}

	bool Locate(string name, vector<Node*> list) {
		for (Node* i : list)
			if (i->Name == name)
				return true;
		return false;
	}
	
	void Get_Inheritted_Class_Members() {
		for (string s : Inheritted) {
			if (Lexer::GetComponents(s)[0].is(Flags::KEYWORD_COMPONENT))
				continue;
			if (s == ".")
				continue;
			Node* inheritted = Find(s, Parent);
			for (auto i : inheritted->Defined) {
				//now insert the inheritted classes members
				if (Locate(i->Name, Defined) != true)
					//if this is already defined no luck trying to re defining the same variable twice :D
					Defined.push_back(i);
			}
		}
	}	
	
	void Get_Inheritted_Class_Members(string s) {
			if (s == ".")
				return;
			Node* inheritted = Find(s, Parent);
			for (auto i : inheritted->Defined) {
				//now insert the inheritted classes members
				if (Locate(i->Name, Defined) != true)
					//if this is already defined no luck trying to re defining the same variable twice :D
					Defined.push_back(i);
			}
	}
	
	//this reqiers that the other local variables inside this object are already having theyre own size!
	void Update_Size() {
		for (Node* m : Defined) {
			//gather member variables
			m->Update_Size();
			Size += m->Size;
		}
		if (is("ptr") != -1) {
			Scaler = Size;
			Size = _SYSTEM_BIT_SIZE_;
		}
		return;
	}

	void Update_Members_Size() {
		if (Name == "_SIZE_")
			return;
		Size = 0;
		//this needs maybe revamping?
		//decide between this forloop and inheritting the members that we inherit
		for (string s : Inheritted) {
			//there is no inheritable type that doesnt have enything init.
			if (Lexer::GetComponents(s)[0].is(Flags::KEYWORD_COMPONENT)) {
				if (s == "func")
					//this is for function pointters.
					Size += _SYSTEM_BIT_SIZE_;
				continue;
			}
			if (Find(s, Parent)->Defined[0]->Name == "_SIZE_")
				//this is a preprossed size, take it!
				Size += Find(s, Parent, true)->Size;
				//if this happends we this class will inherit the members of the inheritted.
			else
				//there we handle more complex inheritance instances.
				Get_Inheritted_Class_Members(s);
		}
		for (Node* i : Defined) {
			//now revaluate the all new and old defined variables.
			i->Update_Members_Size();
		}
		//now apply those revaluated values into us.
		Update_Size();
	}

	void Update_Members_Mem_Offset() {
		int Offset = 0;
		for (auto i : Defined) {
			i->Memory_Offset = Offset;
			Offset += i->Size;
		}
		return;
	}

	Node* Copy_Node(Node* What_Node, Node* p)
	{
		if (What_Node == nullptr)
			return nullptr;
		//this will only copy the ptrs in list but we want to also copy what those ptr point to.
		Node* Result = new Node(*What_Node);
		Result->Parent = p;

		//lets start from defined
		for (int i = 0; i < Result->Defined.size(); i++)
			Result->Defined[i] = Copy_Node(Result->Defined[i], Result);

		for (int i = 0; i < Result->Childs.size(); i++)
			if (Result->is(CONTENT_NODE))
				Result->Childs[i] = Copy_Node(Result->Childs[i], p);
			else
				Result->Childs[i] = Copy_Node(Result->Childs[i], Result);

		for (int i = 0; i < Result->Member_Functions.size(); i++)
			Result->Member_Functions[i] = Copy_Node(Result->Member_Functions[i], Result);

		for (int i = 0; i < Result->Operator_Overloads.size(); i++)
			Result->Operator_Overloads[i] = Copy_Node(Result->Operator_Overloads[i], Result);

		for (int i = 0; i < Result->Parameters.size(); i++)
			if (Result->is(CALL_NODE))
				Result->Parameters[i] = Copy_Node(Result->Parameters[i], p);
			else
				Result->Parameters[i] = Copy_Node(Result->Parameters[i], Result);

		for (int i = 0; i < Result->Header.size(); i++)
			Result->Header[i] = Copy_Node(Result->Header[i], p);

		Result->Left = Copy_Node(Result->Left, p);
		Result->Right = Copy_Node(Result->Right, p);

		Result->Succsessor = Copy_Node(Result->Succsessor, p);
		Result->Predecessor = Copy_Node(Result->Predecessor, p);

		//now we have copyed every ptr into a new base to point.
		return Result;
	}

	vector<Node*> Has(Node* n, int f)
	{
		vector<Node*> Result;
		if (n->is(OPERATOR_NODE)) {
			vector<Node*> left = Has(n->Left, f);
			Result.insert(Result.end(), left.begin(), left.end());

			vector<Node*> right = Has(n->Right, f);
			Result.insert(Result.end(), right.begin(), right.end());
		}

		else if (n->is(CONTENT_NODE)) {
			for (Node* i : n->Childs)
				if (i->is(f))
					Result.push_back(i);
		}


		/*
		//this doesnt work dont use unless must!!
		else if (n->is(CALL_NODE)) {
			for (Node* i : n->Parameters)
				if (i->is(f))
					Result.push_back(i);
		}*/

		if (n->is(f))
			Result.push_back(n);

		return Result;
	}

	vector<Node*> Has(int f) {
		return Has(this, f);
	}

	vector<Node*> Get_all(int f)
	{
		vector<Node*> Result;
		if (Left != nullptr) {
			vector<Node*> left = Left->Get_all(f);
			Result.insert(Result.end(), left.begin(), left.end());
		}
		if (Right != nullptr) {
			vector<Node*> right = Right->Get_all(f);
			Result.insert(Result.end(), right.begin(), right.end());
		}
		if (Succsessor != nullptr) {
			vector<Node*> Succsessors = Succsessor->Get_all(f);
			Result.insert(Result.end(), Succsessors.begin(), Succsessors.end());
		}
		if (Predecessor != nullptr) {
			vector<Node*> Predecessors = Predecessor->Get_all(f);
			Result.insert(Result.end(), Predecessors.begin(), Predecessors.end());
		}
		if (Fetcher != nullptr) {
			vector<Node*> Fetchers = Fetcher->Get_all(f);
			Result.insert(Result.end(), Fetchers.begin(), Fetchers.end());
		}
		for (Node* i : Header) {
			vector<Node*> Headers = i->Get_all(f);
			Result.insert(Result.end(), Headers.begin(), Headers.end());
		}
		for (Node* i : Childs) {
			vector<Node*> childs = i->Get_all(f);
			Result.insert(Result.end(), childs.begin(), childs.end());
		}
		for (Node* i : Parameters) {
			vector<Node*> childs = i->Get_all(f);
			Result.insert(Result.end(), childs.begin(), childs.end());
		}
		for (Node* i : Defined) {
			vector<Node*> childs = i->Get_all(f);
			Result.insert(Result.end(), childs.begin(), childs.end());
		}

		if (is(f))
			Result.push_back(this);

		return Result;
	}

	bool Is_Decimal() {
		if (find(Name.begin(), Name.end(), '.') != Name.end()) {
			return true;
		}
		else {
			return false;
		}
	}

	template<typename T>
	vector<T>& Append(vector<T>& d, vector<T> s) {
		for (int i = 0; i < s.size(); i++)
			d.push_back(s[i]);
		return d;
	}
};

#endif