#include "../H/Lexer/Lexer.h"
#include "../H/Parser/Parser.h"
#include "../H/Back/Definer.h"
#include "../H/Emulator/Emulator.h"
#include "../H/Selector/Selector.h"
#include "../H/Back/Generator.h"
#include <sstream>
#include <iostream>
using namespace std;
int SYNTAX = 0;
extern void Init_Registers();
vector<Token*> Generated_Undefined_Tokens;
vector<string> Included_Files; //for loop holes to not exist
Selector *S;
int _SYSTEM_BIT_TYPE = 4;

vector<string> Pre_Defined_Tokens;
void Init_Pre_Defined_Tokens()
{
    Pre_Defined_Tokens.push_back("return");
    Pre_Defined_Tokens.push_back("pop");
    Pre_Defined_Tokens.push_back("push");
    Pre_Defined_Tokens.push_back("halt");
    Pre_Defined_Tokens.push_back("Size");
    Pre_Defined_Tokens.push_back("Static");
}

//main ~/test.g ~/test.asm -win32 -x86 -F -32
int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		return -1;
	}
    Init_Registers();
    S = new Selector(argv[4]);
	string OUTPUT = "";
    if (strcmp(argv[3],"-win32") == 0)
    {
        OUTPUT = "";// "global main\n";
    }
    else if (strcmp(argv[3],"-unix") == 0)
    {
        OUTPUT = "global _start\n_start:\ncall _main\nmov eax, 1\n mov ebx, 0\nint 80h\n\n";
    }
    if (strcmp(argv[5], "-F") == 0)
    {
        _SYSTEM_BIT_TYPE = -atoi(argv[6]) / 8;
    }

    Lexer l;
	l.OpenFile(argv[1]);
    string start_file = argv[1];
    Included_Files.push_back(start_file);

    Parser p;
    p.Input = l.output;
	p.Working_Dir = argv[1];
    Init_Pre_Defined_Tokens();
    p.Factory();

    Definer d;
    d.Input_Of_Tokens = p.Output;
    d.Defined_Types = p.Defined_Keywords;
    d.Factory();

    Generator g;
    g.Input = p.Output;
    g.Types = d.Output;
    g.Factory();

    Emulator e(OUTPUT);
    e.Input = g.Output;
    e.Factory();

	ofstream o(argv[2]);
    o << OUTPUT;//b.Output;
    o.close();

    if (strcmp(argv[3], "-win32") == 0)
    {
        stringstream output;
        output << "..\\Cpp\\Assemblers\\yasm_win.exe -g dwarf2 -f win32 -o " << argv[1] << ".obj " << argv[2];

        std::system(output.str().c_str());
        output = stringstream();

        output << "..\\Cpp\\Linkers\\GoLink.exe " << "/console " << "/debug coff " << "/entry main " << argv[1] << ".obj " << "kernel32.dll ";

        std::system(output.str().c_str());
    }
    else if (strcmp(argv[3], "-unix") == 0)
    {

    }
    return 0;
}


