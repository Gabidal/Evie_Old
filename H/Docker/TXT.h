#ifndef _TXT_H_
#define _TXT_H_
#include <string>
#include <vector>
#include "../Lexer/Lexer.h"
#include "Docker.h"
#include "../Lexer/Component.h"

using namespace std;

namespace TXT {
	void TXT_Analyzer(vector<string>& Output);
	vector<string> Unwrap(string raw);
}

#endif