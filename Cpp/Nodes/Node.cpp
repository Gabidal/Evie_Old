#include "../../H/Nodes/Node.h"
#include "../../H/Nodes/Token.h"
#include <vector>
#include <string>
#include "../../H/Parser/Algebra.h"
#include "../../H/Docker/Mangler.h"
#include "../../H/UI/Safe.h"

using namespace std;

void Node::Update_Defined_Stack_Offsets()
{
	int Parameter_Offset = 0;
	int Local_Offset = 0;

	for (auto i : Defined) {
		if (i->is(PARAMETER_NODE)) {
			if (!Token(i).is(TOKEN::REGISTER)) {
				i->Memory_Offset = Parameter_Offset;
				i->Update_Size_By_Inheritted();
				Parameter_Offset += i->Get_Size();
			}
		}
		else if (i->is(OBJECT_NODE) || i->is(OBJECT_DEFINTION_NODE)) {
			//every local variable is defined default as a value in a register.
			if (i->Requires_Address) {
				i->Memory_Offset = Local_Offset;
				i->Update_Size_By_Inheritted();
				Local_Offset += i->Get_Size();
			}
		}
	}
}

Variable_Descriptor::Variable_Descriptor(Node* v, int i, vector<Node*> source) {
	Define_Index = i;
	Var = v;

	vector<Node*> Linear_Ast = Linearise(v, false);
	//for complex inlinings
	for (int n = i; n < source.size(); n++) {
		if (source[n]->is(ASSIGN_OPERATOR_NODE)) {
			for (auto c : Linear_Ast) {
				if (source[n]->Left->Name == c->Name) {
					Expiring_Index = n;
					goto Stop;
				}
			}
		}
		if (source[n]->is(CALL_NODE)) {
			for (auto c : Linear_Ast) {
				for (auto p : source[n]->Template_Function->Parameters) {
					if (p->is("ptr") != -1)
						if (p->Name == c->Name) {
							Expiring_Index = n;
							goto Stop;
						}
				}
			}
		}
		Expiring_Index = n;
	}
Stop:;
}

vector<string> Node::Get_Inheritted(bool Skip_Prefixes, bool Get_Name) {
	vector<string> Result;
	if (MANGLER::Is_Base_Type(this) || Get_Name) {
		return { Name };
	}
	else if (is(NUMBER_NODE)) {
		//1.29348
		if (find(Name.begin(), Name.end(), '.') != Name.end()) {
			if ((Name.end() - find(Name.begin(), Name.end(), '.')) <= 7)
				return Find(4, Global_Scope, "decimal")->Get_Inheritted(Skip_Prefixes, true);
			else
				return Find(8, Global_Scope, "decimal")->Get_Inheritted(Skip_Prefixes, true);
		}
		else {
			if (atoll(Name.c_str()) > INT_MAX) {
				return Find(8, Global_Scope, "integer")->Get_Inheritted(Skip_Prefixes, true);
			}
			return Find(4, Global_Scope, "integer")->Get_Inheritted(Skip_Prefixes, true);
		}
	}
	else {
		for (int i = 0; i < Inheritted.size(); i++) {
			if (Skip_Prefixes && ((Inheritted[i] == "ptr") || (Inheritted[i] == "ref")))
				continue;
			Result.push_back(Inheritted[i]);
		}
		return Result;
	}
}

string Node::Get_Inheritted(string seperator, bool Skip_Prefixes, bool Get_Name, bool skip_keywords) {
	if (MANGLER::Is_Base_Type(this) || Get_Name) {
		return seperator + Name;
	}
	else if (is(NUMBER_NODE)) {
		//1.29348
		if (find(Name.begin(), Name.end(), '.') != Name.end()) {
			if ((Name.end() - find(Name.begin(), Name.end(), '.')) <= 7)
				return Find(4, Global_Scope, "decimal")->Get_Inheritted(seperator, Skip_Prefixes, true);
			else
				return Find(8, Global_Scope, "decimal")->Get_Inheritted(seperator,  Skip_Prefixes, true);
		}
		else {
			if (atoll(Name.c_str()) > INT_MAX) {
				return Find(8, Global_Scope, "integer")->Get_Inheritted(seperator, Skip_Prefixes, true);
			}
			return Find(4, Global_Scope, "integer")->Get_Inheritted(seperator, Skip_Prefixes, true);
		}
	}
	else {
		string result = "";
		for (int i = 0; i < Inheritted.size(); i++) {
			if (Skip_Prefixes && ((Inheritted[i] == "ptr") || (Inheritted[i] == "ref")))
				continue;
			else if (skip_keywords && Lexer::GetComponents(Inheritted[i])[0].is(Flags::KEYWORD_COMPONENT))
				continue;
			result += seperator + Inheritted[i];
		}
		return result;
	}
}

Node* Node::Get_Parent_As(int F, Node* parent) {
	if (parent->is(F))
		return parent;
	if (parent->Parent != nullptr)
		return Get_Parent_As(F, parent->Parent);
	Report(Observation(ERROR, "Parent NULL!!", *Location));
	throw::exception("ERROR!");
}

Node* Node::Find(Node* n, Node* p) {
	if (n->Name == "\n")
		return nullptr;
	if (n->is(NUMBER_NODE) || n->is(STRING_NODE) || n->is(LABEL_NODE))
		return n;
	if (p == nullptr) {
		Report(Observation(ERROR, "Critical Error: parent is null!", *Location));
		throw::exception("ERROR!");
	}
	for (Node* i : p->Defined)
		if (i->Name == n->Name)
			return i;
	if (p->Parent != nullptr)
		return Find(n->Name, p->Parent);
	return nullptr;
}

Node* Node::Find(string name, Node* parent, int flags) {
	if (name == "\n")
		return nullptr;
	if (parent == nullptr) {
		Report(Observation(ERROR, "Critical Error: parent is null!", *Location));
		throw::exception("ERROR!");
		return nullptr;
	}
	for (Node* i : parent->Defined)
		if (i->Name == name && i->is(flags))
			return i;
	if (parent->Parent != nullptr)
		return Find(name, parent->Parent, flags);
	return nullptr;
}

Node* Node::Find(string name, Node* parent, bool Need_Parent_existance) {
	if (name == "\n")
		return nullptr;
	if (parent == nullptr /*&& Need_Parent_existance*/) {
		Report(Observation(ERROR, "Critical Error: parent is null!", *Location));
		throw::exception("ERROR!");
		return nullptr;
	}
	for (Node* i : parent->Defined)
		if (i->Name == name)
			return i;
	if (parent->Parent != nullptr)
		return Find(name, parent->Parent, Need_Parent_existance);
	return nullptr;
}