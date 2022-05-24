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

void Application::run() {
    bool end = false;

    FileReader file;
    if(!file.readFile("12")) exit(1);
    graph = file.getGraph();
    map<list<int>, int> paths;
    int maxFlow;
    int groupDim;


    while (!end) {
        auto scenario = showMenu();
        unsigned int subProblem;

        switch (scenario) {
            case 0:
                end = true;
                break;
            case 1:
                subProblem = firstScenario();
                switch (subProblem) {
                    case 0:
                        return;
                    case 1:
                        graph.maxCapacityPath(1,4);
                        return;
                    case 2:
                        graph.maxCapacityPath(1,4);
                        graph.minDistancePath(1,4);
                        return;
                    default:
                        return;
                }
            case 2:
                subProblem = secondScenario();
                paths = graph.FordFulkersen(1, 4);
                groupDim = 9;
                switch (subProblem) {
                    case 0:
                        return;
                    case 1:
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
                                return;
                            }
                        return;
                    case 2:
                        //TODO 2.2
                        return;
                    case 3:
                        maxFlow = 0;
                        for(auto & path : paths) {
                            maxFlow += path.second;
                            cout << '\n';
                            for (int et: path.first)
                                cout << " -> " << et;
                            cout << "\nPath Flow: " << path.second << '\n';
                        }
                        cout << "\nMax Flow is: " << maxFlow;
                        return;
                    case 4:
                        //TODO 2.4
                        return;
                    case 5:
                        //TODO 2.5
                        return;
                    default:
                        return;
                }
            default:
                return;

        }
    }
}

unsigned Application::firstScenario() {
    unsigned int choice;

    while (true) {
        cout << "\n 1.1   [1]"
                "\n 1.2   [2]"
                "\n Exit  [0]\n";

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
                "\n Exit  [0]\n";

        cout << "\nChoose an option: ";
        cin >> choice;

        if (!isBadCin() && choice >= 0 && choice <= 5) return choice;
        cout << "\nINVALID OPTION!\n";
    }
}