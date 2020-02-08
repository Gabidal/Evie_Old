#include "../../H/Back/Registers.h"

map<string, Register*> registers;

void Init_Registers()
{
    registers.insert(make_pair(string(R1->Name), R1));
    registers.insert(make_pair(string(R2->Name), R2));
    registers.insert(make_pair(string(R3->Name), R3));
    registers.insert(make_pair(string(R4->Name), R4));
    registers.insert(make_pair(string(R5->Name), R5));
    registers.insert(make_pair(string(R6->Name), R6));
    registers.insert(make_pair(string(R7->Name), R7));
    registers.insert(make_pair(string(R8->Name), R8));
    registers.insert(make_pair(string(R9->Name), R9));
}

Register *R1 = new Register("r1", 4);
Register *R2 = new Register("r2", 4);
Register *R3 = new Register("r3", 4);
Register *R4 = new Register("r4", 4);
Register *R5 = new Register("r5", 4);
Register *R6 = new Register("r6", 4);
Register *R7 = new Register("r7", 4);
Register *R8 = new Register("r8", 4);
Register *R9 = new Register("r9", 4);