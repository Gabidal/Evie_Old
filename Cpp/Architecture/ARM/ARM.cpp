#include "..\..\..\H\Architecture\ARM\ARM.h"

void ARM::ARC_Factory()
{
	OpC* x86_ADD_ = new OpC(0, "add", "add");
	OpCodes.push_back(x86_ADD_);
	OpC* x86_OR_ = new OpC(0, "or", "or");
	OpCodes.push_back(x86_OR_);
	OpC* x86_AND_ = new OpC(0, "and", "and");
	OpCodes.push_back(x86_AND_);
	OpC* x86_XOR_ = new OpC(0, "xor", "xor");
	OpCodes.push_back(x86_XOR_);
	OpC* x86_CMP_ = new OpC(0, "cmp", "cmp");
	OpCodes.push_back(x86_CMP_);
	OpC* x86_POP_ = new OpC(0, "pop", "pop");
	OpCodes.push_back(x86_POP_);
	OpC* x86_PUSH_ = new OpC(0, "push", "push");
	OpCodes.push_back(x86_PUSH_);
	OpC* x86_XCHG_ = new OpC(0, "xchg", "xchg");
	OpCodes.push_back(x86_XCHG_);
	OpC* x86_LOAD_ = new OpC(0, "load", "lda");
	OpCodes.push_back(x86_LOAD_);
	OpC* x86_STORE_ = new OpC(0, "store", "sta");
	OpCodes.push_back(x86_STORE_);
	OpC* x86_LEA_ = new OpC(0, "lea", "lea");
	OpCodes.push_back(x86_LEA_);
	OpC* x86_SHL_ = new OpC(0, "shl", "shl");
	OpCodes.push_back(x86_SHL_);
	OpC* x86_SHR_ = new OpC(0, "shr", "shr");
	OpCodes.push_back(x86_SHR_);
	OpC* x86_NEG_ = new OpC(0, "neg", "neg");
	OpCodes.push_back(x86_NEG_);
	OpC* x86_NOT_ = new OpC(0, "not", "not");
	OpCodes.push_back(x86_NOT_);
	OpC* x86_CALL_ = new OpC(0, "call", "call");
	OpCodes.push_back(x86_CALL_);
	OpC* x86_SUB_ = new OpC(0, "sub", "sub");
	OpCodes.push_back(x86_SUB_);
	OpC* x86_IMUL_ = new OpC(0, "imul", "imul");
	OpCodes.push_back(x86_IMUL_);
	OpC* x86_IDIV_ = new OpC(0, "idiv", "idiv");
	OpCodes.push_back(x86_IDIV_);
	OpC* x86_MUL_ = new OpC(0, "mul", "mul");
	OpCodes.push_back(x86_MUL_);
	OpC* x86_DIV_ = new OpC(0, "div", "div");
	OpCodes.push_back(x86_DIV_);
}
