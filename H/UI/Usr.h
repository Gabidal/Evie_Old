#ifndef _USR_H_
#define _USR_H_
#include <vector>
#include <string>
#include <map>
#include <optional>
using namespace std;

class Token;

class Waiter
{
protected:
	void* Data;

public:
	Waiter(void* in) {
		Data = in;
	}
	bool operator==(Waiter& other) {
		return this->Get_Value() == other.Get_Value();
	}
	virtual string Get_Value() = 0;
};

class StringWaiter : public Waiter
{
public:
	StringWaiter(string* in) : Waiter(in) {}

	string Get_Value()
	{
		return *(string*)Data;
	}
};

class IntWaiter : public Waiter
{
public:
	IntWaiter(int* in) : Waiter(in) {}
	
	string Get_Value()
	{
		return to_string(*(int*)Data);
	}
};

class Symbol_Table {
public:
	bool Initted = false;
	void Load();
	Symbol_Table();
	virtual map<string, Symbol_Table*> Get_Member_Pointters() = 0;
	virtual map<string, Waiter*> Get_Member_Data() = 0;
	virtual Symbol_Table* Get_Member_Pointter(string key);
	virtual Waiter* Get_Member_Data(string key);
	void Set(string key, Symbol_Table* t);
	optional<Waiter*> Get_Const_Data(Token* t);
private:
	map<string, Symbol_Table*> Member_Pointters;
	map<string, Waiter*> Member_Data;
	void Append(vector<string>* Dest, vector<string> Source);
	vector<string> Get_Members(Token* t);
	void Safe_Merge(map<string, Symbol_Table*> &Dest, map<string, Symbol_Table*> Source);
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
	SymbolTableList(vector<T> &tables) {
		for (T& i : tables) {
			Items.push_back(&(Symbol_Table*&)i);
		}
	}

	map<string, Symbol_Table*> Get_Member_Pointters();
	map<string, Waiter*> Get_Member_Data(); 

	Symbol_Table* Get_Member_Pointter(string key);
	Waiter* Get_Member_Data(string key);
private:
	vector<Symbol_Table**> Items;
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
