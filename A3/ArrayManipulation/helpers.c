#include <stdio.h>
#include "helpers.h"

void print_array(int *data, int len)
{
    printf("{");
    for (int i = 0; i < len - 1; i++)
    {
        printf("%d,", data[i]);
    }
    printf("%d}", data[len - 1]);
}