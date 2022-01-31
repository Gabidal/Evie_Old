#ifndef __MEMORY_MANAGER_H_
#define __MEMORY_MANAGER_H_

#include <algorithm>

#include "../Nodes/Node.h"

class Memory_Manager {
public:
	Node* Scope;

	void Factory();

private:
	void Manage_Function();

	//Class modifiers
	void Manage_Class_Padding();
	void Manage_Class_Re_Order();
	void Re_Order_Vector(vector<Node*>& list);
};

#endif