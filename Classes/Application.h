//
// Created by Rui on 30/03/2022.
//

#include "FileReader.h"

using namespace std;

class Application {
private:
    FileReader reader;
    Graph graph;

private:
    static unsigned showMenu();

public:
    Application();

    void run();

    static unsigned int firstScenario();

    static unsigned int secondScenario();
};
