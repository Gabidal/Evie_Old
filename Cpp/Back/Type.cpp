#include "H/Back/Type.h"

void Type::addFunc(Func *func)
{
    this->Functions.push_back(func);
    func->ParentType = this;
    func->Flags |= Prototype;
}

void Type::InitType()
{
    if (initted)
    {
        return;
    }
    for (Token *t : Childs)
    {
        if (t->is(Used) != true)
        {
            output += COMMENT("Variable not used!");
        }
        else
        { 
            output += MOV + FRAME(t->getFullName()) + FROM + to_string(t->Value) + NL;
        }
    }
}
