//
// Created by Rui on 19/05/2022.
//

#include "application.h"
#include <string>
#include <iostream>

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
    cout << " First Scenario        [1]\n"
            " Second Scenario       [2]\n"
            " Exit                  [0]\n";

    unsigned int choice;

    while (true) {
        cout << "Choose an option:";
        cin >> choice;

        if (isBadCin() || choice < 0 || choice > 2) {
            cout << "Invalid input!" << endl;
            continue;
        }
        return choice;
    }
}

void Application::run() {

    while (true) {
        int option = showMenu();
        if (option == 0) return;
    }
}
