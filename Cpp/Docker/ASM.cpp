#include "../../H/Docker/ASM.h"

void ASM::ASM_Analyzer(vector<string>& Output)
{
	//here we will just make an prototype from every label. Parser can analyse witch one is a function, and what is not.
	//and after that we want to give Evie Core the "use "filename"" without the preprosessor so that Evie Core can implement an
	//post-prosessing include
	vector<string> Header_Data = DOCKER::Get_Header(DOCKER::FileName.back());
	if (Header_Data.size() < 1)
		Header_Data = DOCKER::Get_Header("asm..e");
	if (Header_Data.size() < 1)
		Header_Data = DOCKER::Get_Header("general");
	if (Header_Data.size() < 1)
		cout << "Error: Docker didn't find Header file for " << DOCKER::FileName.back() << endl;
	//DOCKER::Separate_Identification_Patterns(Header_Data);
	vector<uint8_t> tmp = DOCKER::Get_Char_Buffer_From_File(DOCKER::FileName.back(), DOCKER::Working_Dir);
	string buffer = string((char*)tmp.data(), tmp.size());
	Section Function_Section = DOCKER::Get_Section_From_String(buffer);
	vector<string> Raw_Data = DOCKER::Get_Names_Of(Function_Section, DOCKER::Separate_Identification_Patterns(Header_Data));
	//delete all the comments that start with ;
	for (int i = 0; i < Raw_Data.size(); i++) {
		if (Raw_Data[i][0] == ';')
			Raw_Data.erase(Raw_Data.begin() + i);
		if (Raw_Data[i][0] == ';')
			i--;
	}
	//we need to get rid of : in the asm labels
	for (auto& i : Raw_Data)
		i = DOCKER::ReplaceAll(i, ":", "");
	//Syntax_Correcter(Raw_Data);
	//now make the obj token for YASM
	DOCKER::Assembly_Source_File.push_back(DOCKER::Working_Dir + DOCKER::FileName.back());
	return;
}
