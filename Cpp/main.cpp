#include "../H/Lexer/Lexer.h"
#include "../H/Parser/Parser.h"
#include "../H/Back/Definer.h"
#include "../H/Emulator/Emulator.h"
#include "../H/Selector/Selector.h"
#include "../H/Back/Generator.h"
#include "../H/UI/Usr.h"
#include <sstream>
#include <iostream>
#include <windows.h>
using namespace std;
int SYNTAX = 0;
vector<Token*> Generated_Undefined_Tokens;
vector<string> Included_Files; //for loop holes to not exist
map<string, Token*> Register_Lock;
Selector* S;
Usr* sys;
int _SYSTEM_BIT_TYPE = 4;

vector<string> Pre_Defined_Tokens;
void Init_Pre_Defined_Tokens()
{
    //return value
    Pre_Defined_Tokens.push_back("return");
    //pop value from stack into variable
    Pre_Defined_Tokens.push_back("pop");
    //push value into stack
    Pre_Defined_Tokens.push_back("push");

    //for system interrupts
    Pre_Defined_Tokens.push_back("halt");

    //malloc
    Pre_Defined_Tokens.push_back("new");

    //type indicators(
    Pre_Defined_Tokens.push_back("Size");
    Pre_Defined_Tokens.push_back("Static");
    //)

    //attach a string into output file
    Pre_Defined_Tokens.push_back("asm");
}

/*
int argumentIterator;
char dox86;
int targetWin32;
int targetUnix;

char OFBUF[128];
char WDBUF[128];*/

/*t
ypedef int(__cdecl* bananafunction)(int);

void banana(const char* lib) {
    HINSTANCE handle = LoadLibrary(lib);
    if (handle == NULL)
    {
        cout << "ya fool!" << endl;
        return;
    }
    bananafunction banana = (bananafunction)GetProcAddress(handle, "banana");
    if (banana == NULL)
    {
        cout << "stupid!" << endl;
        return;
    }
    cout << banana(1) << " working?" << endl;
    FreeLibrary(handle);
}*/

//main -in ~/test.g -out ~/test.asm -lib exe -os win32 -arch x86 -mode 32
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

    sys = new Usr(argv, argc);
    sys->Load();
    _SYSTEM_BIT_TYPE = atoi(sys->Info.Bits_Mode.c_str());
    S = new Selector(sys->Info.Architecture);

    Lexer l;
    l.OpenFile(sys->Info.Source_File.c_str());
    string start_file = sys->Info.Source_File.c_str();
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

    ofstream o(sys->Info.Destination_File.c_str());
    o << OUTPUT;//b.Output;
    o.close();

    if (sys->Info.OS == "win32" && (sys->Info.Architecture == "x86") && (sys->Info.Obj_Type == "exe"))
    {
        //target windows
        stringstream output;
        output << "..\\Cpp\\Assemblers\\yasm_win.exe -g dwarf2 -f win32 -o " << start_file << ".obj " << sys->Info.Destination_File;

        system(output.str().c_str());
        output = stringstream();

        output << "..\\Cpp\\Linkers\\GoLink.exe " << "/console " << "/debug coff " << "/entry main " << start_file << ".obj " << "kernel32.dll ";
        
        //output << "..\\Cpp\\Linkers\\GoLink.exe " << "/console " << "/dll " << "/debug coff " << start_file << ".obj " << "kernel32.dll ";

        system(output.str().c_str());
        //banana(("C:\\Users\\Quanf\\source\\repos\\GAS\\GAS\\IO\\" + start_file + ".dll").c_str());
    }
    else if (sys->Info.OS == "unix" && (sys->Info.Architecture == "x86") && (sys->Info.Obj_Type == "exe"))
    {
        stringstream output;
        output << "sudo apt install yasm";

        system(output.str().c_str());
        output = stringstream();

        output << "yasm -g dwarf2 -f elf32 -o " << sys->Info.Destination_File + ".o " << sys->Info.Destination_File;
        

        system(output.str().c_str());
        output = stringstream();

        output << "ld -m elf_i386 -o " << sys->Info.Destination_File + ".this_is_the_runnable " << sys->Info.Destination_File + ".o ";

        system(output.str().c_str());
        output = stringstream();

        output << "sudo chmod +x " << sys->Info.Destination_File + ".this_is_the_runnable ";

        system(output.str().c_str());
        //target unix
    }
    return 0;
}
