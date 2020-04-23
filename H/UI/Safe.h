#ifndef _SAFE_H_
#define _SAFE_H_
#include "../../H/Selector/Selector.h"
#include "../../H/Back/Token.h"
#include "../../H/OpC/IR.h"

class Safe
{
private:
	map<string, int> Cache_Usation;
public:
    vector<IR*> Input;
    vector<IR*> Output;
    Safe(){}
    ~Safe(){}
    void Factory();
    void Insight(IR* t);
    void Safe_Cache_Usation(Token* t);
    void Append(vector<IR*> &d, vector<IR*> s);
};



#endif