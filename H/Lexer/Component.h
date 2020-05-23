#ifndef _COMPONENT_H_
#define _COMPONENT_H_
#include <string>
#include <vector>
#include "Position.h"
using namespace std;

constexpr int KEYWORD_COMPONENT         = 1 << 0;
constexpr int UNDEFINED_COMPONENT       = 1 << 1;
constexpr int PAREHTHESIS_COMPONENT     = 1 << 2;
constexpr int END_COMPONENT             = 1 << 3;
constexpr int STRING_COMPONENT          = 1 << 4;
constexpr int NUMBER_COMPONENT          = 1 << 5;
constexpr int COMMENT_COMPONENT         = 1 << 6;
constexpr int OPERATOR_COMPONENT        = 1 << 7;
constexpr int TEXT_COMPONENT            = 1 << 8;

class Component 
{
public:
    string Value;
    int Flags;
    Position Location; // LineNumber

    bool IsUsed = false; // UsedToken
    bool IsPointter = false; // Self_Mirroring
    bool IsInitialized = false; // _initted
    bool IsOperatorized = false; // _operatorized
    bool IsCall = false; // _Call
    bool IsGivingAddress = false; // _Giving_Address
    bool HasMemberOffsetting = false;   //(x.y)
    string PreFix = "";

    string Fetcher;
    vector<Component> Components; // Tokens

    Component* Offsetter = nullptr;

    Component* Left = nullptr; // L
    Component* Right = nullptr; // R

    Component(string value, int flags) : Value(value), Flags(flags) {}
    Component(string value, const Position& position, int flags) : Value(value), Location(position), Flags(flags) {}

    bool is(int flag) 
    {
        return (Flags & flag) == flag;
    }
};

#endif