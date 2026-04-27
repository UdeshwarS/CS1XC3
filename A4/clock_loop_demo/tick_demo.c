#include <stdio.h>
#include "../input.h" /* for demo purposes I'm using the relative path :) */
#define COLS 38
#define FAST_SPEED 1   /* moves every tick */
#define SLOW_SPEED 3   /* moves every 3 ticks */

int main(void) {
    enable_raw_mode();
    set_blocking(0);

    int fast_col = 0;
    int slow_col = 0;
    int fast_dir = 1;
    int slow_dir = 1;
    int tick_count = 0;

    while (get_keypress() != KEY_QUIT) {

        printf("\033[3J\033[H\033[2J\n");

        /*
         * DRAW
         */
        // row for FAST sprite
        putchar('#');
        for (int col = 0; col < COLS; col++) {
            putchar(col == fast_col ? 'F' : '.');
        }
        printf("#  fast (moves every %d tick)\n", FAST_SPEED);

        // row for SLOW sprite
        putchar('#');
        for (int col = 0; col < COLS; col++) {
            putchar(col == slow_col ? 'S' : '.');
        }
        printf("#  slow (moves every %d ticks)\n", SLOW_SPEED);

        printf("\nPress Q to quit.\n");
        fflush(stdout);


        /*
         * UPDATE GAME STATE
         */
        tick_count++;

        /* F moves every FAST_SPEED ticks */
        if (tick_count % FAST_SPEED == 0) {
            fast_col += fast_dir;
            if (fast_col <= 0 || fast_col >= COLS - 1)
                fast_dir = -fast_dir;
        }

        /* S moves every SLOW_SPEED ticks. */
        if (tick_count % SLOW_SPEED == 0) {
            slow_col += slow_dir;
            if (slow_col <= 0 || slow_col >= COLS - 1)
                slow_dir = -slow_dir;
        }
    }

    printf("\033[H\033[2JDone.\n");
    return 0;
}