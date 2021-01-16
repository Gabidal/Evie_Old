#ifndef _TEST_LEXER_H_
#define _TEST_LEXER_H_

#include "../../H/Lexer/Lexer.h"
#include "Base.h"

#include <string>
#include <iostream>
using namespace std;

class Lexer_Expectation_Set : public Base {
public:
	vector<Component> Expecations;
	vector<Lexer_Expectation_Set> Childs;
	bool has(long f) { return (F & f) == f; }
	Lexer_Expectation_Set(long f, vector<Component> E) : Base(EXPECTATION, f), Expecations(E) {}
	Lexer_Expectation_Set(long f, vector<long> E) : Base(EXPECTATION, f) {
		for (auto i : E)
			Expecations.push_back(Component("", i));
	}
	Lexer_Expectation_Set(vector<long> E) : Base(EXPECTATION, NO_NAMES) {
		for (auto i : E)
			Expecations.push_back(Component("", i));
	}
	Lexer_Expectation_Set(initializer_list<pair<long, Component>> l) : Base(EXPECTATION, l.begin()->first) {
		Expecations.push_back(l.begin()->second);
	}
	Lexer_Expectation_Set(initializer_list<pair<long, vector<Component>>> l) : Base(EXPECTATION, l.begin()->first) {
		Expecations = l.begin()->second;
	}
	Lexer_Expectation_Set(initializer_list<long> l) : Base(EXPECTATION, NO_NAMES | NO_ORDER) {
		Expecations.push_back(Component("", *l.begin()));
	}
	Lexer_Expectation_Set(initializer_list<vector<long>> l) : Base(EXPECTATION, NO_NAMES | NO_ORDER) {
		for (auto i : *l.begin())
			Expecations.push_back(Component("", i));
	}
	Lexer_Expectation_Set(initializer_list<vector<pair<long, string>>> l) : Base(EXPECTATION, NO_ORDER) {
		for (auto i : *l.begin())
			Expecations.push_back(Component(i.second, i.first));
	}
	Lexer_Expectation_Set(initializer_list<vector<Base*>> l) : Base(EXPECTATION, NO_ORDER) {
		for (auto& i : *l.begin()) {
			if (i->Type == EXPECTATION)
				Childs.push_back((Lexer_Expectation_Set&)*i);
			else if (i->Type == TEXT_INFO)
				Expecations.push_back(Component(((Text_Info&)*i).Val, ((Text_Info&)*i).F));
		}

	}
	Lexer_Expectation_Set(vector<Lexer_Expectation_Set> l, long f) : Base(EXPECTATION, f) {
		for (auto i : l) {
			Expecations.insert(Expecations.end(), i.Expecations.begin(), i.Expecations.end());
		}
	}
	string Get_Name(Component c) {
		if (has(NO_NAMES))
			return Transform(c.Flags);
		else
			return c.Value;
	}
	string Get_Name(int i) {
		if (has(NO_NAMES))
			return Transform(Expecations[i].Flags);
		else
			return Expecations[i].Value;
	}
};

class Lexer_Test {
private:
	vector<pair<Lexer_Expectation_Set, string>> Tests;
	vector<Component> Run(string);
	void Factory();
	void Check_Assert(Lexer_Expectation_Set expectation, string s);
	bool Check_Assert(Lexer_Expectation_Set expectation, Component a, string s);
	bool Check_Assert(long F, Component a, Component b);
	bool is(long f1, long f2)
	{
		return (f1 & f2) == f2;
	}
public:
	void Init();
	Lexer_Test(vector<pair<Lexer_Expectation_Set, string>> t) : Tests(t) { Factory(); }
	Lexer_Test() { Init(); Factory(); }
};

#endif