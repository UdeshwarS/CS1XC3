#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "scores.h"

#define MAX_LINE_LEN 64

/* -----------------------------------------------------------------------
 * compare_entries: a comparison function for qsort (best run first).
 * Sorting order (best first):
 *   1. Completed runs rank above incomplete.
 *   2. More levels cleared is better.
 *   3. Fewer elapsed seconds is better for equal levels.
 * ----------------------------------------------------------------------- */
static int compare_entries(const void *a, const void *b)
{
    const ScoreEntry *ea = (const ScoreEntry *)a;
    const ScoreEntry *eb = (const ScoreEntry *)b;

    if (ea->completed != eb->completed)
    {
        return eb->completed - ea->completed;
    }

    if (ea->levels_cleared != eb->levels_cleared)
    {
        return eb->levels_cleared - ea->levels_cleared;
    }

    return ea->elapsed_seconds - eb->elapsed_seconds;
}

/* -----------------------------------------------------------------------
 * parse_line: parse one CSV line into a ScoreEntry.
 * Returns 1 on success, 0 on malformed input.
 * ----------------------------------------------------------------------- */
static int parse_line(char *line, ScoreEntry *entry)
{
    int matched;
    char date[DATE_LEN];

    matched = sscanf(line, "%19[^,],%d,%d,%d",
                     date,
                     &entry->levels_cleared,
                     &entry->elapsed_seconds,
                     &entry->completed);

    if (matched != 4)
    {
        return 0;
    }

    if (entry->levels_cleared < 0 || entry->elapsed_seconds < 0)
    {
        return 0;
    }

    if (entry->completed != 0 && entry->completed != 1)
    {
        return 0;
    }

    strcpy(entry->date, date);
    return 1;
}

/* -----------------------------------------------------------------------
 * load_scores
 * Creates and returns the ScoreBoard variable
 * Reads entries in SCORES_FILE
 * Calls qsort to sort the entries (use compare_entries)
 * ----------------------------------------------------------------------- */
ScoreBoard load_scores(void)
{
    ScoreBoard sb;
    FILE *fp;
    char line[MAX_LINE_LEN];

    sb.entries = NULL;
    sb.count = 0;

    fp = fopen(SCORES_FILE, "r");
    if (fp == NULL)
    {
        return sb;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        ScoreEntry entry;
        ScoreEntry *new_entries;

        line[strcspn(line, "\r\n")] = '\0';

        if (!parse_line(line, &entry))
        {
            continue;
        }

        new_entries = realloc(sb.entries, (sb.count + 1) * sizeof(ScoreEntry));
        if (new_entries == NULL)
        {
            free(sb.entries);
            sb.entries = NULL;
            sb.count = 0;
            fclose(fp);
            return sb;
        }

        sb.entries = new_entries;
        sb.entries[sb.count] = entry;
        sb.count++;
    }

    fclose(fp);

    if (sb.count > 1)
    {
        qsort(sb.entries, sb.count, sizeof(ScoreEntry), compare_entries);
    }

    return sb;
}

/*
 * free_scoreboard: Release memory allocated by load_scores().
 * Sets entries to NULL and count to 0 after freeing.
 */
void free_scoreboard(ScoreBoard *sb)
{
    if (sb == NULL)
    {
        return;
    }

    free(sb->entries);
    sb->entries = NULL;
    sb->count = 0;
}

/*
 * save_score: Append one run entry to SCORES_FILE.
 * Called on game over or completed run — never on mid-game quit.
 *
 * start_time:     The time_t recorded when the run began (from main.c).
 *                 Used to compute elapsed seconds and format the date.
 * levels_cleared: How many levels the player finished.
 * completed:      1 if all levels were cleared, 0 if lives ran out.
 */
void save_score(time_t start_time, int levels_cleared, int completed)
{
    FILE *fp;
    time_t now;
    int elapsed_seconds;
    struct tm tm_info;
    char date[DATE_LEN];

    fp = fopen(SCORES_FILE, "a");
    if (fp == NULL)
    {
        return;
    }

    now = time(NULL);
    elapsed_seconds = (int)difftime(now, start_time);
    if (elapsed_seconds < 0)
    {
        elapsed_seconds = 0;
    }

    if (localtime_r(&start_time, &tm_info) == NULL)
    {
        fclose(fp);
        return;
    }

    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", &tm_info);

    fprintf(fp, "%s,%d,%d,%d\n",
            date, levels_cleared, elapsed_seconds, completed);

    fclose(fp);
}

/*
 * print_scoreboard: Print the top SCORES_DISPLAY entries to stdout.
 * Called by main.c when rendering the start screen.
 * Prints a friendly message if no scores exist yet.
 */
void print_scoreboard(const ScoreBoard *sb)
{
    int i;
    int limit;

    if (sb == NULL || sb->entries == NULL || sb->count == 0)
    {
        printf("No scores yet.\n");
        return;
    }

    limit = sb->count;
    if (limit > SCORES_DISPLAY)
    {
        limit = SCORES_DISPLAY;
    }

    printf("Top Scores:\n");
    for (i = 0; i < limit; i++)
    {
        printf("%d. %s | levels: %d | time: %ds | %s\n",
               i + 1,
               sb->entries[i].date,
               sb->entries[i].levels_cleared,
               sb->entries[i].elapsed_seconds,
               sb->entries[i].completed ? "completed" : "game over");
    }
}

/* =======================================================================
 * SCORES_TEST
 * gcc -DSCORES_TEST scores.c -o test_scores && ./test_scores
 * ======================================================================= */
#ifdef SCORES_TEST

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
    printf("=== scores.c tests ===\n\n");
    remove(SCORES_FILE);

    printf("[ save_score ]\n");
    time_t base = time(NULL) - 120;
    save_score(base, 3, 0);
    save_score(base - 3600, 5, 1);
    save_score(base - 7200, 5, 1);
    save_score(base - 100, 5, 1);
    save_score(base - 200, 1, 0);

    FILE *fp = fopen(SCORES_FILE, "r");
    check("file created", fp != NULL);
    int lines = 0;
    char buf[MAX_LINE_LEN];
    while (fgets(buf, sizeof(buf), fp))
        lines++;
    fclose(fp);
    check("5 lines written", lines == 5);

    printf("\n[ load_scores + sorting ]\n");
    ScoreBoard sb = load_scores();
    check("loaded 5 entries", sb.count == 5);
    check("first is completed", sb.entries[0].completed == 1);
    check("first has 5 levels", sb.entries[0].levels_cleared == 5);
    check("second completed", sb.entries[1].completed == 1);
    check("fastest win is first", sb.entries[0].elapsed_seconds <
                                      sb.entries[1].elapsed_seconds);
    check("deaths after wins", sb.entries[3].completed == 0);
    check("best death is 3 lvls", sb.entries[3].levels_cleared == 3);
    check("worst death is 1 lvl", sb.entries[4].levels_cleared == 1);

    printf("\n[ print_scoreboard ]\n");
    print_scoreboard(&sb);

    printf("[ empty scoreboard ]\n");
    ScoreBoard empty = {NULL, 0};
    print_scoreboard(&empty);
    check("no crash on empty", 1);

    printf("[ missing file ]\n");
    free_scoreboard(&sb);
    remove(SCORES_FILE);
    ScoreBoard missing = load_scores();
    check("count 0", missing.count == 0);
    check("no crash", 1);
    free_scoreboard(&missing);

    printf("\n=== Results: %d passed, %d failed ===\n",
           tests_passed, tests_failed);
    return (tests_failed == 0) ? 0 : 1;
}

#endif /* SCORES_TEST */