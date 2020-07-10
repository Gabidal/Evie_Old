#ifndef _NODE_H_
#deifne _NODE_H_
#include <string>

using namespace std;

class Node
{
public:
	Node(){}
	~Node(){}
	string Name = "";
	//this string tells the pattern that created this Node
	string Pattern = "";
	//for the AST
	vector<Node> Right_Side_Nodes;
	vector<Node> Left_Side_Nodes;
private:

};

#endif