#include "../../H/Linux/Linux.h"
/*
string Linux::Malloc()
{
	string self =
		LABEL(string("malloc")) +
		PUSH + DWORD + to_string(0) + NL +
		PUSH + DWORD + to_string(-1) + NL +
		PUSH + DWORD + "0x22" + NL +
		PUSH + DWORD + "0x03" + NL +
		PUSH + DWORD + FRAME(R7->Name + OFFSET + to_string(20)) + NL +
		PUSH + DWORD + to_string(0) + NL +
		MOV + R1->Name + FROM + "0x5a" + NL +
		MOV + R2->Name + FROM + R7->Name + NL +
		INT + "0x80" + NL +
		ADD + R7->Name + FROM + to_string(24) + NL +
		RET + NL;

    return self;
}
string Linux::Raw_Print()
{
	string self =
		LABEL(string("raw_print")) +
		PUSH + R8->Name + NL +
		MOV + R8->Name + FROM + R7->Name + NL +
		MOV + R4->Name + FROM + FRAME(R8->Name + OFFSET + " 8") + NL + //lengh
		MOV + R3->Name + FROM + FRAME(R8->Name + OFFSET + " 4") + NL + //ptr string
		MOV + R2->Name + FROM + to_string(1) + NL +
		MOV + R1->Name + FROM + to_string(4) + NL +
		INT + "80h" + NL +
		MOV + R7->Name + FROM + R8->Name + NL +
		POP + R8->Name + NL +
		RET + NL + NL;

    return self;
}
string Linux::Raw_In()
{
	string self =
		LABEL(string("raw_in")) +
		PUSH + R8->Name + NL +
		MOV + R8->Name + FROM + R7->Name + NL +
		MOV + R1->Name + FROM + to_string(3) + NL +
		MOV + R2->Name + FROM + to_string(2) + NL +
		MOV + R4->Name + FROM + FRAME(R8->Name + OFFSET + " 8") + NL + //lengh
		MOV + R3->Name + FROM + FRAME(R8->Name + OFFSET + " 4") + NL + //ptr string
		INT + "80h" + NL +
		MOV + R7->Name + FROM + R8->Name + NL +
		POP + R8->Name + NL +
		RET + NL + NL;

    return self;
}
string Linux::SYS_CALL()
{
	string self = "" +
		LABEL(string("sys")) +
		PUSH + R8->Name + NL +
		MOV + R8->Name + FROM + R7->Name + NL +
		MOV + R1->Name + FROM + FRAME(R8->Name + OFFSET + " 4") + NL + 
		MOV + R2->Name + FROM + FRAME(R8->Name + OFFSET + " 8") + NL + 
		MOV + R3->Name + FROM + FRAME(R8->Name + OFFSET + " 12") + NL +
		MOV + R4->Name + FROM + FRAME(R8->Name + OFFSET + " 16") + NL +
		INT + "80h" + NL +
		MOV + R7->Name + FROM + R8->Name + NL +
		POP + R8->Name + NL +
		RET + NL + NL;
	return self;
}
*/