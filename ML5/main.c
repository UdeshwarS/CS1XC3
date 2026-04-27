#include <stdio.h>
#include "BubbleSort.h"
#include "SelectionSort.h"

#define N 5

static void print_array(const char *label, const int *a, int n) {
    printf("%s: [", label);
    for (int i = 0; i < n; i++) {
        printf("%d%s", a[i], i + 1 < n ? ", " : "");
    }
    printf("]\n");
}

int main(void) {
    const int arr[N] = {64, 25, 12, 22, 11};
    int a[N];

    for (int i = 0; i < N; i++) {
        a[i] = arr[i];
    }
    print_array("Sort", a, N);
    bubble_sort(a, N);
    print_array("After bubble sort (BubbleSort.h)", a, N);

    for (int i = 0; i < N; i++) {
        a[i] = arr[i];
    }
    print_array("Sort", a, N);
    selection_sort(a, N);   
    print_array("After selection sort (SelectionSort.h)", a, N);

    printf("Lab run finished successfully.\n");
    return 0;
}
