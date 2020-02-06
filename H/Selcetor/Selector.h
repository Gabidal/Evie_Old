#ifndef SELECTOR_H_
#define SELECTOR_H_

#if _x86_
#include "../Architecture/x86/x86.h"
#else
#include "../Architecture/ARM/ARM.h"
#endif


class Selector
{
public:
	Selector()
	{
	}

	~Selector();
private:

};


#endif