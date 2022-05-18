
#include "FileReader.h"
#include "fstream"

bool FileReader::readFile(const string& inputNum) {
    string txt = ".txt";

    string dataPath = path + inputNum + txt;
    //cout << dataPath;

    ifstream file;
    string nNodes, nEdges, dataRead;
    int src, dest, capacity, duration;

    file.open(dataPath);

    if(!file.is_open())
    {
        cerr << "Cannot open in" << inputNum << ".txt file!\n";
        return false;
    }

    getline(file, nNodes, ' ');
    this->numNodes = stoi(nNodes);

    getline(file, nEdges);
    this->numEdges = stoi(nEdges);

    graph = Graph(numNodes, true);

    for(int i = 0; i < numEdges; i++) {
        getline(file, dataRead, ' ');
        src = stoi(dataRead);

        getline(file, dataRead, ' ');
        dest = stoi(dataRead);

        getline(file, dataRead, ' ');
        capacity = stoi(dataRead);

        getline(file, dataRead);
        duration = stoi(dataRead);
        graph.addEdge(src, dest, capacity, duration);
    }

    file.close();
    return true;
}

Graph FileReader::getGraph() {
    return graph;
}
