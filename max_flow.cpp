#include "max_flow.h"

// Function to test the given vertex 'w' and visit it if conditions are met
template <class T>
void testAndVisit(std::queue< Vertex<T>*> &q, Edge<T> *e, Vertex<T> *w, double residual) {
    // Check if the vertex 'w' is not visited and there is residual capacity
    if (! w->isVisited() && residual > 0) {
        // Mark 'w' as visited, set the path through which it was reached, and enqueue it
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

// Function to find an augmenting path using Breadth-First Search
template <class T>
bool findAugmentingPath(Graph<T> *g, Vertex<T> *s, Vertex<T> *t) {
    // Mark all vertices as not visited
    for(auto v : g->getVertexSet()) {
        v->setVisited(false);
    }
    std::queue<Vertex<T>*> q;
    s->setVisited(true);
    q.push(s);
    while(!q.empty()) {
        Vertex<T>* v = q.front();
        q.pop();
        for (auto e : v->getAdj()) {
            double residual = e->getWeight() - e->getFlow();
            auto d = e->getDest();
            testAndVisit(q, e, d, residual);
        }
    }


    // Return true if a path to the target is found, false otherwise
    return t->isVisited();
}

// Function to find the minimum residual capacity along the augmenting path
template <class T>
double findMinResidualAlongPath(Vertex<T> *s, Vertex<T> *t) {
    double f = INF;

    Vertex<T>* v = t;
    while (v != s) {
        auto e = v->getPath();
        double residual = e->getWeight() - e->getFlow();
        f = std::min(f, residual);
        v = e->getOrig();
    }

    // Return the minimum residual capacity
    return f;
}

// Function to augment flow along the augmenting path with the given flow value
template <class T>
void augmentFlowAlongPath(Vertex<T> *s, Vertex<T> *t, double f) {
    // Traverse the augmenting path and update the flow values accordingly

   Vertex<T>* v = t;
    while (v != s) {
        auto e = v->getPath();
        e->setFlow(e->getFlow() + f);
        auto r = e->getReverse();
        r->setFlow(r->getFlow() - f);
        v = e->getOrig();
    }

}

// Main function implementing the Edmonds-Karp algorithm
template <class T>
void edmondsKarp(Graph<T> *g, int source, int target) {
    // Find source and target vertices in the graph
    Vertex<T>* s = g->findVertex(source);
    Vertex<T>* t = g->findVertex(target);

    for (auto v : g->getVertexSet()) {
        for (auto e : v->getAdj()) {
            if (e->getReverse() == nullptr) {
                auto revEdge = e->getDest()->addEdge(v, 0);
                e->setReverse(revEdge);
                revEdge->setReverse(e);
            }
            e->setFlow(0);
        }
    }

    int maxFlow = 0;
    while (findAugmentingPath(g, s, t)) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
        maxFlow += f;
    }
    g->setMaxFlow(maxFlow);

    for (auto v : g->getVertexSet()) {
        auto adj = v->getAdj();
        for (auto e : adj) {
            if (e->getWeight() == 0) {
                v->removeEdge(e->getDest()->getInfo());
            }
        }
    }

    
}

template void edmondsKarp<int>(Graph<int> *g, int s, int t);


