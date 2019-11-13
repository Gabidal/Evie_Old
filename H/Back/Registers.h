#ifndef _REGISTERS_H_
#define _REGISTERS_H_
#include "Token.h"

static Register *NUL = new Register("null");
static Register *EAX = new Register("eax");
static Register *EBX = new Register("ebx");
static Register *ECX = new Register("ecx");
static Register *EDX = new Register("edx");
static Register *ESI = new Register("esi");
static Register *EDI = new Register("edi");
static Register *EBP = new Register("ebp");
static Register *ESP = new Register("esp");

#endif