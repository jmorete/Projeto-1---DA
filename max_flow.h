#include "Graph.h"

#ifndef MAX_FLOW_H
#define MAX_FLOW_H

/**
 * @brief Tests whether a vertex can be visited through a residual edge and enqueues it if valid.
 *
 * Used as part of the BFS in the Edmonds-Karp algorithm to explore the residual network.
 * If the edge has positive residual capacity and the destination vertex has not been visited,
 * it is marked and added to the queue for further exploration.
 *
 * @tparam T Type stored in the graph vertices
 * @param q Queue used for BFS traversal
 * @param e Edge being examined
 * @param w Destination vertex of the edge
 * @param residual Residual capacity of the edge
 */
template <class T>
void testAndVisit(std::queue< Vertex<T>*> &q, Edge<T> *e, Vertex<T> *w, double residual);
/**
 * @brief Finds an augmenting path in the residual graph using BFS.
 *
 * Searches for a path from source vertex s to sink vertex t where all edges
 * have positive residual capacity.
 *
 * @tparam T Vertex data type
 * @param g Input flow network
 * @param s Source vertex
 * @param t Sink vertex
 * @return True if an augmenting path exists, false otherwise
 */
template <class T>
bool findAugmentingPath(Graph<T> *g, Vertex<T> *s, Vertex<T> *t);
/**
 * @brief Computes the minimum residual capacity along the augmenting path.
 *
 * Traverses the parent pointers from sink back to source and determines the
 * bottleneck (minimum residual capacity) of the path.
 *
 * @tparam T Vertex data type
 * @param s Source vertex
 * @param t Sink vertex
 * @return Minimum residual capacity along the path
 */
template <class T>
double findMinResidualAlongPath(Vertex<T> *s, Vertex<T> *t);
/**
 * @brief Augments flow along the selected path by a given flow value.
 *
 * Updates the residual capacities of edges along the path from source to sink,
 * increasing forward flow and decreasing backward flow accordingly.
 *
 * @tparam T Vertex data type
 * @param s Source vertex
 * @param t Sink vertex
 * @param f Flow value to push through the path
 */
template <class T>
void augmentFlowAlongPath(Vertex<T> *s, Vertex<T> *t, double f);

/**
 * @brief Computes the maximum flow in a flow network using the Edmonds-Karp algorithm.
 *
 * Implements the Edmonds-Karp algorithm, which repeatedly
 * finds shortest augmenting paths (in terms of number of edges) using BFS and augments
 * flow until no more augmenting paths exist.
 *
 * @tparam T Vertex data type
 * @param g Flow network graph
 * @param source Source vertex ID
 * @param sink Sink vertex ID
 * @return Value of the maximum flow from source to sink
 *
 * Complexity: O(V * E^2), where V is the number of vertices and E is the number of edges
 */
template <class T>
int edmondsKarp(Graph<T> *g, int source, int sink);

#endif 

