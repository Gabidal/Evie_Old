#include "../../H/Windows/Windows.h"
/*
string Windows::Raw_Print()
{
	string self = "extern _GetStdHandle@4" + NL +
		"global raw_print" + NL +
		LABEL(string("raw_print")) +
		PUSH + to_string(-11) + NL +
		CALL + " _GetStdHandle@4 " + NL +
		PUSH + to_string(0) + NL +
		PUSH + R7->Name + NL +
		PUSH + DWORD + FRAME(R7->Name + OFFSET + to_string(16)) + NL +
		PUSH + DWORD + FRAME(R7->Name + OFFSET + to_string(16)) + NL +
		PUSH + R1->Name + NL +
		CALL + R1->Name + NL +
		RET + NL;
	return self;
}

string Windows::Raw_In()
{
	string self = "extern _ReadConsoleA@20" + NL +
		"global raw_in" + NL +
		LABEL(string("raw_in")) +
		PUSH + to_string(-10) + NL +
		CALL + " _GetStdHandle@4" + NL +
		SUB + R7->Name + to_string(4) + NL +
		MOV + R2->Name + FROM + R7->Name + NL +
		PUSH + to_string(0) + NL +
		PUSH + R2->Name + NL +
		PUSH + DWORD + FRAME(R7->Name + OFFSET + to_string(20)) + NL +
		PUSH + DWORD + FRAME(R7->Name + OFFSET + to_string(20)) + NL +
		PUSH + R1->Name + NL +
		CALL + "_ReadConsoleA@20" + NL +
		MOV + R1->Name + FROM + FRAME(R7->Name) + NL +
		ADD + R7->Name + FROM + to_string(4) + NL +
		RET + NL + NL;
	return self;
}

string Windows::Malloc()
{
	string self = "extern _VirtualAlloc@16" + NL +
		"global malloc" + NL +
		LABEL(string("malloc")) +
		PUSH + DWORD + "0x04" + NL +
		PUSH + DWORD + "0x3000" + NL +
		PUSH + DWORD + FRAME(R7->Name + OFFSET + to_string(8)) + NL +
		PUSH + DWORD + to_string(0) + NL +
		CALL + "_VirtualAlloc@16" + NL +
		RET + NL + NL;
	return self;
}

string Windows::SYS_CALL()
{
	string self = "" +
		string("a");
	return self;
}*/