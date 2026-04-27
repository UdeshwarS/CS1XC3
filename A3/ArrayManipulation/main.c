#include <stdio.h>
#include <assert.h>
#include "remove_dups.h"
#include "helpers.h"

void check(int *arr, int *expected, int n) {
    for (int i = 0; i < n; i++) {
        assert(arr[i] == expected[i]);
    }
}

int main() {
    int arr1[] = {1,2,2,2,3,3,4,2,4,5,6,6};
    int expected1[] = {1,2,3,4,5,6,0,0,0,0,0,0};

    printf("Input : "); print_array(arr1, 12);

    removeDups(arr1, 12);
    printf("\nOutput: "); print_array(arr1, 12); printf("\n");

    check(arr1, expected1, 12);
    printf("Test 1 passed!\n\n");
    
    return 0;
}