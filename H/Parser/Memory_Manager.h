#ifndef __MEMORY_MANAGER_H_
#define __MEMORY_MANAGER_H_

#include <algorithm>

#include "../Nodes/Node.h"
#include "../UI/Safe.h"

class Memory_Manager {
public:
	Node* Scope;

	Memory_Manager(Node* S) {
		Scope = S;
		Factory();
	}
private:
	void Factory();
	void Manage_Function();

	//Class modifiers
	void Manage_Class_Padding();
	void Manage_Class_Re_Order();
	void Re_Order_Vector(vector<Node*>& list);
};

#endif