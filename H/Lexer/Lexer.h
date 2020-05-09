#ifndef _LEXER_H_
#define _LEXER_H_

#include "Component.h"

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
}

#endif