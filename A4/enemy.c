#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "enemy.h"

/* g_level is defined in main.c.
 * Used here to scale enemy difficulty — higher levels = shorter steps. */
extern int g_level;

/* Row and column deltas for each direction. */
static const int row_delta[] = {-1, 1, 0, 0};
static const int col_delta[] = {0, 0, -1, 1};

/* -----------------------------------------------------------------------
 * random_direction: return a random Direction (not DIR_COUNT).
 * ----------------------------------------------------------------------- */
static Direction random_direction(void)
{
    return (Direction)(rand() % DIR_COUNT);
}

/* -----------------------------------------------------------------------
 * random_steps: return a random step count, scaled by level.
 * Higher levels = shorter runs = more erratic enemies.
 * ----------------------------------------------------------------------- */
static int random_steps(void)
{
    int max = ENEMY_MAX_STEPS - (g_level - 1);
    if (max < ENEMY_MIN_STEPS)
        max = ENEMY_MIN_STEPS;
    return ENEMY_MIN_STEPS + rand() % (max - ENEMY_MIN_STEPS + 1);
}

/* -----------------------------------------------------------------------
 * init_enemies
 * ----------------------------------------------------------------------- */
Enemy *init_enemies(const Board *b)
{
    static int seeded = 0;
    Enemy *enemies;
    int i;

    if (b == NULL || b->num_enemies <= 0)
    {
        return NULL;
    }

    if (!seeded)
    {
        srand((unsigned int)time(NULL));
        seeded = 1;
    }

    enemies = malloc(b->num_enemies * sizeof(Enemy));
    if (enemies == NULL)
    {
        return NULL;
    }

    for (i = 0; i < b->num_enemies; i++)
    {
        enemies[i].pos = b->enemy_spawns[i];
        enemies[i].dir = random_direction();
        enemies[i].steps_remaining = random_steps();
    }

    return enemies;
}

/* -----------------------------------------------------------------------
 * cell_is_free: return 1 if (row, col) is walkable and not occupied
 * by another enemy.
 * ----------------------------------------------------------------------- */
static int cell_is_free(const Board *b,
                        const Enemy *all_enemies, int num_enemies,
                        int skip_index, int row, int col)
{
    if (!is_walkable(b, row, col))
        return 0;
    for (int i = 0; i < num_enemies; i++)
    {
        if (i == skip_index)
            continue;
        if (all_enemies[i].pos.row == row &&
            all_enemies[i].pos.col == col)
            return 0;
    }
    return 1;
}

/* -----------------------------------------------------------------------
 * move_enemy
 * ----------------------------------------------------------------------- */
void move_enemy(Enemy *e, const Board *b,
                Enemy *all_enemies, int num_enemies, int index)
{
    int new_row;
    int new_col;

    if (e == NULL || b == NULL)
    {
        return;
    }

    if (e->steps_remaining <= 0)
    {
        e->dir = random_direction();
        e->steps_remaining = random_steps();
    }

    new_row = e->pos.row + row_delta[e->dir];
    new_col = e->pos.col + col_delta[e->dir];

    if (cell_is_free(b, all_enemies, num_enemies, index, new_row, new_col))
    {
        e->pos.row = new_row;
        e->pos.col = new_col;
        e->steps_remaining--;

        if (e->steps_remaining <= 0)
        {
            e->dir = random_direction();
            e->steps_remaining = random_steps();
        }
    }
    else
    {
        e->dir = random_direction();
        e->steps_remaining = random_steps();
    }
}

/* -----------------------------------------------------------------------
 * move_all_enemies
 * ----------------------------------------------------------------------- */
void move_all_enemies(Enemy *enemies, int num_enemies, const Board *b)
{
    int i;

    if (enemies == NULL || b == NULL)
    {
        return;
    }

    for (i = 0; i < num_enemies; i++)
    {
        move_enemy(&enemies[i], b, enemies, num_enemies, i);
    }
}

/* -----------------------------------------------------------------------
 * any_enemy_at
 * ----------------------------------------------------------------------- */
int any_enemy_at(const Enemy *enemies, int num_enemies, int row, int col)
{
    int i;

    if (enemies == NULL)
    {
        return 0;
    }

    for (i = 0; i < num_enemies; i++)
    {
        if (enemies[i].pos.row == row && enemies[i].pos.col == col)
        {
            return 1;
        }
    }

    return 0;
}

/* =======================================================================
 * ENEMY_TEST
 * gcc -DENEMY_TEST board.c enemy.c -o test_enemy && ./test_enemy
 * ======================================================================= */
#ifdef ENEMY_TEST

/* g_level is defined in main.c — provide it here for the test build. */
int g_level = 1;

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
    printf("=== enemy.c tests ===\n\n");
    srand(42);

    Board *b = load_board("test_board.txt");
    if (!b)
    {
        printf("Cannot continue.\n");
        return 1;
    }

    /* ---- Test 1: init ---- */
    printf("[ init_enemies ]\n");
    Enemy *enemies = init_enemies(b);
    check("not NULL", enemies != NULL);
    check("count matches board", b->num_enemies == 1);
    check("pos at spawn row", enemies[0].pos.row == b->enemy_spawns[0].row);
    check("pos at spawn col", enemies[0].pos.col == b->enemy_spawns[0].col);
    check("steps in range", enemies[0].steps_remaining >= ENEMY_MIN_STEPS &&
                                enemies[0].steps_remaining <= ENEMY_MAX_STEPS);

    /* ---- Test 2: basic movement ---- */
    printf("\n[ move_enemy — basic movement ]\n");
    enemies[0].pos.row = 4;
    enemies[0].pos.col = 4;
    enemies[0].dir = DIR_RIGHT;
    enemies[0].steps_remaining = 10;

    move_enemy(&enemies[0], b, enemies, 1, 0);
    check("moved right", enemies[0].pos.col == 5);

    /* ---- Test 3: step counter ---- */
    printf("\n[ move_enemy — step counter ]\n");
    enemies[0].pos.row = 4;
    enemies[0].pos.col = 4;
    enemies[0].dir = DIR_RIGHT;
    enemies[0].steps_remaining = 1;

    move_enemy(&enemies[0], b, enemies, 1, 0);
    check("steps reset", enemies[0].steps_remaining >= ENEMY_MIN_STEPS);

    /* ---- Test 4: obstacle blocking ---- */
    printf("\n[ move_enemy — obstacle blocking ]\n");
    enemies[0].pos.row = 1;
    enemies[0].pos.col = 6; /* just above tree at (2,6) */
    enemies[0].dir = DIR_DOWN;
    enemies[0].steps_remaining = 10;

    int old_row = enemies[0].pos.row;
    int old_col = enemies[0].pos.col;
    move_enemy(&enemies[0], b, enemies, 1, 0);
    check("didn't move into tree", !(enemies[0].pos.row == 2 &&
                                     enemies[0].pos.col == 6));
    (void)old_row;
    (void)old_col;

    /* ---- Test 5: no ghost tiles — board unchanged ---- */
    printf("\n[ enemy movement leaves board unchanged ]\n");
    char tile_before = get_tile(b, 0, 10);
    enemies[0].pos.row = 0;
    enemies[0].pos.col = 9;
    enemies[0].dir = DIR_RIGHT;
    enemies[0].steps_remaining = 10;

    move_enemy(&enemies[0], b, enemies, 1, 0); /* moves onto X */
    check("enemy at end tile", enemies[0].pos.col == 10);
    check("board tile unchanged", get_tile(b, 0, 10) == tile_before);

    move_enemy(&enemies[0], b, enemies, 1, 0); /* moves off X */
    check("board still unchanged", get_tile(b, 0, 10) == tile_before);

    /* ---- Test 6: no walking through each other ---- */
    printf("\n[ enemies don't overlap ]\n");

    /* Add a second enemy manually. */
    Enemy *two = malloc(2 * sizeof(Enemy));
    two[0].pos.row = 4;
    two[0].pos.col = 4;
    two[0].dir = DIR_RIGHT;
    two[0].steps_remaining = 10;
    two[1].pos.row = 4;
    two[1].pos.col = 5; /* blocking right */
    two[1].dir = DIR_LEFT;
    two[1].steps_remaining = 10;

    move_enemy(&two[0], b, two, 2, 0);
    check("didn't walk through", !(two[0].pos.row == 4 &&
                                   two[0].pos.col == 5));
    free(two);

    /* ---- Test 7: any_enemy_at ---- */
    printf("\n[ any_enemy_at ]\n");
    enemies[0].pos.row = 3;
    enemies[0].pos.col = 3;
    check("found at pos", any_enemy_at(enemies, 1, 3, 3));
    check("not at other pos", !any_enemy_at(enemies, 1, 3, 4));

    /* ---- Test 8: move_all_enemies ---- */
    printf("\n[ move_all_enemies ]\n");
    enemies[0].pos.row = 4;
    enemies[0].pos.col = 4;
    enemies[0].dir = DIR_RIGHT;
    enemies[0].steps_remaining = 10;
    move_all_enemies(enemies, b->num_enemies, b);
    check("enemy moved", enemies[0].pos.col == 5);

    free(enemies);
    free_board(&b);
    printf("\n=== Results: %d passed, %d failed ===\n",
           tests_passed, tests_failed);
    return (tests_failed == 0) ? 0 : 1;
}

#endif /* ENEMY_TEST */