#include "../../H/Docker/LIB/LIB.h"

void LIB::Generate_Binary_Symbols(string filename, string WD)
{
	string NM_Posix = "";
	//first start the NM.exe
	if (sys->Info.OS == "win32")
		NM_Posix = "nm.exe ";
	else
		NM_Posix = "./nm ";

	system((NM_Posix + WD + filename + " --extern-only --defined-only -P > .TMP.txt").c_str());
	return;
}