#ifndef _X86_H_
#define _X86_H_
#include "../../OpC/OpC.h"
#include "../../Back/Token.h"

class x86
{
public:
	int Reg_Turn = 0;
	vector<Register*> Registers;
	vector<OpC*> OpCodes;
	void ARC_Factory();
	x86(){}
	~x86(){}

	//Reg's
	//32Bit
	Register* EAX;
	Register* EBX;
	Register* ECX;
	Register* EDX;
	Register* EDI;
	Register* ESI;
	Register* ESP;
	Register* EBP;
	//16Bit
	Register* AX;
	Register* BX;
	Register* CX;
	Register* DX;
	Register* DI;
	Register* SI;
	Register* SP;
	Register* BP;
	//8Bit
	Register* AL;
	Register* AH;
	Register* BL;
	Register* BH;
	Register* CL;
	Register* CH;
	Register* DL;
	Register* DH;
};


#endif