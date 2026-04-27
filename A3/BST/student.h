#ifndef STUDENT_H
#define STUDENT_H

#include <stdbool.h>

typedef struct {
    int id;
    char *name;
    float grade;
} Student;

Student *createStudent(int id, char *name, float grade);
void printStudent(Student *s);
void insertionSort(Student **arr, int n);
Student *binarySearch(Student **arr, int n, char *target);

#endif