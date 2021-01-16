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
	Back_Expectation_Set() : Base(EXPECTATION, 0) {
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
	Back_End_Test() { Init(); Factory(); }
};

#endif