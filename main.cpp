#include <iostream>
#include <fstream>
#include <string>
#include "Lexer.h"
using namespace std;

int main()
{
    string input = readFile("banana.g");
    string output;
    initializeKeyWords();
    lexer(input, output);
    writeFile("banana.asm", output);

    return 0;
}