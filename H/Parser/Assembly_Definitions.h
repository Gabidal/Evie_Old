#ifndef _ASSEMBLY_DEFINITIONS_H_
#define _ASSEMBLY_DEFINITIONS_H_

#define MOV "mov "
#define LEA "lea "
#define ADD "add "
#define SUB "sub "
#define MUL "mul "
#define DIV "div "
#define IMUL "imul "
#define IDIV "idiv "
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
#define DEOFFSET " - "
#define SCALE " * "
#define LABEL(name) (name + ": " + NL)
#define FUNC(name) (name + "()")
#define TYPE(type, name) (type + "::" + name)
#define COMMENT(name) (string(NL) + "; " + name + NL)

#define DWORD "dword "
#define QWORD "qword "
#define BYTE "byte "
#define FRAME(name) ("[" + name + "]")
#define PUSH(name) ("push " + name + NL)
#define POP(name) ("pop " + name + NL)

#endif