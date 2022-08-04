#ifndef _TOKEN_H_
#define _TOKEN_H_
#include "../Flags.h"
#include "Node.h"

#include <string>
#include <vector>

using namespace std;

//memory(handle, operator(offsetter), num(12))
class Token{
public:

	string Name = "";

	long long Flags = 0;
	int Life_Span = 0;
	int Size = 0;
	bool Has_Floating_Point_Value = false;
	vector<pair<Token*, int>> Resources;
	vector<vector<pair<Token*, pair<int, int>>>> Combinations;

	Node* Parent = nullptr;
	string OG = "";	//REG_a_Parameter og is a
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

	Token* ID = nullptr;
	unsigned char XReg = 0;
	union{
		//X86_64
		
	};
	//for tokens
	Token(const Token& t, long long f) { *this = t; Flags = f; }
	Token(const Token& t, int s) { *this = t; Size = s; }
	Token(long long f) : Flags(f) {}
	Token(Node* n, bool Skip_Needed_Address_Protocol = false);
	Token(long long f, int s) : Flags(f), Size(s) {}
	Token(long long f, string n) : Flags(f), Name(n) {}
	Token(long long f, string n, vector<Token*> Param) : Flags(f), Name(n), Parameters(Param) {}
	Token(long long f, string n, int s) : Flags(f), Name(n), Size(s) {}
	Token(long long f, string n, int s, Node* Scope) : Flags(f), Name(n), Size(s), Parent(Scope) {}
	Token(long long f, string n, int s, vector<Token*> c, unsigned char xreg = 0) : Flags(f), Name(n), Size(s), Childs(c), XReg(xreg) {
		if (!Has({TOKEN::NONVOLATILE, TOKEN::VOLATILE, TOKEN::QUOTIENT, TOKEN::REMAINDER, TOKEN::RETURNING, TOKEN::PARAMETER}))
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
	Token(long long f, vector<Token*> c, int s, string n, Node* p) : Flags(f), Childs(c), Size(s), Name(n), Parent(p) {}
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
	bool is(vector<long long> f) {
		for (auto i : f)
			if (!is(i))
				return false;
		return true;
	}
	bool Any(long long flags){return (Flags & flags) != 0;}
	void add(long long flag){this->Flags |= flag;}
	void remove(long long flag){this->Flags ^= (Flags & flag);}
	int Get_Size() { return Size; }
	long long Get_Flags() { return Flags; }
	void Set_Flags(long long f) { Flags = f; }
	string Get_Name() { 
		if (this->is(TOKEN::MEMORY))
			if (Childs[0]->is(TOKEN::OFFSETTER) || Childs[0]->is(TOKEN::DEOFFSETTER))
				return Childs[0]->Left->Get_Name() + "_" + Childs[0]->Right->Get_Name();
			else
				return Childs[0]->Name;
		return Name;
	}
	void Set_Name(string n) { Name = n; }
	void Set_Parent(Node* p) { Parent = p; }
	void Set_Size(int s) { Size = s; }
	Node* Get_Parent() { return Parent; }
	Token* Get_Size_Parent(int s, Token* t) {
		if (t->Get_Size() == s)
			return t;
		//for (auto i : t->Childs)
		//	if (Get_Size_Parent(s, i) != nullptr)
		//		return Get_Size_Parent(s, i);
		if (t->Holder != nullptr)
			return Get_Size_Parent(s, t->Holder);
		return nullptr;
	}
	vector<Token*> Get_Connected_Registers(Token* r) {
		vector<Token*> Result;
		Token* tmp_parent = r->Holder;
		while (tmp_parent != nullptr) {
			Result.push_back(tmp_parent);
			tmp_parent = tmp_parent->Holder;
		}
		vector<Token*> tmp = Get_All_Childs(r);
		Result.insert(Result.end(), tmp.begin(), tmp.end());
		return Result;
	}
	vector<Token*> Get_All_Childs(Token* r) {
		vector<Token*> Result;
		Result.push_back(r);
		for (auto i : r->Childs) {
			vector<Token*> tmp = Get_All_Childs(i);
			Result.insert(Result.end(), tmp.begin(), tmp.end());
		}
		return Result;
	}
	bool Has(long long F) {
		if (is(F))
			return true;
		for (auto i : Childs)
			return i->Has(F);
		if (Left != nullptr && Left->Has(F))
			return true;
		if (Right != nullptr && Right->Has(F))
			return true;
		return false;
	}
	bool Has(vector<long long> F) {
		for (auto i : F) {
			if (Has(i))
				return true;
		}
		return false;
	}
	vector<Token*> Get_All(vector<long long> F);
	vector<Token*> Get_All(long long F);
	vector<Token*> Get_All();

	unsigned char Get_MODRM_Type();

	class SIB Get_SIB();
};

#endif