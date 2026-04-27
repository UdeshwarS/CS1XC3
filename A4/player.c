#include <stdio.h>
#include <time.h>
#include "player.h"

/* -----------------------------------------------------------------------
 * current_time: return wall-clock time in seconds.
 * Used for invincibility timing — independent of tick rate.
 * ----------------------------------------------------------------------- */
static double current_time(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

/* -----------------------------------------------------------------------
 * init_player
 * ----------------------------------------------------------------------- */
Player init_player(const Board *b)
{
    Player p;

    p.pos = b->spawn;
    p.lives = STARTING_LIVES;
    p.invincible_until = current_time() + INVINCIBLE_SECONDS;

    return p;
}

/* -----------------------------------------------------------------------
 * move_player
 * ----------------------------------------------------------------------- */
MoveResult move_player(Player *p, const Board *b, Direction dir)
{
    int new_row;
    int new_col;
    char tile;

    new_row = p->pos.row;
    new_col = p->pos.col;

    switch (dir)
    {
    case DIR_UP:
        new_row--;
        break;
    case DIR_DOWN:
        new_row++;
        break;
    case DIR_LEFT:
        new_col--;
        break;
    case DIR_RIGHT:
        new_col++;
        break;
    default:
        return MOVE_BLOCKED;
    }

    if (!is_in_bounds(b, new_row, new_col))
    {
        return MOVE_BLOCKED;
    }

    tile = get_tile(b, new_row, new_col);

    if (is_obstacle(tile))
    {
        return MOVE_BLOCKED;
    }

    if (tile == TILE_END)
    {
        return MOVE_REACHED_END;
    }

    p->pos.row = new_row;
    p->pos.col = new_col;
    return MOVE_OK;
}

/* -----------------------------------------------------------------------
 * respawn_player
 * ----------------------------------------------------------------------- */
void respawn_player(Player *p, const Board *b)
{
    p->pos = b->spawn;
    p->invincible_until = current_time() + INVINCIBLE_SECONDS;
}

/* -----------------------------------------------------------------------
 * lose_life
 * ----------------------------------------------------------------------- */
int lose_life(Player *p)
{
    if (p->lives > 0)
    {
        p->lives--;
    }

    return p->lives == 0;
}

/* -----------------------------------------------------------------------
 * is_invincible
 * ----------------------------------------------------------------------- */
int is_invincible(const Player *p)
{
    return current_time() < p->invincible_until;
}

/* =======================================================================
 * PLAYER_TEST
 * gcc -DPLAYER_TEST board.c player.c -o test_player && ./test_player
 * ======================================================================= */
#ifdef PLAYER_TEST

static int tests_passed = 0;
static int tests_failed = 0;

static void check(const char *label, int condition)
{
    if (condition)
    {
        printf("  PASS: %s\n", label);
        tests_passed++;
    }
    else
    {
        printf("  FAIL: %s\n", label);
        tests_failed++;
    }
}

int main(void)
{
    printf("=== player.c tests ===\n\n");

    Board *b = load_board("test_board.txt");
    if (!b)
    {
        printf("Cannot continue.\n");
        return 1;
    }

    /* ---- Test 1: init ---- */
    printf("[ init_player ]\n");
    Player p = init_player(b);
    check("lives", p.lives == STARTING_LIVES);
    check("pos at spawn row", p.pos.row == b->spawn.row);
    check("pos at spawn col", p.pos.col == b->spawn.col);
    check("starts invincible", is_invincible(&p));

    /* ---- Test 2: movement ---- */
    printf("\n[ move_player — normal moves ]\n");
    p.pos.row = 4;
    p.pos.col = 1; /* open interior, clear in all directions */

    MoveResult r = move_player(&p, b, DIR_RIGHT);
    check("move right: MOVE_OK", r == MOVE_OK);
    check("move right: col updated", p.pos.col == 2);

    r = move_player(&p, b, DIR_UP);
    check("move up: MOVE_OK", r == MOVE_OK);
    check("move up: row updated", p.pos.row == 3);

    r = move_player(&p, b, DIR_LEFT);
    check("move left: MOVE_OK", r == MOVE_OK);
    r = move_player(&p, b, DIR_DOWN);
    check("move down: MOVE_OK", r == MOVE_OK);

    /* ---- Test 3: boundaries ---- */
    printf("\n[ move_player — boundaries ]\n");
    p.pos.row = 5;
    p.pos.col = 0; /* bottom-left */
    r = move_player(&p, b, DIR_DOWN);
    check("blocked at bottom", r == MOVE_BLOCKED);
    check("pos unchanged", p.pos.row == 5 && p.pos.col == 0);

    r = move_player(&p, b, DIR_LEFT);
    check("blocked at left edge", r == MOVE_BLOCKED);

    p.pos.row = 0;
    p.pos.col = 0;
    r = move_player(&p, b, DIR_UP);
    check("blocked at top edge", r == MOVE_BLOCKED);

    p.pos.col = b->cols - 1;
    r = move_player(&p, b, DIR_RIGHT);
    check("blocked at right edge", r == MOVE_BLOCKED);

    /* ---- Test 4: obstacles ---- */
    printf("\n[ move_player — obstacles ]\n");
    p.pos.row = 1;
    p.pos.col = 6; /* above tree at (2,6) */
    r = move_player(&p, b, DIR_DOWN);
    check("blocked by tree", r == MOVE_BLOCKED);
    check("pos unchanged by tree", p.pos.row == 1);

    p.pos.row = 1;
    p.pos.col = 7; /* above lake at (2,7) */
    r = move_player(&p, b, DIR_DOWN);
    check("blocked by lake", r == MOVE_BLOCKED);

    /* ---- Test 5: end tile ---- */
    printf("\n[ move_player — end tile ]\n");
    p.pos.row = 0;
    p.pos.col = 9; /* one left of X */
    r = move_player(&p, b, DIR_RIGHT);
    check("MOVE_REACHED_END", r == MOVE_REACHED_END);
    check("pos unchanged on end", p.pos.col == 9);

    /* ---- Test 6: lose_life ---- */
    printf("\n[ lose_life ]\n");
    p.lives = 3;
    check("lose 1: not over", lose_life(&p) == 0);
    check("lives = 2", p.lives == 2);
    check("lose 2: not over", lose_life(&p) == 0);
    check("lose 3: game over", lose_life(&p) == 1);
    check("lives = 0", p.lives == 0);

    /* ---- Test 7: respawn ---- */
    printf("\n[ respawn_player ]\n");
    p.pos.row = 3;
    p.pos.col = 3;
    respawn_player(&p, b);
    check("back at spawn row", p.pos.row == b->spawn.row);
    check("back at spawn col", p.pos.col == b->spawn.col);
    check("invincible after spawn", is_invincible(&p));

    /* ---- Test 8: invincibility ---- */
    printf("\n[ is_invincible ]\n");
    p.invincible_until = 0.0; /* expired */
    check("not invincible", !is_invincible(&p));
    p.invincible_until = current_time() + 10.0;
    check("is invincible", is_invincible(&p));

    free_board(&b);
    printf("\n=== Results: %d passed, %d failed ===\n",
           tests_passed, tests_failed);
    return (tests_failed == 0) ? 0 : 1;
}

#endif /* PLAYER_TEST */