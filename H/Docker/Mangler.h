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
		RETURN,
	};
	string Un_Mangle(string raw);
	string Mangle(Node* raw, string Force_Complex);
	string Get_Function_Name(string func);
	bool Is_Base_Type(Node* n);
	bool Is_Based_On_Base_Type(Node* n);
	bool Is_Template(Node* n);
	int Find_Classes(string s);
	//  alias , real id
	//       P, ptr
	//       i, int
			  //cpp
	extern vector<pair<string, vector<pair<string, pair<int, string>>>>> IDS;
	void Add_ID(string Lang, pair<string, pair<int, string>> id);
	string Get_Key(string Val, string Lang);
	vector<pair<string, pair<int, string>>>* Find_STD_List(string Lang);
	pair<int, string>* Find(string Key, vector<pair<string, pair<int, string>>>* Current_IDS);
	void Clear_Class_Zipping_List();

}

#endif