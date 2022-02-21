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

inline string SYNTAX_ERROR = "Syntax error";
inline string DEFINITION_ERROR = "Definition error";

#define ERROR (MSG_Type)1

class Observation {
public:
	Observation(MSG_Type t, string msg, Position p, string cause = "", bool dont_stop = true) {
		//External message request.
		Type = t;
		Msg = msg;
		Pos = p;
		Cause = cause;
		Dont_Stop = dont_stop;

		if (cause == "")
			Cause = Msg;

		if (Type == ERROR || Type == FAIL)
			Dont_Stop = false;
	}

	Observation(MSG_Type t, string msg, string cause = "", bool dont_stop = true) {
		//External message request.
		Type = t;
		Msg = msg;
		Pos = Position(-1, -1);
		Cause = cause;
		Dont_Stop = dont_stop;

		if (cause == "")
			Cause = Msg;

		if (Type == ERROR || Type == FAIL)
			Dont_Stop = false;
	}

	Observation(Observation& O, bool Dont_Stop) {
		*this = O;
		this->Dont_Stop = Dont_Stop;
	}

	void Report(bool last = true);
	MSG_Type Type = NORMAL;
private:
	Position Pos;
	string Msg = "";
	string Cause = "";
	bool Dont_Stop = true;
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
	Safe(vector<Node*> i) : Input(i) { PostProsessor_Factory(); }
	Safe(){}
	//single uses
	void Check_For_Undefined_Inheritance(Node* n);

	void Parser_Factory();
private:
	void PostProsessor_Factory();
	void Check_Return_Validity(Node* n);
	void Disable_Non_Ptr_Class_Return(Node* n);
	void Check_For_Unitialized_Objects(Node* func);
	void Warn_Usage_Of_Depricated(Node* n);
	void Prefer_Class_Cast_Rather_Object_Cast(Node* n);
	void Warn_Usage_Before_Definition(Node* n);

	void Start_Check_Usage_Of_Un_Declared_Variable();
	static void Check_Usage_Of_Un_Declared_Variable(Node*& n);

	void Reference_Count_Type_Un_Availability();
	vector<Node*> Input;
};

#endif