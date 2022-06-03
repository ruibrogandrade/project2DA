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

    /**
     * Displays the path of a group with a certain dimension and the respective path flows
     * @param paths map<list<int>, pair<int, int>> - map containing the paths available to be used and the respective pathFlow and duration of those paths
     * @return pair<list<list<int>>,int> - pair containing the paths that were Used and the remaining Dimension of the last one
     */
    // 2.1
    pair<list<list<int>>,int> fixedFlow(map<list<int>, int> &paths);

    /**
     * Displays the new path after adding a certain amount of size to an existing group
     * @param paths map<list<int>, pair<int, int>> - map containing the paths available to be used and the respective pathFlow and duration of those paths
     * @return list<list<int>> - the paths used in this algorithm
     */
    list<list<int>> changedFlow(map<list<int>, int> &paths);

    /**
     *  Displays the max dimension that a group can grow to while being able to get through the path
     * @param paths map<list<int>, pair<int, int>> - map containing the paths available to be used and the respective pathFlow and duration of those paths
     */
    // 2.3
    void maxFlow(const map<list<int>, int> &paths);

    // 2.4
    /**
     * Displays the minimum Duration that a certain group can take while going through the path
     * @param paths map<list<int>, pair<int, int>> - map containing the paths available to be used and the respective pathFlow and duration of those paths
     */
    void minDuration(map<list<int>, int> &paths);

    // 2.5
    /**
     * Displays the Maximum time a group can have to wait and in what nodes those wait times can happen
     * @param paths
     */
    void maxWaiting(map<list<int>, int> &paths);

    /**
     * Displays the options for the First Scenario
     * @return which algorithm to use in the first scenario
     */
    static unsigned int firstScenario();


    /**
     * Displays the options for the Second Scenario
     * @return which algorithm to use in the second scenario
     */
    static unsigned int secondScenario();

public:
    /**
     * empty constructor
     */
    Application();

    /**
     * Reads the files and Displays the executes the algorithms for each option
     */
    void run();

    int getGroupDimension();
};
