#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sys/mman.h>
#include "Lexer.h"
#include "io.h"
using namespace std;

int main()
{
    getOptions();
    cout << "  G::Do you want to assembly the output to a binary?\n(y = yeas / n = no)\n: ";
    string YN;
    cin >> YN;
    if (YN.size() > 0 && YN.at(0) == 'n')
    {
        return 0;
    }
    cout << "  G::Linux or Windows?\n(l == linux / w == windows)\n: ";
    string option;
    cin >> option;
    string newOut;
    int offset = getWord('.', newOut, outFile, 0);
    if (option.size() > 0 && option.at(0) == 'l')
    {
        codbuffer1 = "global _start\n_start:\ncall function_main\nmov eax, 1\nmov ebx, 0\nint 80h\n\nGASCode:\n\n";
    }
    else if (option.size() > 0 && option.at(0) == 'w')
    {
        codbuffer1 = "global _main\n_main:\ncall function_main\nmov eax, 1\nmov ebx, 0\nint 80h\n\nGASCode:\n\n";
    }

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
    cout << "Lexered  in " + to_string((lexerTimerE - lexerTimerS)/ float(CLOCKS_PER_SEC)) + "  second's" << endl;
    cout << "Parsered in " + to_string(sum / float(CLOCKS_PER_SEC)) + "  second's" << endl;
    cout << "-_-_-_-_-_-_-_-_-_-" << endl;


    if (option.size() > 0 && option.at(0) == 'l')
    {
        system(("yasm -g dwarf2 -f elf32 -o " + newOut + ".o " + outFile).c_str());
        system(("ld -m elf_i386 -o " + newOut + " " + newOut + ".o").c_str());
        system(("chmod +x " + newOut).c_str());
    }
    else if (option.size() > 0 && option.at(0) == 'w')
    {
        system(("yasm -f win32 -o " + newOut + ".obj " + outFile).c_str());
        system(("i686-w64-mingw32-g++ -m32 " + newOut + ".obj -o " + newOut + ".exe ").c_str());
    }
    cout << "  G::Done!\n";

    return 0;
}
