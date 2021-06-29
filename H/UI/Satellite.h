#include <vector>
#include <string>

using namespace std;

enum class INSTALL{
	DEFAULT,
};

enum class OS {
	ANY,
	WINDOWS,
	LINUX,
};

enum class INTRODUCE {
	LOCAL,
	HTTPS,
	CONSOLE,
};

class Medium {
public:
	//Describes the Name of the product in question.
	string Product_ID = "";

	//The OS this product is supposed to be installed onto.
	OS Platform = OS::ANY;

	//The system that can fetch the product.
	INTRODUCE Introducer = INTRODUCE::LOCAL;
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
};