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
    /**
     * Struct that represents graph's edges which contains the destiny
     * of edge, the capacity and the duration.
     */
    struct Edge {
        int dest;
        int capacity;
        int duration;
    };

    /**
     * Struct that represents the graph's nodes which contains
     * the list of edges that come out of a node.
     */
    struct Node {
        /**
         * Adjacent edges.
         */
        list<Edge> adjEdges;
        /**
         * If node was visited or not in an algorithm implemented
         */
        bool visited;
        /**
         * Distance from source node
         */
        int distance;
        /**
         * Parent of a node
         */
        int pred;
        /**
         * Maximum capacity of a node after applying setMaxCapacity algorithm
         */
        int maxCapacity;
        /**
         * Nodes degrees
         */
        int sDegree, eDegree;
        /**
         * LF - latest finish
         * ES - earliest start
         */
        int LF, ES;
    };

    /**
     * Graph size (vertices are numbered from 1 to n)
     */
    int graphSize;
public:
    int getGraphSize() const;

private:
    /**
     * false: undirected; true: directed
     */
    bool hasDir;
    /**
     * The list of nodes being represented
     */
    vector<Node> nodes;

public:

    Graph() = default;

    /**
     * Creates a graph with 'numNodes' nodes that can be directed (dir = true)
     * or undirected (dir = false)
     * @param numNodes - number of graph's nodes
     * @param dir - graph directed or not
     */
    Graph(int numNodes, bool dir = false);

    /**
     * Used for creating the edges of a graph
     * @param src - edge source
     * @param dest - edge destiny
     * @param capacity - edge capacity
     * @param duration - edge duration
     */
    void addEdge(int src, int dest, int capacity, int duration);

    /**
     * Depth first search algorithm from node v
     * @param v
     * @return
     */
    void dfs(int v);

    /**
     * Breadth first search from node v
     * @param v
     */
    void bfs(int v);

    /**
     * Verify if exists path from node a to node b
     * @param a - source node
     * @param b - sink node
     * @return true if exists a path or false otherwise.
     */
    bool existPath(int a, int b);

    /**
     * Set maximum capacity for each node.
     * @param s
     */
    void setMaxCapacity(int s);

    /**
     * Prints the maximum capacity path from a to b
     * @param a - source node
     * @param b - sink node
     */
    void maxCapacityPath(int a, int b);

    /**
     * Sets the distance of all nodes from node s.
     * @param s
     */
    void setDistance(int s);

    /**
     * Ford Fulkerson algorithm.
     * @param source
     * @param sink
     * @param dimension - dimension passed as an input
     * @return returns a map that contains the paths and the capacity used.
     */
    pair<map<list<int>, int>, int> FordFulkerson(int source, int sink, int dimension);

    /**
     *
     * @return Transposed graph of the graph that call this function.
     */
    Graph createTransposed();

    /**
     * Critical path method with earliest start
     * @return Minimum duration
     */
    int minDuration();

    /**
     * Critical path method with latest finish
     * @param sink
     */
    void latestFinish(int sink);

    /**
     * Creates a graph that only has the edges of the specified path
     * @param paths map<list<int>, int> - paths that are going to used to create the graph
     * @return Graph with only the edges of the specified path
     */
    Graph createGraphByPath(const map<list<int>, int>& paths);

    /**
     * Finds the Total Slack of each node
     * @return map - nodes with their respective total Slack
     */
    map<int, int> totalSpare();


    /**
     * Calculates the pareto-optimal solutions for the paths between two nodes
     * @param a int - source path
     * @param b int - sink path
     * @return list<list<int>> - pareto-optimal paths
     */
    list<list<int>> optimalSolutions(int a, int b);


    /**
     * Calls the Max Distance Algorithm and outputs the path to a certain node
     * @param a int - source node
     * @param b int - sink node
     * @return list<int> - path with the maximum capacity to a certain node
     */
    list<int> MaxCapacityList(int a, int b);
    /**
     * Calls the Set Distance Algorithm and outputs the path to a certain node
     * @param a int - source node
     * @param b int - sink node
     * @return list<int> - path with the least amount of transbords to a certain node
     */
    list<int> MinDistanceList(int a, int b);

    void printAllPaths(int s, int d);

    void printAllPathsUtil(int u, int d, bool *visited, int *path, int &path_index,int maxDistance, int minCapacity);

    void checkPath(int u,int d, int minCapacity, int maxDistance, bool visited[],
                   int path[], int& path_index);
};

#endif
