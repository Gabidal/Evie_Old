#ifndef _REGISTERS_H_
#define _REGISTERS_H_
#include "Token.h"
#include <map>
extern map<string, Register*> registers;

extern void Init_Registers();

extern Register *NUL;
extern Register *EAX;
extern Register *EBX;
extern Register *ECX;
extern Register *EDX;
extern Register *ESI;
extern Register *EDI;
extern Register *EBP;
extern Register *ESP;


#endif