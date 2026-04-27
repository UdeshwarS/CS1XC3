#include <stdio.h>

int main(void)
{
    int row;
    int col;

    for (row = 0; row < 8; row++)
    {
        for (col = 0; col < 8; col++)
        {

            if ((row + col) % 2 == 0)
            {
                printf("X");
            }
            else
            {
                printf("O");
            }

            if (col < 7)
            {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}