#include <vector>
#include <string>

using namespace std;

enum class INSTALL{
	DEFAULT,
};

enum class INTRODUCE {
	LOCAL,
	HTTPS,
	CONSOLE,
};

namespace OS {
	const string WIN = "win";
	const string UNIX = "unix";
}

namespace ARCHITECTURE {
	const string X86 = "x86";
	const string ARM = "arm";
}

class Medium {
public:
	//The OS this product is supposed to be installed onto.
	string Platform = "";

	//The system that can fetch the product.
	INTRODUCE Introducer = INTRODUCE::LOCAL;

	//string address the finded dependecy is stored up to for later usage.
	string* Dependency_Location = nullptr;

	//Describes the Name of the product in question.
	string Product_ID = "";

	// Used for the Scraper which finds function and global variables from dll/obj/exe/etc...
	vector<string> Symbols;
};

class Satellite {
public:
	//Default Depedencies installation
	Satellite() {
		this->Installation_Type = INSTALL::DEFAULT;
		Init_Wanted_Dependencies();
		Factory();
	}

	Satellite(INSTALL Installation_Type) {
		this->Installation_Type = Installation_Type;
		Init_Wanted_Dependencies();
		Factory();
	}

	void Scraper();	// Automatically fetches all dll/lib's which contain imported function bodies.

private:
	vector<string> Chache;

	INSTALL Installation_Type;

	vector<Medium> Dependecies;

	void Init_Wanted_Dependencies();
	void Factory();	// For going through all the needed executable files.

	void Process_Local_Dependencies(Medium m);
	void Process_Console_Dependencies(Medium m);

	void Save_To_Cache(Medium m);

	vector<Medium> Read_Symbol_Source_Service(string file_name);	// the SSSS Symbol Source Service System 2000
	void Write_Symbol_Source_Service_Cache(vector<Medium> data, string file_name);
	string Ident(string src, int count);
	string Quote(string src);
};