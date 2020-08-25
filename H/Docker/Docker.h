#ifndef _DOCKER_H_
#define _DOCKER_H_
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <regex>
//the analyzers
#include "../Flags.h"
#include "Section.h"
#include "../Lexer/Component.h"

using namespace std;

namespace DOCKER {
	//filename, mangled name
	extern map<string, vector<string>> Output;
	//vector<pair<Type, Regex string>>
	//vector<pair<string, string>> Types;
	//returns the filename of the header file
	vector<string> Get_Header(string File_Name);
	//parse the tokens from the header file
	//parse the Tokens into Type'n Regex style.
	//and remove the binfile header rule syntax thingys!
	vector<pair<string, string>> Separate_Identification_Patterns(vector<string> Tokens);
	//open file to constexpr char buffer
	vector<unsigned char> Get_Char_Buffer_From_File(string FN, string WD);
	//Read section
	//		function_names, type
	vector<string> Get_Names_Of(Section area, vector<pair<string, string>> Types);
	extern vector<string> Libs;
	extern vector<string> Assembly_Source_File;
	extern vector<string> FileName;
	extern string Working_Dir;
	extern vector<string> Priority_Type;
	//map<ID, function ID>
	extern vector<pair<string, void (*)(vector<string>&)>> Translators;

	extern void (*Default)(vector<string>&);

	void Add_Translator(string id, void (*f)(vector<string>&));
	void Set_Default_Translator(void (*f)(vector<string>&));

	//open the file and look for the identifier of the file header
	void Start_Analyzer(); 
	string ReplaceAll(string str, const string& from, const string& to);
	Section Get_Section_From_String(string& text); 
	template<typename T>
	vector<T>& Append(vector<T>& d, vector<T> s) {
		for (int i = 0; i < s.size(); i++)
			d.push_back(s[i]);
		return d;
	}

	string Get_File_Extension(string raw) {
		string Name_No_Extension = "";
		int i = (int)raw.find_last_of('.');
		if (i != -1)
			Name_No_Extension = raw.substr(0, (size_t)i);
		else
			Name_No_Extension = raw;
		return Name_No_Extension;
	}
}

class Docker
{
public:
	Docker(string FN, string WD, string PT = "") {
		DOCKER::FileName.push_back(FN);
		DOCKER::Working_Dir = WD;
		DOCKER::Priority_Type.push_back(PT);
		//look up table at:https://en.wikipedia.org/wiki/List_of_file_signatures.
		//TXT files do not have a header
		//Translators.push_back({ "TXT", TXT_Analyzer });
		//Translators.push_back({ "MZ", bind(&Docker::DLL_Analyzer, this) });
		//Translators.push_back({ "!<arch>",  bind(&Docker::LIB_Analyzer, this) });
		//Translators.push_back({ "\x7F" "ELF",  bind(&Docker::ELF_Analyzer, this) });
		//Translators.push_back({ ";analyze",  bind(&Docker::ASM_Analyzer, this) });
		//Translators.push_back({ "\x4C" "\x01",  bind(&Docker::OBJ_analyser, this) });
		DOCKER::Start_Analyzer();
		DOCKER::FileName.pop_back();
		DOCKER::Priority_Type.pop_back();
	}
	~Docker() {}
private:
};

#endif