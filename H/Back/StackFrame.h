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
      this->output += PUSH + R8->Name + NL;
      this->output += MOV + R8->Name + FROM + R7->Name + NL + NL;
      EndFunc = Endfunc;
  }
  
  ~StackFrame()
  {
	  output += COMMENT + "Ending stack frame " + NL;
      this->output += MOV + R7->Name + FROM + R8->Name + NL;
      this->output += POP + R8->Name + NL;
      if (EndFunc)
      {
		output += COMMENT + "Returning " + NL;
        this->output += "ret" + string(NL) + NL;
      }
      
  }
};



#endif