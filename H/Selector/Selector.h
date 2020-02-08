#ifndef SELECTOR_H_
#define SELECTOR_H_
#include <vector>
#include "../Back/Token.h"
using namespace std;

#if _ARM_
#include "../Architecture/ARM/ARM.h"
#else
#include "../Architecture/x86/x86.h"
#endif

//Selector's mission is to get right and the best solutionary opecodes for every operation.
class Selector
{
public:
	vector<OpC*> Output;
	Token* Input;
	void Factory();
	void OpCode_Selector();
	Selector()
	{
		#if __ARM__
			ARM::Factory();
		#else
			x86::Factory();
		#endif
	}

	~Selector();
private:

};


#endif