#ifndef ARM_H_
#define ARM_H_
#include "../../OpC/OpC.h"
#include "../../Back/Token.h" //for registers
class ARM
{
public:
	vector<Register*> Registers32;
	vector<Register*> Registers16;
	vector<Register*> Registers8;
	vector<OpC*> OpCodes;
	void ARC_Factory();
	ARM() {}
	~ARM() {}
};


#endif