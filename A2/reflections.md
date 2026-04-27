1. In `char_arithmetic/Q3/question3.c`, the bug was that `counter` was a `char`, and on this system `char` is signed. After reaching 127, incrementing wraps to -128 (overflow), so the condition `counter <= 200` stays true forever, causing an infinite loop. I fixed it by keeping `counter` as a `char`, but doing the comparison and printing using an `unsigned char` cast so the values correctly reach 200 and then stop.

2. 
   a. In C, when you pass an array to a function, it "decays" into a pointer to the first element. That means the function receives the address of the original array data. This is different from passing an `int` or `float`, which are passed by value (a copy). Because arrays are passed by address, changes to elements inside the function affect the original array.

   b. The function signature is missing a parameter for the length/size of the array. It should be something like:
      `void doubleValues(int arr[], int size);`
3.
   a. I used a `while` loop for the game loop because I had a `bool running` variable controlling whether the game continues. A `while (running)` loop makes the condition obvious and allows the program to keep repeating until the user enters `q`/`Q`, where I set `running = false`.

   b. If I switched to a `do while`, the loop body would run at least once automatically, and the condition check would happen at the end. I would keep the same `running` variable, but structure it as:
      `do { ... } while (running);`
      The main change is the loop condition placement: with `while`, the condition is checked before each iteration; with `do while`, it’s checked after the iteration.

4. One challenge was setting up my environment to compile and test reliably. At first I couldn’t compile locally, so I switched to working directly on the server and used VS Code Remote-SSH. That fixed most of the issues with C. Another challenge was debugging overflow problems, like the squares table and the char counter. I learned to identify data type limits, like `SHRT_MAX`, and take care of the overflow by validating input ranges or using correct casting.