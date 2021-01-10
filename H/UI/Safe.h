#include "../Nodes/Node.h"
#include "../Lexer/Position.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

enum MSG_Type {
	NORMAL,
	ERROR,
	WARNING,
	SOLUTION,
	FAIL,
	SUCCESS
};

class Observation {
public:
	Observation(int t, string msg, Position p) {
		//External message request.
		Type = t;
		Msg = msg;
		Pos = p;
	}

	void Report();
private:
	int Type = NORMAL;
	Position Pos;
	string Msg = "";
};

class Lexer_Expectation;
class Components;

void Report(Observation o);
void Report(vector<Observation> o);
void Report(long type, Lexer_Expectation expectation, string source, vector<Component> result);

class Safe {
public:
	Safe(vector<Node*> i) : Input(i) { Factory(); }
private:
	void Factory();
	void Check_Return_Validity(Node* n);
	void Disable_Non_Ptr_Class_Return(Node* n);
	vector<Node*> Input;
};