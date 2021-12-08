#ifndef _LIB_H_
#define _LIB_H_
#include <stdexcept>

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include "Docker.h"
#include "../UI/Usr.h"
#include "Section.h"
using namespace std;

namespace LIB {
	class Packet {
	public:
		struct {
			char File_Indentifier[16];
			char File_Modification_Stamp[12];
			char Owner_ID[6];
			char Group_ID[6];
			char File_Mode[8];
			char File_Size[10];
			char End_Char[2];
		}Info;
		char* Buffer;
	};

	void Generate_Binary_Symbols(string filename, string WD);
	void LIB_Analyzer(vector<string>& Output);
	pair<bool, vector<Packet>> Read_AR_File(string filename); 
	pair<bool, vector<Packet>> Read_LIB_File(string filename);
}

#endif