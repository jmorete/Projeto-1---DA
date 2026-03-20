#include "Graph.h"
#include "Data.h"

Graph<int>* build_Graph(const Data &data) {

    auto *g = new Graph<int>();

    const int SOURCE = -1000;
    const int SINK   = -2000;

    g->addVertex(SOURCE);
    g->addVertex(SINK);

    // add submission nodes
    for (Submission &s : data.getSubmissions()) {
        g->addVertex(s.id);
        g->addEdge(SOURCE, s.id, data.getMinReviewersPerSubmission());
    }

    // add reviewer nodes
    for (Reviewer &r : data.getReviewers()) {
        g->addVertex(r.id + 100000); // to avoid ID collision

        g->addEdge(r.id + 100000, SINK,
            data.getMaxReviewersPerReviewer());
    }

    // no connection yet between submission and reviewer

    // add compatibility edges
    for (auto &s : data.getSubmissions()) {
        for (auto &r : data.getReviewers()) {

            if (s.primaryTopic == r.primaryExpertise) {
                g->addEdge(
                    s.id,
                    r.id + 100000,
                    1
                );
            }
        }
    }

    return g;
}