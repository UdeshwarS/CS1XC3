#include <stdio.h>
#include <limits.h>

int main(void)
{
    short int i, n;
    int max_n = 1;
    while ((max_n + 1) * (max_n + 1) <= SHRT_MAX)
    {
        max_n++;
    }
    printf("This program prints a table of squares.\n");

    printf("Valid range: 1 to %d\n", max_n);

    printf("Enter number of entries in table: ");
    scanf("%hd", &n);

    while (n < 1 || n > max_n)
    {
        printf("Error: value out of range. Please enter again.\n");
        printf("Enter number of entries in table: ");
        scanf("%hd", &n);
    }
    for (i = 1; i <= n; i++)
    {
        printf("%10hd%10hd\n", i, i * i);
    }

    return 0;
}