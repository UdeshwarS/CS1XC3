#include "remove_dups.h"

void removeDups(int *arr, int n)
{
    int *curr = arr;
    int *end = arr + n;
    int *write = arr;

    while (curr < end)
    {
        int seen = 0;
        int *check = arr;

        while (check < write)
        {
            if (*check == *curr)
            {
                seen = 1;
                break;
            }
            check++;
        }

        if (!seen)
        {
            *write = *curr;
            write++;
        }

        curr++;
    }

    while (write < end)
    {
        *write = 0;
        write++;
    }
}