//
// Created by Rui on 19/05/2022.
//

#include "Application.h"
#include <iostream>
#include <algorithm>
#include <climits>

Application::Application() = default;

bool Application::isBadCin() {
    //verify if the menu chose is a possible choice made by the user

    if (cin.fail() || cin.peek() != '\n') {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        return true;
    }
    return false;
}

unsigned Application::showMenu() {
    unsigned int choice;

    while (true) {
        cout << "\n\n- MENU - "
                "\nFirst Scenario        [1]"
                "\nSecond Scenario       [2]"
                "\nExit                  [0]\n";

        cout << "\nChoose an option:";
        cin >> choice;

        if (isBadCin() || choice < 0 || choice > 2) {
            cerr << "\nINVALID OPTION!\n";
            continue;
        }
        return choice;
    }
}

void Application::askSource() {
    int input;
    while (true) {
        cout << "\nSource: ";
        cin >> input;

        if (!isBadCin() && input >= 1 && input <= graph.getGraphSize()) {
            this->source = input;
            return;
        }
        cerr << "\nINVALID NUMBER!\n";
    }
}

void Application::askSink() {
    int input;
    while (true) {
        cout << "\nSink: ";
        cin >> input;

        if (!isBadCin() && input >= 1 && input <= graph.getGraphSize()) {
            this->sink = input;
            return;
        }
        cerr << "\nINVALID NUMBER!\n";
    }
}

int Application::askGroupDim() {
    int input;
    while (true) {
        cout << "\nGroup dimension: ";
        cin >> input;

        if (!isBadCin() && input >= 0) return input;
        cerr << "\nINVALID NUMBER!\n";
    }
}

void Application::run(){
    FileReader file;

    if(!file.readFile("10")) exit(1);

    graph = file.getGraph();

    while (true) {
        auto scenario = showMenu();

        switch (scenario) {
            case 0:
                return;
            case 1:
                askSource();
                askSink();
                firstScenario(graph);
                break;
            case 2:
                askSource();
                askSink();
                groupDim = askGroupDim();
                secondScenario();
                break;
            default:
                break;
        }
    }
}

void Application::firstScenario(Graph g) const {
    while (true) {
        unsigned int choice;

        while (true) {
            cout << "\n1.1   [1]"
                    "\n1.2   [2]"
                    "\nBack  [0]\n";

            cout << "\nChoose an option: ";
            cin >> choice;

            if (!isBadCin() && choice >= 0 && choice <= 2) break;
            cerr << "\nINVALID OPTION!\n";
        }

        switch (choice) {
            case 0:
                return;
            case 1: {
                g.maxCapacityPath(source, sink);
                break;
            }
            case 2: {
                // 1.2
                g.optimalSolutions(source, sink);
                break;
            }
            default:
                break;
        }
    }
}

void Application::secondScenario() {
    while (true) {
        unsigned int choice;
        while (true) {
            cout << "\n2.1   [1]"
                    "\n2.2   [2]"
                    "\n2.3   [3]"
                    "\n2.4   [4]"
                    "\n2.5   [5]"
                    "\nBack  [0]\n";

            cout << "\nChoose an option: ";
            cin >> choice;

            if (!isBadCin() && choice >= 0 && choice <= 5) break;
            cerr << "\nINVALID OPTION!\n";
        }

        switch (choice) {
            case 0:
                return;
            case 1: {
                fixedFlow();
                break;
            }
            case 2:
                changedFlow();
                break;
            case 3: {
                maxFlow();
                break;
            }
            case 4: {
                minDuration();
                break;
            }
            case 5:
                maxWaiting();
                break;
            default:
                break;
        }
    }
}

// 2.1
void Application::fixedFlow() {
    Graph rGraph = graph;

    auto temp = rGraph.FordFulkerson(source, sink, groupDim);
    auto pathsUsed = temp.first;
    auto capacityUsed = temp.second;

    if (capacityUsed < groupDim)
    {
        cout << "\nUnable to pass the entirety of the group."
                "\nThe remaining capacity is: " << groupDim-capacityUsed;
        return;
    }

    for (auto &path: pathsUsed) {
        for (int et: path.first) {
            cout << " -> " << et;
        }
        cout << "\nPath Flow: " << path.second<< '\n';
    }
    cout << "\nSUCCESS!\n";
}

//2.2
void Application::changedFlow() {
    Graph rGraph = graph;

    auto temp = rGraph.FordFulkerson(source, sink, groupDim);
    auto pathsUsed = temp.first;
    auto capacityUsed = temp.second;

    if (capacityUsed < groupDim)
    {
        cout << "\nUnable to pass the entirety of the group."
                "\nThe remaining capacity is: " << groupDim-capacityUsed;
        return;
    }

    cout << "\nAdded group.";
    int addedDimension = askGroupDim();

    if (capacityUsed < groupDim + addedDimension) {
        auto t = rGraph.FordFulkerson(source, sink, groupDim + addedDimension - capacityUsed);
        auto additionalPaths = t.first;
        auto additionalCapacity = t.second;

        for (auto &p : additionalPaths) {
            pathsUsed.insert(p);
        }
        capacityUsed += additionalCapacity;
    }

    if (capacityUsed < groupDim + addedDimension)
    {
        cout << "\nUnable to pass the entirety of the group."
                "\nThe remaining capacity is: " << groupDim + addedDimension -capacityUsed;
        return;
    }

    for (auto &path: pathsUsed) {
        for (int et: path.first) {
            cout << " -> " << et;
        }
        cout << "\nPath Flow: " << path.second<< '\n';
    }
    cout << "\nSUCCESS!\n";
}

// 2.3
void Application::maxFlow() {
    Graph rGraph = graph;
    int maxFlow = rGraph.FordFulkerson(source, sink, INT_MAX).second;
    cout << "\nThe max flow is: " << maxFlow;
}

// 2.4
void Application::minDuration() {
    Graph rGraph = graph;

    auto pathsUsed  = rGraph.FordFulkerson(source, sink, groupDim).first;

    auto reducedGraph = rGraph.createGraphByPath(pathsUsed);
    int result = reducedGraph.minDuration();
    cout << "\nThe minimum duration of travel for the given "
            "group is: " << result << '\n';
}

// 2.5
void Application::maxWaiting() {
    Graph residualGraph = graph;

    auto pathsUsed  = residualGraph.FordFulkerson(source, sink, groupDim).first;

    auto reducedGraph = residualGraph.createGraphByPath(pathsUsed);

    reducedGraph.minDuration();
    reducedGraph.latestFinish(1);

    map<int, int> spares = reducedGraph.totalSpare();
    for (auto s: spares) {
        cout << "\nNode: " << s.first << " - Total spare time: " << s.second;
    }
    cout << '\n';
}