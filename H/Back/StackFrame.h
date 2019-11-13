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
  public:
  StackFrame(string &output) : output(output)
  {
      this->output += PUSH(EBP->Name);
      this->output += MOV + EBP->Name + FROM + ESP->Name + NL;
  }
  
  ~StackFrame()
  {
      this->output += MOV + ESP->Name + FROM + EBP->Name + NL;
      this->output += POP(EBP->Name);
  }
};



#endif