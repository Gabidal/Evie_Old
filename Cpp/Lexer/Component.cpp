#include "../../H/Lexer/Component.h"
#include "../../H/Lexer/Lexer.h"
#include "../../H/Nodes/Node.h"

Component* Component::Copy_Component() {
    Component* Result = new Component(*this);

    if (Result->node)
       Result->node->Copy_Node(Result->node, Result->node, Result->node->Scope);

    for (auto& i : Result->Components)
        i = *i.Copy_Component();

    return Result;
}