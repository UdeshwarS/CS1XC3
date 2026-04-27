#ifndef CONFIG_H
#define CONFIG_H

/*
 * config.h — Game configuration.
 *
 * All tunable constants live here. Students should feel free to
 * experiment with these values during development.
 */

/* -----------------------------------------------------------------------
 * Timing
 * All values are in seconds.
 * ----------------------------------------------------------------------- */

/* How often enemies move and the clock updates.
 * Lower = faster enemies. Higher = slower, more forgiving. */
#define SECONDS_PER_TICK    0.3

/* How long the player is invincible (and flashing) after a hit. */
#define INVINCIBLE_SECONDS  3.0

/* How long "LEVEL CLEAR!" stays on screen before the next level loads. */
#define LEVEL_CLEAR_PAUSE   0.8

/* How long "HIT!" stays on screen before the player respawns. */
#define HIT_PAUSE           0.6

/* -----------------------------------------------------------------------
 * Game rules
 * ----------------------------------------------------------------------- */

/* Number of lives the player starts with. */
#define STARTING_LIVES      3

/* How many steps an enemy walks in one direction before turning.
 * Each level reduces the max by 1, making enemies more erratic. */
#define ENEMY_MIN_STEPS     3
#define ENEMY_MAX_STEPS     8



/* -----------------------------------------------------------------------
 * Scores
 * ----------------------------------------------------------------------- */

#define SCORES_FILE         "scores.csv"
#define SCORES_DISPLAY      5       /* entries shown on the start screen */
#define DATE_LEN            20      /* "YYYY-MM-DD HH:MM:SS\0" */

/* -----------------------------------------------------------------------
 * Display
 * ----------------------------------------------------------------------- */

/* ANSI escape: clear scrollback, move cursor home, then erase screen.
 * \033[3J clears the scrollback buffer — prevents the top of the screen
 * from being cut off in some terminals (e.g. VSCode).
 *
 * Note: an alternative approach is to use \033[H (cursor home without
 * erasing) and overwrite the previous frame character by character. This
 * avoids the brief blank flash between frames. It only works correctly
 * when every frame is guaranteed to be the same size — see reflection
 * question 8 for a discussion of the tradeoffs. */
#define CLEAR_SCREEN "\033[3J\033[H\033[2J"

#endif /* CONFIG_H */