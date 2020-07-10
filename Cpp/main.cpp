#include "../H/Lexer/Lexer.h"
#include "../H/Parser/Parser.h"
#include "../H/UI/Usr.h"
#include "../H/UI/Producer.h"
#include "../H/UI/Safe.h"
#include "../H/Test/Test.h"
#include <sstream>
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
using namespace std;

Usr* sys;
int _SYSTEM_BIT_SIZE_ = 4;

/*
int argumentIterator;
char dox86;
int targetWin32;
int targetUnix;

char OFBUF[128];
char WDBUF[128];
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

//Evie.exe -in ~/test.e -out ~/test.asm -f exe -os win32 -arch x86 -mode 4 -debug dwarf2
int main(int argc, char* argv[])
{
    if (argc == 1)
        return -1 ;
    Lexer::DecimalSeparator = '.';
    Lexer::ExponentSeparator = 'e';
    Lexer::SingleLineCommentIdentifier = '#';
    Lexer::StringIdentifier = '\"';
    Lexer::Keywords = { "while", "type", "func", "loyal", "export", "import", "use", "if", "ptr", "mangle", "cache", "decimal", "hidden"};
    sys = new Usr(argv, argc);
    _SYSTEM_BIT_SIZE_ = atoi(sys->Info.Bits_Mode.c_str());

    string OUTPUT = "";
    
    string start_file = sys->Info.Source_File.c_str();

    //testsweetter
    //Test t;
    //end of testsweetter

    Parser p;
    p.Input = Lexer::GetComponentsFromFile(sys->Info.Source_File.c_str());
    //p.Working_Dir = start_file;
    p.Factory();


    ofstream o(sys->Info.Destination_File.c_str());
    o << OUTPUT;//b.Output;
    o.close();

    Producer pr;
    pr.Assemble_Command();
    return 0;
}
