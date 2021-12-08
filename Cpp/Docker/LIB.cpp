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

pair<bool, vector<LIB::Packet>> LIB::Read_AR_File(string filename){
	vector<string> Result;
	vector<uint8_t> tmp = DOCKER::Get_Char_Buffer_From_File(filename, "");

	vector<Packet> Data;

	const int SKIP_MAGIC_NUMBER = 8;
	const int SKIP_CURRENT_PACKET_INFO = 60;

	try {
		for (int i = SKIP_MAGIC_NUMBER; i < tmp.size();) {
			Packet p;
			p.Info = *(decltype(p.Info)*)tmp.data();

			p.Buffer = new char[DOCKER::Initialize_Number(p.Info.File_Size)];
			memcpy(p.Buffer, tmp.data(), DOCKER::Initialize_Number(p.Info.File_Size));

			i += SKIP_CURRENT_PACKET_INFO + DOCKER::Initialize_Number(p.Info.File_Size);
			Data.push_back(p);
		}
	}
	catch (...) {
		return { false, {} };
	}

	return { true, Data };
}

pair<bool, vector<LIB::Packet>> LIB::Read_LIB_File(string filename)
{

}

void LIB::LIB_Analyzer(vector<string>& Output)
{
	vector<string> Header_Data = DOCKER::Get_Header(DOCKER::FileName.back());
	if (Header_Data.size() < 1)
		Header_Data = DOCKER::Get_Header("lib..e");
	if (Header_Data.size() < 1)
		Header_Data = DOCKER::Default_Header_Data;
	if (Header_Data.size() < 1)
		Report(Observation(ERROR,  "Docker didn't find Header file for " + DOCKER::FileName.back(), Position()));
	
	////write the lib with nm to .TMP.txt file
	//LIB::Generate_Binary_Symbols(DOCKER::FileName.back(), DOCKER::Working_Dir.back().second);
	//vector<uint8_t> tmp = DOCKER::Get_Char_Buffer_From_File(".TMP.txt", "");
	//string buffer = string((char*)tmp.data(), tmp.size());
	////use filtters
	//buffer = DOCKER::ReplaceAll(buffer, "\r\n", "\n");
	//regex filtter("(\\?.*)|(\\ .\\ [0-9]+)|(.+:)|(__.+@.+)");
	//buffer = regex_replace(buffer, filtter, "");
	//regex filtter2("(\\n{2,})");
	//buffer = regex_replace(buffer, filtter2, "\n");
	//Section Function_Section = DOCKER::Get_Section_From_String(buffer);
	//for (int i = 0; i < Function_Section.size; i++) {
	//	if (Function_Section.start[i] == '\0')
	//		Function_Section.start[i] = '?';
	//}
	//string Tmp = string((char*)Function_Section.start, Function_Section.size);
	//DOCKER::Append(Output, DOCKER::Get_Names_Of(Tmp, DOCKER::Separate_Identification_Patterns(Header_Data)));
	//DOCKER::Libs.push_back(DOCKER::Working_Dir.back().second + DOCKER::FileName.back());

	pair<bool, vector<Packet>> Data = Read_AR_File(DOCKER::Working_Dir.back().second + DOCKER::FileName.back());

	if (!Data.first) {
		Data = Read_LIB_File(DOCKER::Working_Dir.back().second + DOCKER::FileName.back());
	}

	if (!Data.first)
		Report(Observation(ERROR, "Cannot parse file: '" + DOCKER::Working_Dir.back().second + DOCKER::FileName.back() + "'"));

	for (auto &i : Data.second) {
		Docker d(i.Info.File_Indentifier, i.Buffer, DOCKER::Initialize_Number(i.Info.File_Size));
	}

	return;
}
