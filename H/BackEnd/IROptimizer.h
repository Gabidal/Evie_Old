#ifndef _IROPTIMIZER_H_
#define _IROPTIMIZER_H_

#include "../Nodes/IR.h"

#include <vector>

using namespace std;

class IROptimizer{
public:

    vector<IR*>& Input;

    IROptimizer(vector<IR*>& input) : Input(input) {
        Factory();
    }

    void Factory();

    vector<Token*> Liquify_MEM_AST(Token* mem);

    void Switch_Operator_Sides(vector<Token*>& liquid);

    void Switch_Sides(vector<Token*>& liquid, int l, int r);

    void Combine_Scale_And_Offset_In_Memory(Token* mem);

};

#endif