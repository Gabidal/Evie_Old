#ifndef _TYPE_H_
#define _TYPE_H_
#include "Token.h"
#include "Func.h"

class Type : public Father
{
  public:
    vector<Token*> Functions;
    void addFunc(Func *func);
};


#endif
