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

bool help(const string &s, int i, const string& p, int j) {
    if (j == p.size() && i == s.size()) {
        return true;
    }

    if (j > p.size() || i > s.size()) {
        return false;
    }

    if (p[j] == '?') {
        return help(s, i, p, j + 1) ||
                help(s, i + 1, p, j + 1);
    } else if (p[j] == '.') {
        return help(s, i + 1, p, j + 1);
    } else if (p[j] == '*') {
        bool res = false;
        for (int k = 0; k < s.size(); k++) {
            res |= help(s, i + k, p, j + 1);
        }
        return res;
    } else {
        if (s[i] != p[j]) {
            return false;
        }
        return help(s, i + 1, p, j + 1);
    }
}
/*
 * Function: matches
 * ------------------
 * Your task is to write a function that takes as input a
 * string and a pattern, then returns whether that string
 * matches the pattern.
 */
bool matches(const string& text, const string& pattern) {
    // 暴搜
//    return help(text, 0, pattern, 0);
    // DP
    int m = text.size(), n = pattern.size();
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));
    dp[0][0] = true;

    string s = " " + text, p = " " + pattern;
    for (int i = 0; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (p[j] == '.') {
                dp[i][j] = i > 0 && dp[i - 1][j - 1];
            } else if (p[j] == '?') {
                dp[i][j] = dp[i][j - 1] || (i > 0 && dp[i - 1][j - 1]);
            } else if (p[j] == '*') {
                // 使用d[i][j - 1] 来优化
                dp[i][j] = (i > 0 && dp[i - 1][j]) || dp[i][j - 1];
//                for (int k = 0; k <= i; k++) {
//                    dp[i][j] = dp[i][j] || dp[i - k][j - 1];
//                }
            } else {
                if (i > 0) dp[i][j] = (s[i] == p[j]) && dp[i - 1][j - 1];
                else dp[i][j] = (s[i] == p[j]);
            }
        }
    }
    return dp[m][n];
}


/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("Provided Test: Testing *") {
    EXPECT_EQUAL(matches("apple", "a*"), true);
    EXPECT_EQUAL(matches("apply", "a*"), true);
    EXPECT_EQUAL(matches("apoplexy", "a*"), true);
    EXPECT_EQUAL(matches("Amicus", "a*"), false);
    EXPECT_EQUAL(matches("banana", "a*"), false);
}

PROVIDED_TEST("Provided Test: Testing .") {
    EXPECT_EQUAL(matches("three", "th..."), true);
    EXPECT_EQUAL(matches("threshold", "th..."), false);
}

PROVIDED_TEST("Provided Test: Testing ?") {
    EXPECT_EQUAL(matches("color", "colo?r"), true);
    EXPECT_EQUAL(matches("colour", "colo?r"), true);
    EXPECT_EQUAL(matches("colouxr", "colo?r"), false);
}
