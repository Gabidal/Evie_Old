#include "../../H/Back/Registers.h"

map<string, Register*> registers;

void Init_Registers()
{
    registers.insert(make_pair(string(NUL->Name), NUL));
    registers.insert(make_pair(string(EAX->Name), EAX));
    registers.insert(make_pair(string(EBX->Name), EBX));
    registers.insert(make_pair(string(ECX->Name), ECX));
    registers.insert(make_pair(string(EDX->Name), EDX));
    registers.insert(make_pair(string(ESI->Name), ESI));
    registers.insert(make_pair(string(EDI->Name), EDI));
    registers.insert(make_pair(string(EBP->Name), EBP));
    registers.insert(make_pair(string(ESP->Name), ESP));
}

Register *NUL = new Register("null");
Register *EAX = new Register("eax");
Register *EBX = new Register("ebx");
Register *ECX = new Register("ecx");
Register *EDX = new Register("edx");
Register *ESI = new Register("esi");
Register *EDI = new Register("edi");
Register *EBP = new Register("ebp");
Register *ESP = new Register("esp");