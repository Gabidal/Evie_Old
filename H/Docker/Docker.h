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
#include <unordered_map>
//the analyzers
#include "../Flags.h"
#include "Section.h"
#include "../Lexer/Component.h"

using namespace std;

enum class Location {
	Header,
	File_Name,
};

namespace DOCKER {
	//filename, mangled name
	extern map<string, vector<string>> Output;
	//Read section
	//		function_names, type
	vector<pair<string, string>> Get_Names_Of(string tmp, vector<pair<string, string>> Types);
	extern vector<string> Libs;
	extern vector<string> Assembly_Source_File;
	extern vector<string> FileName;		//this can contain also the url name
	extern vector<pair<string, string>> Working_Dir;
	extern vector<string> Priority_Type;
	//map<ID, function ID>
	extern vector<pair<Location, pair<string, void (*)(vector<string>&)>>> Translators;
	extern void (*Default)(vector<string>&);
	extern vector<string>(*Slicer)(string);
	extern vector<string> Included_Files;
	extern vector<bool> Is_Local;
	extern bool WORKING_DIR_IS_ABSOLUTE;
	extern vector<string> Default_Header_Data;
	extern vector<string> Default_ASM_Header_Data;
	extern char* Buffer;
	extern long Buffer_Size;

	// SSS System 2000
	class Header_Summary{
	public:
		string OS = "win";
		string Architecture = "x86";
		int Bit_Size = 64;

		vector<string> Exported_Symbols;
		vector<string> Imported_Symbols;

		Header_Summary(string OS, string Architecture, int Bit_Size) {
			this->OS = OS;
			this->Architecture = Architecture;
			this->Bit_Size = Bit_Size;
		}

		Header_Summary() = default;
	};

	extern unordered_map<string, Header_Summary> File_History; 

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
	void Add_Translator(Location filter_Location, string id, void (*f)(vector<string>&));
	void Set_Default_Translator(void (*f)(vector<string>&));
	//open the file and look for the identifier of the file header
	void Start_Analyzer(char* Buffer = nullptr, long Buffer_Size = 0);
	string ReplaceAll(string str, const string& from, const string& to);
	Section Get_Section_From_String(string& text);
	template<typename T>
	vector<T>& Append(vector<T>& d, vector<T> s) {
		for (int i = 0; i < s.size(); i++)
			d.push_back(s[i]);
		return d;
	}
	template<typename T>
	vector<T>& Append(vector<T>& d, vector<T> s, int i) {
		for (int j = 0; j < s.size(); j++)
			d.insert(d.begin() + i + j, s[j]);
		return d;
	}
	vector<string>& Append(vector<string>& d, vector<pair<string, string>> s);
	string Get_File_Extension(string raw);
	string Update_Working_Dir(string File_Name);
	string Update_Working_Dir(string File_Name, string& dir);
	vector<string> Get_File_List(string Dir, bool Contain_Dir_Names = false);
	vector<string> Chop_Chop(string raw, char skip);
	string Remove(string raw, char id, int cut);
	bool Is_Folder(string path);
	bool Is_Same_File(string first, string second);
	pair<char*, long long> Read_Bin_File(string fileName);
	string Find(string File_Name);
	string Find(string File_Name, filesystem::directory_entry Folder);
	vector<string> Get_System_Paths();
	string Get_File_Path(string file_name);

	string Open_File(string File_Name);
	void Write_File(string File_Name, string Buffer);
	void Clear_File(string File_Name);
	int Initialize_Number(string raw);

	using Function_Pointter = void(*)(vector<string>&);
	Function_Pointter Get_Translator(vector<unsigned char>& Buffer);
	string Sanitize_File_Path(string path);
}

class Docker
{
public:
	Docker(string FN, string PT = "") {
		
		// Sanitize include filename
		FN = DOCKER::Sanitize_File_Path(FN);

		for (auto i : DOCKER::Included_Files)
				if (i == FN || (!DOCKER::Working_Dir.empty() && i == DOCKER::Working_Dir[0].second + FN)) {
					//cout << "Warnign: " << FN << " already included!" << endl;
					return;
				}
		DOCKER::FileName.push_back(FN);
		//DOCKER::FileName.push_back(FN);
		//DOCKER::Working_Dir = WD;
		DOCKER::Priority_Type.push_back(PT);
		//look up table at:https://en.wikipedia.org/wiki/List_of_file_signatures.
		// Every analyzer MUST append to the OUTPUT list the data of the symbols AND add a File_Summary to the File_Summary list.
		DOCKER::Start_Analyzer();

		//for include loop to stop existing!
		string Dir = "";
		string File_Name = DOCKER::Update_Working_Dir(DOCKER::FileName.back(), Dir);
		File_Name = DOCKER::Working_Dir.back().second + File_Name;
		bool Already_Included_File_Name = false;
		//the https needs to rename the https url link to the current ablselute path the repo resides in.
		//so remove unnecessary filename from coming into include file list.
		for (auto i : DOCKER::Included_Files)
			if (i == File_Name) {
				Already_Included_File_Name = true;
				break;
			}

		if (Already_Included_File_Name == false)
			DOCKER::Included_Files.push_back(File_Name);

		//cleaner
		DOCKER::FileName.pop_back();
		DOCKER::Priority_Type.pop_back();
	}
	Docker(string FN, char* File_Buffer, long Buffer_Size) {
		for (auto i : DOCKER::Included_Files)
			if (i == FN || (DOCKER::Working_Dir.size() > 0 && i == DOCKER::Working_Dir[0].second + FN)) {
				//cout << "Warnign: " << FN << " already included!" << endl;
				return;
			}
		DOCKER::FileName.push_back(FN);

		vector<pair<string, string>> WD = DOCKER::Working_Dir;

		//DOCKER::FileName.push_back(FN);
		//DOCKER::Working_Dir = WD;
		//DOCKER::Priority_Type.push_back(PT);
		//look up table at:https://en.wikipedia.org/wiki/List_of_file_signatures.
		DOCKER::Start_Analyzer(File_Buffer);

		//for include loop to stop existing!
		string Dir = "";
		string File_Name = DOCKER::Update_Working_Dir(DOCKER::FileName.back(), Dir);
		File_Name = DOCKER::Working_Dir.back().second + File_Name;
		bool Already_Included_File_Name = false;
		//the https needs to rename the https url link to the current ablselute path the repo resides in.
		//so remove unnecessary filename from coming into include file list.
		for (auto i : DOCKER::Included_Files)
			if (i == File_Name) {
				Already_Included_File_Name = true;
				break;
			}

		if (Already_Included_File_Name == false)
			DOCKER::Included_Files.push_back(File_Name);

		//cleaner
		DOCKER::FileName.pop_back();
		DOCKER::Priority_Type.pop_back();

		DOCKER::Working_Dir = WD;
	}
	~Docker() {}
private:
};

#endif