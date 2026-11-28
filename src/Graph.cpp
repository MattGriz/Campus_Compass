#include "Graph.h"

void Graph::addEdge(int from, int to, int weight) {
    //create edge to add to list
    Edge edge;
    edge.from = from;
    edge.to = to;
    edge.weight = weight;
    adjList[from].push_back(edge);

    //create reverse edge to make the list unidrected
    Edge reverseEdge;
    reverseEdge.from = to;
    reverseEdge.to = from;
    reverseEdge.weight = weight;
    adjList[to].push_back(reverseEdge);
}

//void Graph::isConnected(bullshit) {}