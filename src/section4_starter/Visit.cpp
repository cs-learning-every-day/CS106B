/*
 * CS106B Section Handout Test Harness: Section 4
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
#include "map.h"
using namespace std;

/*
 * Function: canVisitAllSites
 * ---------------------------
 * Write a function that takes as input a list of all the
 * sites you’d like to visit and an amount of free time
 * available to you and returns whether it’s possible to
 * visit all those sites in the allotted time (assume you’ve
 * already factored inthe cost of speaking at each site
 * and that you’re just concerned about the travel time.)
 */

double distance(const GPoint &p1, const GPoint &p2) {
    return sqrt(abs(p1.x - p2.x) + abs(p1.y - p2.y));
}

bool help(GPoint start, Vector<GPoint> sites, double time) {
    if (time < 0) {
        return false;
    }

    if (time == 0 && sites.size() != 0) {
        return false;
    }

    for (int i = 0; i < sites.size(); i++) {
        auto tmp = sites;
        tmp.remove(i);
        help(sites[i], tmp, time - distance(sites[i], start));
    }

    return true;
}

bool canVisitAllSites(const Vector<GPoint>& sites, double travelTimeAvailable) {
    for (auto p : sites) {
        if (help(p, sites, travelTimeAvailable)) {
            return true;
        }
    }
    return false;
}

/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("Provided Test: Simple examples!") {
    Vector<GPoint> sites1 = {{0, 0}, {5, 5}};
    Vector<GPoint> sites2 = {{0, 0}, {2, 2}, {5, 5}};
    EXPECT_EQUAL(canVisitAllSites(sites1, 8), true);
    EXPECT_EQUAL(canVisitAllSites(sites2, 8), true);
}
