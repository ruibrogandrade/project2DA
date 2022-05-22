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
    //graph.maxCapacityPath(1,4);
    cout << endl << endl;
    //graph.minDistancePath(1,4);

    cout << endl << "The Max Flow of this path is:" << graph.FordFulkersen(1,4) << endl;

    return 0;
}

