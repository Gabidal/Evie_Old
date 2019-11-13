#include "../../H/Back/Register.h"

void Register::Link(Token *Requester)
{
    Base.push_back(Requester);
    Current = Requester;
}