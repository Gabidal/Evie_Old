#include "../../H/Docker/DLL.h"

vector<DLL::Table> DLL::Gather_All_Tables(vector<char> buffer, Header h)
{
	vector<Table> Result;

	for (int i = sizeof(Header); i < *(int*)h.Number_Of_Rva_And_Sizes; i += sizeof(Table)) {
		Result.push_back(*(Table*)(&buffer[i]));
	}

	return Result;
}

vector<string> DLL::Gather_All_Export_Names(Header h, vector<char> buffer, Table t)
{
	vector<string> Result;

	Export_Directory_Table EDT = *(Export_Directory_Table*)&(buffer[*(int*)t.Table_Name]);

	//gather all symbol name pointters
	vector<int> Indicies;
	for (int i = *(int*)EDT.Name_Pointer_RVA; i < buffer.size(); i += 4) {
		Indicies.push_back(*(int*)&(buffer[i]));
	}

	//now go through the indicies and add the names
	for (auto i : Indicies) {
		string Name = "";
		for (int j = i; j < buffer.size(); j++) {
			if (buffer[j] == '\0')
				break;
			Name += buffer[j];
		}
		Result.push_back(Name);
	}

	return Result;
}

void DLL::DLL_Analyser(vector<string>& Output)
{
	//get the header and then start up the section suckup syste 2000 :D
	//read the file
	vector<uint8_t> tmp = DOCKER::Get_Char_Buffer_From_File(DOCKER::Working_Dir.back().second + DOCKER::FileName.back(), "");
	vector<char> buffer = vector<char>(*(char*)tmp.data(), tmp.size());

	//read the header of this obj file
	Header header = *(Header*)&buffer;

	//now gather all the RVA sizes
	vector<Table> Tables = Gather_All_Tables(buffer, header);

	DOCKER::Append(Output, Gather_All_Export_Names(header, buffer, Tables[0]));
}
