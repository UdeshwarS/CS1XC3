#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "config.h"
#include "types.h"
#include "board.h"
#include "player.h"
#include "enemy.h"
#include "scores.h"
#include "input.h"

/* -----------------------------------------------------------------------
 * g_level — current level number.
 * Defined here (main.c) and accessed in enemy.c via 'extern int g_level'
 * to scale enemy difficulty. This is the extern storage class in practice.
 * ----------------------------------------------------------------------- */
int g_level = 1;

/* -----------------------------------------------------------------------
 * Game states
 * ----------------------------------------------------------------------- */
typedef enum
{
    STATE_START,
    STATE_PLAYING,
    STATE_PAUSED,
    STATE_LEVEL_UP,
    STATE_GAME_OVER,
    STATE_WIN,
    STATE_QUIT
} GameState;

/* -----------------------------------------------------------------------
 * current_time: wall-clock seconds. Used for enemy tick timing.
 * ----------------------------------------------------------------------- */
static double current_time(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

/* -----------------------------------------------------------------------
 * flash_on: returns 1 or 0, alternating every 0.1 seconds.
 * Used to make the player blink while invincible.
 * ----------------------------------------------------------------------- */
static int flash_on(void)
{
    return (int)(current_time() / 0.1) % 2 == 0;
}

/* -----------------------------------------------------------------------
 * render
 *
 * The board holds only static tiles. Entities are layered on top here —
 * this is the ONLY place in the codebase that draws 'P' or 'M'.
 *
 * Render order (highest priority first):
 *   1. Player — drawn as 'P', or '.' when flashing during invincibility
 *   2. Enemies — drawn as 'M'
 *   3. Static tile from the board
 * ----------------------------------------------------------------------- */
static void render(const Board *board, const Player *player,
                   const Enemy *enemies, int num_enemies,
                   time_t start_time)
{
    int row;
    int col;

    /* HUD */
    int elapsed = (int)(time(NULL) - start_time);
    printf("Lives: %d  |  Level: %d  |  Time: %dm%02ds\n",
           player->lives, g_level, elapsed / 60, elapsed % 60);
    printf("-----------------------------------------\n");

    /* Board + entities */
    for (row = 0; row < board->rows; row++)
    {
        for (col = 0; col < board->cols; col++)
        {
            char tile = get_tile(board, row, col);

            if (row == player->pos.row && col == player->pos.col)
            {
                /* Player: blink when invincible */
                tile = (is_invincible(player) && !flash_on()) ? '.' : 'P';
            }
            else
            {
                int i;

                /* Check if any enemy is here */
                for (i = 0; i < num_enemies; i++)
                {
                    if (enemies[i].pos.row == row &&
                        enemies[i].pos.col == col)
                    {
                        tile = 'M';
                        break;
                    }
                }
            }
            putchar(tile);
        }
        putchar('\n');
    }
    fflush(stdout);
}

/* -----------------------------------------------------------------------
 * translate_key: convert a KeyPress to a Direction.
 * Returns 1 if the key was a movement key, 0 otherwise.
 * ----------------------------------------------------------------------- */
static int translate_key(KeyPress k, Direction *dir)
{
    switch (k)
    {
    case KEY_UP:
        *dir = DIR_UP;
        return 1;
    case KEY_DOWN:
        *dir = DIR_DOWN;
        return 1;
    case KEY_LEFT:
        *dir = DIR_LEFT;
        return 1;
    case KEY_RIGHT:
        *dir = DIR_RIGHT;
        return 1;
    default:
        return 0;
    }
}

/* -----------------------------------------------------------------------
 * cleanup: free all heap-allocated game objects.
 * ----------------------------------------------------------------------- */
static void cleanup(Board **board, Enemy **enemies)
{
    free_board(board);

    if (enemies != NULL && *enemies != NULL)
    {
        free(*enemies);
        *enemies = NULL;
    }
}

/* -----------------------------------------------------------------------
 * check_achievements: compare a run against the existing scoreboard
 * and set flags for new achievements. Load scoreboard BEFORE saving.
 * ----------------------------------------------------------------------- */
static void check_achievements(const ScoreBoard *sb,
                               int levels_cleared, int elapsed,
                               int completed,
                               int *new_high_score, int *fastest_time)
{
    int i;
    int best_completed_time;

    *new_high_score = 0;
    *fastest_time = 0;

    if (sb == NULL || sb->entries == NULL || sb->count == 0)
    {
        *new_high_score = 1;
        if (completed)
        {
            *fastest_time = 1;
        }
        return;
    }

    if (completed > sb->entries[0].completed)
    {
        *new_high_score = 1;
    }
    else if (completed == sb->entries[0].completed)
    {
        if (levels_cleared > sb->entries[0].levels_cleared)
        {
            *new_high_score = 1;
        }
        else if (levels_cleared == sb->entries[0].levels_cleared &&
                 elapsed < sb->entries[0].elapsed_seconds)
        {
            *new_high_score = 1;
        }
    }

    if (!completed)
    {
        return;
    }

    best_completed_time = -1;
    for (i = 0; i < sb->count; i++)
    {
        if (sb->entries[i].completed)
        {
            if (best_completed_time == -1 ||
                sb->entries[i].elapsed_seconds < best_completed_time)
            {
                best_completed_time = sb->entries[i].elapsed_seconds;
            }
        }
    }

    if (best_completed_time == -1 || elapsed < best_completed_time)
    {
        *fastest_time = 1;
    }
}

/* -----------------------------------------------------------------------
 * Screen functions
 * ----------------------------------------------------------------------- */
static GameState show_start_screen(void)
{
    ScoreBoard sb;
    KeyPress key;

    set_blocking(1);

    while (1)
    {
        printf(CLEAR_SCREEN);
        printf("=========================================\n");
        printf("           TERMINAL RUN\n");
        printf("=========================================\n\n");
        printf("Reach X to clear the level.\n");
        printf("Avoid M enemies.\n");
        printf("T = tree, L = lake, . = empty tile\n\n");

        sb = load_scores();
        print_scoreboard(&sb);
        free_scoreboard(&sb);

        printf("\n");
        printf("1 = Start game\n");
        printf("2 = Quit\n");
        printf("\nChoose an option: ");
        fflush(stdout);

        key = get_keypress();
        if (key == KEY_YES)
        {
            return STATE_PLAYING;
        }
        if (key == KEY_NO || key == KEY_QUIT)
        {
            return STATE_QUIT;
        }
    }
}

static GameState show_pause_screen(void)
{
    KeyPress key;

    set_blocking(1);

    while (1)
    {
        printf(CLEAR_SCREEN);
        printf("=========== PAUSED ===========\n\n");
        printf("1 = Resume\n");
        printf("2 = Quit to main menu\n");
        printf("q = Exit program\n");
        printf("\nChoose an option: ");
        fflush(stdout);

        key = get_keypress();
        if (key == KEY_YES)
        {
            return STATE_PLAYING;
        }
        if (key == KEY_NO)
        {
            return STATE_START;
        }
        if (key == KEY_QUIT)
        {
            return STATE_QUIT;
        }
    }
}

static void show_level_up_screen(void)
{
    struct timespec ts;

    printf(CLEAR_SCREEN);
    printf("Loading level %d...\n", g_level);
    fflush(stdout);

    ts.tv_sec = 0;
    ts.tv_nsec = (long)(LEVEL_CLEAR_PAUSE * 1e9);
    nanosleep(&ts, NULL);
}

static void show_hit_screen(int lives, time_t start_time)
{
    printf(CLEAR_SCREEN);
    printf("  *** HIT! ***\n\n  Lives remaining: %d\n", lives);
    (void)start_time;
    fflush(stdout);
    struct timespec ts = {0, (long)(HIT_PAUSE * 1e9)};
    nanosleep(&ts, NULL);
}

static void show_game_over_screen(int levels_cleared,
                                  time_t start_time,
                                  int new_high_score)
{
    KeyPress key;
    int elapsed = (int)(time(NULL) - start_time);

    set_blocking(1);

    while (1)
    {
        printf(CLEAR_SCREEN);
        printf("=========== GAME OVER ===========\n\n");
        printf("Levels cleared: %d\n", levels_cleared);
        printf("Time survived:  %dm%02ds\n", elapsed / 60, elapsed % 60);

        if (new_high_score)
        {
            printf("\nNew high score!\n");
        }

        printf("\n1 = Return to main menu\n");
        fflush(stdout);

        key = get_keypress();
        if (key == KEY_YES || key == KEY_QUIT || key == KEY_NO)
        {
            return;
        }
    }
}

static void show_win_screen(int levels_cleared,
                            time_t start_time,
                            int new_high_score,
                            int fastest_time)
{
    KeyPress key;
    int elapsed = (int)(time(NULL) - start_time);

    set_blocking(1);

    while (1)
    {
        printf(CLEAR_SCREEN);
        printf("============= YOU WIN =============\n\n");
        printf("Levels cleared: %d\n", levels_cleared);
        printf("Completion time: %dm%02ds\n", elapsed / 60, elapsed % 60);

        if (new_high_score)
        {
            printf("\nNew high score!\n");
        }
        if (fastest_time)
        {
            printf("Fastest completion time!\n");
        }

        printf("\n1 = Return to main menu\n");
        fflush(stdout);

        key = get_keypress();
        if (key == KEY_YES || key == KEY_QUIT || key == KEY_NO)
        {
            return;
        }
    }
}

/* -----------------------------------------------------------------------
 * load_level: load a board from the level file for g_level.
 * Returns NULL if the file doesn't exist (signals end of levels).
 * ----------------------------------------------------------------------- */
static Board *load_level(void)
{
    char filename[64];

#ifdef EXTRA_CREDIT
    if (g_level > 7)
    {
        return NULL;
    }
#else
    if (g_level > 5)
    {
        return NULL;
    }
#endif

    snprintf(filename, sizeof(filename), LEVEL_FILE_FORMAT, g_level);
    return load_board(filename);
}
/* -----------------------------------------------------------------------
 * main: don't modify (unless using conditional compilation for extra credit)
 * ----------------------------------------------------------------------- */
int main(void)
{
    enable_raw_mode();

    auto GameState state = STATE_START; /* auto: local, stack, destroyed on return */
    Board *board = NULL;
    Enemy *enemies = NULL;
    Player player;
    time_t start_time = 0;

    /* Track when enemies last moved for time-based movement.
     * Enemies move at SECONDS_PER_TICK regardless of player input. */
    double next_enemy_move = 0.0;

    while (state != STATE_QUIT)
    {

        /* ----------------------------------------------------------------
         * START SCREEN
         * ---------------------------------------------------------------- */
        if (state == STATE_START)
        {
            cleanup(&board, &enemies);
            g_level = 1;
            state = show_start_screen();

            if (state == STATE_PLAYING)
            {
                board = load_level();
                if (!board)
                {
                    fprintf(stderr, "Could not load level 1\n");
                    state = STATE_QUIT;
                    break;
                }
                player = init_player(board);
                enemies = init_enemies(board);
                start_time = time(NULL);
                next_enemy_move = current_time() + SECONDS_PER_TICK;
                set_blocking(0);
            }
        }

        /* ----------------------------------------------------------------
         * PLAYING
         * ---------------------------------------------------------------- */
        else if (state == STATE_PLAYING)
        {

            /* Render — clear screen and redraw every frame. */
            printf(CLEAR_SCREEN);
            render(board, &player, enemies, board->num_enemies, start_time);

            KeyPress key = get_keypress();

            /* Q pauses the game. */
            if (key == KEY_QUIT)
            {
                state = show_pause_screen();
                if (state == STATE_PLAYING)
                {
                    set_blocking(0);
                }
                continue;
            }

            int player_was_hit = 0;

            /* Player movement — direction key ends invincibility. */
            Direction dir;
            if (translate_key(key, &dir))
            {
                player.invincible_until = 0.0; /* back in action */

                MoveResult result = move_player(&player, board, dir);

                if (result == MOVE_REACHED_END)
                {
                    /* Brief pause showing P on the exit before transitioning. */
                    player.pos.row += (dir == DIR_DOWN ? 1 : dir == DIR_UP ? -1
                                                                           : 0);
                    player.pos.col += (dir == DIR_RIGHT ? 1 : dir == DIR_LEFT ? -1
                                                                              : 0);
                    printf(CLEAR_SCREEN);
                    render(board, &player, enemies,
                           board->num_enemies, start_time);
                    printf("\n  *** LEVEL CLEAR! ***\n");
                    fflush(stdout);
                    struct timespec ts = {0, (long)(LEVEL_CLEAR_PAUSE * 1e9)};
                    nanosleep(&ts, NULL);
                    g_level++;
                    state = STATE_LEVEL_UP;
                    continue;
                }
            }

            /* Enemy movement — driven by real time, independent of input.
             * Enemies move at SECONDS_PER_TICK even when the player holds
             * a key (which would otherwise prevent KEY_UNKNOWN from firing). */
            if (current_time() >= next_enemy_move)
            {
                move_all_enemies(enemies, board->num_enemies, board);
                next_enemy_move = current_time() + SECONDS_PER_TICK;
            }

            /* Collision detection — pure position comparison.
             * No tile inspection needed since entities don't modify the board. */
            if (!is_invincible(&player) &&
                any_enemy_at(enemies, board->num_enemies,
                             player.pos.row, player.pos.col))
                player_was_hit = 1;

            if (player_was_hit)
            {
                if (lose_life(&player))
                {
                    state = STATE_GAME_OVER;
                }
                else
                {
                    show_hit_screen(player.lives, start_time);
                    respawn_player(&player, board);
                    next_enemy_move = current_time() + SECONDS_PER_TICK;
                }
            }
        }

        /* ----------------------------------------------------------------
         * LEVEL UP
         * ---------------------------------------------------------------- */
        else if (state == STATE_LEVEL_UP)
        {
            cleanup(&board, &enemies);

            board = load_level();
            if (!board)
            {
                /* No more levels — player wins. */
                state = STATE_WIN;
                continue;
            }

            show_level_up_screen();
            player = init_player(board);
            enemies = init_enemies(board);
            next_enemy_move = current_time() + SECONDS_PER_TICK;
            set_blocking(0);
            state = STATE_PLAYING;
        }

        /* ----------------------------------------------------------------
         * GAME OVER
         * ---------------------------------------------------------------- */
        else if (state == STATE_GAME_OVER)
        {
            int levels_cleared = g_level - 1;
            int elapsed = (int)(time(NULL) - start_time);
            ScoreBoard sb = load_scores();
            int new_high_score, fastest_time;
            check_achievements(&sb, levels_cleared, elapsed, 0,
                               &new_high_score, &fastest_time);
            free_scoreboard(&sb);
            save_score(start_time, levels_cleared, 0);
            show_game_over_screen(levels_cleared, start_time, new_high_score);
            state = STATE_START;
        }

        /* ----------------------------------------------------------------
         * WIN
         * ---------------------------------------------------------------- */
        else if (state == STATE_WIN)
        {
            int levels_cleared = g_level - 1;
            int elapsed = (int)(time(NULL) - start_time);
            ScoreBoard sb = load_scores();
            int new_high_score, fastest_time;
            check_achievements(&sb, levels_cleared, elapsed, 1,
                               &new_high_score, &fastest_time);
            free_scoreboard(&sb);
            save_score(start_time, levels_cleared, 1);
            show_win_screen(levels_cleared, start_time,
                            new_high_score, fastest_time);
            state = STATE_START;
        }
    }

    cleanup(&board, &enemies);
    printf(CLEAR_SCREEN);
    printf("Thanks for playing!\n");
    return 0;
}