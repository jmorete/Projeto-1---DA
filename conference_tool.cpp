#include <iostream>
#include "Graph.h"
#include "Data.h"
#include "parser.h"
#include "max_flow.h"
#include "build_graph.h"
#include "output.h"


int main(int argc, char *argv[]){
    if (argc == 1){
        //createMenu();
    }
    if (argc == 4){
        Data data = parse(argv[2]);
        Graph<int> *g = buildGraph(data);
        edmondsKarp(g, -1000, -2000);
        if (data.getGenerateAssignments()) {
            writeOutput(argv[3], g, data);
        }
    }
    else {
        std::cout << "Invalid number of arguments." << std::endl;
        return 1;
    }
    return 0;
}