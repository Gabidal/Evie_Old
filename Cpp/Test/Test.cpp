#include "..\..\H\Test\Test.h"

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

int main() {
    Lexer::DecimalSeparator = '.';
    Lexer::ExponentSeparator = 'e';
    Lexer::SingleLineCommentIdentifier = '#';
    Lexer::StringIdentifier = '\"';
    Lexer::Keywords = { "while", "type", "func", "loyal", "export", "import", "use", "if", "ptr", "mangle", "cache", "decimal", "hidden" };
    _SYSTEM_BIT_TYPE = 4;
    S = new Selector("x86");

    string OUTPUT = "";
    Root = new RootTable();
    Root->Set("_SYS_", sys);
    FT = new FlagTable();
    Test t;
    return 0;
}

Test::Test()
{
    Parser_Classes();
    Print_Results();
}

void Test::Print_Results()
{
}

void Test::Parser_Classes()
{
	/*		type int(){
			}
	*/
	Parser p;
	p.Input = Lexer::GetComponents("type int(){\n}");
	p.Factory();
	if (p.Defined_Keywords[0]->Name != "int"){

	}
    
}
