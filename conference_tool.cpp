#include <iostream>
#include "Graph.h"

int main(int argc, char *argv[]){
    if (argc == 1){
        createMenu();
    }
    if (argc == 4){
        parse(argv[2]);
        Graph* g = buildGraph();
        edmondsKarp(g);
        writeOutput(argv[3]);
    }
    else {
        std::cout << "Invalid number of arguments." << std::endl;
        return 1;
    }
    return 0;
}