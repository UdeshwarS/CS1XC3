#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"


int main() {
    printf("Starting...\n");
    long *start = NULL;
    long *end = NULL;

    // Test 1: empty stack
    print_stack(start, end);
    assert(isEmpty(start, end) == 1);
    printf("Test 1 passed: isEmpty on empty stack\n\n");

    // Test 2: push values
    push(&start, &end, 1L); // the L suffix marks an integer literal as long rather than int. 
    print_stack(start, end);
    push(&start, &end, 2L);
    print_stack(start, end);
    push(&start, &end, 3L);
    print_stack(start, end);
    push(&start, &end, 4L);
    print_stack(start, end);
    push(&start, &end, 5L);
    print_stack(start, end);
    assert(isEmpty(start, end) == 0);
    assert(*(end - 1) == 5L);
    printf("Test 2 passed: pushed 1-5, top is 5\n\n");

    // Test 3: pop
    long val = pop(&start, &end);
    print_stack(start, end);
    assert(val == 5L);
    assert(*(end - 1) == 4L);
    printf("Test 3 passed: popped 5, top is 4\n\n");

    // Test 4: push after pop
    push(&start, &end, 6L);
    print_stack(start, end);
    assert(*(end - 1) == 6L);
    printf("Test 4 passed: pushed 6, top is 6\n\n");

    // Test 5: pop until empty
    pop(&start, &end);
    pop(&start, &end);
    pop(&start, &end);
    pop(&start, &end);
    pop(&start, &end);
    print_stack(start, end);
    assert(isEmpty(start, end) == 1);
    printf("Test 5 passed: stack is empty\n\n");

    return 0;
}

/***Expected Output:****

Starting...
Stack --> [ ]
Test 1 passed: isEmpty on empty stack

Stack --> [ 1 ]
Stack --> [ 1 2 ]
Stack --> [ 1 2 3 ]
Stack --> [ 1 2 3 4 ]
Stack --> [ 1 2 3 4 5 ]
Test 2 passed: pushed 1-5, top is 5

Stack --> [ 1 2 3 4 ]
Test 3 passed: popped 5, top is 4

Stack --> [ 1 2 3 4 6 ]
Test 4 passed: pushed 6, top is 6

Stack --> [ ]
Test 5 passed: stack is empty

**********************/