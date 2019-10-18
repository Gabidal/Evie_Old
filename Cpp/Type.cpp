#include "H/Type.h"

void Type::addFunc(Func *func)
{
    this->Functions.push_back(func);
    func->ParentType = this;
    func->Flags |= Prototype;
}

void Type::InitType(string &output)
{
    if (initted)
    {
        return;
    }
    for (Token *t : Childs)
    {
        if (t->is(Used))
        {
            //something for future :D
        }
        else
        {
            output += COMMENT(string("Variable is not used yet!"));
        }
        output += MOV + FRAME(t->getFullName()) + FROM + to_string(t->Value) + NL;
    }
}
