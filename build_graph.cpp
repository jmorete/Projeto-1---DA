#include "Graph.h"
#include "Data.h"
#include "build_graph.h"
#include "id.h"

Graph<int>* buildGraph(const Data &data) {

    auto *g = new Graph<int>();

    g->addVertex(SOURCE_ID);
    g->addVertex(SINK_ID);

    // add submission nodes
    for (Submission &s : data.getSubmissions()) {
        if (data.getGenerateAssignments() < 2 || s.secondaryTopic == -1) {
            g->addVertex(s.id | PRIMARY_TOPIC_MASK | SOURCE_CONNECTED_MASK);
            g->addEdge(SOURCE_ID, s.id | PRIMARY_TOPIC_MASK | SOURCE_CONNECTED_MASK, data.getMinReviewsPerSubmission());
        }
        else {
            g->addVertex(s.id | SOURCE_CONNECTED_MASK);
            g->addVertex(s.id | PRIMARY_TOPIC_MASK);
            g->addVertex(s.id | SECONDARY_TOPIC_MASK);
            g->addEdge(SOURCE_ID, s.id | SOURCE_CONNECTED_MASK, data.getMinReviewsPerSubmission());
            g->addEdge(s.id | SOURCE_CONNECTED_MASK, s.id | PRIMARY_TOPIC_MASK, data.getMinReviewsPerSubmission());
            g->addEdge(s.id | SOURCE_CONNECTED_MASK, s.id | SECONDARY_TOPIC_MASK, data.getMinReviewsPerSubmission());
        }
    }

    // add reviewer nodes
    for (Reviewer &r : data.getReviewers()) {
        if (data.getGenerateAssignments() != 3 || r.secondaryExpertise == -1) {
            g->addVertex(r.id | REVIEWER_MASK | PRIMARY_TOPIC_MASK);
            g->addEdge(r.id | REVIEWER_MASK | PRIMARY_TOPIC_MASK, SINK_ID, data.getMaxReviewsPerReviewer());
        }
        else {
            g->addVertex(r.id | REVIEWER_MASK);
            g->addVertex(r.id | REVIEWER_MASK | PRIMARY_TOPIC_MASK);
            g->addVertex(r.id | REVIEWER_MASK | SECONDARY_TOPIC_MASK);
            g->addEdge(r.id | REVIEWER_MASK, SINK_ID, data.getMaxReviewsPerReviewer());
            g->addEdge(r.id | REVIEWER_MASK | PRIMARY_TOPIC_MASK, r.id | REVIEWER_MASK, data.getMaxReviewsPerReviewer());
            g->addEdge(r.id | REVIEWER_MASK | SECONDARY_TOPIC_MASK, r.id | REVIEWER_MASK, data.getMaxReviewsPerReviewer());
        }
    }

    // no connection yet between submission and reviewer

    // add compatibility edges
    for (auto &s : data.getSubmissions()) {
        for (auto &r : data.getReviewers()) {

            if (s.primaryTopic == r.primaryExpertise) {
                g->addEdge(
                    s.id | PRIMARY_TOPIC_MASK | SOURCE_CONNECTED_MASK,
                    r.id | REVIEWER_MASK | PRIMARY_TOPIC_MASK,
                    1
                );
            }
            if (data.getGenerateAssignments() > 1){
                if (s.secondaryTopic == r.primaryExpertise) {
                    g->addEdge(
                        s.id | SECONDARY_TOPIC_MASK,
                        r.id | REVIEWER_MASK | PRIMARY_TOPIC_MASK,
                        1
                    );
                }
                if (data.getGenerateAssignments() == 3) {
                    if (s.primaryTopic == r.secondaryExpertise) {
                        g->addEdge(
                            s.id | PRIMARY_TOPIC_MASK,
                            r.id | REVIEWER_MASK | SECONDARY_TOPIC_MASK,
                            1
                        );
                    }
                    if (s.secondaryTopic == r.secondaryExpertise) {
                        g->addEdge(
                            s.id | SECONDARY_TOPIC_MASK,
                            r.id | REVIEWER_MASK | SECONDARY_TOPIC_MASK,
                            1
                        );
                    }
                }
            }
        }
    }

    return g;
}