#include "../H/UI/Usr.h"
#include "../H/Lexer/Lexer.h"
#include "../H/PreProsessor/PreProsessor.h"
#include "../H/Parser/Parser.h"
#include "../H/PostProsessor/PostProsessor.h"
#include "../H/UI/Safe.h"
#include "../H/Test/Test.h"
#include "../H/UI/Producer.h"
#include "../H/Nodes/Node.h"
#include "../H/Flags.h"
#include "../H/Docker/Mangler.h"
#include "../H/Docker/Docker.h"
#include "../H/Docker/HTTPS.h"

#include <sstream>
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

Usr* sys;
Node* Global_Scope;
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

//Evie.exe -in ~/test.e -out ~/test.asm -f exe -os win32 -arch x86 -mode 32 -debug dwarf2
//Evie.exe -in ~/test.e
int main(int argc, char* argv[])
{
    if (argc == 1) {
        //this happends when do parameter are given
        cout << "Argument types are: \n";
        cout << "-in [relative path/source file]\n";
        cout << "-out [relative path/output file name]\n";
        cout << (string)"-f [\n  supported output file formats are:\n" +
            "  exe(executable works for unix as well),\n" + 
            "  lib(static lib),\n" +
            "  dll(dynamic library support is not made yet!)\n" + 
            "]\n";
        cout << "-os [operating system (win32/unix)]\n";
        cout << "-arch [x86/arm]\n";
        cout << "-mode [bit mode 32/64]\n";
        cout << "-debug [debug symbol type(dwarf2)]\n";
        cout << "-repo_dir [folder name]\n";
        cout << endl;
        return -1;
    }
    Lexer::DecimalSeparator = '.';
    Lexer::ExponentSeparator = 'e';
    Lexer::SingleLineCommentIdentifier = '#';
    Lexer::StringIdentifier = '\"';
    Lexer::Keywords = {"type", "func", "loyal", "export", "import", "use", "if", "while", "else", "ptr", "ref", "cache", "decimal", "jump", "size", "return", "state"};
    sys = new Usr(argv, argc);
    _SYSTEM_BIT_SIZE_ = atoi(sys->Info.Bits_Mode.c_str());

    string OUTPUT = "";
    
    string start_file = sys->Info.Source_File.c_str();

    MANGLER::Add_ID({ "P",{MANGLER::PREFIX, "ptr"} });
    MANGLER::Add_ID({ "R",{MANGLER::PREFIX, "ref"} });
    MANGLER::Add_ID({ "c",{MANGLER::VARIABLE, "1"} });
    MANGLER::Add_ID({ "s",{MANGLER::VARIABLE, "2"} });
    MANGLER::Add_ID({ "i",{MANGLER::VARIABLE, "4"} });
    MANGLER::Add_ID({ "f",{MANGLER::VARIABLE, "4"} });
    MANGLER::Add_ID({ "d",{MANGLER::VARIABLE, "8"} });
    MANGLER::Add_ID({ "l",{MANGLER::VARIABLE, "4"} });
    MANGLER::Add_ID({ "x",{MANGLER::VARIABLE, "8"} });

    DOCKER::Set_Default_Translator(TXT::TXT_Analyzer);
    DOCKER::Add_Translator("\x7F" "ELF", ELF::ELF_Analyzer);
    DOCKER::Add_Translator("!<arch>", LIB::LIB_Analyzer);
    DOCKER::Add_Translator(";analyze", ASM::ASM_Analyzer);
    DOCKER::Add_Translator("https", HTTPS::HTTPS_Analyser);

    //testsweetter
    //Test t;
    //end of testsweetter

    Global_Scope = new Node(CLASS_NODE);
    Global_Scope->Name = "GLOBAL_SCOPE";

    vector<Component> Input = Lexer::GetComponentsFromFile(sys->Info.Source_File.c_str());

    PreProsessor preprosessor(Input);
    preprosessor.Included_Files.push_back(DOCKER::Update_Working_Dir(sys->Info.Source_File.c_str()));

    preprosessor.Defined_Constants = 
    {
        {"SOURCE_FILE",         Component("\"" + sys->Info.Source_File + "\"", Flags::STRING_COMPONENT)},
        {"DESTINATION_FILE",    Component("\"" + sys->Info.Destination_File + "\"", Flags::STRING_COMPONENT)},
        {"OS",                  Component("\"" + sys->Info.OS + "\"", Flags::STRING_COMPONENT)},
        {"ARCHITECTURE",        Component("\"" + sys->Info.Architecture + "\"", Flags::STRING_COMPONENT)},
        {"FORMAT",              Component("\"" + sys->Info.Format + "\"", Flags::STRING_COMPONENT)},
        {"BITS_MODE",           Component(sys->Info.Bits_Mode, Flags::NUMBER_COMPONENT)},
        {"true",                Component("1", Flags::NUMBER_COMPONENT)},
        {"false",               Component("0", Flags::NUMBER_COMPONENT)},
    };
    preprosessor.Factory();

    Parser p(Global_Scope);
    p.Input = Input;
    p.Factory();

    PostProsessor postprosessor(Global_Scope);
    postprosessor.Components = p.Input;
    postprosessor.Factory();
    Global_Scope->Append(Global_Scope->Childs, postprosessor.Input);

    ofstream o(sys->Info.Destination_File.c_str());
    o << OUTPUT;//b.Output;
    o.close();

    Producer pr;
    pr.Assemble_Command();
    return 0;
}
