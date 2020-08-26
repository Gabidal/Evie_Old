#include "../../H/Docker/TXT.h"

void TXT::TXT_Analyzer(vector<string>& Output)
{
	ifstream file(DOCKER::Working_Dir + DOCKER::FileName.back()); 
	file.seekg(0, SEEK_END);
	long long size = file.tellg();
	vector<char> Buffer(size); 
	file.seekg(0, SEEK_SET);
	file.read(Buffer.data(), size);
	file.close();
	Output.push_back(string(Buffer.data(), Buffer.size()));
	return;
}