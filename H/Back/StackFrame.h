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
	  output += COMMENT + "Making stack frame " + NL;
      this->output += PUSH + EBP->Name + NL;
      this->output += MOV + EBP->Name + FROM + ESP->Name + NL + NL;
      EndFunc = Endfunc;
  }
  
  ~StackFrame()
  {
	  output += COMMENT + "Ending stack frame " + NL;
      this->output += MOV + ESP->Name + FROM + EBP->Name + NL;
      this->output += POP + EBP->Name + NL;
      if (EndFunc)
      {
		output += COMMENT + "Returning " + NL;
        this->output += "ret" + string(NL) + NL;
      }
      
  }
};



#endif