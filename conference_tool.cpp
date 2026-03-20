#include <iostream>
#include "Graph.h"
#include "Data.h"
#include "parser.h"
#include "max_flow.h"


int main(int argc, char *argv[]){
    if (argc == 1){
        //createMenu();
    }
    if (argc == 4){
        Data data = parse(argv[2]);
        for (auto &s : data.getSubmissions()) {
            std::cout << "Submission " << s.id << ": " << s.title << std::endl;
        }
        //Graph* g = buildGraph(data);
        //edmondsKarp(g);
        //writeOutput(argv[3]);
    }
    else {
        std::cout << "Invalid number of arguments." << std::endl;
        return 1;
    }
    return 0;
}