#include "..\..\H\Test\Test.h"

Test::Test()
{
	Input.push_back({ "Parser", {"Constructor", "type int()\n{}"} });
	Input.push_back({ "Parser", {"Prototype", "type int"} });
	Input.push_back({ "Parser", {"Size", "type int(){size 123}"} });
	//type int()(size 4)\n type test()( size (int a\n int b\n int c))\n int main()(test me\n me.a = 123)
	Input.push_back({ "Parser", {"Member", "type int()(size 4)\n type test()( size (int a\n int b\n int c))\n int main()(test me\n me.b)"} });
	Input.push_back({ "Parser", {"Member", "type int()(size 4)\n type test()( size (int a\n int b\n int c))\n int main()(test ptr me\n me.c)"} });
	for (int i = 0; i < Input.size(); i++) {
		Parser_Constructors(i);
		Parser_Prototypes(i);
		Parser_Size(i);
		Parser_Members(i);
	}
    Print_Results();
}

void Test::Print_Results()
{
	if ((Not_Working_Features.size() > 0) || (Working_Features.size() > 0))
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
	//if (!working)
	//	Not_Working_Features.push_back({ Input[i].first, {In, report} });
	return;
}

void Test::Parser_Constructors(int i)
{
	if (Input[i].first != "Parser")
		return;
	if (Input[i].second.first != "Constructor")
		return;
	/*		type int(){
			}
	*/
	Parser p;
	p.Input = Lexer::GetComponents(Input[i].second.second);
	p.Factory();
	//[-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-]
	if (!(p.Output.size() > 0))
		Report_Behaviour(i, "Output didnt contain made class constructor.", false);
	else
		Report_Behaviour(i, "Output did contain made class constructor " + p.Output[0]->Name + ".", true);
	//[-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-]
}

void Test::Parser_Prototypes(int i)
{
	if (Input[i].first != "Parser")
		return;
	if (Input[i].second.first != "Prototype")
		return;
	/*		int a
	*/
	Parser p;
	p.Input = Lexer::GetComponents(Input[i].second.second);
	p.Factory();
	//[-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-]
	if (!(p.Defined_Keywords.size() > 0))
		Report_Behaviour(i, "Defined_Keywords didnt contain made Prototype.", false);
	else
		Report_Behaviour(i, "Defined_Keywords did contain made Prototype " + p.Defined_Keywords[0]->Name + ".", true);
	//[-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-]
}

void Test::Parser_Size(int i)
{
	if (Input[i].first != "Parser")
		return;
	if (Input[i].second.first != "Size")
		return;
	/*		type banana()(size 4)
	*/
	Parser p;
	p.Input = Lexer::GetComponents(Input[i].second.second);
	p.Factory();
	//[-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-]
	if (!(p.Defined_Keywords.size() > 0))
		Report_Behaviour(i, "Defined_Keywords didnt contain made class size.", false);
	else
		Report_Behaviour(i, "Defined_Keywords did contain made class size " + to_string(p.Defined_Keywords[0]->Size) + ".", true);
	//[-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-]
}

void Test::Parser_Members(int i)
{
	if (Input[i].first != "Parser")
		return;
	if (Input[i].second.first != "Member")
		return;
	//type int()(size 4)\n type test()( size (int a\n int b\n int c))\n int main()(test me\n me.a = 123)
	Parser p;
	p.Input = Lexer::GetComponents(Input[i].second.second);
	p.Factory();
	//[-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-]
	if (Find("main", p.Output) != nullptr) {
		vector<Token*> local_variables = Find("main", p.Output)->Right_Side_Token->Childs;
		if (Find("me", local_variables) != nullptr) {
			Token me;
			for (Token* j : local_variables)
				if ((j->Name == "me") && (j->Offsetter != nullptr)) {
					me = *j;
					break;
				}
			if (me.Offsetter != nullptr) {
				Report_Behaviour(i, "Object did contain the member offset " + me.Offsetter->Name, true);
				if (me.is(_Pointting_))
					Report_Behaviour(i, "Member fetching is called by ptr.", true);
				else if (me.is(_Array_))
					Report_Behaviour(i, "Member fetching is called directly.", true);
			}
			else
				Report_Behaviour(i, "Object offsetter was nullptr!", false);
		}
		else
			Report_Behaviour(i, "Object could not be created!", false);
	}
	else
		Report_Behaviour(i, "Main function could not be made!", false);

}
