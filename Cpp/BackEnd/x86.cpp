#include "../../H/BackEnd/x86.h"

void x86_64_Win::Init()
{
	Token* AL = new Token(TOKEN::VOLATILE, "AL", 1, {});
	Token* AH = new Token(TOKEN::VOLATILE, "AH", 1, {});
	Token* AX = new Token(TOKEN::VOLATILE, "AX", 2, { AH, AL });
	Token* EAX = new Token(TOKEN::VOLATILE, "EAX", 4, { AX });
	Token* RAX = new Token(TOKEN::VOLATILE, "RAX", 8, { EAX });

	Token* BL;
	Token* BH;
	Token* BX;
	Token* EBX;
	Token* RBX;

	Token* CL;
	Token* CH;
	Token* CX;
	Token* ECX;
	Token* RCX;

	Token* RDX;
	Token* EDX;
	Token* DX;
	Token* DL;
	Token* DH;

	Token* RDI;
	Token* EDI;
	Token* DI;
	Token* DL;
	Token* DH;

	Token* RSI;
	Token* ESI;
	Token* SI;
	Token* SL;
	Token* SH;

	Token* XMM0;
	Token* XMM1;
	Token* XMM2;
	Token* XMM3;
	Token* XMM4;
	Token* XMM5;
	Token* XMM6;
	Token* XMM7;
	Token* XMM8;
	Token* XMM9;
	Token* XMM10;
	Token* XMM11;
	Token* XMM12;
	Token* XMM13;
	Token* XMM14;
	Token* XMM15;

	Token* R8;
	Token* R9;
	Token* R10;
	Token* R11;
	Token* R12;
	Token* R13;
	Token* R14;
	Token* R15;

	Parameter_Registers = { RCX, RDX, R8, R9 , XMM0, XMM1, XMM2, XMM3 };
	Registers = { RAX, EAX, AX, AH, AL };
}
