/*
  Major Lab — File 1: digits.c
  ------------------------------------------------------------------------------
  What you implement:
    const int* digits_ltr(unsigned int n);

  Requirements:
    - Extract digits WITHOUT converting to a string.
    - Return an array of digits in LEFT-TO-RIGHT order (most significant first).
    - The returned array MUST end with a sentinel value of -1.
    - Handle n == 0 (the returned array should be: 0, -1).

  Testing:
    - Change TEST_N below.
    - Compile and run normally; main prints digits until it sees -1.

  Notes:
    - The returned pointer must remain valid after the function returns,
      so use a static array inside digits_ltr().
*/

#include <stdio.h>

/* Edit this for testing purposes */
unsigned int TEST_N = 50720;

/*
  Inputs:
    - n: a non-negative integer whose digits you have to extract.

  Output (returned array):
    - Return a pointer to an integer array containing digits of n
      in LEFT-TO-RIGHT order.
    - The final element MUST be -1 (sentinel).

  Task:
    - Extract digits WITHOUT converting to a string.
    - Use integer division and modulus.
    - Special case: if n == 0, return [0, -1].
*/
const int* digits_ltr(unsigned int n)
{
    static int digits[32];

    if (n==0) {
      digits[0] = 0;
      digits[1] = -1;
      return digits;
    }

    unsigned int temp = n;
    int count = 0;
    while (temp > 0) {
      count++;
      temp /= 10;
    }
    
    temp = n;
    for (int i=count-1; i>=0; i--) {
      digits[i] = (int)(temp % 10);
      temp /= 10;
    }

    digits[count] = -1;
    return digits;
}

/* Global test function (DO NOT EDIT) */
void run_test_digits(void)
{
    const int* d = digits_ltr(TEST_N);
    if (d == NULL)
    {
        printf("ERROR\n");
        return;
    }

    for (int i = 0; d[i] != -1; i++)
    {
        printf("%d\n", d[i]);
    }
}

int main(void)
{
    run_test_digits();
    return 0;
}
