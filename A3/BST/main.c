#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"
#include "bst.h"

int main() {
    // Part A: createStudent and printStudent 
    printf("=== Part A: createStudent and printStudent ===\n");
    Student *jenny  = createStudent(321,   "Jenny",  88.5);
    Student *paul   = createStudent(345,   "Paul",   72.0);
    Student *billy  = createStudent(2199,  "Billy",  95.0);
    Student *billie = createStudent(45601, "Billie", 60.5);
    Student *harry  = createStudent(934,   "Harry",  74.0);

    assert(jenny != NULL);
    assert(strcmp(jenny->name, "Jenny") == 0);
    assert(jenny->id == 321);
    assert(jenny->grade == 88.5f);
    printStudent(jenny);
    printStudent(paul);
    printf("Part A passed!\n\n");

    // Part B: insertionSort 
    printf("=== Part B: insertionSort ===\n");
    Student *arr[] = {jenny, paul, billy, billie};
    int n = 4;

    printf("Before sort:\n");
    for (Student **p = arr; p < arr + n; p++) printStudent(*p);

    insertionSort(arr, n);

    printf("After sort:\n");
    for (Student **p = arr; p < arr + n; p++) printStudent(*p);

    // verify alphabetical order
    assert(strcmp(arr[0]->name, "Billie") == 0);
    assert(strcmp(arr[1]->name, "Billy")  == 0);
    assert(strcmp(arr[2]->name, "Jenny")  == 0);
    assert(strcmp(arr[3]->name, "Paul")   == 0);
    printf("Part B passed!\n\n");

    // Part C: binarySearch 
    printf("=== Part C: binarySearch ===\n");
    // arr is now sorted from Part B

    Student *found = binarySearch(arr, n, "Jenny");
    assert(found != NULL);
    assert(strcmp(found->name, "Jenny") == 0);
    printf("Found: "); printStudent(found);

    Student *notFound = binarySearch(arr, n, "Harry");
    assert(notFound == NULL);
    printf("Search for Harry: NULL (not found)\n");
    printf("Part C passed!\n\n");

    // Part D: BST 
    printf("=== Part D: BST ===\n");
    BSTNode *root = NULL;
    root = bstInsert(root, jenny);
    root = bstInsert(root, paul);
    root = bstInsert(root, billie);
    root = bstInsert(root, billy);
    root = bstInsert(root, harry);

    printf("Inorder (alphabetical):\n");
    inorder(root);

    printf("\nPreorder (root first):\n");
    preorder(root);

    printf("\nPostorder (root last):\n");
    postorder(root);

    // verify inorder is sorted by checking root and traversal output
    assert(root->student == jenny);   // jenny inserted first = root
    assert(root->left != NULL);       // billie < jenny
    assert(root->right != NULL);      // paul > jenny
    printf("\nPart D passed!\n\n");

    // Cleanup 
    cleanup(root);

    // free memory
    free(jenny->name);  free(jenny);
    free(paul->name);   free(paul);
    free(billy->name);  free(billy);
    free(billie->name); free(billie);
    free(harry->name);  free(harry);

    printf("All tests passed!\n");
    return 0;
}