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

    // 1.1
    //graph.maxCapacityPath(1,4);

    cout << endl << endl;

    // 1.2
    //graph.maxCapacityPath(1,4);
    //graph.minDistancePath(1,4);


    map<list<int>,int> paths = graph.FordFulkersen(1,4);

    /* 2.3
    int maxFlow = 0;
    for(auto & path : paths) {
        maxFlow += path.second;
        for (int et : path.first)
        {
            cout << " -> " << et;
        }
        cout << "\nPath Flow: " << path.second << endl;
    }
    cout << "\nMax Flow is: " << maxFlow;
    */

    /* 2.1
    int groupDim = 9;
    for(auto & path : paths)
    {
        if (groupDim - path.second > 0)
        {
            groupDim -= path.second;

            for (int et : path.first)
            {
                cout << " -> " << et;
            }
            cout << "\nPath Flow: " << path.second << endl;
        } else
        {
            for (int et : path.first)
            {
                cout << " -> " << et;
            }
            cout << "\nPath Flow: " << groupDim << endl;
            return 0;
        }
    }
    */



    //cout << endl << "The Max Flow of this path is:" << graph.FordFulkersen(1,4) << endl;

    return 0;
}

