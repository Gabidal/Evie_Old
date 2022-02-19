#include "../../H/Lexer/Position.h"
#include <vector>
#include <string>

#include "../../H/Docker/Docker.h"

using namespace std;

string* FileName = new string("No File");

Position::Position(int line, int character, int local, int absolute)
{
	Line = line;
	Character = character;
	Local = local;
	Absolute = absolute;
	File_Name = FileName->c_str();
}

int Position::GetFileIndex()
{
	for (int i = 0; i < DOCKER::Included_Files.size(); i++)
		if (DOCKER::Included_Files[i] == File_Name)
			return i;
}
