#ifndef _WINDOWS_H_
#define _WINDOWS_H_
#include <string>
#include "../Back/Assembly_Definitions.h"
using namespace std;

class Windows
{
public:
	string Malloc();
	string Raw_Print();
	string Raw_In();
	string SYS_CALL();
	Windows()
	{
	}

	~Windows()
	{
	}

private:

};


#endif