#include "../../H/UI/Usr.h"
#include "../../H/Back/Token.h"
#include <cstring>
#include <iostream>
#include <optional>

void Object::Load()
{
	if (Initted)
		return;
	Initted = true;
	Safe_Merge(Members, Get_Members());
	for (auto p : Members) {
		p.second->Load();
	}
}

Object* Object::Get_Member(string key) {
	Load();
	auto i = Members.find(key);
	if (i == Members.end())
		return nullptr;
	return i->second;
}

void Object::Set(string key, Object* t)
{
	Members[key] = t;
}

map<string, Object*> Usr::Get_Members()
{
	/*
	output Info;
	*/
	return {
		std::make_pair(string("Info"), &Info)
	};
}


//main -in ~/test.g -out ~/test.asm -os win32 -arch x86 -mode 32
void Usr::Create_Argument_Stats()
{
	for (int i = 1; i < Argument_Amount; i++) {
		Find_Destination_File(i);
		Find_Source_File(i);
		Find_OS(i);
		Find_Architecture(i);
		Find_Bits_Mode(i);
	}
}

void Usr::Find_Source_File(int &i)
{
	if ((i <= Argument_Amount) && strcmp(Input[i], "-in") == 0)
	{
		Info.Source_File = Input[i + 1];
		i++;
	}
}

void Usr::Find_Destination_File(int &i)
{
	if ((i <= Argument_Amount) && strcmp(Input[i], "-out") == 0)
	{
		Info.Destination_File = Input[i + 1];
		i++;
	}
}

void Usr::Find_OS(int &i)
{
	if ((i <= Argument_Amount) && strcmp(Input[i], "-os") == 0)
	{
		Info.OS = Input[i + 1];
		i++;
	}
}

void Usr::Find_Architecture(int &i)
{
	if ((i <= Argument_Amount) && strcmp(Input[i], "-arch") == 0)
	{
		Info.Architecture = Input[i + 1];
		i++;
	}
}

void Usr::Find_Bits_Mode(int &i)
{
	if ((i <= Argument_Amount) && strcmp(Input[i], "-mode") == 0)
	{
		Info.Bits_Mode = Input[i + 1];
		i++;
	}
}

void Usr::Find_Obj_Type(int &i)
{
	if ((i <= Argument_Amount) && strcmp(Input[i], "-lib") == 0)
	{
		string tmp = string(Input[i + 1]);
		Info.Obj_Type = atoi(tmp.c_str());
		i++;
	}
}

map<string, Object*> output::Get_Members(){
	/*string Source_File;
	string Destination_File;
	string OS;
	string Architecture;
	string Obj_Type;
	int Bits_Mode = 4;*/
	return {
		std::make_pair(string("Source_File"), new StringObject(&Source_File)),
		std::make_pair(string("Destination_File"), new StringObject(&Destination_File)),
		std::make_pair(string("OS"),new StringObject(&OS)),
		std::make_pair(string("Architecture"),new StringObject(&Architecture)),
		std::make_pair(string("Obj_Type"), new StringObject(&Obj_Type)),
		std::make_pair(string("Bits_Mode"), new StringObject(&Bits_Mode))
	};
}

map<string, Object*> SymbolTableList::Get_Members()
{
	return map<string, Object*>();
}

bool is_number(const string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

optional<int> If_Int(string s) {
	if (is_number(s))
	{
		return optional<int> {
			atoi(s.c_str())
		};
	}
	return nullopt;
}

Object* SymbolTableList::Get_Member(string index)
{	
	Load();
	if (auto i = If_Int(index))
	{
		if (i.value() > Items.size() - 1)
			cout << "Error: Index: " << index << ", max-size: " <<  Items.size() << endl;
		return *Items.at(i.value());
	}
	else
	{
		//if constant
	}
	
	throw runtime_error("k Boomer!");
}

optional<Object*> Object::Get_Const_Data(Token* t)
{
	//sys:Info
	if (!t->is(_Number_) && (!t->is(_String_)))
	{
		vector<string> members = Get_Members(t);
		Object* Source = this;
		for (int i = 0; i < members.size(); i++) {
			Source = Source->Get_Member(members.at(i));
			if (Source == nullptr)
			{
				cout << "Error: " << "Illegal pointter fethcing! --> " << t->Name + ", " + t->Type << endl;
				return nullopt;
			}
		}
		return optional<Object*> { Source };
	}
	else if (t->is(_Number_))
	{
		return optional<Object*> { new IntObject(new int(atoi(t->Name.c_str()))) };
	}
	else if (t->is(_String_))
	{
		return optional<Object*> { new StringObject(new string(t->Name.substr(1, t->Name.size() - 2))) };
	}
	return nullopt;
}

void Object::Put(Object& other)
{
	if (Members.size() != other.Members.size())
	{
		cout << "Error: Ur using two totally different classes ya moron!" << endl;
		throw runtime_error("u retard!");
		return;
	}
	for (auto& m : other.Members)
	{
		Members.at(m.first)->Put(*m.second);
	}
}


void Object::Append(vector<string>* Dest, vector<string> Source)
{
	for (string i : Source)
	{
		Dest->push_back(i);
	}
}

vector<string> Object::Get_Members(Token* t)
{
	//sys:(Info:OS)
	vector<string> Phases;
	if (t->Name != "")
		Phases.push_back(t->Name);
	if (t->Offsetter != nullptr)
	{
		Append(&Phases, Get_Members(t->Offsetter));
	}
	else if (t->Childs.size() > 0)
	{
		Append(&Phases, Get_Members(t->Childs.at(0)));
	}
	return Phases;
}

void Object::Safe_Merge(map<string, Object*>& Dest, map<string, Object*> Source)
{
	for (auto i : Source) {
		if (i.second == nullptr)
			continue;
		Dest.insert(make_pair(i.first, i.second));
	}
}
