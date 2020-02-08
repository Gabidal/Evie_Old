#ifndef _STACK_H_
#define _STACK_H_
#include "Assembly_Definitions.h"
#include <vector>
#include "StackFrame.h"
#include <iostream>
using namespace std;

class Stack
{
  private:
    int Secrets; //find the number
  public:
    vector<StackFrame> StackFrames;
    vector<int> stack;
  Stack()
  {
      Secrets = int(&StackFrames);
  }
  
  ~Stack()
  {
      if (StackFrames.size() != 0)
      {
          cout << "Frames remaining!" << endl;
      }
  }
};



#endif