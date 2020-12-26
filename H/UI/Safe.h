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
	SOLUTION
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
	string Msg = "";
	Position Pos;
};

void Report(Observation o);
void Report(vector<Observation> o);

class Safe {
public:
	Safe(vector<Node*> i) : Input(i) { Factory(); }
private:
	void Factory();
	void Check_Return_Validity(Node* n);
	vector<Node*> Input;
};