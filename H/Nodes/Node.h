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

	bool is(int F) {
		return Type == F;
	}
	
	int is(string t) {
		for (int i = 0; i < Inheritted.size(); i++)
			if (t == Inheritted[i])
				return i;
		return -1;
	}
	
	string Get_Mangled_Name() {
		//_int_ptr_Z6banana_int_int_short
		string mname = "";
		//add the returning type
		for (auto i : Inheritted)
			mname += "_" + i;
		mname += "_" + Name;
		for (auto i : Parameters)
			mname += "__" + i->Get_Inheritted("_");
		return mname;
	}
	
	string Get_Inheritted(string seperator) {
		if (is(NUMBER_NODE)) {
			//1.29348
			if (find(Name.begin(), Name.end(), '.') != Name.end()) {
				if ((Name.end() - find(Name.begin(), Name.end(), '.')) <= 7)
					return Find(4, Parent)->Get_Inheritted(seperator);
				else 
					return Find(8, Parent)->Get_Inheritted(seperator);
			}
			else {
				return Find(_SYSTEM_BIT_SIZE_, Parent)->Get_Inheritted(seperator);
			}
		}
		else {
			string result = "";
			for (int i = 0; i < Inheritted.size() - 1; i++) {
				result += Inheritted[i] + seperator;
			}
			return result + Inheritted.back();
		}
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
	
	Node* Un_Mangle(string raw) {
		Node* Result = new Node(FUNCTION_NODE);
		//type ptr new  type
		regex r("_Z[0-9]+");
		smatch match;
		if (regex_match(raw, match, r)) {
			//C++ unmangler
			//_Z3NEWi3ABC
			bool Func_Name = true;
			string Current;
			vector<string> Current_Parameter;
			for (int i = 2; i < raw.size(); i++) {
				if		(raw[i] == 'P') {
					Current_Parameter.push_back("ptr");
					continue;
				}
				else if (raw[i] == 'R') {
					Current_Parameter.push_back("ref");
					continue;
				}
				else if (raw[i] == 'c') {
					Result->Parameters.push_back(new Node(*Find(1, this)));
					Append(Result->Parameters.back()->Inheritted, Current_Parameter);
					Current_Parameter.clear();
				}
				else if (raw[i] == 's') {
					Result->Parameters.push_back(new Node(*Find(2, this)));
					Append(Result->Parameters.back()->Inheritted, Current_Parameter);
					Current_Parameter.clear();
				}
				else if (raw[i] == 'f') {
					Result->Parameters.push_back(new Node(*Find(4, this)));
					Append(Result->Parameters.back()->Inheritted, Current_Parameter);
					Current_Parameter.clear();
				}
				else if (raw[i] == 'i') {
					Result->Parameters.push_back(new Node(*Find(4, this)));
					Append(Result->Parameters.back()->Inheritted, Current_Parameter);
					Current_Parameter.clear();
				}
				else if (raw[i] == 'd') {
					Result->Parameters.push_back(new Node(*Find(8, this)));
					Append(Result->Parameters.back()->Inheritted, Current_Parameter);
					Current_Parameter.clear();
				}

				else if (((raw[i] >= 48) && (raw[i] <= 57))) {
					string tmp = "" + (char)raw[i];
					for (int j = i + 1; j < raw.size(); j++) {
						if (((raw[i] >= 48) && (raw[i] <= 57)))
							tmp += (char)raw[j];
						else
							break;
					}
					int size = atoi(tmp.c_str());
					string name = "";
					for (int j = i + tmp.size(); (j < (size + i)) && j < raw.size(); j++) {
						name += (char)raw[j];
					}
					if (Func_Name) {
						Result->Name = name;
					}
					else {
						Node* p = new Node(OBJECT_DEFINTION_NODE);
						p->Inheritted.push_back(name);
						Append(p->Inheritted, Current_Parameter);
						Current_Parameter.clear();
					}
					i += size;
				}
			}
		}
		else {
			vector<string> Return_type;
			vector<vector<string>> Parameters;
			string Func_Name;
			bool Currently_Return_Type = true;
			string Current;
			vector<string> Current_Parameter_Types;
			for (int i = 0; i < raw.size(); i++) {
				if (raw[i] == ' ') {
					if (!(i + 1 > raw.size()) && (raw[i + 1] == ' ')) {
						//__
						if (Currently_Return_Type) {
							Currently_Return_Type = false;
							Func_Name = Return_type.back();
							Return_type.pop_back();
						}
						else {
							Parameters.push_back(Current_Parameter_Types);
							Current_Parameter_Types.clear();
						}
					}
					else {
						//_
						if (Currently_Return_Type) {
							Return_type.push_back(Current);
							Current = "";
						}
						else {
							Current_Parameter_Types.push_back(Current);
							Current = "";
						}
					}
				}
				else {
					Current += raw[i];
				}
			}
			if (Currently_Return_Type) {
				Func_Name = Current;
			}
			int i = 0;
			for (auto i : Parameters) {
				Node* p = new Node(OBJECT_DEFINTION_NODE);
				p->Inheritted = i;
				Result->Parameters.push_back(p);
			}
			Result->Name = Func_Name;
			Result->Inheritted = Return_type;
		}
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
		if (parent != nullptr)
			return Find(size, parent->Parent);
		return nullptr;
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
	
	void Update_Size() {
		for (Node* m : Defined) {
			//gather member variables
			m->Update_Size();
			Size += m->Size;
		}
		if (is("ptr")) {
			Scaler = Size;
			Size = _SYSTEM_BIT_SIZE_;
		}
		return;
	}

	/*void Update_Members_Size() {
		if (Name != "_SIZE_")
			Size = 0;
		for (auto i : Defined) {
			if (i->Name != "_SIZE_")
				i->Size = 0;
			//this needs maybe revamping?
			for (string s : i->Inheritted) {
				if (Lexer::GetComponents(s)[0].is(Flags::KEYWORD_COMPONENT))
					continue;
				i->Size += Find(s, i->Parent, true)->Size;
			}
			i->Update_Size();
			//-----------------------------
		}
		Update_Size();
	}*/

	void Update_Members_Size() {
		if (Name != "_SIZE_")
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
	Node* Copy_Node(Node* What_Node)
	{
		if (What_Node == nullptr)
			return nullptr;
		//this will only copy the ptrs in list but we want to also copy what those ptr point to.
		Node* Result = new Node(*What_Node);

		//lets start from defined
		for (int i = 0; i < Result->Defined.size(); i++)
			Result->Defined[i] = Copy_Node(Result->Defined[i]);

		for (int i = 0; i < Result->Childs.size(); i++)
			Result->Childs[i] = Copy_Node(Result->Childs[i]);

		for (int i = 0; i < Result->Member_Functions.size(); i++)
			Result->Member_Functions[i] = Copy_Node(Result->Member_Functions[i]);

		for (int i = 0; i < Result->Operator_Overloads.size(); i++)
			Result->Operator_Overloads[i] = Copy_Node(Result->Operator_Overloads[i]);

		for (int i = 0; i < Result->Parameters.size(); i++)
			Result->Parameters[i] = Copy_Node(Result->Parameters[i]);

		Result->Left = Copy_Node(Result->Left);
		Result->Right = Copy_Node(Result->Right);

		Result->Succsessor = Copy_Node(Result->Succsessor);
		Result->Predecessor = Copy_Node(Result->Predecessor);

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

	template<typename T>
	void Append(vector<T>& d, vector<T> s) {
		for (int i = 0; i < s.size(); i++)
			d.push_back(s[i]);
		return;
	}
};

#endif