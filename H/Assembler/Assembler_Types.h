#ifndef _ASSEMBLER_TYPES_H_
#define _ASSEMBLER_TYPES_H_

#include <string>
#include <vector>

using namespace std;

class Alias{
public:
    string Name = "";
    vector<string> Aliases;

    Alias(string Name, vector<string> Aliases){
        this->Aliases = Aliases;
        this->Name = Name;
    }

    bool Has(string value) {
        if (value == Name)
            return true;
        for (auto i : Aliases) {
            if (i == value)
                return true;
        }

        return false;
    }
};

inline vector<Alias> ALIASES = {
    {"global", { "extern", "global", "globl" }},
    {"section", { "section", "segment" }},
    {"text", { "code", "text", ".text" }},
    {"data", { "data", ".data" }},
    {"intel_syntax", { "intel_syntax" }},
    {"noprefix", { "noprefix" }},

    {"zero", { "zero" }},
    {"asciz", { "asciz", "string" }},
    {"byte", { "byte", "byte ptr", "db", "ascii" }},
    {"word", { "word", "word ptr" "short", "dw", "half" }},
    {"dword", { "dword", "dword ptr" "long", "dd" }},
    {"qword", { "qword", "qword ptr", "quad", "dq" }},

    {"xmmword", { "xmmword", "xmmword ptr", "xword", "xword ptr" }},
    {"ymmword", { "ymmword", "ymmword ptr", "yword", "yword ptr" }},
    {"zmmword", { "zmmword", "zmmword ptr", "zword", "zword ptr" }}
};

namespace WORD_FLAGS {
    const int UNKNOWN               = 0;
    const int REGISTER              = 1 << 0;
    const int MEMORY                = 1 << 1;
    const int OPCODE                = 1 << 2;
    const int LABEL                 = 1 << 3;   
    const int NUMBER                = 1 << 4;
    const int OPERATOR              = 1 << 5;   //// '*', '+', ',', '-', '.'
    const int LABEL_INDICATOR       = 1 << 6;
    const int TEXT                  = 1 << 7;
    const int LINE_ENDING           = 1 << 8;
    const int SIZE_IDENTIFIER       = 1 << 9;   //dword ptr
    const int DATA_SIZE_IDENTIFIER  = 1 << 10;   //db, dd, dw, dq, etc..
    const int ALIAS                 = 1 << 11;
}

class Word{
public:
    string Name = "";
    vector<Word*> Childs;

    int Flags = 0;

    int SIZE_IDENTIFIER_VALUE = 0;

    Word(){}
    Word(string name, int f){
        Name = name;
        Flags = f;
    }

    bool is(int f) {
        return (Flags & f) == f;
    }

    void Remove(int f) {
        f = Flags & ~f;
    }

    string is(Alias a) {
        for (auto& i : a.Aliases){
            if (i == Name)
                return a.Name;
        }
        return "";
    }

    Alias* is(vector<Alias> values) {
        for (auto& i : values) {
            if (is(i) != "")
                return &i;
        }
        return nullptr;
    }

    bool is(string name) {
        if (Name == name)
            return true;
        return false;
    }

    bool is(vector<string> values) {
        for (auto& i : values) {
            if (is(i))
                return true;
        }
        return false;
    }

    bool Is_Number(string n) {
        char* index = nullptr;
        return strtol(n.c_str(), &index, 10) >= 0;
    }
};

class REX {
public:
    unsigned char ID = 0;
    bool W = false;
    bool R = false;
    bool X = false;
    bool B = false;
};

class MODRM{
public:
    unsigned char Mod = 0;
    unsigned char Reg = 0;
    unsigned char RM = 0;
};

class SIB{
    public:
    bool Is_Used = false;
    unsigned char Scale = 0;
    unsigned char Index = 0;
    unsigned char Base = 0;
    unsigned int Displacement = 0;

    bool Index_Rex = false;
    bool Base_Rex = false;
};

class Byte_Map {
public:
    unsigned int Prefix = 0;            //upto 1-4 bytes
    REX Rex;                            //upto 1 byte
    unsigned int Opcode = 0;            //upto 1-4 bytes
    MODRM ModRM = {0};                  //upto 1 byte
    SIB Sib = {0};                      //upto 1 byte
    unsigned long long Displacement = 0;//upto 1, 2, 4, 8 bytes
    unsigned long long Immediate = 0;   //upto 1, 2, 4, 8 bytes

    //for locations
    int Size = 0;
    long long Address = 0;
};

class Byte_Map_Section{
public:
    string Name = "";
    vector<Byte_Map*> Byte_Maps;
    string Calculated_Byte_Maps = "";

    long long Calculated_Size = 0;
    long long Calculated_Address = 0;

    bool Is_Data_Section = false;

    Byte_Map_Section(string name){
        Name = name;
    }
};

namespace MODRM_FLAGS {
    static constexpr unsigned char RM       = 1 << 0;
    static constexpr unsigned char DISP8    = 1 << 1;
    static constexpr unsigned char DISP32   = 1 << 2;
    static constexpr unsigned char MEMORY   = 1 << 3;
    static constexpr unsigned char SIB      = 1 << 4;
};

namespace CHAR_GROUPS{
    constexpr char BIG_LETTER_GROUP_START_INDEX = 65;
    constexpr char BIG_LETTER_GROUP_END_INDEX = 90;

    constexpr char SMALL_LETTER_GROUP_START_INDEX = 97;
    constexpr char SMALL_LETTER_GROUP_END_INDEX = 122;

    constexpr char NUMBER_GROUP_START_INDEX = 48;
    constexpr char NUMBER_GROUP_END_INDEX = 57;

    // '*', '+', ',', '-', '.'
    constexpr char OPERATOR_GROUP_START_INDEX = 42; 
    constexpr char OPERATOR_GROUP_END_INDEX = 46;

    constexpr char SPACE_INDEX = 32;   // ' '
    constexpr char LINE_ENDING_INDEX = 10; // '\n'

    constexpr char OPENING_PARANTHESIS_INDEX = 40;
    constexpr char CLOSING_PARANTHESIS_INDEX = 41;

    constexpr char OPENING_BRACKET_INDEX = 123;
    constexpr char CLOSING_BRACKET_INDEX = 125;

    constexpr char HASH_TAG_INDEX = 35;
    constexpr char DOLLAR_SIGN_INDEX = 36;
    constexpr char PERCENT_SIGN_INDEX = 37;
    constexpr char AT_SIGN_INDEX = 64;
    constexpr char UNDERLINE_INDEX = 95;
    constexpr char QUESTION_MARK_INDEX = 63;

    constexpr char LABEL_START_CHARACHTER_INDEX = 58; // ":"
    constexpr char SEMICOLON_INDEX = 59;
}

#endif