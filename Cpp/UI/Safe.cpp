#include "../../H/UI/Safe.h"
extern Selector* S;

void Safe::Factory(){
    for (IR* i: Input){
        for (Token* t: i->Parameters){
            Safe_Cache_Usation(t);
        }
        Insight(i);
    }
}

void Safe::Insight(IR* t){
    Safe s;
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
		cout << "Warning: Cache usation limit --> " << cache_usation << " has been reached on this register size --> " << t->Size << "." << endl;
		cout << "Warning: Dangerously high use of cache on variable --> " << t->Name << ". Inside of --> " << t->Context << endl;
		cout << "Error: Please make --> " << t->Name << " into not cache using object!" << endl;
		return;
	}
	Cache_Usation.at(t->Context) += 1;
}

void Safe::Append(vector<IR*> &d, vector<IR*> s){
    for (IR* t: s)
        d.push_back(t);
}