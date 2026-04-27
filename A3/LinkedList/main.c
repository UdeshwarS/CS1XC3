#include <stdio.h>
#include <assert.h>
#include "linked_list.h"

void check_list(Node *head, int *expected, int n) {
    Node *curr = head;
    for (int i = 0; i < n; i++) {
        assert(curr != NULL);
        assert(curr->value == expected[i]);
        curr = curr->next;
    }
    assert(curr == NULL);
}

int main() {
    // Test 1: insert
    Node *list = NULL;
    list = insert(list, 1);
    list = insert(list, 2);
    list = insert(list, 3);
    printf("After inserting 1, 2, 3:\n");
    print_list(list);
    int expected1[] = {3, 2, 1};
    check_list(list, expected1, 3);
    printf("Test 1 passed!\n\n");

    // Test 2: reverse
    list = reverse(list);
    printf("After reversing:\n");
    print_list(list);
    int expected2[] = {1, 2, 3};
    check_list(list, expected2, 3);
    printf("Test 2 passed!\n\n");

    // Test 3: duplicate_list
    Node *copy = duplicate_list(list);
    printf("Duplicate of [1 -> 2 -> 3]:\n");
    print_list(copy);
    check_list(copy, expected2, 3);
    assert(copy != list); // different list
    assert(copy->value == list->value); // same values
    printf("Test 3 passed!\n\n");

    // Test 4: add_lists (equal length)
    Node *list2 = NULL;
    list2 = insert(list2, 30);
    list2 = insert(list2, 20);
    list2 = insert(list2, 10);
    printf("list1: "); print_list(list);
    printf("list2: "); print_list(list2);
    add_lists(list, list2);
    printf("After add_lists:\n");
    print_list(list);
    int expected4[] = {11, 22, 33};
    check_list(list, expected4, 3);
    printf("Test 4 passed!\n\n");

    // Test 5: add_lists (unequal length)
    Node *short_list = NULL;
    short_list = insert(short_list, 20);
    short_list = insert(short_list, 10);
    printf("list1: "); print_list(list);
    printf("list2 (shorter): "); print_list(short_list);
    add_lists(list, short_list);
    printf("After add_lists with shorter list2:\n");
    print_list(list);
    int expected5[] = {21, 42, 33};  // third node unchanged
    check_list(list, expected5, 3);
    printf("Test 5 passed!\n\n");

    // cleanup
    free_list(list);
    free_list(list2);
    free_list(copy);
    free_list(short_list);

    return 0;
}