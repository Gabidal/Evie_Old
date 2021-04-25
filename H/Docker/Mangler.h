#ifndef _MANGLER_H_
#define _MANGLER_H_
#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

class Node;

namespace MANGLER {
	enum Role {
		VARIABLE,
		PREFIX,
		POSTFIX,
		CLASS,
		END_CLASS,
		NUMBER,
	};
	string Un_Mangle(string raw);
	string Mangle(Node* raw, bool Force_Complex = false);
	bool Is_Base_Type(Node* n);
	bool Is_Based_On_Base_Type(Node* n);
	bool Is_Template(Node* n);
	int Find(string s);
	//  alias , real id
	//       P, ptr
	//       i, int
	extern map<string, pair<int, string>> IDS;
	void Add_ID(pair<string, pair<int, string>> id);
}

#endif