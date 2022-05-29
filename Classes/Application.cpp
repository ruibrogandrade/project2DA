//
// Created by Rui on 19/05/2022.
//

#include "Application.h"
#include <string>
#include <iostream>
#include <climits>

using namespace std;

Application::Application() = default;

bool isBadCin() {
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
void fixedFlow(const map<list<int>, int>& paths) {
    int groupDim;

    while (true) {
        cout << "\n Write the group's dimension: ";
        cin >> groupDim;

        if (!isBadCin() && groupDim >= 0) break;
        cout << "\nINVALID NUMBER!\n";
    }

    for (auto &path: paths)
        if (groupDim - path.second > 0) {
            groupDim -= path.second;
            cout << '\n';
            for (int et: path.first)
                cout << " -> " << et;
            cout << "\nPath Flow: " << path.second << '\n';
        } else {
            cout << '\n';
            for (int et: path.first)
                cout << " -> " << et;
            cout << "\nPath Flow: " << groupDim << '\n';
            groupDim -= path.second;
            break;
        }

    if (groupDim > 0)
        cout << "\nUnable to pass the entirety of the group."
                "\nThe remaining capacity is: " << groupDim;
    else cout << "\nSUCCESS!\n";
}

// 2.3
void maxFlow(const p<list<int>, pair<int, int>> &paths) {
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

void Application::run() {

    FileReader file;
    if(!file.readFile("12")) exit(1);
    graph = file.getGraph();
    map<list<int>, pair<int, int>> paths;

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
                        graph.maxCapacityPath(1,4);
                        break;
                    case 2:
                        // 1.2
                        graph.maxCapacityPath(1,4);
                        graph.minDistancePath(1,4);
                        break;
                    default:
                        break;
                }
                break;
            case 2:
                subProblem = secondScenario();
                paths = graph.FordFulkersen(1, 4);
                switch (subProblem) {
                    case 1:
                        fixedFlow(paths);
                        break;
                    case 2:
                        //TODO 2.2
                        cout << "\n2.2 isn't implemented yet.\n";
                        break;
                    case 3:
                        maxFlow(paths);
                        break;
                    case 4:
                        //TODO 2.4
                        cout << "\n2.4 isn't implemented yet.\n";
                        break;
                    case 5:
                        //TODO 2.5
                        cout << "\n2.5 isn't implemented yet.\n";
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
