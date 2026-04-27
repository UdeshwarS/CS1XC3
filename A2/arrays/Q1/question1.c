
#include <stdio.h>
#include <math.h>

double mean(int *x, int size);
double median(int *x, int size);
int mode(int *x, int size);

double mean(int *x, int size)
{
    long long sum = 0;

    for (int i = 0; i < size; i++)
    {
        sum += x[i];
    }

    return (double)sum / (double)size;
}

double median(int *x, int size)
{
    if (size % 2 == 1)
    {
        return (double)x[size / 2];
    }
    else
    {
        int left = x[(size / 2) - 1];
        int right = x[size / 2];
        return ((double)left + (double)right) / 2.0;
    }
}

int mode(int *x, int size)
{
    int best_value = x[0];
    int best_count = 1;

    int current_value = x[0];
    int current_count = 1;

    for (int i = 1; i < size; i++)
    {
        if (x[i] == current_value)
        {
            current_count++;
        }
        else
        {
            if (current_count > best_count)
            {
                best_count = current_count;
                best_value = current_value;
            }
            current_value = x[i];
            current_count = 1;
        }
    }

    if (current_count > best_count)
    {
        best_count = current_count;
        best_value = current_value;
    }

    return best_value;
}

int main()
{

    // Test case 1: Odd number of elements
    int data1[] = {1, 2, 3, 4, 5};
    int size1 = 5;

    printf("Mean: %.2f\n", mean(data1, size1));
    printf("Median: %.2f\n", median(data1, size1));

    // Test case 2: Even number of elements
    int data2[] = {1, 2, 3, 4, 5, 6};
    int size2 = 6;

    printf("Mean: %.2f\n", mean(data2, size2));
    printf("Median: %.2f\n", median(data2, size2));

    // Test case 3: Mode example
    int data3[] = {1, 2, 2, 3, 4};
    int size3 = 5;

    printf("Mode: %d\n", mode(data3, size3));

    return 0;
}