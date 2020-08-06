#ifndef _USR_H_
#define _USR_H_
#include <vector>
#include <string>
#include <map>
#include <optional>
using namespace std;

class output{
public:
	string Source_File;
	string Destination_File;
	string OS = "win32";
	string Architecture = "x86";
	vector<string> Libs;
	vector<string> Source_Files;
	string Format = "exe";
	string Bits_Mode = "0";
	string Disable = "";
	string Debug = "";
	output() {
		#ifndef _WIN32
			OS = "unix";
		#endif
	}
	void Fill_Empty_Arguments();
};

class Usr
{
public:
	output Info;
	Usr(char** in, int count)
	{
		Input = in;
		Argument_Amount = count;
		Create_Argument_Stats();
		Info.Fill_Empty_Arguments();
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
