#ifndef _LEXER_H_
#define _LEXER_H_

#include <sstream>
#include <iomanip>

#include "Component.h"
#include "..//Flags.h"

namespace Lexer
{
    extern char SingleLineCommentIdentifier;
    extern char StringIdentifier;
    extern char DecimalSeparator;
    extern char ExponentSeparator;

    extern vector<string> Operators;
    extern vector<string> Keywords;

    extern vector<Component> GetComponentsFromFile(string file);
    extern vector<Component> GetComponents(string text);
    extern Component GetComponent(string text);
}

#endif