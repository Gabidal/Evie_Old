#ifndef _IRGENERATOR_H_
#define _IRGENERATOR_H_
#include "../Nodes/IR.h"
#include "../Nodes/Token.h"
#include "../Nodes/Node.h"
#include "../Flags.h"

#include <vector>
#include <string>

using namespace std;

class IRGenerator {
public:
	Node* Parent = nullptr;
	vector<IR*> Output;
	vector<Node*> Input;
	IRGenerator(Node* p) : Parent(p) {}
	IRGenerator(Node* p, vector<Node*> in) : Parent(p), Input(in) {}
	IRGenerator(Node* p, vector<Node*> in, vector<IR*>& Out) : Parent(p), Input(in), Output(Out) { Factory(); }

	void Factory();
	void Parse_Function(int i);
	void Parse_If(int i);
	//TODO: hey gab! use log(x) base 10 for the global inlining label adding rendom char adder.

	IR* Make_Label(Node* n);
};

#endif