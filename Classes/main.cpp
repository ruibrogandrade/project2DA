#include "Graph.h"
#include "FileReader.h"

int main(){
    FileReader file;
    if(!file.readFile("07")) exit(1);
    Graph graph = file.getGraph();
    graph.bfs(1);
    return 0;
}

