#include "..\..\H\UI\Safe.h"

const string Red = "\x1B[1;31m";
const string Green = "\x1b[1;32m";
const string Yellow = "\x1b[1;33m";
const string Blue = "\x1b[1;34m";
const string Magenta = "\x1b[1;35m";
const string Cyan = "\x1b[1;36m";
const string White = "\x1b[1;37m";
const string Reset = "\x1b[1;0m";

void Safe::Factory()
{
}

void Observation::Report()
{
	string Head;
	if (Type == ERROR)
		Head = Red + "Error" + Reset + ": ";
	else if (Type == WARNING)
		Head = Yellow + "Warning" + Reset + ": ";
	else if (Type == SOLUTION)
		Head = Green + "Solution" + Reset + ": {\n  ";

	if (Pos.GetFilePath() != nullptr)
		cout << Pos.GetFilePath() << ":" << Pos.GetFriendlyLine() << ":" << Pos.GetFriendlyCharacter() << ": " << Head << Msg << endl;
	else 
		cout << Head << Msg << endl;
	if (Type == SOLUTION)
		cout << "}" << endl;
}

void Report(Observation o)
{
	o.Report();
}

void Report(vector<Observation> o)
{
	for (auto i : o)
		i.Report();
}
