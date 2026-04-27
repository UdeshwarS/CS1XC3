/*
 * board.h — Board module interface.
 *
 * The board holds only STATIC tile data, including obstacles, the exit, 
 * empty space. Moving entities (player, enemies) are stored separately 
 * and layered on top during rendering.
 *
 * This means the board never contains 'P' or 'M'. Movement is just
 * updating a Position, which is defined in types.h.
 */
#ifndef BOARD_H
#define BOARD_H

#include "types.h"
#include "config.h"

/* Maximum board size — must fit in a standard 80x24 terminal with the HUD. */
#define MAX_BOARD_ROWS 20
#define MAX_BOARD_COLS 78

/* Level files are named levels/level01.txt, levels/level02.txt, etc. */
#define LEVEL_FILE_FORMAT "levels/level%02d.txt"

/* -----------------------------------------------------------------------
 * Tile characters 
 * ----------------------------------------------------------------------- */
#define TILE_EMPTY        '.'
#define TILE_PLAYER_SPAWN 'S'
#define TILE_END          'X'
#define TILE_TREE         'T'
#define TILE_LAKE         'L'
#define TILE_ENEMY_SPAWN  'E'

/* -----------------------------------------------------------------------
 * Board struct
 *
 * tiles:         2D array of static tile characters. Never contains
 *                moving entity tiles ('P', 'M') — those are layered
 *                on top during render.
 * rows / cols:   Dimensions determined at load time from the file.
 * spawn:         Where the player starts (recorded from 'S' on load).
 * end:           Where the exit is (recorded from 'X' on load).
 * enemy_spawns:  Dynamically allocated array of 'E' positions.
 * num_enemies:   Length of enemy_spawns.
 * ----------------------------------------------------------------------- */
typedef struct {
    char    **tiles;
    int       rows;
    int       cols;
    Position  spawn;
    Position  end;
    Position *enemy_spawns;
    int       num_enemies;
} Board;

/* -----------------------------------------------------------------------
 * Function declarations
 * ----------------------------------------------------------------------- */

/*
 * load_board: Read a board file and return a dynamically allocated Board.
 * Returns NULL on failure (file not found, bad format, size exceeded).
 * The caller must call free_board() when done.
 */
Board *load_board(const char *filename);

/*
 * free_board: Free all memory and set *b to NULL.
 */
void free_board(Board **b);

/*
 * get_tile: Return the static tile at (row, col), or '\0' if out of bounds.
 */
char get_tile(const Board *b, int row, int col);

/*
 * is_walkable: Return 1 if an entity can move onto (row, col).
 * A cell is walkable if it is in bounds and not an obstacle.
 */
int is_walkable(const Board *b, int row, int col);

/* -----------------------------------------------------------------------
 * Inline helpers
 * ----------------------------------------------------------------------- */

static inline int is_in_bounds(const Board *b, int row, int col) {
    return (row >= 0 && row < b->rows && col >= 0 && col < b->cols);
}

static inline int is_obstacle(char tile) {
    return (tile == TILE_TREE || tile == TILE_LAKE);
}

#endif /* BOARD_H */