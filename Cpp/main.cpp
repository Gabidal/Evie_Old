#include "../H/Lexer/Definer.h"
#include "../H/Parser/Parser.h"
#include "../H/Parser/Optimizer.h"
#include "../H/Back/Back.h"
#include <sstream>
#include <iostream>
using namespace std;
int SYNTAX = 0;

vector<string> Pre_Defined_Tokens;
void Init_Pre_Defined_Tokens()
{
    Pre_Defined_Tokens.push_back("return");
    Pre_Defined_Tokens.push_back("pop");
    Pre_Defined_Tokens.push_back("push");
}

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		return -1;
	}
    Init_Registers();

	string OUTPUT = "";
#ifndef _win32_
    OUTPUT = "global main\n";
#else
    OUTPUT = "global _start\n_start:\ncall main\nmov eax, 1\n mov ebx, 0\nint 80h\n\n";
#endif // !1


    Definer d;
	d.OpenFile(argv[1]);

    Parser p;
    p.Input = d.output;
	p.Working_Dir = argv[1];
    Init_Pre_Defined_Tokens();
    p.Factory();

    //Optimizer o(*p.Output);
    //o.Factory();

    //Back b(*p.Output, OUTPUT);
	//b.Factory_Variables();
    //b.Factory();
	//OUTPUT += b.Strings;

	ofstream o(argv[2]);
    o << "banana";//b.Output;
    o.close();

    #ifndef _Win32_
    stringstream output;
    output << "..\\Cpp\\Assemblers\\yasm_win.exe -g dwarf2 -f win32 -o " << argv[1] << ".obj " << argv[2];

    system(output.str().c_str());
    output = stringstream();

    output << "..\\Cpp\\Linkers\\GoLink.exe " << "/console " << "/debug coff " << "/entry main " << argv[1] << ".obj " << "kernel32.dll ";

    system(output.str().c_str());
    #else

    #endif
    return 0;
}