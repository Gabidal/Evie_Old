#include "../../H/Windows/Windows.h"

string Windows::Raw_Print()
{
	string self = "extern _GetStdHandle@4" + NL +
		LABEL(string("raw_print")) +
		PUSH + to_string(-11) + NL +
		CALL + " _GetStdHandle@4 " + NL +
		PUSH + to_string(0) + NL +
		PUSH + ESP->Name + NL +
		PUSH + DWORD + FRAME(ESP->Name + OFFSET + to_string(16)) + NL +
		PUSH + DWORD + FRAME(ESP->Name + OFFSET + to_string(16)) + NL +
		PUSH + EAX->Name + NL +
		CALL + EAX->Name + NL +
		RET + NL;
	return self;
}

string Windows::Raw_In()
{
	string self = "" +
		string("a");
	/*
	global function_sys_read
	function_sys_read:

	push -10 ; STD_INPUT_HANDLE
	call _GetStdHandle@4

	; lpNumberOfCharsRead
	sub esp, 4
	mov ebx, esp

	push 0 ; pInputControl
	push ebx ; lpNumberOfCharsRead
	push dword [esp+20] ; nNumberOfCharsToRead
	push dword [esp+20] ; lpBuffer
	push eax ; hConsoleInput
	call _ReadConsoleA@20

	; lpNumberOfCharsRead
	mov eax, [esp]
	add esp, 4
	ret
	*/
	return self;
}

string Windows::Malloc()
{
	string self = "" +
		string("a");
	return self;
}

string Windows::SYS_CALL()
{
	string self = "" +
		string("a");
	return self;
}