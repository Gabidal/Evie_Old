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


class Selector
{
public:
	vector<OpC*> Output;
	Token* Input;
	Selector()
	{
	}

	~Selector();
private:

};


#endif