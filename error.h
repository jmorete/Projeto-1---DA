#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <iostream>

extern bool isBatchMode;

inline void printError(const std::string& message) {
    if (isBatchMode) std::cerr << message << std::endl;
    else std::cout << "[ERROR] " << message << '\n';
}

#endif //ERROR_H
