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
    //its idea is to go as the executable woulb be runned
    //get index of main function
    int Get_Start_Of_Runnable();
    //analyse main function
    void Analyse_Function(int i);
    //get knoligde of function using any global functions is it has n parameters
    void Analyse_Math(Token &t);
    //getting modiafiable in math
    Token& Get_Abselute_Destination(Token &t);
    //checking if the destinaton specific math is used enywhere.
    Token& Look_up_Probality_To_Be_Used(Token &t);
    //look up what variable has been returned in spesicif function
    void Find_Return(Token& t);
    //handle given source in math to dest
    void Handle_Source(Token& t);
    //handle is source is a function call
    void Handle_Function_Call(Token& t);
};



#endif