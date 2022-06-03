//
// Created by Rui on 19/05/2022.
//

#include "Application.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <climits>
#include <chrono>

using namespace std;
using namespace std::chrono;

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
        cout << "\n\n - MENU - "
                "\n First Scenario        [1]"
                "\n Second Scenario       [2]"
                "\n Exit                  [0]\n";

        cout << "\nChoose an option:";
        cin >> choice;

        if (isBadCin() || choice < 0 || choice > 2) {
            cout << "\nINVALID OPTION!\n";
            continue;
        }
        return choice;
    }
}

void Application::askSource() {
    int input;
    while (true) {
        cout << "\n Source: ";
        cin >> input;

        if (!isBadCin() && input >= 1 && input < graph.getGraphSize()) {
            this->source = input;
            return;
        }
        cout << "\nINVALID NUMBER!\n";
    }
}

void Application::askSink() {
    int input;
    while (true) {
        cout << "\n Sink: ";
        cin >> input;

        if (!isBadCin() && input >= 1 && input < graph.getGraphSize()) {
            this->sink = input;
            return;
        }
        cout << "\nINVALID NUMBER!\n";
    }
}

int Application::askGroupDim() {
    int input;
    while (true) {
        cout << "\n Group dimension: ";
        cin >> input;

        if (!isBadCin() && input >= 0) return input;
        cout << "\nINVALID NUMBER!\n";
    }
}

void Application::run(){
    FileReader file;
    if(!file.readFile("07")) exit(1);
    graph = file.getGraph();

    while (true) {
        auto scenario = showMenu();

        askSource();
        askSink();

        switch (scenario) {
            case 0:
                return;
            case 1:
                firstScenario(Graph());
                break;
            case 2:
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
            cout << "\n 1.1   [1]"
                    "\n 1.2   [2]"
                    "\n Back  [0]\n";

            cout << "\nChoose an option: ";
            cin >> choice;

            if (!isBadCin() && choice >= 0 && choice <= 2) break;
            cout << "\nINVALID OPTION!\n";
        }

        switch (choice) {
            case 0:
                return;
            case 1: {
                // 1.1
                auto start = high_resolution_clock::now();
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                start = high_resolution_clock::now();

                g.maxCapacityPath(source, sink);

                stop = high_resolution_clock::now();
                duration = duration_cast<microseconds>(stop - start);
                cout << endl << "Duration of Algorithm is: " << duration.count() << endl;
                break;
            }
            case 2: {
                // 1.2
                list<list<int>> paretoSolutions = g.optimalSolutions(source, sink);
                for(auto path : paretoSolutions)
                {
                    cout << "(" << path.front() << "," << path.back() << "," << path.size() - 1 << ")\n";
                }
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
            cout << "\n 2.1   [1]"
                    "\n 2.2   [2]"
                    "\n 2.3   [3]"
                    "\n 2.4   [4]"
                    "\n 2.5   [5]"
                    "\n Back  [0]\n";

            cout << "\nChoose an option: ";
            cin >> choice;

            if (!isBadCin() && choice >= 0 && choice <= 5) break;
            cout << "\nINVALID OPTION!\n";
        }

        switch (choice) {
            case 0:
                return;
            case 1:
                fixedFlow();
                break;
            case 2:
                if (!pathsUsed.empty()) changedFlow();
                else cout << "\nPlease execute 2.1 first.\n";
                break;
            case 3:
                maxFlow();
                break;
            case 4:
                if (!pathsUsed.empty()) minDuration();
                else cout << "\nPlease execute 2.1 first.\n";
                break;
            case 5:
                if (!pathsUsed.empty()) maxWaiting();
                else cout << "\nPlease execute 2.1 first.\n";
                break;
            default:
                break;
        }
    }
}

// 2.1
void Application::fixedFlow() {
    auto temp = graph.FordFulkerson(source, sink, groupDim);
    pathsUsed = temp.first;
    capacityUsed = temp.second;

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
    if (capacityUsed < groupDim)
    {
        cout << "\nUnable to pass the entirety of the group."
                "\nThe remaining capacity is: " << groupDim-capacityUsed;
        return;
    }

    int addedDimension = askGroupDim();

    groupDim = addedDimension;

    // TODO 2.2

    /*
    int n;
    if(capacityUsed > 0) {
        n = 1;
    } else {
        n = 0;
    }

    cout << "Added path:" << endl;

    bool firstIter = true;
    int edgeDim;

    for (auto path = next(pathsUsed.begin(),pathsUsed.size() - n); path != pathsUsed.end(); path++) {
        //pathsUsed.push_back(path->first);
        if(firstIter) {
            edgeDim = capacityUsed;
            firstIter = false;
        } else{
            edgeDim = path->second;
        }
        if (groupDim - edgeDim > 0) {
            groupDim -= edgeDim;
            cout << '\n';
            for (int et: path->first)
                cout << " -> " << et;
            cout << "\nPath Flow: " << edgeDim << '\n';
        } else {
            capacityUsed = abs(groupDim - path->second);
            cout << '\n';
            for (int et: path->first)
                cout << " -> " << et;
            cout << "\nPath Flow: " << groupDim << '\n';
            groupDim -= edgeDim;
            break;
        }
    }
     */
}

// 2.3
void Application::maxFlow() {
    int maxFlow = graph.FordFulkerson(source, sink, INT_MAX).second;
    cout << "\nThe max flow is: " << maxFlow;
}

// 2.4
void Application::minDuration() {
    auto reducedGraph = graph.createGraphByPath(pathsUsed);
    int result = reducedGraph.minDuration();
    cout << "\nThe minimum duration of travel for the given "
            "group is: " << result << '\n';
}

// 2.5
void Application::maxWaiting() {
    auto reducedGraph = graph.createGraphByPath(pathsUsed);

    reducedGraph.minDuration();
    reducedGraph.latestFinish(1);

    map<int, int> spares = reducedGraph.totalSpare();
    for (auto s: spares) {
        cout << "\nNode: " << s.first << " - Total spare time: " << s.second;
    }
    cout << '\n';
}
