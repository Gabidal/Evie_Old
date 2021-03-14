#include "../../H/Nodes/Node.h"
#include "../../H/Nodes/Token.h"
#include "../../H/Parser/Algebra.h"
#include "../../H/Docker/Mangler.h"
#include "../../H/UI/Safe.h"

#include <vector>
#include <string>
#include <climits>

using namespace std;

void Node::Update_Defined_Stack_Offsets()
{
	//skip the returnin address.
	int Parameter_Offset = 8;
	int Local_Offset = 0;
	//first conmpute all the memory locaitions.
	for (auto& i : Defined) {
		if (i->is(OBJECT_NODE) || i->is(OBJECT_DEFINTION_NODE)) {
			//every local variable is defined default as a value in a register.
			if (i->Requires_Address) {
				i->Memory_Offset = Local_Offset + Size_of_Call_Space;
				i->Update_Size_By_Inheritted();
				Local_Offset += i->Get_Size();
			}
		}
		if (i->is(PARAMETER_NODE)) {
			if (!Token(i).is(TOKEN::REGISTER)) {
				//the parameters locate below the local variable space and the returning address 
				//also, do remeber that, the pushes that the code needs for the nonvolatiles
				//those come before the parameter space.
				i->Memory_Offset = Parameter_Offset + Size_of_Call_Space;
				i->Update_Size_By_Inheritted();
				Parameter_Offset += i->Get_Size();
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
		if (source[n]->is(ASSIGN_OPERATOR_NODE) || source[n]->is(POSTFIX_NODE)) {
			for (auto c : Linear_Ast) {
				if (source[n]->Left->Name == c->Name) {
					Expiring_Index = n;
					goto Stop;
				}
			}
		}
		if (source[n]->is(PREFIX_NODE)) {
			for (auto c : Linear_Ast) {
				if (source[n]->Right->Name == c->Name) {
					Expiring_Index = n;
					goto Stop;
				}
			}
		}
		if (source[n]->is(CALL_NODE)) {
			for (auto c : Linear_Ast) {
				for (auto p : source[n]->Function_Implementation->Parameters) {
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
	if (parent->Scope != nullptr)
		return Get_Parent_As(F, parent->Scope);
	Report(Observation(ERROR, "Parent NULL!!", *Location));
	throw::runtime_error("ERROR!");
}

Node* Node::Find(Node* n, Node* p) {
	if (n->Name == "\n")
		return nullptr;
	if (n->is(NUMBER_NODE) || n->is(STRING_NODE) || n->is(LABEL_NODE))
		return n;
	if (p == nullptr) {
		Report(Observation(ERROR, "Critical Error: parent is null!", *Location));
		throw::runtime_error("ERROR!");
	}
	for (Node* i : p->Defined)
		if (i->Name == n->Name) {
			if (n->Cast_Type != "") {
				Node* tmp = i->Copy_Node(i, i->Scope);
				tmp->Cast_Type = n->Cast_Type;
				return tmp;
			}
			return i;
		}
	if (p->Scope != nullptr)
		if (Find(n->Name, p->Scope) != nullptr)
			return Find(n->Name, p->Scope);
	if (p->Cast_Type != "")
		for (auto i : p->Find(p->Cast_Type, p, CLASS_NODE)->Defined)
			if (i->Name == n->Name)
				return i;
	return nullptr;
}

Node* Node::Find(string name, Node* parent, int flags) {
	if (name == "\n")
		return nullptr;
	if (parent == nullptr) {
		Report(Observation(ERROR, "Critical Error: parent is null!", *Location));
		throw::runtime_error("ERROR!");
		return nullptr;
	}
	for (Node* i : parent->Defined)
		if (i->Name == name && i->is(flags))
			return i;
	if (parent->Scope != nullptr)
		if (Find(name, parent->Scope, flags) != nullptr)
			return Find(name, parent->Scope, flags);
	if (parent->Cast_Type != "")
		for (auto i : parent->Find(parent->Cast_Type, parent, CLASS_NODE)->Defined)
			if (i->Name == name)
				return i;
	return nullptr;
}

Node* Node::Find(string name, Node* parent, bool Need_Parent_existance) {
	if (name == "\n")
		return nullptr;
	if (parent == nullptr /*&& Need_Parent_existance*/) {
		Report(Observation(ERROR, "Critical Error: parent is null!", *Location));
		throw::runtime_error("ERROR!");
		return nullptr;
	}
	for (Node* i : parent->Defined)
		if (i->Name == name)
			return i;
	if (parent->Scope != nullptr)
		if (Find(name, parent->Scope, Need_Parent_existance) != nullptr)
			return Find(name, parent->Scope, Need_Parent_existance);
	if (parent->Cast_Type != "")
		for (auto i : parent->Find(parent->Cast_Type, parent, CLASS_NODE)->Defined)
			if (i->Name == name)
				return i;
	return nullptr;
}

void Node::Get_Inheritted_Class_Members() {
	for (string s : Inheritted) {
		if (Lexer::GetComponents(s)[0].is(Flags::KEYWORD_COMPONENT))
			continue;
		if (s == ".")
			continue;
		Node* inheritted = Find(s, Scope, CLASS_NODE);
		for (auto i : inheritted->Defined)
			for (auto j : this->Defined) {
				if (j->Name == i->Name)
					Report(Observation(ERROR, "Overlapping member variable names '" + i->Name + "' and '" + j->Name + "' in '" + this->Scope->Name + ".", *this->Scope->Location));
			}
		this->Defined.insert(this->Defined.begin(), inheritted->Defined.begin(), inheritted->Defined.end());
	}
}

void Node::Update_Inheritance() {
	if (Cast_Type != "")
		return;
	//save all keyword inheritances.
	vector<string> Keyword_Inheritance;
	for (auto i : Inheritted)
		if (Lexer::GetComponents(i)[0].is(Flags::KEYWORD_COMPONENT))
			Keyword_Inheritance.push_back(i);
	//remove all inheritances
	Inheritted.clear();

	Inheritted.push_back(Cast_Type);
	Inheritted.insert(Inheritted.end(), Keyword_Inheritance.begin(), Keyword_Inheritance.end());
}