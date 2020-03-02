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
	Token* MMX0;
	Token* MMX1;
	Token* MMX2;
	Token* MMX3;
	Token* MMX4;
	Token* MMX5;
	Token* MMX6;
	Token* MMX7;
	//64Bit
	Token* RAX;
	Token* RBX;
	Token* RCX;
	Token* RDX;
	Token* RDI;
	Token* RSI;
	Token* RSP;
	Token* RBP;
	//32Bit
	Token* EAX;
	Token* EBX;
	Token* ECX;
	Token* EDX;
	Token* EDI;
	Token* ESI;
	Token* ESP;
	Token* EBP;
	//16Bit
	Token* AX;
	Token* BX;
	Token* CX;
	Token* DX;
	Token* DI;
	Token* SI;
	Token* SP;
	Token* BP;
	//8Bit
	Token* AL;
	Token* AH;
	Token* BL;
	Token* BH;
	Token* CL;
	Token* CH;
	Token* DL;
	Token* DH;
};


#endif