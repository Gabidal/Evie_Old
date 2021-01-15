#ifndef _TEST_LEXER_H_
#define _TEST_LEXER_H_

#include "../../H/Lexer/Lexer.h"

#include <string>
#include <iostream>
using namespace std;

constexpr long NO_ORDER = 1 << 0;
constexpr long NO_NAMES = 1 << 1;

enum Types{
	INFO,
	EXPECTATION
};

class Base {
public: 
	Types Type;
	Base(Types t) : Type(t){}
};

class Info : public Base {
public:
	string Val = "";
	long F = 0;
	Info(initializer_list<pair<long, string>> l) : Base(INFO) {
		Val = l.begin()->second;
		F = l.begin()->first;
	}
	Info(pair<long, string> l) : Base(INFO) {
		Val = l.second;
		F = l.first;
	}
};

class Lexer_Expectation : public Base {
public:
	vector<Component> Expecations;
	vector<Lexer_Expectation> Childs;
	long Flags = 0;
	bool has(long f) { return (Flags & f) == f; }
	Lexer_Expectation(long F, vector<Component> E) : Base(EXPECTATION), Flags(F), Expecations(E) {}
	Lexer_Expectation(long F, vector<long> E) : Base(EXPECTATION), Flags(F) {
		for (auto i : E)
			Expecations.push_back(Component("", i));
	}
	Lexer_Expectation(vector<long> E) : Base(EXPECTATION) {
		for (auto i : E)
			Expecations.push_back(Component("", i));
		Flags = NO_NAMES;
	}
	Lexer_Expectation(initializer_list<pair<long, Component>> l) : Base(EXPECTATION) {
		Flags = l.begin()->first;
		Expecations.push_back(l.begin()->second);
	}
	Lexer_Expectation(initializer_list<pair<long, vector<Component>>> l) : Base(EXPECTATION) {
		Flags = l.begin()->first;
		Expecations = l.begin()->second;
	}
	Lexer_Expectation(initializer_list<long> l) : Base(EXPECTATION) {
		Flags = NO_NAMES | NO_ORDER;
		Expecations.push_back(Component("", *l.begin()));
	}
	Lexer_Expectation(initializer_list<vector<long>> l) : Base(EXPECTATION) {
		Flags = NO_NAMES | NO_ORDER;
		for (auto i : *l.begin())
			Expecations.push_back(Component("", i));
	}
	Lexer_Expectation(initializer_list<vector<pair<long, string>>> l) : Base(EXPECTATION) {
		Flags = NO_ORDER;
		for (auto i : *l.begin())
			Expecations.push_back(Component(i.second, i.first));
	}
	Lexer_Expectation(initializer_list<vector<Base*>> l) : Base(EXPECTATION) {
		Flags = NO_ORDER;
		for (auto& i : *l.begin()) {
			if (i->Type == EXPECTATION)
				Childs.push_back((Lexer_Expectation&)*i);
			else if (i->Type == INFO)
				Expecations.push_back(Component(((Info&)*i).Val, ((Info&)*i).F));
		}

	}
	Lexer_Expectation(vector<Lexer_Expectation> l, long f) : Base(EXPECTATION) {
		Flags = f;
		for (auto i : l) {
			Expecations.insert(Expecations.end(), i.Expecations.begin(), i.Expecations.end());
		}
	}
	string Get_Name(Component c) {
		if (has(NO_NAMES))
			return c.Transform(c.Flags);
		else
			return c.Value;
	}
	string Get_Name(int i) {
		if (has(NO_NAMES))
			return Expecations[i].Transform(Expecations[i].Flags);
		else
			return Expecations[i].Value;
	}
};

class Lexer_Test {
private:
	vector<pair<Lexer_Expectation, string>> Tests;
	vector<Component> Run(string);
	void Factory();
	void Check_Assert(Lexer_Expectation expectation, string s);
	bool Check_Assert(Lexer_Expectation expectation, Component a, string s);
	bool Check_Assert(long F, Component a, Component b);
	bool is(long f1, long f2)
	{
		return (f1 & f2) == f2;
	}
public:
	void Init();
	Lexer_Test(vector<pair<Lexer_Expectation, string>> t) : Tests(t) { Factory(); }
	Lexer_Test() { Init(); Factory(); }
};

#endif