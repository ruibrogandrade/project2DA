#include "Graph.h"
#include <queue>
#include <algorithm>
#include <climits>
#include "maxHeap.h"

using namespace std;

Graph::Graph(int numNodes, bool dir) : graphSize(numNodes), hasDir(dir), nodes(numNodes + 1) {}

void Graph::addEdge(int src, int dest, int capacity, int duration) {
    if (src < 0 || src > graphSize || dest < 0 || dest > graphSize){
        cout << "Can't add edge. Invalid bound." << endl;
        return;
    }
    nodes[src].adjEdges.push_back({dest, capacity, duration});

    if (!hasDir)
        nodes[dest].adjEdges.push_back({src, capacity, duration});
}

int Graph::dfs(int v) {
    if (nodes[v].adjEdges.empty())
        return 1;
    cout << v << " "; // show node order
    nodes[v].visited = true;
    int result = 1;
    for (auto e : nodes[v].adjEdges) {
        int w = e.dest;
        if (!nodes[w].visited) {
            result += dfs(w);
        }
    }
    return result;
}

void Graph::bfs(int v) {
    for (int v = 1; v <= graphSize; v++) nodes[v].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v]. visited = true;
    nodes[v].distance = 0;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        cout << u << " "; // show node order
        int maxCapacity = nodes[u].adjEdges.front().capacity;
        Edge* edgePtr;
        for (auto e : nodes[u].adjEdges)
        {
            int w = e.dest;
            if(e.capacity > maxCapacity)
            {
                maxCapacity =  e.capacity;
                edgePtr = &e;
            }

            if (!nodes[w].visited)
            {
                nodes[w].visited = true;
            }
        }

        for(auto e : nodes[u].adjEdges)
        {
            if(e.capacity == maxCapacity)
                q.push(e.dest);
        }
    }
}

int Graph::distance(int a, int b) {
    bfs(a);
    if(nodes[b].visited)
        return nodes[b].distance;
    return -1;
}


void Graph::setMaxCapacity(Graph G, int s) {
    MaxHeap<int, int> maxHeap = MaxHeap<int, int>(graphSize,-1);
    for (int v = 1; v <= graphSize; v++) {
        if(v == s) {
            continue;
        }
        nodes[v].maxCapacity = 0;
        nodes[v].pred = NULL;
        maxHeap.insert(v,0);
    }
    nodes[s].maxCapacity = INT_MIN;
    maxHeap.insert(s,INT_MIN);
    int v;
    while(maxHeap.getSize()) {
        v = maxHeap.removeMax();
        for(auto e : nodes[v].adjEdges) {
            int w = e.dest;
            if(max(-nodes[v].maxCapacity,e.capacity) > -nodes[w].maxCapacity) {
                nodes[w].maxCapacity = -max(-nodes[v].maxCapacity,-e.capacity);
                nodes[w].pred = v;
                maxHeap.increaseKey(w,nodes[w].maxCapacity);
            }
        }
    }
}

void Graph::maxCapacityPath(Graph g,int a, int b) {
    setMaxCapacity(g,a);
    cout << "The Max Capacity Path is: " << nodes[b].maxCapacity << endl;
    cout << "And the Path Taken was:" << endl;
    cout << b << endl;
    b = nodes[b].pred;
    cout << b << endl;
    while(b != a) {
        cout << nodes[b].pred << endl;
        b = nodes[b].pred;
    }
}


/*
 void Graph::bfs(int v) {
    for (int v = 1; v <= graphSize; v++) nodes[v].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v]. visited = true;
    nodes[v].distance = 0;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        cout << u << " "; // show node order
        for (auto e : nodes[u].adjEdges)
        {
            int w = e.dest;

            if (!nodes[w].visited)
            {
                q.push(w);
                nodes[w].visited = true;
            }
        }
    }
}
*/