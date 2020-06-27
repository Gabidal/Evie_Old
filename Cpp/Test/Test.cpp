#include "..\..\H\Test\Test.h"

Test::Test()
{
	Input.push_back({ "Parser", {"Classes", "type int()\n{\nsize 123\n}"} });
	Input.push_back({ "Parser", {"Classes", "type int(){\nsize 123\n}"} });
	Input.push_back({ "Parser", {"Classes", "type int(){size 123}"} });
	for (int i = 0; i < Input.size(); i++) {
		Parser_Classes(i);
	}
    Print_Results();
}

void Test::Print_Results()
{
	cout << "\n[-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-]" << endl;
	for (auto i : Not_Working_Features)
		cout << "  Errors:     " << i.second.first << " => " << i.first << " => " << i.second.second << endl;
	if (Not_Working_Features.size() > 0)
		cout << "[-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-]" << endl;
	for (auto i : Working_Features)
		cout << "  Working:     " << i.second.first << " => " << i.first << " => " << i.second.second << endl;
	if (Working_Features.size() > 0)
		cout << "[-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-]\n\n" << endl;
}

Token* Test::Find(string name, vector<Token*> list)
{
	for (auto* i : list)
		if (i->Name == name)
			return i;
	return nullptr;
}

string Test::Replace(string Source, char oldVal, string newVal)
{
	string Dest = "";
	for (char c : Source) {
		if (c == oldVal)
			Dest += newVal;
		else
			Dest += c;
	}
	return Dest;
}

void Test::Report_Behaviour(int i, string report, bool working)
{
	string In = Replace(Input[i].second.second, '\n', "\\n");
	if (working)
		Working_Features.push_back({ Input[i].first, {In, report} });
	else
		Not_Working_Features.push_back({ Input[i].first, {In, report} });
	return;
}

void Test::Parser_Classes(int i)
{
	if (Input[i].first != "Parser")
		return;
	if (Input[i].second.first != "Classes")
		return;
	/*		type int(){
			}
	*/
	Parser p;
	p.Input = Lexer::GetComponents(Input[i].second.second);
	p.Factory();
	//[-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-]
	if (Find("int", p.Defined_Keywords) == nullptr)
		Report_Behaviour(i, "Defined_Keywords[0] didnt contain made class.", false);
	else
		Report_Behaviour(i, "Defined_Keywords[0] did contain made class", true);
	//[-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-]
	if (Find("int", p.Output) == nullptr)
		Report_Behaviour(i, "Output[0] didnt contain made class constructor.", false);
	else
		Report_Behaviour(i, "Output[0] did contain made class constructor", true);
	//[-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-]
	if ((Find("int", p.Defined_Keywords) != nullptr) && (Find("int", p.Defined_Keywords)->Size == 0))
		Report_Behaviour(i, "Defined_Keywords[0] didnt contain made class size.", false);
	else if (Find("int", p.Defined_Keywords) != nullptr)
		Report_Behaviour(i, "Defined_Keywords[0] did contain made class size", true);
	//[-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-]
}
