#ifndef _COMPONENT_H_
#define _COMPONENT_H_
#include <string>
#include <vector>
#include "Position.h"
#include "../Flags.h"
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
    bool is(long flag)
    {
        return (Flags & flag) == flag;
    }
    bool Has(vector<long> f) {
        for (auto i : f)
            if (is(i))
                return true;
        return false;
    }
    vector<Component*> Get_all() {
        vector<Component*> Result;

        Result.push_back(this);

        if (is(::Flags::PAREHTHESIS_COMPONENT))
            for (auto& i : Components) {
                vector<Component*> tmp = i.Get_all();
                Result.insert(Result.end(), tmp.begin(), tmp.end());
            }

        return Result;
    }
};

#endif