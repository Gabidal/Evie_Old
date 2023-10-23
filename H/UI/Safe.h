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
inline string DEFINITION_ERROR = "Use of un-defined";
inline string MISSING_CAST = "Missing cast";
inline string ONLY_NUMBER_OPERATION = "Use of most left side of an operand as a number";
inline string MISSING_CRITICAL_INFORMATION = "Missing critical information";
inline string CANNOT_UNWRAP_PTR = "Cannot unwrap pointer";
inline string INVALID_OPERATION = "Invalid operation";

inline string ASSEMBLER_SYNTAX_ERROR = "Error in given assembly code";

inline string LINKER_MISSING_STARTING_FUNCTION = "Missing starting function";
inline string LINKER_INVALID_FILE = "Invalid file";
inline string LINKER_INTERNAL = "Internal linker error";

inline string SCRAPER_PROBLEM_READING = "Problem reading file"; 

inline string MISSING_DEFINITION = "Missing definition";

#define ERROR (MSG_Type)1
#define NO 0
#define YES 1
#define IDK -1

class Not_Found : public std::runtime_error{
public:
	Not_Found() : runtime_error("Not found"){}
};

class Observation {
public:
	Observation(MSG_Type t, string msg, Position p, string cause = "", int stop_On_Error = IDK) {
		//External message request.
		Type = t;
		Msg = msg;
		Pos = p;
		Cause = cause;
		Stop_On_Error = false;

		if (cause == "")
			Cause = Msg;

		if ((Type == ERROR || Type == FAIL) && (stop_On_Error == YES || stop_On_Error == IDK))
			Stop_On_Error = true;
		else if (stop_On_Error == NO)
			Stop_On_Error = false;
	}

	Observation(MSG_Type t, string msg, string cause = "", int stop_On_Error = IDK) {
		//External message request.
		Type = t;
		Msg = msg;
		Pos = Position(-1, -1);
		Cause = cause;
		Stop_On_Error = true;

		if (cause == "")
			Cause = Msg;

		if ((Type == ERROR || Type == FAIL) && (stop_On_Error == YES || stop_On_Error == IDK))
			Stop_On_Error = true;
		else if (stop_On_Error == NO)
			Stop_On_Error = false;
	}

	Observation(Observation& O, bool Stop_On_Error) {
		*this = O;
		this->Stop_On_Error = Stop_On_Error;
	}

	void Report(bool last = true);
	MSG_Type Type = NORMAL;
private:
	Position Pos;
	string Msg = "";
	string Cause = "";
	bool Stop_On_Error = true;
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

	
	vector<Node*> Input;
	static inline vector<Component> Components;


	//single uses
	static void Check_For_Undefined_Inheritance(Node* n);

	static void Parser_Factory();

	static void Go_Through_AST(void(*Modifier)(Node*& n));
	static void Check_Return_Validity(Node* n);
	static void Disable_Non_Ptr_Class_Return(Node* n);
	static void Check_For_Unitialized_Objects(Node* func);
	static void Warn_Usage_Of_Depricated(Node* n);
	static void Prefer_Class_Cast_Rather_Object_Cast(Node* n);
	static void Warn_Usage_Before_Definition(Node* n);

	//Variable Un-Declarative Error givers.
	static void AST_Factory(Node*& n);
	static void Check_Usage_Of_Un_Declared_Variable(Node*& n);
	static void Flush_Errors();

	//Cast missing error givers.
	static void Report_Missing_Cast(Node*& n);

	static void Reference_Count_Type_Un_Availability();


	void PostProsessor_Factory();
};

#endif