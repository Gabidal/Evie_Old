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
	string* Dependency_Location;

	//Describes the Name of the product in question.
	string Product_ID = "";
};

class Satellite {
public:
	//Default Depedencies installation
	Satellite() {
		this->Installation_Type = INSTALL::DEFAULT;
	}

	Satellite(INSTALL Installation_Type) {
		this->Installation_Type = Installation_Type;
	}
private:
	INSTALL Installation_Type;

	vector<Medium> Dependecies;

	void Init_Wanted_Dependencies();
	void Factory();

	void Process_Local_Dependencies(Medium m);
	void Process_Console_Dependencies(Medium m);
};