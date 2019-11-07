#include "../H/Lexer/Definer.h"
#include "../H/Parser/Parser.h"
#include <iostream>
using namespace std;

int main()
{
    Definer d;
    d.OpenFile("/home/gabidalg/GAS/IO/test.g");
    Parser p(d.output);
    p.Factory();
    return 0;
}
