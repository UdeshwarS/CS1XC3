#include <stdio.h>
#include <unistd.h>   /* for usleep */

#define COLS 38
#define SECONDS_PER_TICK 0.3 /* TRY DIFFERENT VALUES HERE */
#define DELAY (unsigned int)(1000000 * SECONDS_PER_TICK)

int main(void) {
    int col = 0;
    int direction = 1;

    do {
        /* DRAW (render the screen) */
        printf("#");
        for (int i = 0; i < COLS; i++)
            putchar(i == col ? 'M' : '.');
        printf("#\n");
        printf("Ctrl+C to quit\n");
        fflush(stdout);
        printf("\033[2A");// moves cursor up to overwrite frame.

        /* UPDATE POSITION */
        col += direction;
        if (col <= 0 || col >= COLS - 1)
            direction = -direction;

        /* WAIT ONE TICK 
         * usleep pauses the program for 
         * a given number of microseconds
         */
        usleep(DELAY);
        
    } while (1);
}