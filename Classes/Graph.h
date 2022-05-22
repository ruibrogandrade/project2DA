#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include "minHeap.h"

using namespace std;

class Graph {
    struct Edge {
        int dest;
        //double weight;
        int capacity;
        int duration;
        int fluxo;
        bool removed = false;
    };

    struct Node {

        list<Edge> adjEdges;
        bool visited;
        int distance; //distance from source node
        int pred; // previous node
        bool removed = false;
        int maxCapacity;
    };

    int graphSize;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirected; true: directed
    vector<Node> nodes; // The list of nodes being represented
    //int dest, src;

public:

    Graph() = default;

    Graph(int numNodes, bool dir = false);

    void addEdge(int src, int dest, int capacity, int duration);

    int distance(int a, int b);

    int dfs(int v);

    void bfs(int v);

    bool existPath(int a, int b);

    void setMaxCapacity(int s);

    void maxCapacityPath(int a, int b);

    void setDistance(int s);

    void minDistancePath(int a, int b);

    int FordFulkersen(int source, int sink);
};

#endif
