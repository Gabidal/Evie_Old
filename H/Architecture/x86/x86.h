#ifndef _X86_H_
#define _X86_H_
#include "../../OpC/OpC.h"

class Register;
namespace x86
{
	static int Reg_Turn = 0;
	static vector<Register*> Registers;
	static vector<OpC*> OpCodes;
	void ARC_Factory();

	//Reg's
	//32Bit
	static Register* EAX;
	static Register* EBX;
	static Register* ECX;
	static Register* EDX;
	static Register* EDI;
	static Register* ESI;
	static Register* ESP;
	static Register* EBP;
	//16Bit
	static Register* AX;
	static Register* BX;
	static Register* CX;
	static Register* DX;
	static Register* DI;
	static Register* SI;
	static Register* SP;
	static Register* BP;
	//8Bit
	static Register* AL;
	static Register* AH;
	static Register* BL;
	static Register* BH;
	static Register* CL;
	static Register* CH;
	static Register* DL;
	static Register* DH;
}


#endif