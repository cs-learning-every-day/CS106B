/* File: OnlyConnect.cpp
 *
 * TODO: Edit these comments to describe anything interesting or noteworthy in your implementation.
 *
 * TODO: Edit these comments to leave a puzzle for your section leader to solve!
 */
#include "OnlyConnect.h"
#include "Testing/OnlyConnectTests.h"
#include "strlib.h"
#include <cctype>


using namespace std;

const string CONSONANTS = "aeiou";

bool isConsonant(char c) {
    if (!isalpha(c)) return true;

    c = toLowerCase(c);
    if (CONSONANTS.find(c) == string::npos) {
        return false;
    }
    return true;
}

string onlyConnectize(string phrase) {
    /* The next few lines just exist to make sure you don't get compiler warning messages
     * when this function isn't implemented. Delete these lines, then implement this function.
     */
    if (phrase == "" || phrase.size() == 0) {
        return "";
    }

    if (isConsonant(phrase[0])) {
        return onlyConnectize(phrase.substr(1));
    }

    return charToString(toUpperCase(phrase[0])) + onlyConnectize(phrase.substr(1));
}


/* * * * * * Test Cases * * * * * */

ADD_TEST("Converts lower-case to upper-case.") {
    EXPECT_EQUAL(onlyConnectize("lowercase"), "LWRCS");
    EXPECT_EQUAL(onlyConnectize("uppercase"), "PPRCS");
}

ADD_TEST("Handles non-letter characters properly.") {
    EXPECT_EQUAL(onlyConnectize("2.718281828459045"), "");
    EXPECT_EQUAL(onlyConnectize("'Hi, Mom!'"), "HMM");
}

ADD_TEST("Handles single-character inputs.") {
    EXPECT_EQUAL(onlyConnectize("A"), "");
    EXPECT_EQUAL(onlyConnectize("+"), "");
    EXPECT_EQUAL(onlyConnectize("Q"), "Q");
}

ADD_TEST("Big Test.") {
    EXPECT_EQUAL(onlyConnectize("123123123123213123ae3414134341431321i123123123o123123124124123123u123123123123a123123123u"), "");
}
/* TODO: You will need to add your own tests into this suite of test cases. Think about the sorts
 * of inputs we tested here, and, importantly, what sorts of inputs we *didn't* test here. Some
 * general rules of testing:
 *
 *    1. Try extreme cases. What are some very large cases to check? What are some very small cases?
 *
 *    2. Be diverse. There are a lot of possible inputs out there. Make sure you have tests that account
 *       for cases that aren't just variations of one another.
 *
 *    3. Be sneaky. Don't just try standard inputs. Try weird ones that you wouldn't expect anyone to
 *       actually enter, but which are still perfectly legal.
 *
 * Happy testing!
 */






