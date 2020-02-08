#ifndef _X86_H_
#define _X86_H_
#include "../../OpC/OpC.h"
#include "../../Back/Token.h" //for registers
namespace x86
{
	vector<Register*> Registers;
	vector<OpC*> OpCodes;
	void Factory();
	int x86_ADD(vector<int> Parameters)
	{
		return Parameters.at(0) + Parameters.at(1);
	}

	int x86_SUB(vector<int>Parameters)
	{
		return Parameters.at(0) - Parameters.at(1);
	}

	int x86_IMUL(vector<int>Parameters)
	{
		return Parameters.at(0) * Parameters.at(1);
	}

	int x86_IDIV(vector<int>Parameters)
	{
		return Parameters.at(0) / Parameters.at(1);
	}

	int x86_MUL(vector<int>Parameters)
	{
		return Parameters.at(0) * Parameters.at(1);
	}

	int x86_DIV(vector<int>Parameters)
	{
		return Parameters.at(0) / Parameters.at(1);
	}


	//Reg's
	//32Bit
	Register* EAX = new Register("EAX", 4);
	Register* EBX = new Register("EBX", 4);
	Register* ECX = new Register("ECX", 4);
	Register* EDX = new Register("EDX", 4);
	Register* EDI = new Register("EDI", 4);
	Register* ESI = new Register("ESI", 4);
	Register* ESP = new Register("ESP", 4);
	Register* EBP = new Register("EBP", 4);
	//16Bit
	Register* AX = new Register("AX", 2);
	Register* BX = new Register("BX", 2);
	Register* CX = new Register("CX", 2);
	Register* DX = new Register("DX", 2);
	Register* DI = new Register("DI", 2);
	Register* SI = new Register("SI", 2);
	Register* SP = new Register("SP", 2);
	Register* BP = new Register("BP", 2);
	//8Bit
	Register* AL = new Register("AL", 1);
	Register* AH = new Register("AH", 1);
	Register* BL = new Register("BL", 1);
	Register* BH = new Register("BH", 1);
	Register* CL = new Register("CL", 1);
	Register* CH = new Register("CH", 1);
	Register* DL = new Register("DL", 1);
	Register* DH = new Register("DH", 1);
}


#endif