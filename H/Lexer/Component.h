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
    long Flags;
    Position Location; // LineNumber
    vector<Component> Components; // Tokens
    Component(string value, long flags) : Value(value), Flags(flags) {}
    Component(string value, const Position& position, long flags) : Value(value), Location(position), Flags(flags) {}
    Node* node = nullptr;
    bool is(long flag)
    {
        return (Flags & flag) == flag;
    }
};

#endif