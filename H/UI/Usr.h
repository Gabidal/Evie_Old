#ifndef _USR_H_
#define _USR_H_
#include <vector>
#include <string>
#include <map>
using namespace std;

template<typename T>
class Waiter
{
private:
	void* Data;

public:
	Waiter(T* in) {
		Data = in;
	}

	string Get_Value()
	{
		return *(string*)Data;
	}
};

template<int>
class Waiter
{
public:
	string Get_Value()
	{
		return to_string((int*)Data);
	}
};

class Symbol_Table {
public:
	void Load();
	Symbol_Table();
	virtual map<string, Symbol_Table*> Get_Member_Pointters() = 0;
	virtual map<string, Waiter*> Get_Member_Data() = 0;
	virtual Symbol_Table* Get_Member_Pointter(string key);
	virtual Waiter* Get_Member_Data(string key);
private:
	map<string, Symbol_Table*> Member_Pointters;
	map<string, Waiter*> Member_Data;
};

class output : public Symbol_Table {
public:
	map<string, Symbol_Table*> Get_Member_Pointters();
	map<string, Waiter*> Get_Member_Data();

	string Source_File;
	string Destination_File;
	string OS = "win32";
	string Architecture = "x86";
	string Obj_Type = "exe";
	string Bits_Mode = "4";
	string Diable = "";
};

class SymbolTableList : public Symbol_Table
{
public:
	template<class T>
	SymbolTableList(vector<T> tables) {
		for (auto& i : tables) {
			Items.push_back(&i);
		}
	}

	map<string, Symbol_Table*> Get_Member_Pointters();
	map<string, Waiter*> Get_Member_Data(); 

	Symbol_Table* Get_Member_Pointter(string key);
	Waiter* Get_Member_Data(string key);
private:
	vector<Symbol_Table*> Items;
};



class Usr : public Symbol_Table
{
public:
	map<string, Symbol_Table*> Get_Member_Pointters();
	map<string, Waiter*> Get_Member_Data();
	output Info;
	Usr(char** in, int count)
	{
		Input = in;
		Argument_Amount = count;
		Create_Argument_Stats();
	}

	~Usr(){}

private:
	char** Input;
	int Argument_Amount;
	void Create_Argument_Stats();
	void Find_Source_File(int &i);
	void Find_Destination_File(int &i);
	void Find_OS(int &i);
	void Find_Architecture(int &i);
	void Find_Bits_Mode(int &i);
	void Find_Obj_Type(int &i);
};


#endif
