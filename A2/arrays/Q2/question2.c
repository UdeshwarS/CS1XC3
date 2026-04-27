#include <stdio.h>
#include <math.h>

int bubblesort(int *x, int size)
{
    int swaps = 0;

    for (int pass = 0; pass < size - 1; pass++)
    {
        for (int i = 0; i < size - 1 - pass; i++)
        {
            if (x[i] > x[i + 1])
            {
                int temp = x[i];
                x[i] = x[i + 1];
                x[i + 1] = temp;
                swaps++;
            }
        }
    }

    return swaps;
}

static void print_arr(int *x, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d", x[i]);
        if (i < size - 1)
        {
            printf(", ");
        }
    }
    printf("\n");
}

int main(void)
{
    int data1[] = {548, 845, 731, 258, 809, 522, 73, 385, 906, 891, 988, 289, 808, 128};
    int size1 = 14;

    int swaps1 = bubblesort(data1, size1);
    printf("swaps: %d\n", swaps1);
    print_arr(data1, size1);

    int data2[] = {100};
    int size2 = 1;

    int swaps2 = bubblesort(data2, size2);
    printf("swaps: %d\n", swaps2);
    print_arr(data2, size2);

    return 0;
}