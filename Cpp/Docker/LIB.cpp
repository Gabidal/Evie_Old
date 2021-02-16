#include "../../H/Docker/LIB.h"
#include "../../H/UI/Safe.h"

extern Usr* sys;

void LIB::Generate_Binary_Symbols(string filename, string WD)
{
	string NM_Posix = "";
	//first start the NM.exe
	if (sys->Info.HOST_OS == "win32")
		NM_Posix = "nm.exe ";
	else
		NM_Posix = "./nm ";

	system((NM_Posix + WD + filename + " --extern-only --defined-only -P > .TMP.txt").c_str());
	return;
}

void LIB::LIB_Analyzer(vector<string>& Output)
{
	vector<string> Header_Data = DOCKER::Get_Header(DOCKER::FileName.back());
	if (Header_Data.size() < 1)
		Header_Data = DOCKER::Get_Header("lib..e");
	if (Header_Data.size() < 1)
		Header_Data = DOCKER::Get_Header("general");
	if (Header_Data.size() < 1)
		Report(Observation(ERROR,  "Docker didn't find Header file for " + DOCKER::FileName.back(), Position()));
	
	//write the lib with nm to .TMP.txt file
	LIB::Generate_Binary_Symbols(DOCKER::FileName.back(), DOCKER::Working_Dir.back().second);
	vector<uint8_t> tmp = DOCKER::Get_Char_Buffer_From_File(".TMP.txt", "");
	string buffer = string((char*)tmp.data(), tmp.size());
	//use filtters
	buffer = DOCKER::ReplaceAll(buffer, "\r\n", "\n");
	regex filtter("(\\?.*)|(\\ .\\ [0-9]+)|(.+:)|(__.+@.+)");
	buffer = regex_replace(buffer, filtter, "");
	regex filtter2("(\\n{2,})");
	buffer = regex_replace(buffer, filtter2, "\n");
	Section Function_Section = DOCKER::Get_Section_From_String(buffer);
	for (int i = 0; i < Function_Section.size; i++) {
		if (Function_Section.start[i] == '\0')
			Function_Section.start[i] = '?';
	}
	string Tmp = string((char*)Function_Section.start, Function_Section.size);
	DOCKER::Append(Output, DOCKER::Get_Names_Of(Tmp, DOCKER::Separate_Identification_Patterns(Header_Data)));
	DOCKER::Libs.push_back(DOCKER::Working_Dir.back().second + DOCKER::FileName.back());
	return;
}
