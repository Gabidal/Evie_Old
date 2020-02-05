#include "..\..\..\H\Architecture\x86\x86.h"

void x86::Factory()
{
	OpC* x86_ADD_ = new OpC("add", 2, 4, 4, 6, x86_ADD);
	OpCodes.push_back(x86_ADD_);
	OpC* x86_SUB_ = new OpC("sub", 2, 4, 4, 6, x86_SUB);
	OpCodes.push_back(x86_SUB_);
	OpC* x86_IMUL_ = new OpC("imul", 2, 4, 4, 8, x86_IMUL);
	OpCodes.push_back(x86_IMUL_);
	OpC* x86_IDIV_ = new OpC("idiv", 2, 4, 4, 28, x86_IDIV);
	OpCodes.push_back(x86_IDIV_);
	OpC* x86_MUL_ = new OpC("mul", 1, 4, 0, 4, x86_MUL);
	OpCodes.push_back(x86_MUL_);
	OpC* x86_DIV_ = new OpC("div", 1, 4, 0, 76, x86_DIV);
	OpCodes.push_back(x86_DIV_);
}
