#include <iostream>
#include "Graph.h"
#include "Data.h"
#include "parser.h"
#include "max_flow.h"
#include "build_graph.h"
#include "output.h"
#include "id.h"


int main(int argc, char *argv[]){
    if (argc == 1){
        //createMenu();
    }
    if (argc == 4){
        Data data;
        if (!parse(argv[2], data)){
            return -1;
        }
        Graph<int> *g = buildGraph(data);
        edmondsKarp(g, SOURCE_ID, SINK_ID);
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