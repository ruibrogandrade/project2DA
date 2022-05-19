#include "FileReader.h"
#include "Graph.h"
#include "maxHeap.h"
int main(){

    FileReader file;
    if(!file.readFile("11")) exit(1);
    Graph graph = file.getGraph();
    graph.maxCapacityPath(1,4);

    return 0;
}

