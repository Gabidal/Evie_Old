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
  StackFrame(string &output, bool Endfunc) : output(output)
  {
      Selector s;
	  output += COMMENT + "Making stack frame " + NL;
      this->output += s.Get_ID("push") + s.Get_Right_Reg(Task_For_Type_Address_Basing) + NL;
      this->output += s.Get_ID("=") + s.Get_Right_Reg(Task_For_Type_Address_Basing) + FROM + s.Get_Right_Reg(Task_For_Type_Address) + NL;
      EndFunc = Endfunc;
  }
  
  ~StackFrame()
  {
      Selector S;
	  output += COMMENT + "Ending stack frame " + NL;
      output += S.Get_ID("=") + S.Get_Right_Reg(Task_For_Type_Address) + FROM + S.Get_Right_Reg(Task_For_Type_Address_Basing) + NL;
      output += S.Get_ID("pop") + S.Get_Right_Reg(Task_For_Type_Address_Basing) + NL;
      if (EndFunc)
      {
		output += COMMENT + "Returning " + NL;
        output += S.Get_ID("ret") + NL + NL;
      }
      
  }
};



#endif