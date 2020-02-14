#ifndef ARM_H_
#define ARM_H_
#include "../../OpC/OpC.h"
#include "../../Back/Token.h" //for registers
class ARM
{
public:
	vector<Register*> Registers;
	vector<OpC*> OpCodes;
	void ARC_Factory();
	ARM() {}
	~ARM() {}
};


#endif