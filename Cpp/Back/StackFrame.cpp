#include "..\..\H\Back\StackFrame.h"

StackFrame::StackFrame(string& output, bool Endfunc) : output(output)
{
    Selector s;
    output += COMMENT + "Making stack frame " + NL;
    this->output += s.Get_ID("push") + s.Get_Right_Reg(Task_For_Type_Address_Basing) + NL;
    this->output += s.Get_ID("=") + s.Get_Right_Reg(Task_For_Type_Address_Basing) + FROM + s.Get_Right_Reg(Task_For_Type_Address) + NL;
    EndFunc = Endfunc;
}

StackFrame::~StackFrame()
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
