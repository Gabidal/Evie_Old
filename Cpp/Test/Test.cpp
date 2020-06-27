#include "..\..\H\Test\Test.h"

Test::Test()
{
    Parser_Classes();
    Print_Results();
}

void Test::Print_Results()
{
	cout << "\n[-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-]" << endl;
	for (auto i : Not_Working_Features)
		cout << "  Errors:     " << i.first << " " << i.second.first << " " << i.second.second << endl;
	if (Not_Working_Features.size() > 0)
		cout << "[-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-]" << endl;
	for (auto i : Working_Features)
		cout << "  Working:     " << i.first << " " << i.second.first << " " << i.second.second << endl;
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

void Test::Parser_Classes()
{
	/*		type int(){
			}
	*/
	Parser p;
	p.Input = Lexer::GetComponents("type int()\n{\nsize 123\n}");
	p.Factory();
	//[-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-]
	if (Find("int", p.Defined_Keywords) == nullptr)
		Not_Working_Features.push_back({ "Parser", {"Classes", "Defined_Keywords[0] didnt contain made class."} });
	else
		Working_Features.push_back({ "Parser", {"Classes", "Defined_Keywords[0] did contain made class"} });
	//[-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-]
	if (Find("int", p.Output) == nullptr)
		Not_Working_Features.push_back({ "Parser", {"Classes", "Output[0] didnt contain made class constructor."} });
	else
		Working_Features.push_back({ "Parser", {"Classes", "Output[0] did contain made class constructor"} });
	//[-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-]
	if ((Find("int", p.Defined_Keywords) != nullptr) && (Find("int", p.Defined_Keywords)->Size != 123))
		Not_Working_Features.push_back({ "Parser", {"Classes", "Defined_Keywords[0] didnt contain made class size."} });
	else if (Find("int", p.Defined_Keywords) != nullptr)
		Working_Features.push_back({ "Parser", {"Classes", "Defined_Keywords[0] did contain made class size"} });
	//[-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-]
}
