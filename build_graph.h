#ifndef BUILD_GRAPH_H
#define BUILD_GRAPH_H

#include "Graph.h"
#include "Data.h"

/**
 * @brief Builds the flow network graph used for the assignment problem.
 *
 * This function constructs a directed graph representing the assignment of
 * reviewers to submissions as a maximum flow problem.
 *
 * The graph structure is:
 *   SOURCE → submissions → reviewers → SINK
 *
 * Complexity: O(V + E), where V is the number of vertices and E is the number of edges
 * @param data The input data containing submissions, reviewers, and constraints.
 * @return Pointer to the constructed graph.
 *
 * @note The caller is responsible for deleting the returned graph.
 */
Graph<int>* buildGraph(const Data &data);

#endif