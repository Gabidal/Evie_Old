#ifndef _LIB_H_
#define _LIB_H_
#include <stdexcept>

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "../../UI/Usr.h"
using namespace std;
extern Usr* sys;

namespace LIB {
	void Generate_Binary_Symbols(string filename, string WD);
}

#endif