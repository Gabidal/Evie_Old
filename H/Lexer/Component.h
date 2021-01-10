#ifndef _COMPONENT_H_
#define _COMPONENT_H_
#include <string>
#include <vector>
#include "Position.h"
using namespace std;

class Node;

class Component 
{
public:
    string Value;
    vector<Component> Components; // Tokens
    Node* node = nullptr;
    Position Location; // LineNumber
    long Flags;
    Component(string value, long flags) : Value(value), Flags(flags) {}
    Component(string value, const Position& position, long flags) : Value(value), Location(position), Flags(flags) {}
    string Transform(long f);
    bool is(long flag)
    {
        return (Flags & flag) == flag;
    }
};

#endif