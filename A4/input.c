/* don't modify */
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include "input.h"
#include "config.h"

/* File-scope static: private to this module, persists for the lifetime
 * of the program. Stores the terminal's original settings so we can
 * restore them on exit. Nothing outside input.c can access this. */
static struct termios orig_termios;
static struct termios raw_termios;

void disable_raw_mode(void) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enable_raw_mode(void) {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disable_raw_mode);

    raw_termios = orig_termios;
    raw_termios.c_lflag &= ~(ECHO | ICANON);

    /* Start in non-blocking mode (gameplay default).
     * VTIME is in tenths of a second. SECONDS_PER_TICK converts it:
     * 0.3 seconds -> VTIME = 3. */
    raw_termios.c_cc[VMIN]  = 0;
    raw_termios.c_cc[VTIME] = (int)(SECONDS_PER_TICK * 10);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_termios);
}

void set_blocking(int blocking) {
    if (blocking) {
        raw_termios.c_cc[VMIN]  = 1;
        raw_termios.c_cc[VTIME] = 0;
    } else {
        raw_termios.c_cc[VMIN]  = 0;
        raw_termios.c_cc[VTIME] = (int)(SECONDS_PER_TICK * 10);
    }
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_termios);
}

KeyPress get_keypress(void) {
    char c;
    if (read(STDIN_FILENO, &c, 1) != 1) return KEY_UNKNOWN;

    switch (c) {
        case 'w': case 'W': return KEY_UP;
        case 's': case 'S': return KEY_DOWN;
        case 'a': case 'A': return KEY_LEFT;
        case 'd': case 'D': return KEY_RIGHT;
        case ' ':           return KEY_SPACE;
        case 'q': case 'Q': return KEY_QUIT;
        case '1':           return KEY_YES;
        case '2':           return KEY_NO;
        default:            return KEY_UNKNOWN;
    }
}

/* =======================================================================
 * INPUT_TEST
 * gcc -DINPUT_TEST input.c -o test_input && ./test_input
 * Interactive — run manually.
 * ======================================================================= */
#ifdef INPUT_TEST

static const char *keypress_name(KeyPress k) {
    switch (k) {
        case KEY_UP:      return "KEY_UP";
        case KEY_DOWN:    return "KEY_DOWN";
        case KEY_LEFT:    return "KEY_LEFT";
        case KEY_RIGHT:   return "KEY_RIGHT";
        case KEY_PAUSE:   return "KEY_PAUSE";
        case KEY_SPACE:   return "KEY_SPACE";
        case KEY_QUIT:    return "KEY_QUIT";
        case KEY_YES:     return "KEY_YES";
        case KEY_NO:      return "KEY_NO";
        case KEY_UNKNOWN: return "KEY_UNKNOWN";
        default:          return "???";
    }
}

int main(void) {
    enable_raw_mode();
    printf("=== input.c tests ===\n\n");

    printf("[ key recognition — blocking mode ]\n");
    const char *prompts[] = {
        "Press W : ", "Press S : ", "Press A : ", "Press D : ",
        "Press SPACE : ", "Press Q : ", "Press 1 : ", "Press 2 : ",
    };
    set_blocking(1);
    int n = sizeof(prompts) / sizeof(prompts[0]);
    for (int i = 0; i < n; i++) {
        printf("  %s", prompts[i]); fflush(stdout);
        printf("got %s\n", keypress_name(get_keypress()));
    }

    printf("\n[ timeout — non-blocking mode ]\n");
    printf("Don't press anything — KEY_UNKNOWN should fire 3 times:\n\n");
    set_blocking(0);
    int ticks = 0;
    while (ticks < 3) {
        if (get_keypress() == KEY_UNKNOWN)
            printf("  tick %d: KEY_UNKNOWN\n", ++ticks);
    }

    printf("\n[ non-blocking with input ]\n");
    printf("Press keys or wait — capturing 5 events:\n\n");
    int events = 0;
    while (events < 5) {
        KeyPress k = get_keypress();
        if (k == KEY_UNKNOWN)
            printf("  event %d: timeout\n", ++events);
        else
            printf("  event %d: %s\n", ++events, keypress_name(k));
        fflush(stdout);
    }

    printf("\n[ switch back to blocking ]\n");
    printf("Press any key: "); fflush(stdout);
    set_blocking(1);
    printf("got %s\n", keypress_name(get_keypress()));

    printf("\n=== Input test complete ===\n");
    return 0;
}

#endif /* INPUT_TEST */