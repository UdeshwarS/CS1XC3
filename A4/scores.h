/*
 * scores.h — Score history module interface.
 *
 * Scores are written only on game over or completed run.
 * Quitting mid-game does not save.
 *
 * File format (one line per run):
 *   YYYY-MM-DD HH:MM:SS,levels_cleared,elapsed_seconds,completed
 */

#ifndef SCORES_H
#define SCORES_H

#include <time.h>
#include "config.h"

/* -----------------------------------------------------------------------
 * ScoreEntry
 * ----------------------------------------------------------------------- */
typedef struct {
    char date[DATE_LEN];
    int  levels_cleared;
    int  elapsed_seconds;
    int  completed;         /* 1 = cleared all levels, 0 = ran out of lives */
} ScoreEntry;

/* -----------------------------------------------------------------------
 * ScoreBoard
 * A dynamically allocated array of all entries, sorted best-first.
 * ----------------------------------------------------------------------- */
typedef struct {
    ScoreEntry *entries;
    int         count;
} ScoreBoard;

/* -----------------------------------------------------------------------
 * load_scores
 * Creates and returns the ScoreBoard variable 
 * Reads entries in SCORES_FILE
 * Calls qsort to sort the entries (use compare_entries)
 * ----------------------------------------------------------------------- */
ScoreBoard load_scores(void);

/*
 * free_scoreboard: Release memory allocated by load_scores().
 * Sets entries to NULL and count to 0 after freeing.
 */
void free_scoreboard(ScoreBoard *sb);


/*
 * save_score: Append one run entry to SCORES_FILE.
 * Called on game over or completed run — never on mid-game quit.
 *
 * start_time:     The time_t recorded when the run began (from main.c).
 *                 Used to compute elapsed seconds and format the date.
 * levels_cleared: How many levels the player finished.
 * completed:      1 if all levels were cleared, 0 if lives ran out.
 */
void save_score(time_t start_time, int levels_cleared, int completed);

/*
 * print_scoreboard: Print the top SCORES_DISPLAY entries to stdout.
 * Called by main.c when rendering the start screen.
 * Prints a friendly message if no scores exist yet.
 */
void print_scoreboard(const ScoreBoard *sb);

#endif /* SCORES_H */