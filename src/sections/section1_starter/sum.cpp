/*
 * CS106B Section Handout Test Harness: Section 1
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified by Trip Master and Nick
 * Bowman for CS106B Spring 2020.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */
#include <iostream>
#include <vector>
#include <cctype>
#include "grid.h"
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
#include "filelib.h"
using namespace std;

bool isNumber(string word) {
    int i = 0;
    int n = word.length();

    if  (n > 0 && word[i] == '-') {
        i++;
    }

    for (; i < n; i++) {
        if (!isdigit(word[i])) {
            return false;
        }
    }
    return true;
}
/*
 * Sum Numbers (Code Write)
 * ----------------------------------
 * Write a program to read through a given file and sum
 * all of the numbers in the file. You can assume that numbers
 * will be composed entirely of numerical digits, optionally
 * preceded by a single negative sign.
 */
int sumNumbers(string filename){
    ifstream inStream;

    if (!openFile(inStream, filename)) {
        return 0;
    }

    Vector<string> lines;
    readEntireFile(inStream, lines);

    int res = 0;
    for (string line : lines) {
        Vector<string> words = stringSplit(line, " ");
        for (string word : words) {
            if (isNumber(word)) {
                res += stringToInteger(word);
            }
        }
    }

    return res;
}


/* * * * * Provided Tests Below This Point * * * * */
PROVIDED_TEST("given file in handout"){
    EXPECT_EQUAL(sumNumbers("res/numbers.txt"), 42);
}

PROVIDED_TEST("Nonexistent file should sum to zero") {
    EXPECT_EQUAL(sumNumbers("nonexistent_filename"), 0);
}

