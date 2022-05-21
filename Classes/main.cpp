#include "FileReader.h"
#include "Graph.h"
#include "maxHeap.h"
#include "Application.h"

int main(){
    //Application app;
    //app.run();
    FileReader file;
    if(!file.readFile("12")) exit(1);
    Graph graph = file.getGraph();
    graph.maxCapacityPath(1,5);
    cout << endl << endl;
    graph.minDistancePath(1,5);

    return 0;
}

