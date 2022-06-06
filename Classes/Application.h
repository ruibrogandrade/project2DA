//
// Created by Rui on 30/03/2022.
//

#include "FileReader.h"

using namespace std;

class Application {
private:
    Graph graph;
    int source{}, sink{}, groupDim{};

private:
    /**
     * Displays the different algorithms available
     * @return unsigned - number of the algorithm chosen
     */
    static unsigned showMenu();


    /**
     * Checks if the cin is not what was expected
     * @return bool - if the cin was expected or not
     */
    static bool isBadCin();


    void askSource();

    void askSink();

    static int askGroupDim();

    /**
     * Displays the options for the First Scenario
     * @return which algorithm to use in the first scenario
     */
    void firstScenario(Graph g) const;


    /**
     * Displays the options and executes the functions for the Second Scenario
     */
    void secondScenario();

    /***
     * Displays the path of a group with a certain dimension and the respective path flows
     */
    // 2.1
    void fixedFlow();

    /**
     * Displays the new path after adding a certain amount of size to an existing group
     */
    void changedFlow();

    /**
     *  Displays the max dimension that a group can grow to while being able to get through the path
     */
    // 2.3
    void maxFlow();

    // 2.4
    /**
     * Displays the minimum Duration that a certain group can take while going through the path
     */
    void minDuration();

    // 2.5
    /**
     * Displays the Maximum time a group can have to wait and in what nodes those wait times can happen
     */
    void maxWaiting();

public:
    /**
     * empty constructor
     */
    Application();

    /**
     * Reads the files and Displays the executes the algorithms for each option
     */
    void run();

};
