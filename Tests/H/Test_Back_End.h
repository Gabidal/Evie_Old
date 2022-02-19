#ifndef _TEST_BACK_END_H_
#define _TEST_BACK_END_H_


#include "Base.h"

#include <string>
#include <iostream>
#include <vector>

class Back_Expectation_Set : public Base {
public:
	vector<Base*> Expecations;
	vector<Back_Expectation_Set> Childs;
	bool has(long f) { return (F & f) == f; }
	Back_Expectation_Set(initializer_list<vector<Base*>> l) : Base(EXPECTATION, NO_ORDER) {
		for (auto& i : *l.begin()) {
			if (i->Type == EXPECTATION)
				Childs.push_back((Back_Expectation_Set&)*i);
			else if (i->Type == TEXT_INFO || i->Type == NUMERIC_INFO)
				Expecations.push_back(i);
		}
	}
	Back_Expectation_Set(initializer_list<long long> l) : Base(EXPECTATION, NO_ORDER) {
		Expecations.push_back(new Numeric_Info{ l });
	}
	
	string Get_Name(Base* c) {
		if (has(NO_NAMES))
			return Transform(c->F);
		else {
			if (c->Type == TEXT_INFO)
				return ((Text_Info*)c)->Val;
			else if (c->Type == NUMERIC_INFO)
				return to_string(((Numeric_Info*)c)->Val);
		}
	}
	string Get_Name(int i) {
		return Get_Name(Expecations[i]);
	}
};

class Back_End_Test  {
private:
	string Executable_Location;

	vector<pair<Back_Expectation_Set, string>> Tests;
	vector<Base*> Run(string);
	void Factory();
	void Check_Assert(Back_Expectation_Set expectation, string s);
	bool Check_Assert(Back_Expectation_Set expectation, Base* a, string s);
	bool Check_Assert(long F, Base* a, Base* b);
	int Run_Dll(string f);
	bool is(long f1, long f2)
	{
		return (f1 & f2) == f2;
	}
public:
	void Init();
	Back_End_Test(vector<pair<Back_Expectation_Set, string>> t) : Tests(t) { Factory(); }
	Back_End_Test(string Executable_Location) : Executable_Location(Executable_Location) { Init(); Factory(); }
};

#endif