#ifndef _OPTIMIZER_H_
#define _OPTIMIZER_H_

#include "../Back/Token.h"
#include <vector>
#include <string>
#include "../Linux/Linux.h"
#include "../Windows/Windows.h"
#include "../Emulator/Emulator.h"
#include <iostream>

class Optimizer
{
private:
    /* data */
    //this class job is to search for those variables witch are used and mark em flags 'Used'
    bool Lib = false;
public:
    vector<Token*> Input; //direct connect to the original tokens.
    void Factory();
    Optimizer(vector<Token*>& In)
    {
        Input = In;
    }
    ~Optimizer() {}
    //find func main
    int Find_Start_Of_Runnable();
    //if there is no main we need to simulate every function by it self.
    //if there is main function then we can start our simulation from there.
    void Simulate_Runnable(int start);
};



#endif