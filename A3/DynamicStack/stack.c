#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void print_stack(const long *start, const long *end)
{
    printf("Stack --> [ ");
    if (start != NULL && start != end)
    {
        for (const long *p = start; p < end; p++)
        {
            printf("%ld ", *p);
        }
    }
    printf("]\n");
}

int isEmpty(const long *start, const long *end)
{
    return start == NULL || end == NULL || start == end;
}

void push(long **start, long **end, long value)
{
    long size;
    long *new_start;

    if (isEmpty(*start, *end))
    {
        new_start = malloc(sizeof(long));
        if (new_start == NULL)
        {
            return;
        }

        *new_start = value;
        *start = new_start;
        *end = new_start + 1;
        return;
    }

    size = *end - *start;
    new_start = realloc(*start, (size + 1) * sizeof(long));
    if (new_start == NULL)
    {
        return;
    }

    *(new_start + size) = value;
    *start = new_start;
    *end = new_start + size + 1;
}

long pop(long **start, long **end)
{
    long size;
    long value;
    long *old_start;
    long *new_start;

    size = *end - *start;
    value = *(*end - 1);

    if (size == 1)
    {
        free(*start);
        *start = NULL;
        *end = NULL;
        return value;
    }

    old_start = *start;
    new_start = realloc(*start, (size - 1) * sizeof(long));

    if (new_start == NULL)
    {
        *start = old_start;
        *end = old_start + size - 1;
        return value;
    }

    *start = new_start;
    *end = new_start + size - 1;

    return value;
}