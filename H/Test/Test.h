#ifndef _TEST_H_
#define _TEST_H_

#include "../Lexer/Lexer.h"

#include <string>
#include <iostream>
using namespace std;

constexpr long NO_ORDER = 1 << 0;
constexpr long NO_NAMES = 1 << 1;

class Lexer_Expectation {
public:
	vector<Component> Expecations;
	long Flags = 0;
	bool has(long f) { return (Flags & f) == f; }
	Lexer_Expectation(long F, vector<Component> E) : Flags(F), Expecations(E) {}
	Lexer_Expectation(long F, vector<long> E) : Flags(F) {
		for (auto i : E)
			Expecations.push_back(Component("", i));
	}
	Lexer_Expectation(vector<long> E) {
		for (auto i : E)
			Expecations.push_back(Component("", i));
		Flags = NO_NAMES;
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
	bool Check_Assert(long F, Component a, Component b);
public:
	Lexer_Test(vector<pair<Lexer_Expectation, string>> t) : Tests(t) { Factory(); }
};

#endif