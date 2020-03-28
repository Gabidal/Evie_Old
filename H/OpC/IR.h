#ifndef IR_H_
#define IR_H_
#include "OpC.h"
#include "../Back/Token.h"
#include "../UI/Usr.h"
#define _Start_Of_Label (1<<0)
#define _End_Of_Label (1<<1)
#define _Allocated_ (1<<2)
#define _Restricted_ (1<<4)
#define _Double_Task_ (1<<5)

class IR : Symbol_Table
{
private:
	int Flags = 0;
public:
	string Comment = "";
	//for single line:
		int Reg_Flag = 0;
		string PreFix = "";
		string ID = "";
		vector<Token*> Parameters;
	//for multi levelled opcodes:
		vector<IR*> Childs;
		void add(int Flag);
		int get();
		map<string, Symbol_Table*> Get_Member_Pointters();
		map<string, Waiter*> Get_Member_Data();
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