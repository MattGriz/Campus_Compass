#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// The edge values that go in the list
struct Edge {
    int from = 0;
    int to = 0;
    int weight = 0;
    bool isOpen = true;
};

class Graph {
    private:
        unordered_map<int, vector<Edge>> adjList;

    public:
        Graph () {}
        void buildGraph(const string& edgesFile);
};