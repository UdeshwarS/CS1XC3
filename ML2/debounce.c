/*
  Major Lab — File 2: debounce.c
  -------------------------------------------------------------------------
  What you implement:
    const char* debounce_log(const char* in);

  Requirements (debounce_log):
    - Remove ONLY consecutive duplicate characters.
    - Preserve order.

  Requirements (main):
    - Read exactly ONE line from stdin into a buffer.
    - Call debounce_log(...)
    - Do NOT print prompts.
*/

#include <stdio.h>

/* Optional: Edit this and use run_test_debounce() to test without stdin. */
char TEST_INPUT[512] = "HHeellooo!!";

/*
  debounce_log
  ------------
  Input:
    - in: a null-terminated C string (the line read from stdin; NO SPACES)

  Output:
    - Return a pointer to a debounced C string stored in a STATIC buffer.
    - The debounced string must be null-terminated ('\0').
    - Example: "aaabcccdd" -> "abcd"

  Return:
    - pointer to static output string
*/
const char* debounce_log(const char* in)
{
    static char out[512];

    if (in==NULL) {
      out[0] = '\0';
      return out;
    }
    
    int j = 0;

    if (in[0] != '\0') {
      out[j] = in[0];
      j++;
    }

    for (int i= 1; in[i] != '\0'; i++) {
      if (in[i] !=in[i-1]){
        out[j] = in[i];
        j++;
      }
    }

    out[j] = '\0';
    return out;
}

/* Global test function (prints output for TEST_INPUT). DO NOT EDIT */
void run_test_debounce(void)
{
    const char* res = debounce_log(TEST_INPUT);
    if (res == NULL)
    {
        printf("ERROR\n");
        return;
    }
    printf("%s\n", res);
}

int main(void)
{
    char in[512];

    /* 1) Read one line from stdin */
    if (fgets(in, sizeof(in), stdin) == NULL)
    {
        return 0; /* EOF / no input */
    }

    /* 2) Remove trailing '\n' if present */
    for (int i = 0; in[i] != '\0'; i++)
    {
        if (in[i] == '\n')
        {
            in[i] = '\0';
            break;
        }
    }

    /* 3) Call debounce_log and print result */
    const char* res = debounce_log(in);
    if (res == NULL)
    {
        printf("ERROR\n");
        return 0;
    }

    printf("%s\n", res);
    return 0;
}
