#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
/* TODO: Create your global constants
    for the world dimensions:

    1. R_BOUND (right boundary - try 7)
    2. L_BOUND (left boundary - try 0)
    3. T_BOUND (top boundary - try 0)
    4. B_BOUND (bottom boundary - try 7)

    This creates an 8x8 world (0-7 in each direction)
*/

const int R_BOUND = 7;
const int L_BOUND = 0;
const int T_BOUND = 0;
const int B_BOUND = 7;

/* TODO: Implement function to "draw" game state
    by printing the `.` and `P` characters

    hints:
    - Use a nested for-loop to iterate over world
    - Determine which char to print at each position
    - Don't forget newlines at the end of each row
*/
void draw_screen(int player_x, int player_y)
{
    for (int y = T_BOUND; y <= B_BOUND; y++)
    {
        for (int x = L_BOUND; x <= R_BOUND; x++)
        {
            if (x == player_x && y == player_y)
            {
                printf("P");
            }
            else
            {
                printf(".");
            }
        }
        printf("\n");
    }
    return;
}

/* TODO: Create your own test cases to
         make sure your function works

    Example:
    printf("Test 1: Player at (0,0)\n");
    draw_screen(0, 0);

    Compare your output to the expected pattern.
    Does the 'P' appear in the correct position?

    This part is not graded, but it is
    important to test your code before
    submitting. Your function will be
    graded using test cases like these.
*/
int main(void)
{
    printf("Test 1: Player at (0,0)\n");
    draw_screen(0, 0);
    printf("\n"); /* blank line between tests */

    printf("Test 2: Player at (3,2)\n");
    draw_screen(3, 2);
    printf("\n");

    printf("Test 3: Player at (7,7)\n");
    draw_screen(7, 7);

    return 0;
}