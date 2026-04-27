/*
 * enemy.h — Enemy module interface.
 *
 * Each enemy roams the board by walking in a random direction for a
 * random number of steps, then picking a new direction.
 *
 * Enemies do NOT modify the board — they just update their Position.
 * Collision detection is done in main.c by comparing positions.
 */
#ifndef ENEMY_H
#define ENEMY_H

#include "board.h"
#include "config.h"

/* -----------------------------------------------------------------------
 * Enemy
 *
 * pos:              Current position on the board.
 * dir:              Current movement direction.
 * steps_remaining:  Steps left before picking a new direction.
 * ----------------------------------------------------------------------- */
typedef struct {
    Position  pos;
    Direction dir;
    int       steps_remaining;
} Enemy;

/* -----------------------------------------------------------------------
 * Function declarations
 * ----------------------------------------------------------------------- */

/*
 * init_enemies: Allocate and return an array of Enemy structs, one per
 * spawn point in the board. Seeds the RNG with time(NULL).
 * Returns NULL if there are no enemies. Caller frees the array.
 */
Enemy *init_enemies(const Board *b);

/*
 * move_enemy: Move one enemy one step.
 * Avoids obstacles, boundaries, and other enemies (by checking
 * the positions array). Picks a new direction when steps run out
 * or when blocked.
 *
 * positions:    Array of all current enemy positions (used to avoid
 *               enemies walking through each other).
 * num_enemies:  Length of the positions array.
 * index:        Index of this enemy in the positions array.
 */
void move_enemy(Enemy *e, const Board *b,
                Enemy *all_enemies, int num_enemies, int index);

/*
 * move_all_enemies: Call move_enemy() for every enemy.
 */
void move_all_enemies(Enemy *enemies, int num_enemies, const Board *b);

/*
 * any_enemy_at: Return 1 if any enemy is at (row, col), 0 otherwise.
 * Used by main.c for collision detection.
 */
int any_enemy_at(const Enemy *enemies, int num_enemies, int row, int col);

#endif /* ENEMY_H */