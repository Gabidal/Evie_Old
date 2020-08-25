#ifndef _LIB_H_
#define _LIB_H_
#include <stdexcept>

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Docker.h"
#include "../UI/Usr.h"
#include "Section.h"
using namespace std;

namespace LIB {
	void Generate_Binary_Symbols(string filename, string WD);
	void LIB_Analyzer(vector<string>& Output);
}

#endif