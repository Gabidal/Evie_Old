#include "../../H/Lexer/Position.h"
#include <vector>
#include <string>

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