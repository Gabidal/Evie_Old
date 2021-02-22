#ifndef _HTTPS_H_
#define _HTTPS_H_

#include <string>
#include <vector>
#include "Docker.h"


using namespace std;

struct MemoryStruct {
	char* memory;
	size_t size;
	MemoryStruct() {
		memory = (char*)malloc(1);
		size = 0;
	}
};

size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp);


namespace HTTPS {
	extern string File_Name;
	void HTTPS_Analyser(vector<string>& output);

}

namespace HTTP {

}

#endif