#include "../H/Lexer/Lexer.h"
#include "../H/Parser/Parser.h"
#include "../H/Back/Definer.h"
#include "../H/Emulator/Emulator.h"
#include "../H/Selector/Selector.h"
#include "../H/Back/Generator.h"
#include "../H/UI/Usr.h"
#include <sstream>
#include <iostream>
using namespace std;
int SYNTAX = 0;
vector<Token*> Generated_Undefined_Tokens;
vector<string> Included_Files; //for loop holes to not exist
map<string, Token*> Register_Lock;
Selector* S;
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
    Pre_Defined_Tokens.push_back("new");
}

/*
int argumentIterator;
char dox86;
int targetWin32;
int targetUnix;

char OFBUF[128];
char WDBUF[128];*/

//main -in ~/test.g -out ~/test.asm -os win32 -arch x86 -mode 32
int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        return -1;
    }
    string OUTPUT = "";
    /*
    dox86 = 0;
    targetWin32 = 0;
    targetUnix = 0;
    const char* Source = "";
    //SuperLeaf 1995#5912   //committed these 19/03/2020, added 19/03/2020 at:9:15 AM
    
    {
        for (argumentIterator = 1; argumentIterator < argc; argumentIterator++) {
            if (strcmp(argv[argumentIterator], "-win32") == 0) {
                OUTPUT = "";
                targetWin32 = 1;
            }
            else if (strcmp(argv[argumentIterator], "-unix") == 0 && dox86 == 1) {
                OUTPUT = "global _start\n_start:\ncall main\nmov eax, 1\n mov ebx, 0\nint 80h\n\n";
                targetUnix = 1;
            }
            else if (strcmp(argv[argumentIterator], "-x86") == 0) {
                dox86 = 1;
                S = new Selector(argv[argumentIterator]);
            }
            else if (strcmp(argv[argumentIterator], "-ARM") == 0){
                S = new Selector(argv[argumentIterator]);
            }
            else if (strcmp(argv[argumentIterator], "-F") == 0) {
                argumentIterator++;
                if (argv[argumentIterator != NULL]) {
                    _SYSTEM_BIT_TYPE = -atoi(argv[argumentIterator]) / 8;
                }
                else {
                    fprintf(stderr, "ERROR WHEN NO ARGS TO -F ARE SPECIFIED");
                    return -1; //i assume this is like an exit
                }
            }
            else if (strcmp(argv[argumentIterator], "--working-dir") == 0) {
                argumentIterator++;
                if (argv[argumentIterator != NULL]) { //argv[1] idk what is this argv, just gave it a nice name
                    strcpy_s(OFBUF, argv[argumentIterator]);
                }
                else {
                    fprintf(stderr, "ERROR WHEN NO ARGS TO --working-dir ARE SPECIFIED");
                    return -1; //i assume this is like an exit
                }
            }
            else if (strcmp(argv[argumentIterator], "--output") == 0) {
                argumentIterator++;
                if (argv[argumentIterator != NULL]) { // argv[2] SEE OFFSTREAM!
                    strcpy_s(WDBUF, argv[argumentIterator]);
                }
                else {
                    fprintf(stderr, "ERROR WHEN NO ARGS TO --output ARE SPECIFIED");
                    return -1; //i assume this is like an exit
                }
            }
            else
            {
                Source = argv[argumentIterator];
            }
        }
    }*/

    Usr usr(argv, argc);
    _SYSTEM_BIT_TYPE = usr.Output.Bits_Mode;
    S = new Selector(usr.Output.Architecture);


    Lexer l;
    l.OpenFile(usr.Output.Source_File.c_str());
    string start_file = usr.Output.Source_File.c_str();
    Included_Files.push_back(start_file);

    Parser p;
    p.Input = l.output;
    p.Working_Dir = start_file;
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

    ofstream o(usr.Output.Destination_File.c_str());
    o << OUTPUT;//b.Output;
    o.close();

    if (usr.Output.OS == "win32")
    {
        //target windows
        stringstream output;
        output << "..\\Cpp\\Assemblers\\yasm_win.exe -g dwarf2 -f win32 -o " << usr.Output.Destination_File << ".obj " << usr.Output.Destination_File;

        std::system(output.str().c_str());
        output = stringstream();

        output << "..\\Cpp\\Linkers\\GoLink.exe " << "/console " << "/debug coff " << "/entry main " << usr.Output.Destination_File << ".obj " << "kernel32.dll ";

        std::system(output.str().c_str());
    }
    else if (usr.Output.OS == "unix")
    {
        //target unix
    }
    return 0;
}