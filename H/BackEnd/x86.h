#ifndef _X86_H_
#define _X86_H_

#include <vector>
#include <string>
#include <map>

using namespace std;

#include "../Nodes/Token.h"
#include "../Flags.h"

namespace x86_64_Win {
	constexpr int SIZE = 8;
	vector<Token*> Registers;

	vector<Token*> Parameter_Registers;


	void Init();
}

#endif