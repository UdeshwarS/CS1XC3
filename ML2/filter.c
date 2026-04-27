/*
  Major Lab — File 3: filter.c
  ---------------------------------------------------------------------
  What you implement:
    const int* filter_readings(const int in[], int n, int *ignored_out, int *stopped_out)

  Rules:
    - Process readings from left to right.
    - Range rule: if reading is outside [-100, 100], IGNORE it (continue) and count it as ignored.
    - Sentinel rule: if reading equals 9999, STOP immediately (break) and set *stopped_out = 1.
    - Glitch rule:
        * Track last ACCEPTED reading.
        * If abs(current - last_accepted) > 30, treat as glitch:
            IGNORE (continue) and count as ignored.
      Note: the first accepted reading has no glitch comparison.

    - Store accepted readings into out[] in the same order.

  Return:
    - Return a pointer to an integer array stored in a STATIC buffer.
    - The final element MUST be -1 (sentinel).

  Local testing:
    - Edit TEST_READINGS below.
*/

#include <stdio.h>

#define ABS(x) (((x) < 0) ? (-(x)) : (x))

/* # Edit these for local testing */
int TEST_READINGS[] = { 10, 15, 60, 59, 200, 61, 30, 9999, 40 };
int TEST_READINGS_N = (int)(sizeof(TEST_READINGS) / sizeof(TEST_READINGS[0]));

/*
  TODO: Implement this.
*/
const int* filter_readings(const int in[], int n, int *ignored_out, int *stopped_out)
{
    static int out[128];  /* fixed output buffer */

    int ignored = 0;
    int stopped = 0; 
    int out_index = 0;
    int have_last = 0;
    int last_accepted = 0;
    
    for (int i=0; i<n; i++){
      int x=in[i];

      if (x==9999){
        stopped = 1;
        break;
      }

      if (x < -100 || x > 100){
        ignored++;
        continue;
      }
      
      if (have_last ){
        if (ABS(x-last_accepted) > 30){
          ignored++;
          continue;
        }
      }

      out[out_index] = x;
      out_index++;

      last_accepted = x;
      have_last = 1;
    }

    out[out_index] = -1;

    if (ignored_out) {
      *ignored_out = ignored;
    }

    if (stopped_out) {
      *stopped_out = stopped;
    }
    return out;
}

/* Global test function (prints results for TEST_READINGS). DO NOT EDIT */
void run_test_filter(void)
{
    int ignored = 0;
    int stopped = 0;

    const int* cleaned = filter_readings(TEST_READINGS, TEST_READINGS_N, &ignored, &stopped);
    if (cleaned == NULL)
    {
        printf("ERROR\n");
        return;
    }

    printf("ignored=%d\n", ignored);
    printf("stopped=%d\n", stopped);
    printf("cleaned:\n");
    for (int i = 0; cleaned[i] != -1; i++)
    {
        printf("%d\n", cleaned[i]);
    }
}

int main(void)
{
    run_test_filter();
    return 0;
}