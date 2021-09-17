#ifndef __SAFE_H__
#define __SAFE_H__

#include "../Nodes/Node.h"
#include "../Lexer/Position.h"
#include <vector>
#include <string>
#include <iostream>
#undef ERROR

using namespace std;

enum MSG_Type {
	NORMAL,
	ERROR,
	WARNING,
	SOLUTION,
	INFO,
	FAIL,
	SUCCESS,
};

#define ERROR (MSG_Type)1

class Observation {
public:
	Observation(MSG_Type t, string msg, Position p) {
		//External message request.
		Type = t;
		Msg = msg;
		Pos = p;
	}

	Observation(MSG_Type t, string msg) {
		//External message request.
		Type = t;
		Msg = msg;
		Pos = Position(-1, -1);
	}

	Observation(Observation& O, bool Dont_Stop) {
		*this = O;
		this->Dont_Stop = Dont_Stop;
	}

	void Report();
	MSG_Type Type = NORMAL;
private:
	Position Pos;
	string Msg = "";
	bool Dont_Stop = false;
};

class Lexer_Expectation_Set;
class Components;
class Back_Expectation_Set;
class Base;

extern const string Red;
extern const string Green;
extern const string Yellow;
extern const string Blue;
extern const string Magenta;
extern const string Cyan;
extern const string White;
extern const string Reset;

void Report(Observation o);
void Report(vector<Observation> o);
void Report(long type, Lexer_Expectation_Set expectation, string source, vector<Component> result);
void Report(long type, Back_Expectation_Set expectation, string source, vector<Base*> result);

class Safe {
public:
	Safe(vector<Node*> i) : Input(i) { Factory(); }
	Safe(){}
	//single uses
	void Check_For_Undefined_Inheritance(Node* n);

private:
	void Factory();
	void Check_Return_Validity(Node* n);
	void Disable_Non_Ptr_Class_Return(Node* n);
	void Check_For_Unitialized_Objects(Node* func);
	void Warn_Usage_Of_Depricated(Node* n);
	void Prefer_Class_Cast_Rather_Object_Cast(Node* n);
	void Warn_Usage_Before_Definition(Node* n);
	vector<Node*> Input;
};

#endif