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

// 2.1
pair<list<list<int>>,int> Application::fixedFlow(map<list<int>, int> &paths) {
    int groupDim;
    list<list<int>> pathsUsed;
    int remainingDim;
    while (true) {
        cout << "\n Write the group's dimension: ";
        cin >> groupDim;

        if (!isBadCin() && groupDim >= 0) break;
        cout << "\nINVALID NUMBER!\n";
    }

    for (auto &path: paths) {
        pathsUsed.push_back(path.first);
        if (groupDim - path.second > 0) {
            groupDim -= path.second;
            cout << '\n';
            for (int et: path.first)
                cout << " -> " << et;
            cout << "\nPath Flow: " << path.second<< '\n';
        } else {
            remainingDim = abs(groupDim - path.second);
            cout << '\n';
            for (int et: path.first)
                cout << " -> " << et;
            cout << "\nPath Flow: " << groupDim << '\n';
            groupDim -= path.second;
            break;
        }
    }

    if (groupDim > 0)
        cout << "\nUnable to pass the entirety of the group."
                "\nThe remaining capacity is: " << groupDim;
    else cout << "\nSUCCESS!\n";

    return {pathsUsed,remainingDim};
}

//2.2
list<list<int>> Application::changedFlow(map<list<int>, int> &paths) {
    int addedDimension;

    pair<list<list<int>>,int> fixedFl = fixedFlow(paths);
    list<list<int>> pathsUsed = fixedFl.first;
    int remainingDim = fixedFl.second;

    while (true) {
        cout << "\n Write the group's added dimension: ";
        cin >> addedDimension;

        if (!isBadCin() && addedDimension >= 0) break;
        cout << "\nINVALID NUMBER!\n";
    }


    int groupDim = addedDimension;
    int n;
    if(remainingDim > 0) {
        n = 1;
    } else {
        n = 0;
    }

    cout << "Added path:" << endl;

    bool firstIter = true;
    int edgeDim;

    for (auto path = next(paths.begin(),pathsUsed.size() - n); path != paths.end(); path++) {
        //pathsUsed.push_back(path->first);
        if(firstIter) {
            edgeDim = remainingDim;
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
            remainingDim = abs(groupDim - path->second);
            cout << '\n';
            for (int et: path->first)
                cout << " -> " << et;
            cout << "\nPath Flow: " << groupDim << '\n';
            groupDim -= edgeDim;
            break;
        }
    }

    if (groupDim > 0)
        cout << "\nUnable to pass the entirety of the group."
                "\nThe remaining capacity is: " << groupDim;
    else cout << "\nSUCCESS!\n";

    return pathsUsed;
}

// 2.3
void Application::maxFlow(const map<list<int>, int> &paths) {
    int maxFlow = 0;
    for(auto & path : paths) {
        maxFlow += path.second;
        cout << '\n';
        for (int et: path.first)
            cout << " -> " << et;
        cout << "\nPath Flow: " << path.second << '\n';
    }
    cout << "\nMax Flow is: " << maxFlow;
}

// 2.4
void Application::minDuration(map<list<int>, int> &paths) {
    list<list<int>> usedPaths = fixedFlow(paths).first;
    auto reducedGraph = graph.createGraphByPath(usedPaths);
    int result = reducedGraph.minDuration();
    cout << "\nThe minimum duration of travel for the given "
            "group is: " << result << '\n';
}

// 2.5
void Application::maxWaiting(map<list<int>, int> &paths) {
    list<list<int>> usedPaths = fixedFlow(paths).first;
    auto reducedGraph = graph.createGraphByPath(usedPaths);

    reducedGraph.minDuration();
    reducedGraph.latestFinish(1);

    map<int, int> spares = reducedGraph.totalSpare();
    for (auto s: spares) {
        cout << "\nNode: " << s.first << " - Total spare time: " << s.second;
    }
    cout << '\n';
}

void Application::run(){
    FileReader file;
    if(!file.readFile("13")) exit(1);
    graph = file.getGraph();
    map<list<int>, int> paths;
    list<list<int>> paretoSolutions;
    auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    while (true) {
        auto scenario = showMenu();
        unsigned subProblem;

        switch (scenario) {
            case 0:
                return;
            case 1:
                subProblem = firstScenario();
                switch (subProblem) {
                    case 1:
                        // 1.1
                        start = high_resolution_clock::now();
                        graph.maxCapacityPath(1,4);
                        stop = high_resolution_clock::now();
                        duration = duration_cast<microseconds>(stop - start);
                        cout << endl << "Duration of Algorithm is: " << duration.count() << endl;
                        break;
                    case 2:
                        // 1.2
                        paretoSolutions = graph.optimalSolutions(1,4);
                        for(auto path : paretoSolutions){
                            cout << "(" << path.front() << "," << path.back() << "," << path.size() - 1 << ")\n";
                        }
                        break;
                    default:
                        break;
                }
                break;
            case 2:
                subProblem = secondScenario();
                paths = graph.FordFulkerson(1, 4);
                switch (subProblem) {
                    case 1:
                        fixedFlow(paths);
                        break;
                    case 2:
                        changedFlow(paths);
                        break;
                    case 3:
                        maxFlow(paths);
                        break;
                    case 4:
                        minDuration(paths);
                        break;
                    case 5:
                        maxWaiting(paths);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}

unsigned Application::firstScenario() {
    unsigned int choice;

    while (true) {
        cout << "\n 1.1   [1]"
                "\n 1.2   [2]"
                "\n Back  [0]\n";

        cout << "\nChoose an option: ";
        cin >> choice;

        if (!isBadCin() && choice >= 0 && choice <= 2) return choice;
        cout << "\nINVALID OPTION!\n";
    }
}

unsigned Application::secondScenario() {
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

        if (!isBadCin() && choice >= 0 && choice <= 5) return choice;
        cout << "\nINVALID OPTION!\n";
    }
}
