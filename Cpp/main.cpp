#include "../H/Lexer/Definer.h"
#include "../H/Parser/Parser.h"
#include "../H/Back/Back.h"
#include <iostream>
using namespace std;

int main()
{
    string OUTPUT = "";

    Definer d;
    d.OpenFile("/home/gabidalg/GAS/IO/test.g");

    Parser p(d.output, OUTPUT);
    p.Factory();

    Back b(p.Output, OUTPUT);
    b.Factory();
    //14
    return 0;
}
