#ifndef _NODE_H_
#define _NODE_H_
#include <string>
#include <vector>

using namespace std;

class Scope_Node;

class Node
{
	//test ptr a
public:
	Node() {};
	Node(long type) : Type(type){}
	~Node(){}
	string Name = "";

	long Type = 0;

	inline bool is(int type) {
		return Type == type;
	}

	//the parent
	Scope_Node* Parent = nullptr;
private:

};

#endif