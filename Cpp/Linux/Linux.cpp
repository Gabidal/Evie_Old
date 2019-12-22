#include "../../H/Linux/Linux.h"

string Linux::Malloc()
{
	string self =
		LABEL(string("malloc")) +
		PUSH + DWORD + to_string(0) + NL +
		PUSH + DWORD + to_string(-1) + NL +
		PUSH + DWORD + "0x22" + NL +
		PUSH + DWORD + "0x03" + NL +
		PUSH + DWORD + FRAME(ESP->Name + OFFSET + to_string(20)) + NL +
		PUSH + DWORD + to_string(0) + NL +
		MOV + EAX->Name + FROM + "0x5a" + NL +
		MOV + EBX->Name + FROM + ESP->Name + NL +
		INT + "0x80" + NL +
		ADD + ESP->Name + FROM + to_string(24) + NL +
		RET + NL;

    return self;
}
string Linux::Raw_Print()
{
	string self =
		LABEL(string("raw_print")) +
		PUSH + EBP->Name + NL +
		MOV + EBP->Name + FROM + ESP->Name + NL +
		MOV + EDX->Name + FROM + FRAME(EBP->Name + OFFSET + " 8") + NL + //lengh
		MOV + ECX->Name + FROM + FRAME(EBP->Name + OFFSET + " 4") + NL + //ptr string
		MOV + EBX->Name + FROM + to_string(1) + NL +
		MOV + EAX->Name + FROM + to_string(4) + NL +
		INT + "80h" + NL +
		MOV + ESP->Name + FROM + EBP->Name + NL +
		POP + EBP->Name + NL +
		RET + NL + NL;

    return self;
}
string Linux::Raw_In()
{
	string self =
		LABEL(string("raw_in")) +
		PUSH + EBP->Name + NL +
		MOV + EBP->Name + FROM + ESP->Name + NL +
		MOV + EAX->Name + FROM + to_string(3) + NL +
		MOV + EBX->Name + FROM + to_string(2) + NL +
		MOV + EDX->Name + FROM + FRAME(EBP->Name + OFFSET + " 8") + NL + //lengh
		MOV + ECX->Name + FROM + FRAME(EBP->Name + OFFSET + " 4") + NL + //ptr string
		INT + "80h" + NL +
		MOV + ESP->Name + FROM + EBP->Name + NL +
		POP + EBP->Name + NL +
		RET + NL + NL;

    return self;
}
string Linux::SYS_CALL()
{
	string self = "" +
		LABEL(string("sys")) +
		PUSH + EBP->Name + NL +
		MOV + EBP->Name + FROM + ESP->Name + NL +
		MOV + EAX->Name + FROM + FRAME(EBP->Name + OFFSET + " 4") + NL + 
		MOV + EBX->Name + FROM + FRAME(EBP->Name + OFFSET + " 8") + NL + 
		MOV + ECX->Name + FROM + FRAME(EBP->Name + OFFSET + " 12") + NL +
		MOV + EDX->Name + FROM + FRAME(EBP->Name + OFFSET + " 16") + NL +
		INT + "80h" + NL +
		MOV + ESP->Name + FROM + EBP->Name + NL +
		POP + EBP->Name + NL +
		RET + NL + NL;
	return self;
}
