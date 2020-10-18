#ifndef _TOKEN_H_
#define _TOKEN_H_
#include "../Flags.h"
#include "Node.h"

#include <string>
#include <vector>

using namespace std;

//memory(handle, operator(offsetter), num(12))
class Token{
private:
	long Flags = 0;
	int Life_Span = 0;
	int Size = 0;
	string Name;
	vector<Token*> Childs;
	vector<pair<Token*, int>> Resources;
	vector<pair<pair<Token*, pair<int, int>>, pair<Token*, pair<int, int>>>> Combinations;

	Node* Parent = nullptr;
public:
	//for tokens
	Token(long f) : Flags(f) {}
	Token(Node* n) {
		if (n->is(OBJECT_NODE) || n->is(OBJECT_DEFINTION_NODE))
			Flags = TOKEN::MEMORY;
		else if (n->is(NUMBER_NODE)) {
			if (n->Is_Decimal())
				Flags = TOKEN::DECIMAL;
			else
				Flags = TOKEN::NUM;
		}
		else
			return;
		Size = n->Size;
		Name = n->Name;
		Parent = n->Parent;
	}
	Token(long f, int s) : Flags(f), Size(s) {}
	Token(long f, string n) : Flags(f), Name(n) {}
	Token(long f, string n, int s) : Flags(f), Name(n), Size(s) {}
	Token(long f, string n, int s, vector<Token*> c) : Flags(f), Name(n), Size(s), Childs(c) {}

	Token(long f, vector<Token*> c) : Flags(f), Childs(c){}
	Token(long f, vector<pair<Token*, int>> Res) : Flags(f), Resources(Res) {}
	Token(long f, vector<pair<pair<Token*, pair<int, int>>, pair<Token*, pair<int, int>>>> comb) : Flags(f), Combinations(comb){}

	Token* Get_Child(int s) {
		if (this->Size != s)
			return Childs[0]->Get_Child(s);
		return nullptr;
	}
	bool is(int flag){return (Flags & flag) == flag;}
	bool Any(int flags){return (Flags & flags) != 0;}
	void add(int flag){this->Flags |= flag;}
	void remove(int flag){this->Flags ^= (Flags & flag);}
	void add(vector<Token*> args) { Childs = args; }
	int Get_Size() { return Size; }
	string Get_Name() { return Name; }
	void Se_Parent(Node* p) { Parent = p; }
	Node* Get_Parent() { return Parent; }
};

#endif