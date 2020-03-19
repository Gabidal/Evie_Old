#ifndef _USR_H_
#define _USR_H_
#include <vector>
#include <string>
using namespace std;


struct output {
	string Source_File;
	string Destination_File;
	string OS;
	string Architecture;
	string Obj_Type;
	int Bits_Mode = 4;
};

class Usr
{
public:
	output Output;
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
	void Find_Source_File(int i);
	void Find_Destination_File(int i);
	void Find_OS(int i);
	void Find_Architecture(int i);
	void Find_Bits_Mode(int i);
	void Find_Obj_Type(int i);
};


#endif