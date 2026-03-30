#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <iostream>

/**
 * @brief Indicates whether the program is running in batch mode.
 */
extern bool isBatchMode;

/**
 * @brief Prints an error message to the appropriate output stream.
 *
 * In batch mode, the message is printed directly to the standard error stream.
 * Otherwise, it is printed to the standard output stream with an "[ERROR]" prefix.
 *
 * @param message Error message to display
 */
inline void printError(const std::string& message) {
    if (isBatchMode) std::cerr << message << std::endl;
    else std::cout << "[ERROR] " << message << '\n';
}

#endif //ERROR_H
