#ifndef _FILEREADER_H
#define _FILEREADER_H

#include "Graph.h"


class FileReader {
private:
    /**
     * path skeleton that is used to build the file's paths;
     */
    string path = "../Dataset/in";
    /**
     * graph that will be constructed after reading
     */
    Graph graph;
    /**
     * Number of nodes.
     * Number of edges.
     */
    int numNodes{}, numEdges{};

public:
    FileReader()= default;;
    /**
     * Reads a file associated with the number 'inputNum'
     * @param inputNum - used to build a file's path ( "path" + "inputNum" + ".txt")
     * @return True if the could open specified file or false otherwise.
     */
    bool readFile(const string& inputNum);
    /**
     *
     * @return Graph created with readFile function
     */
    Graph getGraph();
};

#endif //_FILEREADER_H