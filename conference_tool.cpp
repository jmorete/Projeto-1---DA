#include <iostream>
#include "Graph.h"
#include "Data.h"
#include "parser.h"
#include "max_flow.h"
#include "build_graph.h"
#include "output.h"
#include "id.h"
#include "menu.h"

bool isBatchMode = false;

int main(int argc, char *argv[]){
    if (argc == 1){
        Menu menu;
        menu.run();
    }
    else if (argc == 4){
        isBatchMode = true;
        Data data;
        if (!parse(argv[2], data)){
            return 1;
        }
        Output out;
        Graph<int> *g = buildGraph(data);
        out.setMaxFlow(edmondsKarp(g, SOURCE_ID, SINK_ID));
        out.generateOutput(g,data);
        if (data.getGenerateAssignments()) {
            out.writeAToFile(argv[3]);
        }
        if (data.getRiskAnalysis() == 1) {
            std::vector<int> critical;
            int og_flow = out.getMaxFlow();

            for (Reviewer r : data.getReviewers()) {
                Data risk_data = data;
                risk_data.removeReviewer(r.id); // remove one reviewer at each iteration

                // get maxFlow of altered set of reviewers
                Graph<int> *risk_g = buildGraph(risk_data);
                int risk_flow = edmondsKarp(risk_g, SOURCE_ID, SINK_ID);
                delete risk_g;

                if (risk_flow < og_flow) {
                    critical.push_back(r.id);
                }
            }
            out.setCriticalReviewers(critical);
            out.setRiskAnalysisDone(true);
            out.writeRAToFile(argv[3]);
        }
        delete g;
    }
    else {
        std::cout << "Invalid number of arguments." << std::endl;
        return 1;
    }
    return 0;
}