#ifndef _REGISTERS_H_
#define _REGISTERS_H_
#include "Token.h"
#include <map>
extern map<string, Register*> registers;

extern void Init_Registers();

extern Register *R1; //EAX
extern Register *R2; //EBX
extern Register *R3; //ECX
extern Register *R4; //EDX
extern Register *R5; //EDI
extern Register *R6; //ESI
extern Register *R7; //ESP
extern Register *R8; //EBP
extern Register *R9; //...


#endif