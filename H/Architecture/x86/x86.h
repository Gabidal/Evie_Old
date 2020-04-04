#ifndef _X86_H_
#define _X86_H_
#include "../../OpC/OpC.h"
#include "../../Back/Token.h"

class x86
{
public:
	int Reg_Turn128 = 0;
	int Reg_Turn64 = 0;
	int Reg_Turn32 = 0;
	int Reg_Turn16 = 0;
	int Reg_Turn8 = 0;
	vector<Token*> Registers128;
	vector<Token*> Registers64;
	vector<Token*> Registers32;
	vector<Token*> Registers16;
	vector<Token*> Registers8;
	vector<OpC*> OpCodes;
	void ARC_Factory();
	x86(){}
	~x86(){}

	//Reg's
	//64Bit float
	Token* MMX0 = nullptr;
	Token* MMX1 = nullptr;
	Token* MMX2 = nullptr;
	Token* MMX3 = nullptr;
	Token* MMX4 = nullptr;
	Token* MMX5 = nullptr;
	Token* MMX6 = nullptr;
	Token* MMX7 = nullptr;
	//64Bit
	Token* RAX = nullptr;
	Token* RBX = nullptr;
	Token* RCX = nullptr;
	Token* RDX = nullptr;
	Token* RDI = nullptr;
	Token* RSI = nullptr;
	Token* RSP = nullptr;
	Token* RBP = nullptr;

	Token* R8 = nullptr;
	Token* R9 = nullptr;
	Token* R10 = nullptr;
	Token* R11 = nullptr;
	Token* R12 = nullptr;
	Token* R13 = nullptr;
	Token* R14 = nullptr;
	Token* R15 = nullptr;
	//32Bit
	Token* EAX = nullptr;
	Token* EBX = nullptr;
	Token* ECX = nullptr;
	Token* EDX = nullptr;
	Token* EDI = nullptr;
	Token* ESI = nullptr;
	Token* ESP = nullptr;
	Token* EBP = nullptr;
	//16Bit
	Token* AX = nullptr;
	Token* BX = nullptr;
	Token* CX = nullptr;
	Token* DX = nullptr;
	Token* DI = nullptr;
	Token* SI = nullptr;
	Token* SP = nullptr;
	Token* BP = nullptr;
	//8Bit
	Token* AL = nullptr;
	Token* AH = nullptr;
	Token* BL = nullptr;
	Token* BH = nullptr;
	Token* CL = nullptr;
	Token* CH = nullptr;
	Token* DL = nullptr;
	Token* DH = nullptr;
};


#endif