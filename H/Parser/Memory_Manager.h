#ifndef __MEMORY_MANAGER_H_
#define __MEMORY_MANAGER_H_

#include "../Nodes/Node.h"

class Memory_Manager {
public:
	Node* Scope;

	void Factory();

private:
	void Manage_Function();
	void Manage_Class();
};

#endif