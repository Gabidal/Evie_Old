#include "../H/UI/Usr.h"
#include "../H/Lexer/Lexer.h"
#include "../H/PreProsessor/PreProsessor.h"
#include "../H/Parser/Parser.h"
#include "../H/Parser/PostProsessor.h"
#include "../H/UI/Safe.h"
#include "../H/Test/Test.h"
#include "../H/UI/Producer.h"
#include "../H/Nodes/Node.h"
#include "../H/Flags.h"
#include "../H/Docker/Mangler.h"
#include "../H/Docker/Docker.h"
#include "../H/Docker/HTTPS.h"
#include "../H/Docker/OBJ.h"
#include "../H/BackEnd/BackEnd.h"
#include "../H/BackEnd/IRGenerator.h"
#include "../H/BackEnd/Selector.h"
#include "../H/BackEnd/x86.h"
#include "../H/BackEnd/IRPostProsessor.h"

#include <sstream>
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

Usr* sys;
Node* Global_Scope;
Selector* selector;
x86_64_Win X86_64_WIN;
int _SYSTEM_BIT_SIZE_ = 4;

string Output = "";

//Evie.exe -in ~/test.e -out ~/test.asm -f exe -os win32 -arch x86 -mode 32 -debug dwarf2
//Evie.exe -in ~/test.e
int main(int argc, char* argv[])
{
    if (argc == 1) {
        //this happends when no parameter are given
        cout << "Argument types are: \n";
        cout << "-in [relative path/source file]\n";
        cout << "-out [relative path/output file name]\n";
        cout << "-os [target operating system (win32/unix)]\n";
        cout << "-host [the host operating system (win32/unix)]\n";
        cout << "-arch [output assembly type (x86/arm)]\n";
        cout << "-lib [relative path/lib name]\n";
        cout << "-repo_dir [relative path/folder name (for saving git repos there)]\n";
        cout << (string)"-f [\n  supported output file formats are:\n" +
            "  exe(executable (works for unix as well)),\n" + 
            "  lib(static lib),\n" +
            "  dll(dynamic library (support is not made yet!))\n" + 
            "]\n";
        cout << "-mode [bit mode for assembly output (32/64)]\n";
        cout << (string)"-debug [\n supported debug symbol types:\n" +
            "  dwarf2\n" +
            "]\n";
        cout << endl;
        return -1;
    }
    Lexer::DecimalSeparator = '.';
    Lexer::ExponentSeparator = 'e';
    Lexer::SingleLineCommentIdentifier = '#';
    Lexer::StringIdentifier = '\"';
    Lexer::Keywords = {
        "type", "func", "loyal", "export", "import", "use", "if", "while", "else", "ptr", "ref", "cache", "decimal", "jump", /*"size", size is no more a keyword because it can be also a variable name, only special in a class scoope*/ "return", "state", "const",
        "cpp", "evie", "vivid"
    };
    sys = new Usr(argv, argc);
    _SYSTEM_BIT_SIZE_ = atoi(sys->Info.Bits_Mode.c_str());
    
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

    //temporary
    MANGLER::Add_ID({ "t",{MANGLER::VARIABLE, "type"} });

    DOCKER::Slicer = TXT::Unwrap;
    DOCKER::Set_Default_Translator(TXT::TXT_Analyzer);
    DOCKER::Add_Translator("\x7F" "ELF", ELF::ELF_Analyzer);
    DOCKER::Add_Translator("!<arch>", LIB::LIB_Analyzer);
    DOCKER::Add_Translator(";analyze", ASM::ASM_Analyzer);
    DOCKER::Add_Translator("https", HTTPS::HTTPS_Analyser);
    DOCKER::Add_Translator("L\x1", OBJ::OBJ_Analyser);
    DOCKER::Add_Translator("\x64\x86\x01", OBJ::OBJ_Analyser);

    Global_Scope = new Node(CLASS_NODE);
    Global_Scope->Name = "GLOBAL_SCOPE";

    vector<Component> Input;
    PreProsessor preprosessor(Input);
    preprosessor.Include(sys->Info.Source_File.c_str());

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

    selector = new Selector();

    vector<IR*> IRs;
    IRGenerator g(Global_Scope, Global_Scope->Childs, &IRs);

    IRPostProsessor IRpost(&IRs);

    BackEnd Back(IRs, Output);

    ofstream o(sys->Info.Destination_File.c_str());
    o << Output;
    o.close();

    Producer pr;
    pr.Assemble_Command();
    return 0;
}
