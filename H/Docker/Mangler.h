#ifndef _MANGLER_H_
#define _MANGLER_H_
#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;



namespace MANGLER {
	enum Role {
		VARIABLE,
		PREFIX,
		POSTFIX,
		CLASS,
		NUMBER,
	};
	string Un_Mangle(string raw);
	//  alias , real id
	//       P, ptr
	//       i, int
	extern map<string, pair<int, string>> IDS;
	void Add_ID(pair<string, pair<int, string>> id);
}

#endif