#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"

#define MAX_LINE_LEN 1024

static void trim_newline(char *line)
{
    size_t len = strlen(line);

    while (len > 0 &&
           (line[len - 1] == '\n' || line[len - 1] == '\r'))
    {
        line[len - 1] = '\0';
        len--;
    }
}

/* -----------------------------------------------------------------------
 * load_board
 * Two-pass read: first pass determines dimensions, second fills tiles.
 * ----------------------------------------------------------------------- */
Board *load_board(const char *filename)
{
    FILE *fp;
    char line[MAX_LINE_LEN];
    int rows;
    int cols;
    int num_enemies;
    int spawn_count;
    int end_count;
    int r;
    Board *b;
    int enemy_index;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        return NULL;
    }

    rows = 0;
    cols = 0;
    num_enemies = 0;
    spawn_count = 0;
    end_count = 0;

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        int c;
        int len;

        trim_newline(line);
        len = (int)strlen(line);

        if (len <= 0 || len > MAX_BOARD_COLS || rows >= MAX_BOARD_ROWS)
        {
            fclose(fp);
            return NULL;
        }

        if (len > cols)
        {
            cols = len;
        }

        for (c = 0; c < len; c++)
        {
            char tile = line[c];

            if (tile == TILE_PLAYER_SPAWN)
            {
                spawn_count++;
            }
            else if (tile == TILE_END)
            {
                end_count++;
            }
            else if (tile == TILE_ENEMY_SPAWN)
            {
                num_enemies++;
            }
            else if (tile != TILE_EMPTY &&
                     tile != TILE_TREE &&
                     tile != TILE_LAKE)
            {
                fclose(fp);
                return NULL;
            }
        }

        rows++;
    }

    fclose(fp);

    if (rows <= 0 || cols <= 0 || spawn_count != 1 || end_count != 1)
    {
        return NULL;
    }

    b = malloc(sizeof(Board));
    if (b == NULL)
    {
        return NULL;
    }

    b->tiles = malloc(rows * sizeof(char *));
    if (b->tiles == NULL)
    {
        free(b);
        return NULL;
    }

    b->rows = rows;
    b->cols = cols;
    b->spawn.row = -1;
    b->spawn.col = -1;
    b->end.row = -1;
    b->end.col = -1;
    b->num_enemies = num_enemies;
    b->enemy_spawns = NULL;

    for (r = 0; r < rows; r++)
    {
        b->tiles[r] = NULL;
    }

    if (num_enemies > 0)
    {
        b->enemy_spawns = malloc(num_enemies * sizeof(Position));
        if (b->enemy_spawns == NULL)
        {
            free_board(&b);
            return NULL;
        }
    }

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        free_board(&b);
        return NULL;
    }

    enemy_index = 0;
    r = 0;

    while (r < rows && fgets(line, sizeof(line), fp) != NULL)
    {
        int c;
        int len;

        trim_newline(line);
        len = (int)strlen(line);

        if (len <= 0 || len > cols)
        {
            fclose(fp);
            free_board(&b);
            return NULL;
        }

        b->tiles[r] = malloc((cols + 1) * sizeof(char));
        if (b->tiles[r] == NULL)
        {
            fclose(fp);
            free_board(&b);
            return NULL;
        }

        memset(b->tiles[r], TILE_EMPTY, cols);
        b->tiles[r][cols] = '\0';

        for (c = 0; c < len; c++)
        {
            char tile = line[c];

            if (tile == TILE_PLAYER_SPAWN)
            {
                b->spawn.row = r;
                b->spawn.col = c;
                b->tiles[r][c] = TILE_EMPTY;
            }
            else if (tile == TILE_END)
            {
                b->end.row = r;
                b->end.col = c;
                b->tiles[r][c] = TILE_END;
            }
            else if (tile == TILE_ENEMY_SPAWN)
            {
                b->enemy_spawns[enemy_index].row = r;
                b->enemy_spawns[enemy_index].col = c;
                enemy_index++;
                b->tiles[r][c] = TILE_EMPTY;
            }
            else
            {
                b->tiles[r][c] = tile;
            }
        }

        r++;
    }

    fclose(fp);

    if (r != rows || enemy_index != num_enemies)
    {
        free_board(&b);
        return NULL;
    }

    return b;
}

/* -----------------------------------------------------------------------
 * free_board
 * ----------------------------------------------------------------------- */
void free_board(Board **b)
{
    int r;

    if (b == NULL || *b == NULL)
    {
        return;
    }

    if ((*b)->tiles != NULL)
    {
        for (r = 0; r < (*b)->rows; r++)
        {
            free((*b)->tiles[r]);
        }
        free((*b)->tiles);
    }

    free((*b)->enemy_spawns);
    free(*b);
    *b = NULL;
}

/* -----------------------------------------------------------------------
 * get_tile
 * ----------------------------------------------------------------------- */
char get_tile(const Board *b, int row, int col)
{
    if (b == NULL || !is_in_bounds(b, row, col))
    {
        return '\0';
    }

    return b->tiles[row][col];
}

/* -----------------------------------------------------------------------
 * is_walkable
 * ----------------------------------------------------------------------- */
int is_walkable(const Board *b, int row, int col)
{
    char tile;

    if (b == NULL || !is_in_bounds(b, row, col))
    {
        return 0;
    }

    tile = get_tile(b, row, col);
    return !is_obstacle(tile);
}

/* =======================================================================
 * BOARD_TEST
 * gcc -DBOARD_TEST board.c -o test_board && ./test_board
 * ======================================================================= */
#ifdef BOARD_TEST

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
    printf("=== board.c tests ===\n\n");

    printf("[ load_board ]\n");
    Board *b = load_board("test_board.txt");
    check("not NULL", b != NULL);
    if (!b)
    {
        printf("Cannot continue.\n");
        return 1;
    }
    check("rows", b->rows == 6);
    check("cols", b->cols == 13);
    check("spawn row", b->spawn.row == 5);
    check("spawn col", b->spawn.col == 0);
    check("end row", b->end.row == 0);
    check("end col", b->end.col == 10);
    check("enemy count", b->num_enemies == 1);
    check("enemy spawn row", b->enemy_spawns[0].row == 0);
    check("enemy spawn col", b->enemy_spawns[0].col == 2);

    printf("\n[ tile contents ]\n");
    check("spawn is empty", get_tile(b, 5, 0) == TILE_EMPTY);
    check("enemy spawn empty", get_tile(b, 0, 2) == TILE_EMPTY);
    check("end tile is X", get_tile(b, 0, 10) == TILE_END);
    check("tree preserved", get_tile(b, 2, 6) == TILE_TREE);
    check("lake preserved", get_tile(b, 2, 8) == TILE_LAKE);

    printf("\n[ is_walkable ]\n");
    check("empty is walkable", is_walkable(b, 5, 0));
    check("end is walkable", is_walkable(b, 0, 10));
    check("tree not walkable", !is_walkable(b, 2, 6));
    check("lake not walkable", !is_walkable(b, 2, 8));
    check("out of bounds", !is_walkable(b, -1, 0));
    check("out of bounds", !is_walkable(b, 0, b->cols));

    printf("\n[ is_obstacle / is_in_bounds ]\n");
    check("tree is obstacle", is_obstacle(TILE_TREE));
    check("lake is obstacle", is_obstacle(TILE_LAKE));
    check("empty not obstacle", !is_obstacle(TILE_EMPTY));
    check("in bounds", is_in_bounds(b, 0, 0));
    check("corner in bounds", is_in_bounds(b, b->rows - 1, b->cols - 1));
    check("negative out", !is_in_bounds(b, -1, 0));
    check("too large out", !is_in_bounds(b, b->rows, 0));

    printf("\n[ render — visual check ]\n");
    printf("(no P or M — board holds static tiles only)\n");
    printf("\nAnnotations:\n");
    for (int r = 0; r < b->rows; r++)
    {
        printf("  row %d: %s", r, b->tiles[r]);
        if (r == b->spawn.row)
            printf("  <- spawn at col %d", b->spawn.col);
        if (r == b->end.row)
            printf("  <- end at col %d", b->end.col);
        for (int i = 0; i < b->num_enemies; i++)
            if (b->enemy_spawns[i].row == r)
                printf("  <- enemy spawn at col %d", b->enemy_spawns[i].col);
        printf("\n");
    }

    printf("\n[ free_board ]\n");
    free_board(&b);
    check("NULL after free", b == NULL);
    free_board(&b);
    check("double free safe", b == NULL);

    printf("\n=== Results: %d passed, %d failed ===\n",
           tests_passed, tests_failed);
    return (tests_failed == 0) ? 0 : 1;
}

#endif /* BOARD_TEST */