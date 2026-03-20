#include <fstream>
#include <sstream>
#include <iostream>
#include "Data.h"

Data parse(const std::string &filename) {
    Data data;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
    std::string line, section;
    while (std::getline(file, line)) {
        if (line[0] == '#'){
            if (line == "#Reviewers") {
                section = "reviewers";
            } 
            else if (line == "#Submissions") {
                section = "submissions";
            } 
            else if (line == "#Control") {
                section = "constraints";
            } 
            else if (line == "#Output") {
                section = "output";
            }
            else {
                continue;
            }
        }
    }

    return data;
}