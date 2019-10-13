#include "H/Type.h"

void Type::addFunc(Func *func)
{
    this->Functions.push_back(func);
    func->ParentType = this;
    func->Parent = this;
    func->Flags |= Prototype;
}