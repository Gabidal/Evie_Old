#ifndef _BASE_H_
#define _BASE_H_

#include <string>
#include <vector>
#include "../../H/Lexer/Lexer.h"
#include <stdexcept>

using namespace std;

constexpr long NO_ORDER = 1 << 0;
constexpr long NO_NAMES = 1 << 1;

enum Types {
	TEXT_INFO,
	NUMERIC_INFO,
	EXPECTATION
};

class Base {
public:
	Types Type;
	long F = 0;
	Base(Types t, long f) : Type(t), F(f) {}
	string Transform(long f);
};

class Text_Info : public Base {
public:
	string Val = "";
	Text_Info(initializer_list<pair<long, string>> l) : Base(TEXT_INFO, l.begin()->first) {
		Val = l.begin()->second;
	}
	Text_Info(pair<long, string> l) : Base(TEXT_INFO, l.first) {
		Val = l.second;
	}
};

class Numeric_Info : public Base {
public:
	long long Val = 0;
	Numeric_Info(initializer_list<pair<long, long long>> l) : Base(NUMERIC_INFO, l.begin()->first) {
		Val = l.begin()->second;
	}
	Numeric_Info(initializer_list<long long> l) : Base(NUMERIC_INFO, NO_ORDER) {
		Val = *l.begin();
	}
};

#endif