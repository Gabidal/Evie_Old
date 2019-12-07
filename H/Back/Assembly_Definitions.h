#ifndef _ASSEMBLY_DEFINITIONS_H_
#define _ASSEMBLY_DEFINITIONS_H_

#define MOVSD string("movsd")
#define MOV string("mov ")
#define LEA string("lea ")
#define ADD string("add ")
#define SUB string("sub ")
#define MUL string("mul ")
#define DIV string("div ")
#define IMUL string("imul ")
#define IDIV string("idiv ")
#define XOR string("xor ")
#define CMP string("cmp ")
#define JE string("je ")
#define JNE string("jne ")
#define JG string("jg ")
#define JNG string("jng ")
#define JL string("jl ")
#define JNGE string("jnge ")
#define JNLE string("jnle ")
#define JGE string("jge ")
#define JLE string("jle ")
#define JMP string("jmp ")
#define CALL string("call ")
#define CDQ string("cdq ")
#define XCHG(dest, source) ("xchg " + string(dest) + FROM + source + NL)

#define JNL "jnl "
#define JZ "jz "
#define RET "ret "
#define INT "int "
#define _NULL(name) (name == "null" || name == "")
#define FROM ", "
#define NL string("\n")
#define OFFSET " + "
#define DEOFFSET " - "
#define SCALE " * "
#define LABEL(name) (name + ": " + NL)
#define FUNC(name) (name)
#define TYPE(type, name) (type + "_" + name)
#define COMMENT string(" ; ")

#define DWORD "dword "
#define QWORD "qword "
#define BYTE "byte "
#define FRAME(name) ("[" + name + "]")
#define CONTENT(name) (string("(") + name + ")")
#define PUSH "push "
#define POP "pop "
#define DD " resd 1"
#define CODESEGMENT "section .code\n"
#define BSSSEGMENT "section .bss\n"

#endif