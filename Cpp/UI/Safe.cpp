#include "../../H/UI/Safe.h"
extern Selector* S;

void Safe::Factory(){
    for (IR* i: Input){
        for (Token* t: i->Parameters){
            Safe_Cache_Usation(t);
            Safe_Loyal_Usation(t);
            Safe_Type_Inheritance(t);
            Safe_Array_Usage(t);
        }
        Insight(i);
    }
    //for (Token* i: Types)
    //    Safe_Type_Inheritance(i);
}

void Safe::Insight(IR* t){
    Safe s = *this;
    s.Context += ", " + t->PreFix + " " + t->ID;
    s.Input = t->Childs;
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
        for (string s: Avoid_Duplication_On_Cache_Usation)
            if (s == t->Name)
                return;
		cout << "\nWarning: Use of cache at " << Context << ". Is dangeriusly high!" << endl;
        cout << "Solution: If this runnable/lib wont work try to fix this problem:" << endl;
        cout << "{" << endl;
        cout << "   Problem: Possible error caused by " << t->Name << " being cached object." << endl;
        cout << "   Fix: Try to get rid of 'cache' name inharitance at making " << t->Name << endl;
		cout << "}" << endl;
        Avoid_Duplication_On_Cache_Usation.push_back(t->Name);
        return;
	}
	Cache_Usation.at(t->Context) += 1;
}

void Safe::Append(vector<IR*> &d, vector<IR*> s){
    for (IR* t: s)
        d.push_back(t);
}

void Safe::Get_Token_Info(Token* t, string name, int layer){
    //get the syntax tabbing ready as a string
    string tab = "";
    for (int i = 0; i < layer; i++)
        tab += "    ";
    if (t == nullptr || !t->Size > 0){
        cout << tab << name << ": " << Get_Keyword_Info(name) << endl;
        return;
    }
    cout << tab << t->Name << " { " << endl;
    cout << tab << "    " << "Size is " << t->Size << endl;
    cout << tab << "    " << "State is " << t->State << endl;
    cout << tab << "    " << "Inheritting { " << endl;
        for (string s: t->Types)
            Get_Token_Info(Find(s), s, layer + 2);
    cout << tab << "    }" << endl;
    cout << tab << "}" << endl;
    return;
}

void Safe::Safe_Type_Inheritance(Token* t){
    if (!t->is(_Inheritting_))
        return;
    //if (!t->Size > 0)
    //    return;
    for (string s: Avoid_Duplication_On_Inheritance)
        if (s == t->Name)
            return;
    //Warning: You are using an inheritance type(s) 'cache, int' on symbol 'a' in ...
    cout << "Warning: You are using an inheritance type(s) '";
    for (string s: t->Types)
        cout << s + ", ";
    cout << "' on symbol '" << t->Name << "' in '" << Context << "' scope." << endl;
    cout << "Generating Symbol map..." << endl;
    Get_Token_Info(t, t->Name, 0);
    Avoid_Duplication_On_Inheritance.push_back(t->Name);
    return;
}

Token* Safe::Find(string name){
    for (Token* t: Types)
        if (t->Name == name)
            return t;
    return nullptr;
}

void Safe::Safe_Loyal_Usation(Token* t){
    if (!t->is("loyal"))
        return;
    for (string s: Avoid_Duplication_On_Loyal_Usation)
        if (s == t->Name)
            return;
    cout << "Warning: Possible stack-overflow at '" << Context << "'" << endl;
    cout << "Problem: The use of 'loyal' keyword when defining '" << t->Name << "'" << endl;
    cout << "Solution: " << endl;
    cout << "{" << endl;
    cout << "   " << "Try to get rid of 'loyal' keyword when defining " << t->Name << endl;
    cout << "}" << endl;
    Avoid_Duplication_On_Loyal_Usation.push_back(t->Name);
    return;
}

string Safe::Get_Keyword_Info(string s){
    if (s == "func")
        return "Generic f(x).";
    if (s == "type")
        return "Base definition.";
    if (s == "if")
        return "Compares data.";
    if (s == "loyal")
        return "No parameter cleaning.";
    if (s == "export")
        return "Globalize to other platforms.";
    if (s == "import")
        return "Import from outside world.";
    if (s == "hidden")
        return "Dont print inheritted info into output.";
    if (s == "cache")
        return "No Saving into memory.";
    return "No info.";   
}

void Safe::Safe_Array_Usage(Token* t){
    if (t->is("cache") && t->is(_Array_))
    {
        cout << "Error: Illegal use of 'cache' at '" << Context << "'!" << endl;
        cout << "Problem: Use of 'array' with 'cache'." << endl;
        cout << "Solution: " << endl;
        cout << "{" << endl;
        cout << "    If you want to get the address of '" << t->Name << "' offsetted by '" << t->Offsetter->Name << "'," << endl;
        cout << "    Try changing the '" << t->Name << ":" << t->Offsetter->Name << "' into: " << endl;
        cout << "    '" << t->Name << "::" << t->Offsetter->Name << "'" << endl;
        cout << "}" << endl;
    }
}