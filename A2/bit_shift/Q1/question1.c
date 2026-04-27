/*
Write a C program that implements two functions:

1. `int multiplyBy8(int n)` - multiplies an integer by 8 using left bitshift instead of the `*` operator
2. `int divideBy4(int n)` - divides an integer by 4 using right bitshift instead of the `/` operator

Your `main()` function should:

- Prompt the user to enter an integer with `"Enter an integer: "`
- You may use scanf
- Print the multiplication and division expressions with their results, as in:

    `input * 8 = result`

    `input / 4 = result`
*/

#include <stdio.h>
int multiplyBy8(int n)
{
    return n << 3;
}

int divideBy4(int n)
{
    return n >> 2;
}

int main(void)
{
    int input;

    printf("Enter an integer: ");
    scanf("%d", &input);

    printf("%d * 8 = %d\n", input, multiplyBy8(input));
    printf("%d / 4 = %d\n", input, divideBy4(input));

    return 0;
}