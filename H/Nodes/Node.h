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
	Node(int t) : Type(t){}
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
	//operator features
	Node* Left = nullptr;
	Node* Right = nullptr;
	//pointter features
	int Scaler = 0;
	//content features
	char Paranthesis_Type = 0;
	

	bool is(int F) {
		return Type == F;
	}
	bool is(string t) {
		for (string s : Inheritted)
			if (t == s)
				return true;
		return false;
	}
	string Get_Mangled_Name() {
		//_int_ptr_Z6banana_int_int_short
		string mname = "";
		//add the returning type
		for (auto i : Inheritted)
			mname += "_" + i;
		mname += "Z" + to_string(Name.size()) + Name;
		for (auto i : Parameters)
			mname += "_" + i->Name;
		return mname;
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
	Node* Find(string name, Node* parent) {
		if (parent == nullptr) {
			cout << "Critical Error: parent is null!" << endl;
			return nullptr;
		}
		for (Node* i : parent->Defined)
			if (i->Name == name)
				return i;
		return Find(name, parent->Parent);
	}
	void Update_Size() {
		Size = 0;
		for (string s : Inheritted) {
			if (Lexer::GetComponents(s)[0].is(Flags::KEYWORD_COMPONENT))
				continue;
			Size += Find(s, Parent)->Size;
		}
		if (is("ptr")) {
			Scaler = Size;
			Size = _SYSTEM_BIT_SIZE_;
		}
		return;
	}
	void Update_Members_Size() {
		for (auto i : Defined)
			i->Update_Size();
	}
	void Update_Members_Mem_Offset() {
		int Offset = 0;
		for (auto i : Defined) {
			i->Memory_Offset = Offset;
			Offset += i->Memory_Offset;
		}
		return;
	}
};

#endif