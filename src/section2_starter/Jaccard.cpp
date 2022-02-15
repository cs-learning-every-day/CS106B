/*
 * CS106B Section Handout Test Harness: Section 2
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified for Qt and Ed by Neel
 * Kishnani for Winter 2022.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include "testing/SimpleTest.h"
#include "set.h"
#include "filelib.h"
#include "simpio.h"
#include "tokenscanner.h"
#include "queue.h"
using namespace std;

string queueToString(Queue<string> q) {
    string result = "";
    while (!q.isEmpty()) {
        if (result != "") result += " ";
        result += q.dequeue();
    }
    return result;
}

Set<string> kGramsIn(istream& input, int k) {
    if (k <= 0) error("k must be positive");

    Set<string> res;
    TokenScanner scanner(input);
    scanner.addWordCharacters("'");

    Queue<string> q;

    while (scanner.hasMoreTokens()) {
        string token = scanner.nextToken();
        if (scanner.getTokenType(token) == TokenScanner::TokenType::WORD) {
            q.enqueue(token);

            if (q.size() == k){
                res.add(queueToString(q));
                (void) q.dequeue();
            }
        }
    }

    return res;
}

/*
 * See Stanford library's promptUserForFile function to get
 * a file into a stream format:
 * https://web.stanford.edu/dept/cs_edu/resources/cslib_docs/filelib.html#Function:promptUserForFile
 */
Set<string> wordsIn(istream& input) {
    return kGramsIn(input, 1);
}

Set<string> contentsOfUserFileChoice(int k) {
    ifstream input;
    // res/EnglishWords.txt
    promptUserForFile(input, "Enter filename: ");
    return kGramsIn(input, k);
}

int chooseKGramSize() {
    while (true) {
        int result = getInteger("Enter K: ");
        if (result > 0) {
            return result;
        }
        cout << "Please enter a positive integer" << endl;
    }
}

STUDENT_TEST("basic test\n") {
    EXPECT_EQUAL(queueToString({"A", "B"}), "A B");

    int k = chooseKGramSize();
    Set<string> s1 = contentsOfUserFileChoice(k);
    Set<string> s2 = contentsOfUserFileChoice(k);

    /* Compute |S1 n S2| and |S1 u S2| using the overloaded * and + operators. */
    double intersectSize = (s1 * s2).size();
    double unionSize     = (s1 + s2).size();

    cout << "Jaccard similarity: " << intersectSize / unionSize << endl;
}
