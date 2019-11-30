#include "../H/Lexer/Definer.h"
#include "../H/Parser/Parser.h"
#include "../H/Parser/Optimizer.h"
#include "../H/Back/Back.h"
#include <iostream>
using namespace std;

int main()
{
    Init_Registers();

    string OUTPUT = "global _start" + NL +
                    "_start:" + NL +
                    "call main" + NL +
                    "mov eax, 1" + NL +
                    "mov ebx, 0" + NL +
                    "int 80h" + NL + NL;


    Definer d;
    d.OpenFile("C:\\Users\\Quanf\\source\\repos\\GAS\\GAS\\IO\\test.g");

    Parser p(d.output, OUTPUT);
    p.Pattern_Init_Sys_Functions();
    p.Factory();

    Optimizer first(p.Output);
    first.Factory();
    
    Optimizer second(p.Output);
    second.Factory();

    Back b(p.Output, OUTPUT);
    b.Factory();

    ofstream o("C:\\Users\\Quanf\\source\\repos\\GAS\\GAS\\IO\\test.asm");
    o << b.Output;
    o.close();
    return 0;
}
