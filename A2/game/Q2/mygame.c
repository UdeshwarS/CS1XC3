#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
/* TODO:
Create your global constants for 8x8 world dimensions:
    R_BOUND, L_BOUND , T_BOUND, B_BOUND
*/

const int R_BOUND = 7;
const int L_BOUND = 0;
const int T_BOUND = 0;
const int B_BOUND = 7;

/* TODO:
Place your draw_screen implementation from question1.c
*/
void draw_screen(int player_x, int player_y)
{
    /*  DON'T REMOVE. This clears the terminal window.
        It should be called at the top of the function.
    */
    system("clear");

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
}

int main()
{

    /*  TODO: Create variables

    1. Create variables "player_x" and "player_y" with
        an appropriate datatype, to represent the
        player's initial starting point at (0, 0)
    2. Create bool variable "running" with the appropriate
        initial value for the game loop to function
    3. Create variable "input" using the appropriate
        datatype that will allow users to press 1 key
        to take an action
    */

    int player_x = 0;
    int player_y = 0;
    bool running = true;

    char input[256];

    /* TODO: Implement game loop

        The loop should include the following actions:

        - Display current state:
            - Call draw_screen() with the player's current position.
            - Print the player's coordinates: "Player position: (x, y)".
            - Prompt for input: "Input command (W/A/S/D to move, Q to quit) and hit enter:"
        - Get the user command through standard input.
            - Accepted movement commands: w/a/s/d, W/A/S/D
            - Accepted q/Q as user commands.
        - Update the game state using a switch statement.
            - Update player's position if within world boundaries
                w/W: Moves the player 1 pixel up.
                a/A: Moves the player 1 pixel left.
                s/S: Moves the player 1 pixel down.
                d/D: Moves the player 1 pixel right.
            - End game
                q/Q: Modify the variable that handles the loop condition.
                print "Game ended."
    */

    while (running)
    {

        draw_screen(player_x, player_y);
        printf("\n");
        printf("Player position: (%d, %d)\n", player_x, player_y);
        printf("Input command (W/A/S/D to move, Q to quit) and hit enter: ");

        scanf("%255s", input);

        for (int i = 0; input[i] != '\0'; i++)
        {
            switch (input[i])
            {

            case 'w':
            case 'W':
                if (player_y > T_BOUND)
                {
                    player_y--;
                }
                break;

            case 'a':
            case 'A':
                if (player_x > L_BOUND)
                {
                    player_x--;
                }
                break;

            case 's':
            case 'S':
                if (player_y < B_BOUND)
                {
                    player_y++;
                }
                break;

            case 'd':
            case 'D':
                if (player_x < R_BOUND)
                {
                    player_x++;
                }
                break;

            case 'q':
            case 'Q':
                running = false;
                break;

            default:
                break;
            }

            if (!running)
            {
                break;
            }
        }
    }

    draw_screen(player_x, player_y);
    printf("Game ended.\n");

    return 0;
}