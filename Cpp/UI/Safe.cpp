#include "../../H/UI/Safe.h"
#include <sstream>
extern Selector* S;

void Safe::Factory(){
    for (IR* i: Input){
        for (Token* t: i->Parameters){
            Safe_Cache_Usation(t);
            Safe_Loyal_Usation(t);
            Safe_Type_Inheritance(t);
            Safe_Array_Usage(t);
            Safe_Calling(t);
            Safe_Hidden_Usage(t);
        }
        if (ERROR)
        {
            stringstream error;
            error << "Cant continue, please fix the error's first!" << endl;;
            throw runtime_error(error.str().c_str());
        }
        Insight(i);
    }
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
	if (cache_usation >= S->Get_Right_Size_List(t->Size).size() / 2)
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
        tab += "  ";
    if (t == nullptr || t->Size == 0){
        cout << tab << name << ": " << Get_Keyword_Info(name) << endl;
        return;
    }
    cout << tab << t->Name << " { " << endl;
    cout << tab << "  " << "In '" << Context << "' at line " << t->Line_Number << endl;
    cout << tab << "  " << "Size is " << (float)t->Size * 8 << " bits" << endl;
    cout << tab << "  " << "State is " << Get_State_Info(t) << "." << endl;
    cout << tab << "  " << "Inheritting { " << endl;
        for (string s: t->Types)
            Get_Token_Info(Find(s), s, layer + 2);
    cout << tab << "  }" << endl;
    cout << tab << "}" << endl;
    return;
}

void Safe::Safe_Type_Inheritance(Token* t){
    if (t->Types.size() < 2)
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
    cout << "' on symbol '" << t->Name << "' in '" << Context << "' scope at line " << t->Line_Number << "." << endl;
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
    if (s == "number")
        return "Ordinary number.";
    if (s == "ptr")
        return "Uses the generic pointter scaling.";
    if (s == "string")
        return "Is a list of characters.";
    if (s == "static")
        return "Represents a shared object.";
    if (s == "virtual")
        return "Represents a changable func.";
    if (s == "virtual")
        return "Represents a changable func.";
    return "No info.";   
}

void Safe::Safe_Array_Usage(Token* t){
    if (t->is("cache") && t->is(_Array_))
    {
        cout << "Error: Illegal use of 'cache' at '" << Context << "'!" << endl;
        cout << "Problem: 'cache' variables dont have emory address for array offsetting." << endl;
        cout << "Solution: {" << endl;
        cout << "    If you want to get the address of '" << t->Name << "' offsetted by '" << t->Offsetter->Name << "'," << endl;
        cout << "    Try changing the '" << t->Name << ":" << t->Offsetter->Name << "' into: " << endl;
        cout << "    '" << t->Name << "::" << t->Offsetter->Name << "'" << endl;
        cout << "}" << endl;
        ERROR = true;
        return;
    }
    //if a objects size is bigger than 12bits then we need to
    //point into the original address and then array offset by the new pointter.
    //error way
    //banana x;
    //x:0 = 123;
    //right way
    //int y = @x;
    //y::0 = 123;
    if (t->is(_Array_) && t->Size > 12 && (!t->_Has_Member_)) {
        //this is the wrong way
        cout << "Error: Illegal use of array operator at '" << Context << "'!" << endl;
        cout << "Problem: Use of 128bit or bigger object as a raw array address is too big!" << endl;
        cout << "Solution: {" << endl;
        cout << "    If you want to get hands on " << t->Name << ":" << t->Offsetter->Name << " that badly then use this." << endl;
        cout << "    First make a 32bit variable that can work as a pointter. 'int a = @" << t->Name << "'" << endl;
        cout << "    Then use the newly created pointter like this: 'a::" << t->Offsetter->Name << " = VALUE'" << endl;
        cout << "}" << endl;
        ERROR = true;
        return;
    }
}

void Safe::Safe_Calling(Token* t)
{
    //type int a;
    //a()   #cant exist simply becayse it has a raw template inheritted (TYPE).
    //int a;
    //a()   #will be called but! it will call the value as a address not calling into the variable's a's location!
    //func a;
    //a()   #will call as a normal generic function into a's location.
    if (!t->is(_Call_))
        return;
    if (t->is("type") && (!t->is("func") && t->State != "func")) {
        Inform_Location_Of(t);
        cout << "Error: Cannot call template " << t->Name << endl;
        cout << "Solution: {" << endl;
        cout << "Try to make a object that inherits " << t->Name << " and call that if must." << endl;
        cout << "}" << endl;
        ERROR = true;
        return;
    }
    else if (!t->is("func") && t->State != "func") {
        cout << "Warning: You are trying to call object " << t->Name << " value as an address." << endl;
    }
    Token* Function = Find(t->Name);
    vector<Token*> Callation_Parameters = t->Left_Side_Token->Childs;
    reverse(Callation_Parameters.begin(), Callation_Parameters.end());
    int j = 0;
    for (Token*i : Function->Left_Side_Token->Childs) {
        if (j >= Callation_Parameters.size()) {
            cout << "Warning: The original function has different amount of parameters!" << endl;
            break;
        }
        if (i->Size != Callation_Parameters.at(j)->Size) {
            cout << "Warning: " + Function->Name + " doesnt take size " + to_string(Callation_Parameters.at(j)->Size) + " parameter at " + to_string(j) + "." << endl;
            cout << "Solution: {" << endl;
            cout << "    Try to give size " + to_string(i->Size) + " parameter at " + to_string(j) << endl;
            cout << "}" << endl;
        }
         j++;
    }
    return;
}

void Safe::Safe_Hidden_Usage(Token* t)
{
    //document about the hidden keyword
    //              v-hidden 
    //export hidden int banana()()
    //^-written into asm
    //hidden gives user the power to accept/decline what is written as prefix into asm file
    if (t->is("hidden") || t->State == "hidden") {
        int Current_Type = 0;
        string Not_Hidden = "'";
        for (; Current_Type < t->Types.size(); Current_Type++) {
            if (t->Types.at(Current_Type) == "hidden")
                //we have the start point of the hiddens
                break;
            Not_Hidden += t->Types.at(Current_Type) + ", ";
        }
        cout << "Warning: Active type(s) of '" << t->Name << "' are " << Not_Hidden << "'." << endl;
        cout << "Rest of the type(s) will be dismiss!" << endl;
    }
}

string Safe::Get_State_Info(Token* t){
    if (t->State != "")
        return t->State;
    else if (t->is(_Register_))
        return "register";
    else
        return "normal";
}

void Safe::Inform_Location_Of(Token* t)
{
    cout << t->Name << " caused some issues in " << Context << " line " << t->Line_Number << endl;
}
