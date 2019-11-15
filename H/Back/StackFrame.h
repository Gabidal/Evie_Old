#ifndef _STACKFRAME_H_
#define _STACKFRAME_H_
#include "Assembly_Definitions.h"
#include <string>
#include "Token.h"
#include "Registers.h"
using namespace std;

class StackFrame
{
  private:
    string &output;
    bool EndFunc = false;
  public:
  StackFrame(string &output, bool Endfunc) : output(output)
  {
      this->output += PUSH(EBP->Name);
      this->output += MOV + EBP->Name + FROM + ESP->Name + NL + NL;
      EndFunc = Endfunc;
  }
  
  ~StackFrame()
  {
      this->output += MOV + ESP->Name + FROM + EBP->Name + NL;
      this->output += POP(EBP->Name);
      if (EndFunc)
      {
        this->output += "ret" + string(NL) + NL;
      }
      
  }
};



#endif