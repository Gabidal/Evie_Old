#ifndef _MANGLER_H_
#define _MANGLER_H_
#include <vector>
#include <string>

#include "../Back/Token.h"

using namespace std;

namespace Mangler{
	//				 Mangled Name
	string Un_Mangle(string Name);
	//			  Mangable function
	string Mangle(Token* t);
	//Returns the main function name
	string Get_Main_Name(string Mangled);
};

#endif