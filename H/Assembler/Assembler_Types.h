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
        Aliases = Aliases;
        Name = Name;
    }
};

namespace KEYWORDS{
    const Alias GLOBAL("global", { "extern", "global", "globl" });
    const Alias SECTION("section", { "section", "segment" });
    const Alias TEXT("text", { "code", "text" });
    const Alias DATA("data", { "data" });
    const Alias INTEL_SYNTAX("intel_syntax", { "intel_syntax" });
    const Alias PREFIX("noprefix", { "noprefix" });

    const Alias ZERO("zero", { "zero" });
    const Alias ASCII("asciz", { "asciz", "string" });
    const Alias BYTE("byte", { "byte", "byte ptr", "db", "ascii" });
    const Alias WORD("word", { "word", "word ptr" "short", "dw", "half" });
    const Alias DWORD("dword", { "dword", "dword ptr" "long", "dd" });
    const Alias QWORD("qword", { "qword", "qword ptr", "quad", "dq" });

    const Alias XMMWORD("xmmword", { "xmmword", "xmmword ptr", "xword", "xword ptr" });
    const Alias YMMWORD("ymmword", { "ymmword", "ymmword ptr", "yword", "yword ptr" });
    const Alias ZMMWORD("zmmword", { "zmmword", "zmmword ptr", "zword", "zword ptr" });
}

class Word{
public:
    string Name = "";
    vector<Word*> Childs;

    Word(){}
    Word(string name){
        Name = name;
    }
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
    constexpr char LINE_ENDING_INDEX = '10'; // '\n'
}

#endif