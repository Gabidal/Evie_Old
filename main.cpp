#include <iostream>
#include <fstream>
#include <string>
#include "Lexer.h"
using namespace std;

int main()
{
    string input = readFile("test.g");
    string output;
    initializeKeyWords();
    lexer(input, output);
    writeFile("test.asm", output);

    return 0;
}
