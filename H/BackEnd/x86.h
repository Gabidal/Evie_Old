#ifndef _X86_H_
#define _X86_H_

#include <vector>
#include <string>
#include <map>

using namespace std;

#include "../Nodes/Token.h"
#include "../Nodes/IR.h"
#include "../Flags.h"

class x86_64_Win {
public:
	int size;
	vector<Token*> Registers;
	vector<Token*> Parameter_Registers;
	vector<IR*> Opcodes;
	vector<Token*> Utility;


	string Seperator;
	string Register_Pre_Fix;
	string Number_Pre_Fix;
	string Label_Post_Fix;
	void Init();
};

#endif