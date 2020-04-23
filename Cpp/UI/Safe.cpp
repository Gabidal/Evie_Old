#include "../../H/UI/Safe.h"
extern Selector* S;

void Safe::Factory(){
    for (IR* i: Input){
        for (Token* t: i->Parameters){
            Safe_Cache_Usation(t);
            Safe_Type_Inheritance(t);
        }
        Insight(i);
    }
    for (Token* i: Types)
        Safe_Type_Inheritance(i);
}

void Safe::Insight(IR* t){
    Safe s;
    s.Context += ", " + t->PreFix + " " + t->ID;
    s.Input = t->Childs;
    s.Types = Types;
    s.Avoid_Duplication = Avoid_Duplication;
    s.Factory();
    Append(Output, s.Output);
}

void Safe::Safe_Cache_Usation(Token* t){
	//gather up same context using cache variables
	if (!t->is("cache"))
		return;
	int cache_usation = Cache_Usation[t->Context];
    
	if (cache_usation >= S->Get_Usable_Register_Amount(t->Size, Task_For_General_Purpose) / 2)
	{
		cout << "\nWarning: Cache usation at " << Context << ". Is dangeriusly high!" << endl;
        cout << "Solution: If this runnable/lib wont work try to fix this problem:" << endl;
        cout << "{" << endl;
        cout << "   Problem: Possible error caused by " << t->Name << " being cached object." << endl;
        cout << "   Fix: Try to get rid of 'cache' name inharitance at making " << t->Name << endl;
		cout << "}" << endl;
        return;
	}
	Cache_Usation.at(t->Context) += 1;
}

void Safe::Append(vector<IR*> &d, vector<IR*> s){
    for (IR* t: s)
        d.push_back(t);
}

void Safe::Get_Token_Info(Token* t, int layer){
    //get the syntax tabbing ready as a string
    string tab = "";
    for (int i = 0; i < layer; i++)
        tab += "    ";
    if (!t->Size > 0){
        cout << tab << t->Name << ": " << endl;
        return;
    }
    cout << tab << t->Name << " { " << endl;
    cout << tab << "   " << "Size is " << t->Size << endl;
    cout << tab << "   " << "Inheritted { " << endl;
        for (string s: t->Types)
            if (s == "type")
                continue;
            else
                Get_Token_Info(Find(s), layer + 2);
    cout << tab << "    }" << endl;
    cout << tab << "}" << endl;
    return;
}

void Safe::Safe_Type_Inheritance(Token* t){
    if (!t->is(_Inheritting_))
        return;
    if (!t->Size > 0)
        return;
    for (string s: Avoid_Duplication)
        if (s == t->Name)
            return;
    //Warning: You are using an inheritance type(s) 'cache, int' on symbol 'a' in ...
    cout << "Warning: You are using an inheritance type(s) '";
    for (string s: t->Types)
        cout << s + ", ";
    cout << "' on symbol '" << t->Name << "' in '" << Context << "' scope." << endl;
    cout << "Generating Symbol map..." << endl;
    Get_Token_Info(t, 0);
    Avoid_Duplication.push_back(t->Name);
    return;
}

Token* Safe::Find(string name){
    for (Token* t: Types)
        if (t->Name == name)
            return t;
    return nullptr;
}