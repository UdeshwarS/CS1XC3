#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "strings.h"

int main() {
    // Test 1: isDigit
    assert(isDigit('5') == true);
    assert(isDigit('a') == false);
    assert(isDigit('+') == false);
    assert(isDigit('0') == true);
    assert(isDigit('9') == true);
    printf("Test 1 passed: isDigit\n");

    // Test 2: str2int basic
    assert(str2int("123") == 123);
    assert(str2int("0") == 0);
    printf("Test 2 passed: str2int basic\n");

    // Test 3: str2int with signs
    assert(str2int("-45") == -45);
    assert(str2int("+7") == 7);
    printf("Test 3 passed: str2int with signs\n");

    // Test 4: str2int invalid
    assert(str2int("abc") == 0);
    assert(str2int("12a") == 0);
    printf("Test 4 passed: str2int invalid input\n");

    // Test 5: evaluate basic
    char e1[] = "123+456";
    char e2[] = "100-42";
    char e3[] = "6*7";
    assert(evaluate(e1) == 579);
    assert(evaluate(e2) == 58);
    assert(evaluate(e3) == 42);
    printf("Test 5 passed: evaluate basic\n");

    // Test 6: evaluate with negative operands
    char e4[] = "-12+4";
    char e5[] = "-3*5";
    assert(evaluate(e4) == -8);
    assert(evaluate(e5) == -15);
    printf("Test 6 passed: evaluate with negatives\n");

    printf("\nAll tests passed!\n");
    return 0;
}