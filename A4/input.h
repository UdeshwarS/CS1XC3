/* don't modify */
#ifndef INPUT_H
#define INPUT_H

/*
 * input.h — Raw terminal input module.
 * Provided to students. Do not modify.
 *
 * Call enable_raw_mode() once at the start of your program.
 * Call set_blocking(0) for gameplay, set_blocking(1) for menus.
 * Use get_keypress() in your game loop.
 */

typedef enum {
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_SPACE,    /* space bar */
    KEY_QUIT,     /* q — pauses during gameplay, quits from pause menu */
    KEY_YES,      /* 1 — confirm prompts */
    KEY_NO,       /* 2 — confirm prompts */
    KEY_UNKNOWN   /* timeout elapsed with no input */
} KeyPress;

/* Switch the terminal to raw mode (single keypress, no echo).
 * Starts in non-blocking mode. Terminal is restored automatically on exit. */
void enable_raw_mode(void);

/* Restore terminal to original settings.
 * Called automatically on exit — you don't need to call this directly. */
void disable_raw_mode(void);

/* set_blocking(1): wait indefinitely for a keypress (use for menus).
 * set_blocking(0): return KEY_UNKNOWN after SECONDS_PER_TICK if no key
 *                  is pressed (use during gameplay). */
void set_blocking(int blocking);

/* Read one keypress. Returns KEY_UNKNOWN if the tick timeout elapsed. */
KeyPress get_keypress(void);

#endif /* INPUT_H */