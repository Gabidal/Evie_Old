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
#define JNGE "jnge "
#define JNLE "jnle "
#define JGE "jge "
#define JLE "jle "
#define JMP "jmp "
#define CALL "call "
#define CDQ "cdq "
#define XCHG(dest, source) ("xchg " + string(dest) + FROM + source + NL)

#define JNL "jnl "
#define JZ "jz "
#define RET "ret "
#define INT "int "
#define _NULL(name) (name == "null" || name == "")
#define FROM ", "
#define NL "\n"
#define OFFSET " + "
#define DEOFFSET " - "
#define SCALE " * "
#define LABEL(name) (name + ": " + NL)
#define FUNC(name) (name)
#define TYPE(type, name) (type + "_" + name)
#define COMMENT(name) (string(NL) + "; " + name + NL)

#define DWORD "dword "
#define QWORD "qword "
#define BYTE "byte "
#define FRAME(name) ("[" + name + "]")
#define PUSH "push "
#define POP "pop "

#endif