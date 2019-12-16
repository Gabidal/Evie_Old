#include "../../H/Linux/Linux.h"

string Linux::Malloc()
{
	string self =
		LABEL(string("malloc")) +
		PUSH + DWORD + to_string(0) + NL +
		PUSH + DWORD + to_string(-1) + NL +
		PUSH + DWORD + "0x22" + NL +
		PUSH + DWORD + "0x03" + NL +
		PUSH + DWORD + FRAME(ESP->Name + OFFSET + to_string(16)) + NL +
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
		POP + EDX->Name + NL + //lengh
		POP + ECX->Name + NL + //ptr string
		MOV + EBX->Name + FROM + to_string(1) + NL +
		MOV + EAX->Name + FROM + to_string(4) + NL +
		INT + "80h" + NL +
		RET + NL;

    return self;
}
string Linux::Raw_In()
{
	string self =
		LABEL(string("raw_in")) +
		MOV + EAX->Name + FROM + to_string(3) + NL +
		MOV + EBX->Name + FROM + to_string(2) + NL +
		//POP + ECX->Name + NL + 
		//POP + EDX->Name + NL +
		INT + "80h" + NL +
		RET + NL;

    return self;
}
