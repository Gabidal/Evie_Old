#ifndef _OPTIMIZER_H_
#define _OPTIMIZER_H_

#include "../Back/Token.h"
#include <vector>
#include <string>
#include "../Linux/Linux.h"
#include "../Windows/Windows.h"

class Optimizer
{
private:
    /* data */
    //this class job is to search for those variables witch are used and mark em flags 'Used'
public:
    vector<Token*> Input; //direct connect to the original tokens.
    Optimizer(vector<Token*> &In)
    {
        Input = In;
    }
    ~Optimizer(){}
    void Factory();
};



#endif