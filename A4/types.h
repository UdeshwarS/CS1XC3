#ifndef TYPES_H
#define TYPES_H

/*
 * types.h — Types shared across multiple modules.
 *
 * Types that belong to a specific module live in their own headers.
 * Types used by two or more modules with no clear owner live here.
 */

/* -----------------------------------------------------------------------
 * Position
 * A (row, col) coordinate. Zero-indexed from the top-left.
 * ----------------------------------------------------------------------- */
typedef struct {
    int row;
    int col;
} Position;

/* -----------------------------------------------------------------------
 * Direction
 * Used by both the player (move_player takes a Direction) and enemies
 * (each enemy stores its current direction).
 *
 * DIR_COUNT is the total number of directions — useful for picking a
 * random one: rand() % DIR_COUNT gives a valid Direction value.
 * ----------------------------------------------------------------------- */
typedef enum {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_COUNT
} Direction;

#endif /* TYPES_H */