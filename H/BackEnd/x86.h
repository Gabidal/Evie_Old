#ifndef _X86_H_
#define _X86_H_

#include <vector>
#include <string>
#include <map>

using namespace std;

#include "../Nodes/Token.h"
#include "../Nodes/IR.h"
#include "../Flags.h"

namespace x86_64_Win {
	int SIZE;
	vector<Token*> Registers;
	vector<Token*> Parameter_Registers;
	vector<IR*> Opcodes;

	void Init();
}

#endif