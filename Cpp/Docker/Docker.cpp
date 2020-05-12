#include "../../H/Docker/Docker.h"

void Docker::Get_Analyzer()
{
	//if everything fails to check out it means,
	//that it is a txt file and thus call the lexer for that purpose.
	//function<void()> analyzer = bind(&Docker::TXT_Analyzer, this);//[this]() {TXT_Analyzer(); };
	//function<void()> analyzer = this->TXT_Analyzer;		//!!!
	ifstream file(Working_Dir + FileName);
	//safe check
	if (!file.is_open()) {
		cout << "Error: Unable to open file " << Working_Dir + FileName << endl;
		return;
	}
	//read Max_ID size into a buffer
	char Buffer[16];
	file.read(Buffer, 16);
	//iterate every map ID in Translators map
	for (auto i : Translators) {
		if (strncmp(Buffer, i.first.c_str(), i.first.size()) == 0) {
			i.second();
			return;
		}
	}
	TXT_Analyzer();
	return;
}

void Docker::TXT_Analyzer()
{
	Output = Lexer::GetComponentsFromFile(Working_Dir + FileName);
}

void Docker::DLL_Analyzer()
{
}

void Docker::LIB_Analyzer()
{
}

void Docker::ELF_Analyzer()
{
}
