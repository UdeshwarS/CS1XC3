/*
 * player.h — Player module interface.
 *
 * The player module owns position, lives, and invincibility state.
 * It does NOT modify the board — the board holds only static tiles.
 * Movement is just updating the player's Position.
 *
 * Invincibility uses wall-clock time rather than a tick counter, so
 * it works correctly regardless of how fast the game loop runs.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"
#include "config.h"

/* -----------------------------------------------------------------------
 * MoveResult
 * Returned by move_player(). main.c switches on this to decide what
 * happens next. Defined here since only the player module returns it.
 * ----------------------------------------------------------------------- */
typedef enum {
    MOVE_OK,           /* normal move */
    MOVE_BLOCKED,      /* obstacle, boundary — player did not move */
    MOVE_REACHED_END   /* player stepped onto the exit tile */
} MoveResult;

/* -----------------------------------------------------------------------
 * Player
 *
 * pos:              Current position on the board.
 * lives:            Remaining lives. 0 = game over.
 * invincible_until: Wall-clock time (from clock_gettime) when invincibility
 *                   ends. 0.0 = not invincible. Using real time means the
 *                   duration is independent of tick rate or loop speed.
 * ----------------------------------------------------------------------- */
typedef struct {
    Position pos;
    int      lives;
    double   invincible_until;
} Player;

/* -----------------------------------------------------------------------
 * Function declarations
 * ----------------------------------------------------------------------- */

/*
 * init_player: Initialise a Player at the board's spawn point.
 * Returns a Player by value — no malloc needed for such a small struct.
 * Sets invincible_until to give the player a grace period at level start.
 */
Player init_player(const Board *b);

/*
 * move_player: Attempt to move the player one step in the given direction.
 * Checks bounds and obstacles against the board's static tiles.
 * Does NOT check enemy collision — main.c handles that by comparing positions.
 * Returns MOVE_BLOCKED, MOVE_REACHED_END, or MOVE_OK.
 */
MoveResult move_player(Player *p, const Board *b, Direction dir);

/*
 * respawn_player: Return the player to the board's spawn point and
 * grant invincibility for INVINCIBLE_SECONDS. Does not touch lives.
 */
void respawn_player(Player *p, const Board *b);

/*
 * lose_life: Decrement lives by one.
 * Returns 1 if the player is now out of lives (game over), 0 otherwise.
 */
int lose_life(Player *p);

/*
 * is_invincible: Return 1 if the player is currently invincible.
 */
int is_invincible(const Player *p);

#endif /* PLAYER_H */