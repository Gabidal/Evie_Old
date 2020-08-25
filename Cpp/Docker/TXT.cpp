#include "../../H/Docker/TXT.h"

void TXT::TXT_Analyzer(vector<string>& Output)
{
	DOCKER::Append(Output, DOCKER::Get_Header(DOCKER::FileName.back()));
}
