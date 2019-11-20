#include "../H/Lexer/Definer.h"
#include "../H/Parser/Parser.h"
#include "../H/Back/Back.h"
#include <iostream>
using namespace std;

int main()
{
    Init_Registers();

    string OUTPUT = "";

    Definer d;
    d.OpenFile("/home/gabidalg/GAS/IO/std.g");

    Parser p(d.output, OUTPUT);
    p.Factory();

    Back b(p.Output, OUTPUT);
    b.Factory();

    ofstream o("/home/gabidalg/GAS/IO/test.asm");
    o << b.Output;
    o.close();
    return 0;
}
