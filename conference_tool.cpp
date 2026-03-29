#include <iostream>
#include "Graph.h"
#include "Data.h"
#include "parser.h"
#include "max_flow.h"
#include "build_graph.h"
#include "output.h"
#include "id.h"
#include "menu.h"


int main(int argc, char *argv[]){
    if (argc == 1){
        Menu menu;
        menu.run();
    }
    else if (argc == 4){
        Data data;
        if (!parse(argv[2], data)){
            return -1;
        }
        Graph<int> *g = buildGraph(data);
        edmondsKarp(g, SOURCE_ID, SINK_ID);
        if (data.getGenerateAssignments()) {
            Output out;
            out.generateOutput(g,data);
            out.writeToFile(argv[3]);
        }
    }
    else {
        std::cout << "Invalid number of arguments." << std::endl;
        return 1;
    }
    return 0;
}