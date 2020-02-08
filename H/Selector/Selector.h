#ifndef SELECTOR_H_
#define SELECTOR_H_
#include <vector>
#include "../Back/Token.h"
using namespace std;

#if _ARM_
#include "../Architecture/ARM/ARM.h"
using namespace ARM;
#else
#include "../Architecture/x86/x86.h"
using namespace x86;
#endif

//Selector's mission is to get right and the best solutionary opecodes for every operation.
class Selector
{
public:
	OpC* Output;
	Token* Input;
	vector<int> Values;
	void OpCode_Selector();
	Selector(vector<int> V)
	{
		#if __ARM__
			ARC_Factory();
		#else
			ARC_Factory();
		#endif
			Values = V;
			OpCode_Selector();
	}

	~Selector();
private:

};


#endif