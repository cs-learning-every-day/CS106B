#include "testing/SimpleTest.h"

int factorial(int num);

int factorial(int num) {
    if (num == 0) return 1;
    return num * factorial(num - 1);
}


PROVIDED_TEST("Some provided tests.") {
    EXPECT_EQUAL(factorial(1), 1);
    EXPECT_EQUAL(factorial(3), 6);
    EXPECT_EQUAL(factorial(4), 24);
}
