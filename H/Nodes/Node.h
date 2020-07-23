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

	Node* Find(string name, Scope_Node* p)
	{
		for (Node* s : p->Defined)
			if (name == s->Name)
				return s;
		if (p->Parent != nullptr)
			return Find(name, p->Parent);
		return nullptr;
	}



	//the parent
	Scope_Node* Parent = nullptr;
private:

};

#endif