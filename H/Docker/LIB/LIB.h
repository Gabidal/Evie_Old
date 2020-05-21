#ifndef _LIB_H_
#define _LIB_H_
#include <stdexcept>

#include <vector>
#include <string>
#include <iostream>

using ObjectFile = std::vector<uint8_t>;

namespace LIB {
    std::vector<ObjectFile> ExtractAllObjectFiles(uint8_t* buffer, uint64_t length);

    std::vector<ObjectFile> ExtractAllObjectFiles(std::vector<uint8_t> buffer);
}

#endif