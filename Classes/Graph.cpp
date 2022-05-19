#include "Graph.h"
#include <queue>
#include <algorithm>
#include <climits>
#include "maxHeap.h"
#include <stack>

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
    //cout << v << " "; // show node order
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
        //cout << u << " "; // show node order
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

int Graph::distance(int a, int b) {
    bfs(a);
    if(nodes[b].visited)
        return nodes[b].distance;
    return -1;
}

void Graph::setMaxCapacity(int s) {
    MaxHeap<int, int> maxHeap = MaxHeap<int, int>(graphSize,-1);
    for (int v = 1; v <= graphSize; v++) {
        if(v == s) {
            continue;
        }
        nodes[v].maxCapacity = 0;
        nodes[v].pred = 0;
        maxHeap.insert(v,0);
    }
    nodes[s].maxCapacity = INT_MAX;
    maxHeap.insert(s,-nodes[s].maxCapacity);
    int v;
    while(maxHeap.getSize()) {
        v = maxHeap.removeMax();
        for(auto e : nodes[v].adjEdges) {
            int w = e.dest;

            if(min(nodes[v].maxCapacity,e.capacity) > nodes[w].maxCapacity) {
                nodes[w].maxCapacity = min(nodes[v].maxCapacity,e.capacity);
                nodes[w].pred = v;
                maxHeap.increaseKey(w,-nodes[w].maxCapacity);
            }
        }
    }
}

void Graph::maxCapacityPath(int a, int b) {
    if(!existPath(a,b))
    {
        cerr << "Doesn't exist a path from " << a << " to " << b << endl;
        return;
    }

    setMaxCapacity(a);
    cout << "The max dimension of a group is: " << nodes[b].maxCapacity << endl << endl;
    cout << "Alternative way: ";

    stack<int> path;
    path.push(b);
    while(b != a) {
        path.push(nodes[b].pred);
        b = nodes[b].pred;
    }

    while(!path.empty())
    {
        cout << " -> " << path.top();
        path.pop();
    }
}

bool Graph::existPath(int a, int b) {
    bfs(a);
    return nodes[b].visited;
}
