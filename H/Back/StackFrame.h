#ifndef _STACKFRAME_H_
#define _STACKFRAME_H_
#include "Assembly_Definitions.h"
#include <string>
#include "Token.h"
#include "Registers.h"
#include "../Selector/Selector.h"
using namespace std;

class StackFrame
{
  private:
    string &output;
    bool EndFunc = false;
  public:
      StackFrame(string& output, bool Endfunc);
  
      ~StackFrame();
};



#endif