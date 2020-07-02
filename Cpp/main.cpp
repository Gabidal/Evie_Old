#include "../H/Lexer/Lexer.h"
#include "../H/Parser/Parser.h"
#include "../H/Back/Definer.h"
#include "../H/Emulator/Emulator.h"
#include "../H/Selector/Selector.h"
#include "../H/Back/Generator.h"
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
int SYNTAX = 0;

Object* Root;
class RootTable : public Object {
    map<string, Object*> Get_Members() {
        return map<string, Object*>();
    }
};

class FlagTable : public Object {
    
    map<string, Object*> Get_Members() {
        return {
            make_pair("_NUMBER_", new IntObject(new int(_Number_))),
            make_pair("_EXTERNAL_", new IntObject(new int(_External_))),
            make_pair("_TYPE_", new IntObject(new int(_Type_))),
            make_pair("_FUNCTION_", new IntObject(new int(_Function_))),
            make_pair("_ARRAY_", new IntObject(new int(_Array_))),
            make_pair("_CONDITION_", new IntObject(new int(_Condition_))),
            make_pair("_OPERATOR_", new IntObject(new int(_Operator_))),
            make_pair("_RETURNING_", new IntObject(new int(_Returning_))),
            make_pair("_CALL_", new IntObject(new int(_Call_))),
            make_pair("_PARAMETER_", new IntObject(new int(_Parameter_))),
            make_pair("_CONSTRUCTOR_", new IntObject(new int(_Constructor_))),
            make_pair("_PARAMETER_", new IntObject(new int(_Parameter_))),
            make_pair("_REGISTER_", new IntObject(new int(_Register_))),

            make_pair("_TASK_FOR_NON_VOLATILING_", new IntObject(new int(Task_For_Non_Volatiling))),
            make_pair("_TASK_FOR_RETURNING_", new IntObject(new int(Task_For_Returning))),
            make_pair("_TASK_FOR_STACK_BASE_ADDRESSING_", new IntObject(new int(Task_For_Type_Address_Basing))),
            make_pair("_TASK_FOR_STACK_ADDRESSING_", new IntObject(new int(Task_For_Type_Address))),
            make_pair("_TASK_FOR_DEST_OFFSETTING_", new IntObject(new int(Task_For_Dest_Offsetting))),
            make_pair("_TASK_FOR_SOURCE_OFFSETTING_", new IntObject(new int(Task_For_Source_Offsetting))),
            make_pair("_TASK_FOR_REMAINDER_", new IntObject(new int(Task_For_Remainder))),
            make_pair("_TASK_FOR_GENERAL_PURPOSE_", new IntObject(new int(Task_For_General_Purpose))),
            make_pair("_TASK_FOR_FLOATING_MATH_", new IntObject(new int(Task_For_Floating_Math))),

            make_pair("_NEED_FOR_SPACE_", new IntObject(new int(_Need_For_Space_))),
            make_pair("_GENERATED_", new IntObject(new int(_Generated_))),

            make_pair("_POINTTING_", new IntObject(new int(_Pointting_))),
            make_pair("_ARRAY_", new IntObject(new int(_Array_))),
            make_pair("_GIVING_ADDRESS_", new IntObject(new int(_Giving_Address_))),
            make_pair("_STRING_", new IntObject(new int(_String_))),
            make_pair("_PREPROSESSOR_", new IntObject(new int(_Preprosessor_))),
            make_pair("_SKIP_", new IntObject(new int(_Skip_))),
        };
    }
};
Object* FT;

extern vector<Token*> Global_Data;
extern vector<Token*> Defined_Local_To_Global_Variables;
map<string, Token*> Preprosessor_Tokens;
vector<string> Included_Files; //for loop holes to not exist
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
    Pre_Defined_Tokens.push_back("size");
    Pre_Defined_Tokens.push_back("state");
    //)

    //the caster
    //Pre_Defined_Tokens.push_back("as");
}

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
    _SYSTEM_BIT_TYPE = atoi(sys->Info.Bits_Mode.c_str());
    S = new Selector(sys->Info.Architecture);

    string OUTPUT = "";
    Root = new RootTable();
    Root->Set("_SYS_", sys);
    FT = new FlagTable();
    
    string start_file = sys->Info.Source_File.c_str();
    Included_Files.push_back(start_file);

    Init_Pre_Defined_Tokens();

    //testsweetter
    //Test t;
    //end of testsweetter

    Parser p;
    p.Update_Dir(sys->Info.Source_File.c_str());
    p.Input = Lexer::GetComponentsFromFile(sys->Info.Source_File.c_str());
    //p.Working_Dir = start_file;
    p.Factory();

    p.Append(&p.Output, Global_Data);
    p.Append(&p.Defined_Keywords, Defined_Local_To_Global_Variables);

    Definer d;
    d.Input_Of_Tokens = p.Output;
    d.Defined_Types = p.Defined_Keywords;
    d.Factory();

    Generator g;
    g.Input = d.Input_Of_Tokens;
    g.Types = d.Output;
    g.Factory();

    Safe s;
    s.Input = g.Output;
    s.Types = p.Defined_Keywords;
    s.Factory();

    Emulator e(OUTPUT);
    e.Input = g.Output;
    e.Factory();

    ofstream o(sys->Info.Destination_File.c_str());
    o << OUTPUT;//b.Output;
    o.close();

    Producer pr;
    pr.Assemble_Command();
    return 0;
}
