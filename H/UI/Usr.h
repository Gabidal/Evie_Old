#ifndef _USR_H_
#define _USR_H_
#include <vector>
#include <string>
#include <map>
#include <optional>
using namespace std;

class Token;


class Object {
public:
	Object() {}
	Object(void* in) {
		Data = in;
	}

	bool Initted = false;
	void Load();
	virtual map<string, Object*> Get_Members() = 0;
	virtual Object* Get_Member(string key);
	void Set(string key, Object* t);
	optional<Object*> Get_Const_Data(Token* t);
	virtual void Put(Object& other);

	bool operator==(Object& other) {
		return this->Get_Value() == other.Get_Value();
	}
	virtual string Get_Value()
	{
		return "";
	}
	void* Data = nullptr;

protected:
	map<string, Object*> Members;
	void Append(vector<string>* Dest, vector<string> Source);
	vector<string> Get_Members(Token* t);
	void Safe_Merge(map<string, Object*>& Dest, map<string, Object*> Source);
};

class StringObject : public Object
{
public:
	StringObject(string* in) : Object(in) {}
	map<string, Object*> Get_Members() { return map<string, Object*>(); }
	void Put(Object& other) {
		*(string*)Data = *(string*)other.Data;
	}

	string Get_Value()
	{
		return *(string*)Data;
	}
};

class IntObject : public Object
{
public:
	IntObject(int* in) : Object(in) {}
	map<string, Object*> Get_Members() { return map<string, Object*>(); }
	void Put(Object& other) {
		*(int*)Data = *(int*)other.Data;
	}
	int& Get_Int_Value() {
		return *(int*)Data;
	}
	string Get_Value()
	{
		return to_string(*(int*)Data);
	}
};


class output : public Object {
public:
	map<string, Object*> Get_Members();
	string Source_File;
	string Destination_File;
	string OS = "win32";
	string Architecture = "x86";
	vector<string> Libs;
	string Format = "exe";
	string Bits_Mode = "4";
	string Disable = "";
	string Debug = "";
	Object& operator=(output& other) {
		 Source_File = other.Source_File;
		 Destination_File = other.Destination_File;
		 OS = other.OS;
		 Architecture = other.Architecture;
		 Libs = other.Libs;
		 Format = other.Format;
		 Bits_Mode = other.Bits_Mode;
		 Disable = other.Disable;
		 Debug = other.Debug;
		return *this;
	}

};

class SymbolTableList : public Object
{
public:
	template<class T>
	SymbolTableList(vector<T> &tables) {
		for (T& i : tables) {
			Items.push_back(&(Object*&)i);
		}
	}

	map<string, Object*> Get_Members();

	Object* Get_Member(string key);
private:
	vector<Object**> Items;
};



class Usr : public Object
{
public:
	map<string, Object*> Get_Members();
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
	void Find_Format(int &i);
	void Find_Lib(int& i);
	void Find_Debug_Type(int& i);
};


#endif
