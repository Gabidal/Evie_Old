#include <iostream>
#include <fstream>
#include <string>
#include "Lexer.h"
#include "io.h"
using namespace std;

int main()
{
    getOptions();
    cout << "\n  G::Reading input file...\n";
    string input = readFile(inFile);
    string output;
    cout << "  G::Lexer analysing...\n";
    initializeKeyWords();
    clock_t lexerTimerS = clock();
    lexer(input, output);
    clock_t lexerTimerE = clock();
    cout << "  G::Parsing...\n  G::Writing the output...\n";
    writeFile(outFile, output);
    double sum = 0;
    double parsedSize = parsed.size();
    for (int i = 0; i < parsed.size(); i++)
    {
        sum += parsed.back();
        parsed.pop_back();
    }
    cout << "  G::Done!\n\n";

    cout << "-_-_-_-_-_-_-_-_-_-" << endl;
    cout << "Lexered  == " + to_string((lexerTimerE - lexerTimerS)/ float(CLOCKS_PER_SEC)) + "  second's" << endl;
    cout << "Parsered == " + to_string(sum / float(CLOCKS_PER_SEC)) + "  second's" << endl;
    cout << "-_-_-_-_-_-_-_-_-_-" << endl;

    return 0;
}
