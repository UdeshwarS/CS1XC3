#include <stdio.h>

int main(void)
{
    char counter = 0;

    while ((unsigned char)counter <= 200)
    {
        printf("%d\n", (unsigned char)counter);
        counter++;
    }

    return 0;
}