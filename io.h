#include <string>
#include <iostream>
using namespace std;

string inFile;
string outFile;

void getOptions()
{
    cout << "\n  G::You have chosen GAS...\n  G::Loading...\n  G::Give the name of the file you want to compile here: ";
    cin >> inFile;
    cout << "\n  G::Give the name of the output file here: ";
    cin >> outFile;
}