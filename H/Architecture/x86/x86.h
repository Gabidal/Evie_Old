#ifndef _X86_H_
#define _X86_H_
#include "../../OpC/OpC.h"

class Register;
namespace x86
{
	vector<Register*> Registers;
	vector<OpC*> OpCodes;
	void ARC_Factory();

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
}


#endif