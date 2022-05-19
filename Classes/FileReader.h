#ifndef _FILEREADER_H
#define _FILEREADER_H

#include "Graph.h"

class FileReader {
private:
    string path = "../Dataset/in";
    Graph graph;
    int numNodes, numEdges;

public:
    FileReader(){};
    bool readFile(const string& inputNum);
    Graph getGraph();
};

#endif //_FILEREADER_H