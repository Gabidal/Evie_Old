#include "..\..\..\H\Architecture\ARM\ARM.h"

void ARM::ARC_Factory()
{
	OpC* ARM_ADD_ = new OpC("add", 2, 4, 4, 6, ARM::ARM_ADD);
	OpCodes.push_back(ARM_ADD_);
	OpC* ARM_SUB_ = new OpC("sub", 2, 4, 4, 6, ARM::ARM_SUB);
	OpCodes.push_back(ARM_SUB_);
	OpC* ARM_IMUL_ = new OpC("imul", 2, 4, 4, 8, ARM::ARM_IMUL);
	OpCodes.push_back(ARM_IMUL_);
	OpC* ARM_IDIV_ = new OpC("idiv", 2, 4, 4, 28, ARM::ARM_IDIV);
	OpCodes.push_back(ARM_IDIV_);
	OpC* ARM_MUL_ = new OpC("mul", 1, 4, 0, 4, ARM::ARM_MUL);
	OpCodes.push_back(ARM_MUL_);
	OpC* ARM_DIV_ = new OpC("div", 1, 4, 0, 76, ARM::ARM_DIV);
	OpCodes.push_back(ARM_DIV_);
}
