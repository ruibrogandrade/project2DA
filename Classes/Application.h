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

    static bool isBadCin();

    // 2.1
    pair<list<list<int>>,int> fixedFlow(const map<list<int>, pair<int, int>> &paths);

    // 2.3
    static void maxFlow(const map<list<int>, pair<int, int>> &paths);

    // 2.4
    void minDuration(const map<list<int>, pair<int, int>> &paths);

    // 2.5
    void maxWaiting(const map<list<int>, pair<int, int>> &paths);

    static unsigned int firstScenario();

    static unsigned int secondScenario();

public:
    Application();

    void run();

    list<list<int>>
    changedFlow(const map<list<int>, pair<int, int>> &paths);
};
