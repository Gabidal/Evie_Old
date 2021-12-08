#include "../../H/Docker/ASM.h"
#include "../../H/UI/Safe.h"

void ASM::ASM_Analyzer(vector<string>& Output)
{
	//here we will just make an prototype from every label. Parser can analyse wich one is a function, and what is not.
	//and after that we want to give Evie Core the "use "filename"" without the preprosessor so that Evie Core can implement an
	//post-prosessing include
	vector<string> Header_Data = DOCKER::Get_Header(DOCKER::FileName.back());
	if (Header_Data.size() < 1)
		Header_Data = DOCKER::Get_Header("asm..e");
	if (Header_Data.size() < 1)
		Header_Data = DOCKER::Default_ASM_Header_Data;
	if (Header_Data.size() < 1)
		Report(Observation(ERROR, "Docker didn't find Header file for " + DOCKER::FileName.back(), Position()));
	//DOCKER::Separate_Identification_Patterns(Header_Data);
	vector<uint8_t> tmp;
	if (DOCKER::Buffer) {
		tmp = vector<uint8_t>(DOCKER::Buffer, DOCKER::Buffer + DOCKER::Buffer_Size);
	}
	else {
		tmp = DOCKER::Get_Char_Buffer_From_File(DOCKER::FileName.back(), DOCKER::Working_Dir.back().second);
	}
	string buffer = string((char*)tmp.data(), tmp.size());
	Section Function_Section = DOCKER::Get_Section_From_String(buffer); 

	string Tmp = string((char*)Function_Section.start, Function_Section.size);
	auto Types = DOCKER::Separate_Identification_Patterns(Header_Data);
	vector<pair<string, string>> Raw_Data = DOCKER::Get_Names_Of(Tmp, Types);
	for (auto& i : Raw_Data) {
		if (i.second.find("global ") != -1)
			i.second.erase(i.second.find("global "), 7);
	}
	DOCKER::Append(Output, Raw_Data);
	//
	//Syntax_Correcter(Raw_Data);
	//now make the obj token for YASM
	DOCKER::Assembly_Source_File.push_back(DOCKER::Working_Dir.back().second + DOCKER::FileName.back());
	return;
}
