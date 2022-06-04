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

list<list<int>> Graph::optimalSolutions(int a, int b) {
    Graph paretoGraph = *this;
    list<list<int>> maxCapacityPaths;
    list<list<int>> minDistancePaths;
    list<int> path;

    list<int> maxCapacitySolution = paretoGraph.MaxCapacityList(a,b);
    maxCapacityPaths.push_back(maxCapacitySolution);
    list<int> minDistanceSolution = paretoGraph.MinDistanceList(a,b);
    ///minDistancepaths.push_back(minDistanceSolution);
    list<list<int>> solutions;
    solutions.push_back(maxCapacitySolution);
    solutions.push_back(minDistanceSolution);
    int aux;
    int v = b;
    while(v != a) {
        int w = paretoGraph.nodes[v].pred;
        for(auto &e: paretoGraph.nodes[w].adjEdges) {
            if(e.dest == v) {
                aux = e.capacity;
                e.capacity = INT_MIN;
                list<int> newPathMaxCapacityList = paretoGraph.MaxCapacityList(a,b);
                if(newPathMaxCapacityList.size() < maxCapacitySolution.size() &&
                    nodes[newPathMaxCapacityList.back()].maxCapacity > nodes[minDistanceSolution.back()].maxCapacity){
                    solutions.push_back(newPathMaxCapacityList);
                }
                e.capacity = aux;
                break;
            }
        }
        v = w;
    }
    return solutions;
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
        nodes[v].pred = 0;
        minHeap.insert(v,INT_MAX);
    }
    nodes[s].distance = 0;
    minHeap.insert(s,nodes[s].distance);
    int v;
    while(minHeap.getSize()) {
        v = minHeap.removeMin();
        for(auto e : nodes[v].adjEdges) {
            int w = e.dest;
            if((nodes[v].distance + 1) < nodes[w].distance) {
                nodes[w].distance = nodes[v].distance + 1;
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

    Graph rGraph = *this;

    int capacityUsed = 0;

    while (rGraph.existPath(source, sink) && capacityUsed < dimension){
        list<int> path;
        int pathFlow = INT_MAX;
        int v = sink, u;
        path.push_front(v);

        // This while calculates the pathflow for a path found
        while (v != source) {
            u = rGraph.nodes[v].pred;
            for (auto &e: rGraph.nodes[u].adjEdges){
                if (e.dest == v){
                    pathFlow = min(pathFlow, e.capacity);
                }
            }
            v = rGraph.nodes[v].pred;
            path.push_front(v);
        }

        v = sink;

        // This while updates the path found in the residual graph
        // reducing all edges by pathflow encountered in the while above
        while (v != source){
            u = rGraph.nodes[v].pred;
            for (auto &e: rGraph.nodes[u].adjEdges){
                if (e.dest == v) {
                    e.capacity -= pathFlow;
                }
            }

            for (auto edge = rGraph.nodes[v].adjEdges.begin();
                 edge != rGraph.nodes[v].adjEdges.end(); edge++)
            {
                if (edge->dest == u){
                    edge->capacity += pathFlow;
                } else if (edge == --rGraph.nodes[v].adjEdges.end()) {
                    rGraph.addEdge(v, u, pathFlow, edge->duration);
                }
            }
            v = rGraph.nodes[v].pred;
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


