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
	long long Flags = 0;
	int Life_Span = 0;
	int Size = 0;
	bool Has_Floating_Point_Value = false;
	string Name = "";
	string OG = "";	//REG_a_Parameter og is a
	vector<pair<Token*, int>> Resources;
	vector<vector<pair<Token*, pair<int, int>>>> Combinations;

	Node* Parent = nullptr;
public:
	//for return
	bool Is_Initted = false;
	//for register parents
	Token* Holder = nullptr;
	//for parameters
	int Parameter_Index = -1;
	//for numeric or something elses usable types.
	vector<Token*> Usable_Types;
	//for memory
	vector<Token*> Childs;	//here resides registers, constants, scalers, offsetters.
	//for call handling
	vector<Token*> Parameters;	//this contains information about the parameters.
	//scaler/offsetter
	Token* Left = nullptr;
	Token* Right = nullptr;

	string ID = "";
	//for tokens
	Token(const Token& t, long long f) { *this = t; Flags = f; }
	Token(const Token& t, int s) { *this = t; Size = s; }
	Token(long f) : Flags(f) {}
	Token(Node* n);
	Token(long long f, int s) : Flags(f), Size(s) {}
	Token(long long f, string n) : Flags(f), Name(n) {}
	Token(long long f, string n, vector<Token*> Param) : Flags(f), Name(n), Parameters(Param) {}
	Token(long long f, string n, int s) : Flags(f), Name(n), Size(s) {}
	Token(long long f, string n, int s, vector<Token*> c) : Flags(f), Name(n), Size(s), Childs(c) {
		if (!is(TOKEN::REGISTER) && !is(TOKEN::VOLATILE) && !is(TOKEN::NONVOLATILE) && !is(TOKEN::RETURNING))
			return;
		for (auto i : Childs) {
			i->Holder = this;
		}
	}
	Token(long long f, string n, Token* L, Token* R) : Flags(f), Name(n), Left(L), Right(R){}

	Token(long long f, string n, string o) : Flags(f), Name(n), OG(o) {}
	Token(long long f, string n, string o, vector<Token*> Param) : Flags(f), Name(n), Parameters(Param), OG(o) {}
	Token(long long f, string n, string o, int s) : Flags(f), Name(n), Size(s), OG(o) {}
	Token(long long f, string n, string o, int s, vector<Token*> c) : Flags(f), Name(n), Size(s), Childs(c), OG(o) {
		if (!is(TOKEN::REGISTER) && !is(TOKEN::VOLATILE) && !is(TOKEN::NONVOLATILE) && !is(TOKEN::RETURNING))
			return;
		for (auto i : Childs) {
			i->Holder = this;
		}
	}
	
	Token(long long f, vector<Token*> c) : Flags(f), Childs(c) {}
	Token(long long f, vector<Token*> c, int s) : Flags(f), Childs(c), Size(s) {}
	Token(long long f, vector<Token*> c, int s, string n) : Flags(f), Childs(c), Size(s), Name(n) {}
	Token(long long f, vector<Token*> ut, string id) : Flags(f), Usable_Types(ut), Name(id) {}

	Token(long long f, vector<pair<Token*, int>> Res) : Flags(f), Resources(Res) {}
	Token(long long f, vector<pair<Token*, int>> Res, string id) : Flags(f), Resources(Res), Name(id) {}

	Token(long long f, vector<vector<pair<Token*, pair<int, int>>>> comb) : Flags(f), Combinations(comb){}

	Token* Get_Child(int s) {
		if (this->Size != s)
			return Childs[0]->Get_Child(s);
		return nullptr;
	}
	vector<Token*>* Get_Childs() { return &Childs; }
	bool is(long long flag){return (Flags & flag) == flag;}
	bool Any(long long flags){return (Flags & flags) != 0;}
	void add(long long flag){this->Flags |= flag;}
	void remove(long long flag){this->Flags ^= (Flags & flag);}
	int Get_Size() { return Size; }
	long long Get_Flags() { return Flags; }
	string Get_Name() { if (this->is(TOKEN::MEMORY))return Childs[0]->Name; return Name; }
	void Set_Name(string n) { Name = n; }
	void Set_Parent(Node* p) { Parent = p; }
	void Set_Size(int s) { Size = s; }
	Node* Get_Parent() { return Parent; }
	Token* Get_Size_Parent(int s, Token* t) {
		if (t->Get_Size() == s)
			return t;
		if (t->Holder != nullptr)
			return Get_Size_Parent(s, t->Holder);
		return nullptr;
	}
};

#endif