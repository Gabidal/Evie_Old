#ifndef IR_H_
#define IR_H_
#include "OpC.h"
#include "../Back/Token.h"
#define _Start_Of_Label (1<<0)
#define _End_Of_Label (1<<1)
#define _Allocated_ (1<<2)
#define _Restricted_ (1<<4)
#define _Double_Task_ (1<<5)

class IR
{
public:
	string Comment = "";
	//for single line:
		int Flags = 0;
		int Reg_Flag = 0;
		string PreFix = "";
		string ID = "";
		vector<Token*> Parameters;
	//for multi levelled opcodes:
		vector<IR*> Childs;
	IR()
	{
	}
	bool is(int flag)
	{
		return (Flags & flag) == flag;
	}

	~IR();

private:

};


#endif