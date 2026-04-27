#include <stdio.h>

/* TODO: Implement the function below
Function: void to_upper(char str[])
Purpose: Turn a string into all uppercase
Parameters:
  - char str[]: Input string
Behaviour:
    - Iterates over the character array
    - If the current char is lowercase, convert to upper.
Rules:
    - When converting a char, ONLY character
      literals are allowed (no integer literals)
        str[i] - 32 is NOT ALLOWED
    - integer literals are allowed elsewhere in the function
*/
void to_upper(char str[])
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] = str[i] - ('a' - 'A');
        }
        i++;
    }
}

/* TODO: Implement the function below
Function: void to_lower(char str[])
Purpose: Turn a string into all uppercase
Parameters:
  - char str[]: Input string
Behaviour:
    - Iterates over the character array
    - If the current char is uppercase, convert to lower.
Rules:
    - When converting a char, ONLY character
      literals are allowed (no integer literals)
        str[i] + 32 is NOT ALLOWED
    - integer literals are allowed elsewhere in the function
*/
void to_lower(char str[])
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = str[i] + ('a' - 'A');
        }
        i++;
    }
}

/* Test case:
    The program should print
    HELLO, WORLD!
    hello, world!
*/
int main()
{
    char message[] = "Hello, World!";
    to_upper(message);
    printf("%s\n", message);

    to_lower(message);
    printf("%s\n", message);

    return 0;
}