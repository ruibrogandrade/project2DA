#include "Graph.h"
#include <queue>
#include <algorithm>
#include <climits>
#include "maxHeap.h"
#include <stack>
#include "minHeap.h"
#include <map>
#include <utility>

using namespace std;

Graph::Graph(int numNodes, bool dir) : graphSize(numNodes), hasDir(dir), nodes(numNodes + 1) {}

void Graph::addEdge(int src, int dest, int capacity, int duration) {
    if (src < 0 || src > graphSize || dest < 0 || dest > graphSize){
        cout << "\nCan't add edge. Invalid bound.\n" << endl;
        return;
    }
    nodes[src].adjEdges.push_back({dest, capacity, duration});

    if (!hasDir)
        nodes[dest].adjEdges.push_back({src, capacity, duration});
}

void Graph::dfs(int v) {
    if (nodes[v].adjEdges.empty()){
        return;
    }
    nodes[v].visited = true;
    cout << "v" << endl;
    for (auto e : nodes[v].adjEdges) {
        int w = e.dest;
        if (!nodes[w].visited) {
            dfs(w);
        }
    }
}

void Graph::bfs(int v) {
    for (int v = 1; v <= graphSize; v++)
        nodes[v].visited = false;

    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    nodes[v].pred = - 1;

    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        for (auto &e : nodes[u].adjEdges){
            int w = e.dest;

            if (!nodes[w].visited && e.capacity > 0){
                q.push(w);
                nodes[w].visited = true;
                nodes[w].pred = u;
            }
        }
    }
}

void Graph::setMaxCapacity(int s) {
    MaxHeap<int, int> maxHeap = MaxHeap<int, int>(graphSize,-1);
    for (int v = 1; v <= graphSize; v++) {
        if (v == s) continue;
        nodes[v].maxCapacity = 0;
        nodes[v].distance = INT_MAX;
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

            if(min(nodes[v].maxCapacity,e.capacity) > nodes[w].maxCapacity ||  (min(nodes[v].maxCapacity,e.capacity) == nodes[w].maxCapacity && (nodes[v].distance + 1) < nodes[w].distance)) {
                nodes[w].maxCapacity = min(nodes[v].maxCapacity,e.capacity);
                nodes[w].pred = v;
                nodes[w].distance = nodes[v].distance + 1;
                maxHeap.increaseKey(w,-nodes[w].maxCapacity);
            }
        }
    }
}

list<int> Graph::MaxCapacityList(int a, int b) {
    setMaxCapacity(a);
    int v = b;
    list<int> path;
    while(v != a) {
        path.push_front(v);
        v = nodes[v].pred;
    }
    path.push_front(a);
    return path;
}

list<list<int>> Graph::optimalSolutions(int source, int sink) {
    map<list<int>, int> paths;
    list<int> ActualMinDistanceList = MinDistanceList(source, sink);
    int minCapacity = nodes[ActualMinDistanceList.back()].maxCapacity;
    list<int> ActualMaxTransbordList = MaxCapacityList(source, sink);
    int maxDistance = ActualMaxTransbordList.size() - 1;
    bool end = false;
    list<list<int>> possibleSolutions;

    bool visited[graphSize];
    int path[graphSize];
    int pathIndex = 0;

    for(auto it = ActualMinDistanceList.begin(); it != ActualMinDistanceList.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
    for(auto it = ActualMaxTransbordList.begin(); it != ActualMaxTransbordList.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
    checkPath(source, sink, minCapacity, maxDistance,visited,path, pathIndex);
    list<list<int>> lol;
    return lol;
}


void Graph::checkPath(int u,int d, int minCapacity, int maxDistance, bool visited[],
                      int path[], int& path_index) {
    visited[u] = true;
    path[path_index] = u;
    path_index++;

    // If current vertex is same as destination, then print
    // current path[]
    if (u == d) {
        for (int i = 0; i < path_index; i++) {
            cout << path[i] << " ";
        }
        cout << endl;
    }
    else // If current vertex is not destination
    {
        // Recur for all the vertices adjacent to current vertex
        list<Edge>::iterator i;
        for (i = nodes[u].adjEdges.begin(); i != nodes[u].adjEdges.end(); ++i) {
            if (!visited[i->dest]) {
                if (nodes[i->dest].maxCapacity > minCapacity) {
                    if (nodes[i->dest].distance < maxDistance)
                        checkPath(i->dest, d, minCapacity, maxDistance, visited, path, path_index);
                }
            }
        }
    }

    // Remove current vertex from path[] and mark it as unvisited
    path_index--;
    visited[u] = false;
}


void Graph::maxCapacityPath(int a, int b) {
    if(!existPath(a,b)){
        cerr << "\nDoesn't exist a path from " << a << " to " << b << endl;
        return;
    }

    setMaxCapacity(a);
    cout << "\nThe max dimension of a group is: " << nodes[b].maxCapacity;
    cout << "\nAlternative way: ";

    stack<int> path;
    path.push(b);
    while(b != a) {
        path.push(nodes[b].pred);
        b = nodes[b].pred;
    }

    while(!path.empty()){
        cout << " -> " << path.top();
        path.pop();
    }
}

void Graph::setDistance(int s) {
    MinHeap<int, int> minHeap = MinHeap<int, int>(graphSize,-1);
    for (int v = 1; v <= graphSize; v++) {
        if(v == s) {
            continue;
        }
        nodes[v].distance = INT_MAX;
        nodes[v].maxCapacity = 0;
        nodes[v].pred = 0;
        minHeap.insert(v,INT_MAX);
    }
    nodes[s].maxCapacity = INT_MAX;
    nodes[s].distance = 0;
    minHeap.insert(s,nodes[s].distance);
    int v;
    while(minHeap.getSize()) {
        v = minHeap.removeMin();
        for(auto e : nodes[v].adjEdges) {
            int w = e.dest;
            if((nodes[v].distance + 1) < nodes[w].distance || ((nodes[v].distance + 1) == nodes[w].distance && min(nodes[v].maxCapacity,e.capacity) > nodes[w].maxCapacity)) {
                nodes[w].distance = nodes[v].distance + 1;
                nodes[w].maxCapacity = min(nodes[v].maxCapacity,e.capacity);
                nodes[w].pred = v;
                minHeap.decreaseKey(w, nodes[w].distance);
            }
        }
    }
}

list<int> Graph::MinDistanceList(int a, int b) {
    setDistance(a);
    int v = b;
    list<int> path;
    while(v != a) {
        path.push_front(v);
        v = nodes[v].pred;
    }
    path.push_front(a);
    return path;
}


pair<map<list<int>, int>, int> Graph::FordFulkerson(int source, int sink, int dimension) {
    map<list<int>,int> paths;
    int capacityUsed = 0;

    while (existPath(source, sink) && capacityUsed < dimension){
        list<int> path;
        int pathFlow = INT_MAX;
        int v = sink, u;
        path.push_front(v);

        // This while calculates the pathflow for a path found
        while (v != source) {
            u = nodes[v].pred;
            for (auto &e: nodes[u].adjEdges){
                if (e.dest == v){
                    pathFlow = min(pathFlow, e.capacity);
                }
            }
            v = nodes[v].pred;
            path.push_front(v);
        }

        v = sink;

        // This while updates the path found in the residual graph
        // reducing all edges by pathflow encountered in the while above
        while (v != source){
            u = nodes[v].pred;
            for (auto &e: nodes[u].adjEdges){
                if (e.dest == v) {
                    e.capacity -= pathFlow;
                }
            }

            for (auto edge = nodes[v].adjEdges.begin();
                 edge != nodes[v].adjEdges.end(); edge++)
            {
                if (edge->dest == u){
                    edge->capacity += pathFlow;
                } else if (edge == --nodes[v].adjEdges.end()) {
                    addEdge(v, u, pathFlow, edge->duration);
                }
            }
            v = nodes[v].pred;
        }
        capacityUsed += pathFlow;
        paths.insert({path,pathFlow});
    }
    return {paths, capacityUsed};
}

bool Graph::existPath(int a, int b) {
    bfs(a);
    return nodes[b].visited;
}

Graph Graph::createTransposed(){
    Graph transposed(graphSize, true);
    for(int v = 1; v <= graphSize; v++) {
        for(auto e: nodes[v].adjEdges) {
            transposed.addEdge(e.dest, v, e.capacity, e.duration);
        }
    }
    return transposed;
}

void Graph::latestFinish(int sink) {
    int minDuration = this->minDuration();

    for(int i = 1; i <= graphSize; i++){
        nodes[i].LF = minDuration;
        nodes[i].sDegree = 0;
    }

    for(int v = 1; v <= graphSize; v++) {
        for(auto e: nodes[v].adjEdges) {
            nodes[e.dest].sDegree++;
        }
    }
    Graph transposed = createTransposed();
    stack<int> S;
    for(int v = 1; v <= graphSize; v++) {
        if(nodes[v].sDegree == 0) {
            S.push(v);
        }
    }
    while(!S.empty()) {
        int v = S.top();
        S.pop();
        for(auto e: transposed.nodes[v].adjEdges) {
            int w = e.dest;
            if(nodes[w].LF > nodes[v].LF - e.duration) {
                nodes[w].LF = nodes[v].LF - e.duration; //Duvida
            }
            nodes[w].sDegree--;
            if(nodes[w].sDegree == 0) {
                S.push(w);
            }
        }
    }

    /* É impressão minha ou isto n serve para nada?
    map<int,int> earliestFinishes;
    for(auto e : transposed.nodes[sink].adjEdges) {
        int w = e.dest;
        earliestFinishes.insert({nodes[w].ES + e.duration, w});
    }
    */
}

int Graph::minDuration(){
    for(int v = 1; v <= graphSize; v++){
        nodes[v].ES = 0;
        nodes[v].pred = 0;
        nodes[v].eDegree = 0;
    }

    for(int v = 1; v <= graphSize; v++){
       for(auto e : nodes[v].adjEdges)
       {
           int w = e.dest;
           nodes[w].eDegree++;
       }
    }

    stack<int> S;
    for (int v = 1; v <= graphSize; v++)
        if (nodes[v].eDegree == 0)
            S.push(v);

    int minDuration = -1;
    int v;

    while(!S.empty()){
        v = S.top(); S.pop();
        if(minDuration < nodes[v].ES){
            minDuration = nodes[v].ES;
        }
        for (auto e : nodes[v].adjEdges){
            int w = e.dest;
            if (nodes[w].ES < nodes[v].ES + e.duration){
                nodes[w].ES = nodes[v].ES + e.duration;
                nodes[w].pred = v;
            }
            nodes[w].eDegree--;
            if (nodes[w].eDegree == 0) {
                S.push(w);
            }
        }
    }
    return minDuration;
}

Graph Graph::createGraphByPath(const map<list<int>, int>& paths){
    int v, w;

    Graph semiGraph(graphSize, true);

    for(const auto& pair: paths){
        auto path = pair.first;
        while(path.size() != 1){
            v = path.back();
            path.pop_back();
            w = path.back();
            for(auto e : nodes[w].adjEdges){
                if(e.dest == v){
                    semiGraph.addEdge(w,v,e.capacity,e.duration);
                    break;
                }
            }
        }
    }
    return semiGraph;
}

map<int, int> Graph::totalSpare() {
    map<int, int> totalSpares;
    for(int v = 1; v <= graphSize; v++){
        for (auto e : nodes[v].adjEdges) {
            int spare;
            if ((spare = nodes[e.dest].LF - e.duration - nodes[v].ES) > 0 ) {
                totalSpares.insert(pair<int, int> (e.dest, spare));
            }
        }
    }
    return totalSpares;
}

int Graph::getGraphSize() const {
    return graphSize;
}


//PARA O EU (IGOR) VER
void Graph::printAllPaths(int s, int d)
{
    // Mark all the vertices as not visited
    bool* visited = new bool[graphSize];

    // Create an array to store paths
    int* path = new int[graphSize];
    int path_index = 0; // Initialize path[] as empty

    // Initialize all vertices as not visited
    for (int i = 0; i < graphSize; i++)
        visited[i] = false;

    // Call the recursive helper function to print all paths
    printAllPathsUtil(s, d, visited, path, path_index);
}

// A recursive function to print all paths from 'u' to 'd'.
// visited[] keeps track of vertices in current path.
// path[] stores actual vertices and path_index is current
// index in path[]
void Graph::printAllPathsUtil(int u, int d, bool visited[],
                              int path[], int& path_index)
{
    // Mark the current node and store it in path[]
    visited[u] = true;
    path[path_index] = u;
    path_index++;

    // If current vertex is same as destination, then print
    // current path[]
    if (u == d) {
        for (int i = 0; i < path_index; i++)
            cout << path[i] << " ";
        cout << endl;
    }
    else // If current vertex is not destination
    {
        // Recur for all the vertices adjacent to current vertex
        list<Edge>::iterator i;
        for (i = nodes[u].adjEdges.begin(); i != nodes[u].adjEdges.end(); ++i)
            if (!visited[i->dest])
                printAllPathsUtil(i->dest, d, visited, path, path_index);
    }

    // Remove current vertex from path[] and mark it as unvisited
    path_index--;
    visited[u] = false;
}




