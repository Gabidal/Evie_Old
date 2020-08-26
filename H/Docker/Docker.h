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
	//Read section
	//		function_names, type
	vector<string> Get_Names_Of(Section area, vector<pair<string, string>> Types);
	extern vector<string> Libs;
	extern vector<string> Assembly_Source_File;
	extern vector<string> FileName;		//this can contain also the url name
	extern string Working_Dir;
	extern vector<string> Priority_Type;
	//map<ID, function ID>
	extern vector<pair<string, void (*)(vector<string>&)>> Translators;
	extern void (*Default)(vector<string>&);
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
	string Get_File_Extension(string raw);
	//URL Interface
	string Update_Working_Dir(string File_Name);
	string Update_Working_Dir(string File_Name, string& dir);
}

class Docker
{
public:
	Docker(string FN, string PT = "") {
		DOCKER::FileName.push_back(FN);
		//DOCKER::FileName.push_back(FN);
		//DOCKER::Working_Dir = WD;
		DOCKER::Priority_Type.push_back(PT);
		//look up table at:https://en.wikipedia.org/wiki/List_of_file_signatures.
		DOCKER::Start_Analyzer();
		DOCKER::FileName.pop_back();
		DOCKER::Priority_Type.pop_back();
	}
	~Docker() {}
private:
};

#endif