/*
 * CS106B Section Handout Test Harness: Section 3
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified for Qt and Ed by Neel
 * Kishnani for Winter 2022.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include <iostream>
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
#include "set.h"
#include "error.h"
#include "map.h"
using namespace std;


void dfs(int total, const Set<string>& people,
                    Map<string, int>& map) {
    if (people.size() == 1) {
        map[people.first()] = total;
        cout << map << endl;
    } else {
        for (int t = 0; t <= total; t++) {
            map[people.first()] = t;
            dfs(total - t, people - people.first(), map);
            map[people.first()] = 0;
        }
    }
}

/*
 * Function: listPossiblePayments
 * -------------------------------
 * Write a function that takes as input a total amount of money
 * to pay (in dollars) and a set of all the people who ordered
 * something, then lists off every possible way you could split
 * the bill, assuming everyone pays a whole number of dollars.
 */
void listPossiblePayments(int total, const Set<string>& people) {
    if (total < 0) {
        error("total must be not negative!");
    }

    if (people.size() < 1) {
        error("must be at least one person!");
    }

    Map<string, int> map;
    dfs(total, people, map);
    return;
}


/* * * * * Provided Tests Below This Point * * * * */

/*
 * Since this is a void function, we don't have a return value to verify with.
 * We will instead just run your code to make sure there is no obvious error.
 */
PROVIDED_TEST("Provided Test: Run the provided example. There should be 15 entries.") {
    Set<string> s = {"A", "B", "C"};
    listPossiblePayments(4, s);
}
