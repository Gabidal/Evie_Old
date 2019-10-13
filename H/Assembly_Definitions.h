#ifndef _ASSEMBLY_DEFINITIONS_H_
#define _ASSEMBLY_DEFINITIONS_H_

#define MOV "mov "
#define LEA "lea "
#define ADD "add "
#define SUB "sub "
#define MUL "mul "
#define DIV "div "
#define XOR "xor "
#define CMP "cmp "
#define JE "je "
#define JNE "jne "
#define JG "jg "
#define JNG "jng "
#define JL "jl "

#define JNL "jnl "
#define JZ "jz "
#define RET "ret "
#define INT "int "
#define NULL(name) (name == "null" || name == "")
#define FROM ", "
#define NL "\n"
#define OFFSET " + "
#define SCALE " * "


#define DWORD "dword "
#define QWORD "qword "
#define BYTE "byte "
#define FRAME(name) ("[" + name + "]")


#endif