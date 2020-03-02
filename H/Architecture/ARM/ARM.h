#ifndef ARM_H_
#define ARM_H_
#include "../../OpC/OpC.h"
#include "../../Back/Token.h" //for registers
class ARM
{
public:
	vector<Token*> Registers128;
	vector<Token*> Registers64;
	vector<Token*> Registers32;
	vector<Token*> Registers16;
	vector<Token*> Registers8;
	vector<OpC*> OpCodes;
	void ARC_Factory();
	ARM() {}
	~ARM() {}
};


#endif