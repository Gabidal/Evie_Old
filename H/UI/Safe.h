#include "../Nodes/Node.h"
#include <vector>
#include <string>

using namespace std;

enum note {
	ERROR,
	WARNING,
	
};

class Observation {
public:
private:
};

class Safe {
public:
	Safe(vector<Node*> i) : Input(i) { Factory(); }
private:
	void Factory();
	vector<Node*> Input;
};