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
	int Coefficient = 0;
	Node* Current_Value = nullptr;
	bool Inlined = false;

	bool is(int F) {
		return Type == F;
	}
	int is(string t) {
		for (int i = 0; i < Inheritted.size(); i++)
			if (t == Inheritted[i])
				return i;
		return false;
	}
	string Get_Mangled_Name() {
		//_int_ptr_Z6banana_int_int_short
		string mname = "";
		//add the returning type
		for (auto i : Inheritted)
			mname += "_" + i;
		mname += "_Z" + to_string(Name.size()) + Name;
		for (auto i : Parameters)
			mname += "__" + i->Get_Inheritted("_");
		return mname;
	}
	string Get_Inheritted(string seperator) {
		string result = "";
		for (int i = 0; i < Inheritted.size() - 1; i++) {
			result += Inheritted[i] + seperator;
		}
		return result + Inheritted.back();
	}
	Node* Un_Mangle(string raw) {
		//TODO!!
		//_int_ptr_Z6banana_int_int_short
		regex r("_Z[0-9]+");
		smatch match;
		if (!regex_match(raw, match, r))
			cout << "Critical Error: " << raw << " didnt contain the start of the name indicator '_Z[0-9]'" << endl;
		int Name_Start = match.position();
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
	void Get_Inheritted_Class_Members() {
		for (string s : Inheritted) {
			if (Lexer::GetComponents(s)[0].is(Flags::KEYWORD_COMPONENT))
				continue;
			if (s == ".")
				continue;
			Node* inheritted = Find(s, Parent);
			for (auto i : inheritted->Defined) {
				//now insert the inheritted classes members
				Defined.push_back(i);
			}
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
	void Update_Members_Size() {
		if (Name != "_SIZE_")
			Size = 0;
		for (auto i : Defined) {
			if (i->Name != "_SIZE_")
				i->Size = 0;
			for (string s : i->Inheritted) {
				if (Lexer::GetComponents(s)[0].is(Flags::KEYWORD_COMPONENT))
					continue;
				i->Size += Find(s, i->Parent, true)->Size;
			}
			i->Update_Size();
		}
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
		//this will only copy the ptrs in list but we want to also copy what those ptr point to.
		Node* Result = new Node(*What_Node);

		//lets start from defined
		for (Node* d : Result->Defined)
			//also define theyre insides
			d = Copy_Node(d);

		for (Node* c : Result->Childs)
			c = Copy_Node(c);

		for (Node* m : Result->Member_Functions)
			m = Copy_Node(m);

		for (Node* o : Result->Operator_Overloads)
			o = Copy_Node(o);

		for (Node* p : Result->Parameters)
			p = Copy_Node(p);

		Result->Left = Copy_Node(Result->Left);
		Result->Right = Copy_Node(Result->Right);

		Result->Succsessor = Copy_Node(Result->Succsessor);
		Result->Predecessor = Copy_Node(Result->Predecessor);

		//now we have copyed every ptr into a new base to point.
		return Result;
	}
};

#endif