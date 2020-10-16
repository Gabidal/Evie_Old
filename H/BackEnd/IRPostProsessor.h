#ifndef _IRPOSTPROSESSOR_H_
#define _IRPOSTPROSESSOR_H_

#include "../Flags.h"
#include "../Nodes/IR.h"
#include "../Nodes/Token.h"


#include <vector>
#include <string>

using namespace std;

class IRPostProsessor {
private:
	vector<IR*>* Input;

	void Scale_To_Same_Size(int i);
public:
	IRPostProsessor(vector<IR*>* in) : Input(in) { Factory(); }
	void Factory();
};

#endif