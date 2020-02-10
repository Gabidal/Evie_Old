//
#include "..\..\..\H\Architecture\ARM\ARM.h"

void ARM::ARC_Factory()
{
	OpC* ARM_ADD_ = new OpC(0, "add", "add");
	OpCodes.push_back(ARM_ADD_);
	OpC* ARM_OR_ = new OpC(0, "or", "or");
	OpCodes.push_back(ARM_OR_);
	OpC* ARM_AND_ = new OpC(0, "and", "and");
	OpCodes.push_back(ARM_AND_);
	OpC* ARM_XOR_ = new OpC(0, "xor", "xor");
	OpCodes.push_back(ARM_XOR_);
	OpC* ARM_CMP_ = new OpC(0, "cmp", "cmp");
	OpCodes.push_back(ARM_CMP_);
	OpC* ARM_POP_ = new OpC(0, "pop", "pop");
	OpCodes.push_back(ARM_POP_);
	OpC* ARM_PUSH_ = new OpC(0, "push", "push");
	OpCodes.push_back(ARM_PUSH_);
	OpC* ARM_XCHG_ = new OpC(0, "xchg", "xchg");
	OpCodes.push_back(ARM_XCHG_);
	OpC* ARM_LOAD_ = new OpC(0, "load", "lda");
	OpCodes.push_back(ARM_LOAD_);
	OpC* ARM_STORE_ = new OpC(0, "store", "sta");
	OpCodes.push_back(ARM_STORE_);
	OpC* ARM_LEA_ = new OpC(0, "lea", "lea");
	OpCodes.push_back(ARM_LEA_);
	OpC* ARM_SHL_ = new OpC(0, "shl", "shl");
	OpCodes.push_back(ARM_SHL_);
	OpC* ARM_SHR_ = new OpC(0, "shr", "shr");
	OpCodes.push_back(ARM_SHR_);
	OpC* ARM_NEG_ = new OpC(0, "neg", "neg");
	OpCodes.push_back(ARM_NEG_);
	OpC* ARM_NOT_ = new OpC(0, "not", "not");
	OpCodes.push_back(ARM_NOT_);
	OpC* ARM_CALL_ = new OpC(0, "call", "call");
	OpCodes.push_back(ARM_CALL_);
	OpC* ARM_SUB_ = new OpC(0, "sub", "sub");
	OpCodes.push_back(ARM_SUB_);
	OpC* ARM_IMUL_ = new OpC(0, "imul", "imul");
	OpCodes.push_back(ARM_IMUL_);
	OpC* ARM_IDIV_ = new OpC(0, "idiv", "idiv");
	OpCodes.push_back(ARM_IDIV_);
	OpC* ARM_MUL_ = new OpC(0, "mul", "mul");
	OpCodes.push_back(ARM_MUL_);
	OpC* ARM_DIV_ = new OpC(0, "div", "div");
	OpCodes.push_back(ARM_DIV_);
}
//#endif