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
    int Secrets;
  public:
    vector<StackFrame> StackFrames;
    Stack();
    ~Stack();
};

Stack::Stack()
{
    Secrets = int(&StackFrames);
}

Stack::~Stack()
{
    if (StackFrames.size() != 0)
    {
        cout << "Frames remaining!" << endl;
    }
}


#endif