#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

static Student *binarySearchRange(Student **left, Student **right, char *target)
{
    Student **mid;
    int cmp;

    if (left > right)
    {
        return NULL;
    }

    mid = left + (right - left) / 2;
    cmp = strcmp((*mid)->name, target);

    if (cmp == 0)
    {
        return *mid;
    }

    if (cmp > 0)
    {
        return binarySearchRange(left, mid - 1, target);
    }

    return binarySearchRange(mid + 1, right, target);
}

Student *createStudent(int id, char *name, float grade)
{
    Student *s = malloc(sizeof(Student));

    if (s == NULL)
    {
        return NULL;
    }

    s->name = malloc((strlen(name) + 1) * sizeof(char));
    if (s->name == NULL)
    {
        free(s);
        return NULL;
    }

    strcpy(s->name, name);
    s->id = id;
    s->grade = grade;

    return s;
}

void printStudent(Student *s)
{
    if (s != NULL)
    {
        printf("ID: %d Name: %s Grade: %.1f\n", s->id, s->name, s->grade);
    }
}

void insertionSort(Student **arr, int n)
{
    Student **i = arr + 1;

    while (i < arr + n)
    {
        Student *key = *i;
        Student **j = i;

        while (j > arr && strcmp((*(j - 1))->name, key->name) > 0)
        {
            *j = *(j - 1);
            j--;
        }

        *j = key;
        i++;
    }
}

Student *binarySearch(Student **arr, int n, char *target)
{
    if (n <= 0)
    {
        return NULL;
    }

    return binarySearchRange(arr, arr + n - 1, target);
}