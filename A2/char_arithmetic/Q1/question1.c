#include <stdio.h>

int main()
{
    /* TODO
        - write a for-loop that prints: abcdefghijklmnopqrstuvwxyz
        - integer literals are NOT allowed:
            i + 1 is not allowed because 1 is an integer literal
        - char is NOT allowed:
            char a = 'a' is not allowed. No char.
    */

    for (int i = 'a'; i <= 'z'; i++)
    {
        printf("%c", i);
    }

    printf("\n");
}