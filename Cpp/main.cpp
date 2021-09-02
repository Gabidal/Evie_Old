#include "../H/UI/Usr.h"
#include "../H/Lexer/Lexer.h"
#include "../H/PreProsessor/PreProsessor.h"
#include "../H/Parser/Parser.h"
#include "../H/Parser/PostProsessor.h"
#include "../H/UI/Safe.h"
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
#include "../H/BackEnd/ARM.h"
#include "../H/BackEnd/IRPostProsessor.h"
#include "../H/BackEnd/DebugGenerator.h"
#include "../H/UI/Satellite.h"
#include "../H/UI/Service.h"

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
x86_64 X86_64;
ARM_64 _ARM_64;
int _SYSTEM_BIT_SIZE_ = 4;

string Output; 

extern string VT_API;
//Evie.exe -in ~/test.e -out ~/test.asm -f exe -os win32 -arch x86 -mode 32 -d
//Evie.exe -in ~/test.e
int Build(int argc, const char* argv[])
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
        cout << "-repo-dir [relative/absolute path for saving git repos]\n";
        cout << (string)"-f [\n  supported output file formats are:\n" +
            "  exe(executable (works for unix as well)),\n" +
            "  lib(static lib),\n" +
            "  dll(dynamic library (support is not made yet!))\n" +
            "]\n";
        cout << "-mode [bit mode for assembly output (32/64)]\n";
        cout << (string)"-debug [\n supported debug symbol types:\n" +
            "  dwarf2\n" +
            "]\n";
        cout << "-vt [virus total API-key]\n";
        cout << "-reference-count-size [reference count size]\n";
        cout << "-service [starts Evie as a service with a port returned in standard out]\n";
        cout << endl;
        return -1;
    }
    Lexer::DecimalSeparator = '.';
    Lexer::ExponentSeparator = 'e';
    Lexer::SingleLineCommentIdentifier = '#';
    Lexer::StringIdentifier = '\"';
    Lexer::Keywords = {
        "type", "func", "export", "import", "use", "if", "while", "else", "ptr", "ref", "jump", /*"size", size and deciaml and integer and format is no more a keyword because it can be also a variable name, only special in a class scoope*/ "return", "state", "const",
        "cpp", "evie", "vivid", "plain", "static"
    };
    sys = new Usr(argv, argc);
    if (VT_API != "")
        sys->Info.VT_API = VT_API;
    _SYSTEM_BIT_SIZE_ = atoi(sys->Info.Bits_Mode.c_str());
    if (sys->Info.Architecture == "x86")
        Output = ".intel_syntax noprefix\n";
    string start_file = sys->Info.Source_File.c_str();

    Satellite satellite;

    MANGLER::Add_ID("cpp", { "P",{MANGLER::PREFIX, "ptr"} });
    MANGLER::Add_ID("cpp", { "R",{MANGLER::PREFIX, "ref"} });
    MANGLER::Add_ID("cpp", { "c",{MANGLER::VARIABLE, "1 integer"} });
    MANGLER::Add_ID("cpp", { "s",{MANGLER::VARIABLE, "2 integer"} });
    MANGLER::Add_ID("cpp", { "i",{MANGLER::VARIABLE, "4 integer"} });
    MANGLER::Add_ID("cpp", { "f",{MANGLER::VARIABLE, "4 decimal"} });
    MANGLER::Add_ID("cpp", { "d",{MANGLER::VARIABLE, "8 decimal"} });
    MANGLER::Add_ID("cpp", { "l",{MANGLER::VARIABLE, "4 integer"} });
    MANGLER::Add_ID("cpp", { "x",{MANGLER::VARIABLE, "8 integer"} });
    MANGLER::Add_ID("cpp", { { "N" }, { MANGLER::CLASS, "" } });
    MANGLER::Add_ID("cpp", { { "E" }, { MANGLER::END_CLASS, "" } });
    //temporary
    MANGLER::Add_ID("cpp", { "t",{MANGLER::VARIABLE, "type"} });

    MANGLER::Add_ID("vivid", { "P",{MANGLER::PREFIX, "ptr"} });
    MANGLER::Add_ID("vivid", { "R",{MANGLER::PREFIX, "ref"} });
    MANGLER::Add_ID("vivid", { "h",{MANGLER::VARIABLE, "1 integer"} });
    MANGLER::Add_ID("vivid", { "c",{MANGLER::VARIABLE, "1 integer"} });
    MANGLER::Add_ID("vivid", { "t",{MANGLER::VARIABLE, "2 integer"} });
    MANGLER::Add_ID("vivid", { "s",{MANGLER::VARIABLE, "2 integer"} });
    MANGLER::Add_ID("vivid", { "j",{MANGLER::VARIABLE, "4 integer"} });
    MANGLER::Add_ID("vivid", { "i",{MANGLER::VARIABLE, "4 integer"} });
    MANGLER::Add_ID("vivid", { "f",{MANGLER::VARIABLE, "4 decimal"} });
    MANGLER::Add_ID("vivid", { "d",{MANGLER::VARIABLE, "8 decimal"} });
    MANGLER::Add_ID("vivid", { "x",{MANGLER::VARIABLE, "8 integer"} });
    MANGLER::Add_ID("vivid", { "y",{MANGLER::VARIABLE, "8 integer"} });
    MANGLER::Add_ID("vivid", { { "N" }, { MANGLER::CLASS, "" } });
    MANGLER::Add_ID("vivid", { { "E" }, { MANGLER::END_CLASS, "" } });
    MANGLER::Add_ID("vivid", { { "_r" }, { MANGLER::RETURN, "" } });
    //temporary
    //MANGLER::Add_ID("vivid", { "t",{MANGLER::VARIABLE, "type"} });

    DOCKER::Slicer = TXT::Unwrap;
    DOCKER::Set_Default_Translator(TXT::TXT_Analyzer);
    DOCKER::Add_Translator(Location::Header, "\x7F" "ELF", ELF::ELF_Analyzer);
    DOCKER::Add_Translator(Location::Header, "!<arch>", LIB::LIB_Analyzer);
    DOCKER::Add_Translator(Location::Header, "#analyze", ASM::ASM_Analyzer);
    DOCKER::Add_Translator(Location::Header, "https", HTTPS::HTTPS_Analyser);
    DOCKER::Add_Translator(Location::Header, "L\x1", OBJ::OBJ_Analyser);
    DOCKER::Add_Translator(Location::Header, "\x64\x86", OBJ::OBJ_Analyser);
    DOCKER::Add_Translator(Location::Header, "\x32\x86", OBJ::OBJ_Analyser);

    DOCKER::Add_Translator(Location::File_Name, "asm", ASM::ASM_Analyzer);

    vector<Component> Input;
    PreProsessor preprosessor(Input);

    Global_Scope = new Node(CLASS_NODE, new Position());
    Global_Scope->Name = "GLOBAL_SCOPE";
    Global_Scope->Inheritted.push_back("static");

    selector = new Selector();

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
    
    if (sys->Info.Is_Service) {
        Service service = Service();
        return 0;
    }

    preprosessor.Include(sys->Info.Source_File.c_str());
    
    preprosessor.Factory();

    Parser p(Global_Scope);
    p.Input = Input;
    p.Factory();

    PostProsessor postprosessor(Global_Scope);
    postprosessor.Components = p.Input;
    postprosessor.Factory();
    Global_Scope->Append(Global_Scope->Childs, postprosessor.Input);

    vector<IR*> IRs;
    IRGenerator g(Global_Scope, Global_Scope->Childs, &IRs);

    IRPostProsessor IRpost(&IRs);

    if (sys->Info.Debug)
        DebugGenerator DG(IRs);

    BackEnd Back(IRs, Output);

    ofstream o(sys->Info.Destination_File.c_str());
    o << Output;
    o.close();

    Producer pr;
    pr.Assemble_Command();
    return 0;
}

#ifndef Test
//Evie.exe -in ~/test.e -out ~/test.asm -f exe -os win32 -arch x86 -mode 32 -debug dwarf2
//Evie.exe -in ~/test.e
int main(int argc, const char* argv[])
{
    Build(argc, argv);
    return 0;
}
#endif