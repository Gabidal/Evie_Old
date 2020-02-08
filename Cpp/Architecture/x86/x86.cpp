#include "..\..\..\H\Architecture\x86\x86.h"

void x86::Factory()
{
	OpC* x86_ADD_ = new OpC("add", 2, 4, 4, 6, x86::x86_ADD);
	OpCodes.push_back(x86_ADD_);
	OpC* x86_OR_ = new OpC("or", 2, 4, 4, 1, x86::x86_OR);
	OpCodes.push_back(x86_OR_);
	OpC* x86_AND_ = new OpC("AND", 2, 4, 4, 1, x86::x86_AND);
	OpCodes.push_back(x86_AND_);
	OpC* x86_XOR_ = new OpC("xor", 2, 4, 4, 1, x86::x86_XOR);
	OpCodes.push_back(x86_XOR_);
	OpC* x86_CMP_ = new OpC("cmp", 2, 4, 4, 6, x86::x86_CMP);
	OpCodes.push_back(x86_CMP_);
	OpC* x86_POP_ = new OpC("pop", 1, 4, 0, 6, x86::x86_POP);
	OpCodes.push_back(x86_POP_);
	OpC* x86_PUSH_ = new OpC("push", 1, 4, 0, 2, x86::x86_PUSH);
	OpCodes.push_back(x86_PUSH_);
	OpC* x86_XCHG_ = new OpC("xchg", 2, 4, 4, 2, x86::x86_XCHG);
	OpCodes.push_back(x86_XCHG_);
	OpC* x86_MOV_ = new OpC("mov", 2, 4, 4, 5, x86::x86_MOV);
	OpCodes.push_back(x86_MOV_);
	OpC* x86_LEA_ = new OpC("lea", 2, 4, 4, 1, x86::x86_LEA);
	OpCodes.push_back(x86_LEA_);
	OpC* x86_SHL_ = new OpC("shl", 2, 4, 1, 3, x86::x86_SHL);
	OpCodes.push_back(x86_SHL_);
	OpC* x86_SHR_ = new OpC("shr", 2, 4, 1, 3, x86::x86_SHR);
	OpCodes.push_back(x86_SHR_);
	OpC* x86_NEG_ = new OpC("neg", 1, 4, 0, 1, x86::x86_NEG);
	OpCodes.push_back(x86_NEG_);
	OpC* x86_NOT_ = new OpC("not", 1, 4, 0, 1, x86::x86_NOT);
	OpCodes.push_back(x86_NOT_);
	OpC* x86_CALL_ = new OpC("call", 1, 4, 0, 1, x86::x86_CALL);
	OpCodes.push_back(x86_CALL_);
	OpC* x86_SUB_ = new OpC("sub", 2, 4, 4, 6, x86::x86_SUB);
	OpCodes.push_back(x86_SUB_);
	OpC* x86_IMUL_ = new OpC("imul", 2, 4, 4, 8, x86::x86_IMUL);
	OpCodes.push_back(x86_IMUL_);
	OpC* x86_IDIV_ = new OpC("idiv", 2, 4, 4, 28, x86::x86_IDIV);
	OpCodes.push_back(x86_IDIV_);
	OpC* x86_MUL_ = new OpC("mul", 1, 4, 0, 4, x86::x86_MUL);
	OpCodes.push_back(x86_MUL_);
	OpC* x86_DIV_ = new OpC("div", 1, 4, 0, 76, x86::x86_DIV);
	OpCodes.push_back(x86_DIV_);
}
