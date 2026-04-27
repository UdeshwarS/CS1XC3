# Game Programming

<aside>
📚

The part includes the following concepts:

- Basic C syntax: variables, constants, including header files, functions
- Control flow: nested for-loops, while, do while, conditionals, switch statements.
- Input/Output: printf and scanf with format specifiers
</aside>


## Program Overview

You will implement a program in C that executes the basic game mechanic of moving the player’s position. 

### **WORLD LAYOUT**

Our world is simple a set of 8x8 characters.

- The player’s position is represented with `P` and takes up one cell (x,y).
- Empty cells (wherever the player isn’t located) are represented by `.` (period).

If player is at (0,0) the world looks like:
```
P.......
........
........
........
........
........
........
........
```



### **START**

**Player position:**

The player always starts at (0,0).

Two variables represent the player’s position:

- `player_x`
- `player_y`

**Game loop condition:** 

A `bool` variable called `running` is initialized as `true` to be used as the game loop condition.

**Start screen:**

When you run `./mygame` the terminal displays:

```
P.......
........
........
........
........
........
........
........

Player position: (0, 0)
Input command (W/A/S/D to move, Q to quit) and hit enter: 
```

### **PLAYER INPUT**

**Move commands:** 

The player will use w/s/a/d or W/S/A/D to move their position up/down/left/right. 

**Quit command:**

The player can quit the game using q or Q. 

### UPDATE STATE

**Move player:**

The player’s position is updated based on the input.

From the starting point (0,0) 

- If the player enters `d` - `d` - `d`, their position should be (3, 0)
- If the player enters `d` - `d` - `s` - `s`, their position should be (2, 2). If the player subsequently presses `a`, the position would be (1,2).

**BOUNDARIES:**

The player **may not exit** the 8x8 bounds. 

- If the player’s input would cause their position to step out of bounds, the program should simply not update the player’s position.
- For example, if the player is at (3,0) and they input `w`, their position should should not update to (3,-1). It should remain at (3,0).


### **DRAW SCREEN**

A function called `draw_screen` takes the player’s position as input and “draws” the world in its current state by printing it to the terminal.

If the player is at (2,2) the screen shows: 

```
........
.P......
........
........
........
........
........
........
```

If the position updates to (3,2), `draw_screen` will `clear` the terminal and print:

```
........
..P.....
........
........
........
........
........
........
```

## Instructions

This part of the assignment requires you to implement code in `game/Q1/question1.c` and `game/Q2/mygame.c`. The expected behaviour of `mygame.c` is detailed in [EXPECTED BEHAVIOUR](#expected-behaviour). 

**ALLOWED HEADERS:** At the top of `mygame.c` we have three preprocessor directives that enable us to `printf` and `scanf`, use `bool` variables for holding `true` or `false`, and use `system("clear")` to clear the game screen. You may not include any other header files.

```c
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
```

### EXPECTED BEHAVIOUR

There are numerous ways to implement `mygame.c`. Your implementation is expected to behave like so:

**1) Start the program with `./mygame`.**

```
**user@cs1xc3:~$** ./mygame
```

**Expected behaviour: The terminal window shows:**

```
P.......
........
........
........
........
........
........
........

Player position: (0, 0)
Input command (W/A/S/D to move, Q to quit) and hit enter: 

```

- Notice that the command prompt “**user@cs1xc3:~$**” is not there.
- There is nothing displayed above the game world.
- The cursor should be blinking/showing *underneath* this output.
- There is an empty line between the ‘world’ and `Player position: (0,0)`

**2) Press `s` and hit `Enter`** 

**Expected behaviour: The terminal window shows:**

```
........
P.......
........
........
........
........
........
........

Player position: (0, 1)
Input command (W/A/S/D to move, Q to quit) and hit enter: 
```

- `P` is now in the second row and first column.
- Player position is now: `Player position: (0,1)`

**3) Press `d` and hit `Enter`** 

**Expected behaviour:**
```
.P......
........
........
........
........
........
........

Player position: (1, 1)
Input command (W/A/S/D to move, Q to quit) and hit enter:
```

- `P` moved 1 cell to the right

**4) Press `w` and hit `Enter`**

**Expected behaviour:** 

```
.P......
........
........
........
........
........
........
........

Player position: (1, 0)
Input command (W/A/S/D to move, Q to quit) and hit enter: 
```

- `P` moved up one cell

**5) Press `w` and hit `Enter`** 

**Expected behaviour: Terminal window shows:**
```
.P......
........
........
........
........
........
........
........

Player position: (1, 0)
Input command (W/A/S/D to move, Q to quit) and hit enter: 

```


- `P` is in the same position. The player is in the highest possible row, so the position is not updated.

**6) Type `DdD` and hit `Enter`** 


**Expected behaviour: The terminal window shows:**
```
....P...
........
........
........
........
........
........
........

Player position: (4, 0)
Input command (W/A/S/D to move, Q to quit) and hit enter: 
```

- The player moved 3 spaces to the right as a result of encountering three `d` commands.
- The program’s commands should be *case-insensitive* (i.e., uppercase and lowercase are valid)

**7) Type `dddddddddd` and hit `Enter`**

**Expected behaviour:**
```
.......P
........
........
........
........
........
........
........

Player position: (7, 0)
Input command (W/A/S/D to move, Q to quit) and hit enter: 
```

- The player went as far right as it can go.

**8) Type `ssssss` and hit `Enter`**


**Expected behaviour:**

```
........
........
........
........
........
........
.......P
........

Player position: (7, 6)
Input command (W/A/S/D to move, Q to quit) and hit enter: 
```

- Player’s position is (7, 6). There is only one more space before the lower boundary.

**9) Type a bunch of `s` commands and hit `Enter`** 

**Expected behaviour:**

```
........
........
........
........
........
........
........
.......P

Player position: (7, 7)
Input command (W/A/S/D to move, Q to quit) and hit enter: 
```

- The player only goes as far as the lowest row.

**10) Type a bunch of `a` commands and hit `Enter`.**

**Expected behaviour:** 

```
........
........
........
........
........
........
........
P.......

Player position: (0, 7)
Input command (W/A/S/D to move, Q to quit) and hit enter: 
```

- The player’s position stops at the left boundary.

**11) Type `q` and hit `Enter`** 

**Expected behaviour: The terminal window shows:**
```
........
........
........
........
........
........
........
P.......
Game ended.
user@cs1xc3:~$
```

- World state still displaying
- Prints Game ended.
- The command prompt “**user@cs1xc3:~$**” returns.

### Question 1. Drawing the Game State

Complete the code in `game/Q1/question1.c`. 

Create global constants for the world boundaries:

- `R_BOUND` (right boundary)
- `L_BOUND` (left boundary)
- `T_BOUND` (top boundary)
- `B_BOUND` (bottom boundary)

Implement the `draw_screen()` function to display the game world:

```c
Function: void draw_screen(int player_x, int player_y)
Purpose: Draws game state to terminal 
Parameters:
  - player_x: Player's current x-coordinate
  - player_y: Player's current y-coordinate
Assumptions:
  - Coordinates are within L_BOUND to R_BOUND and T_BOUND to B_BOUND 
behaviour: 
	- Prints '.' for empty cells and 'P' at player's position
	- Uses R_BOUND, L_BOUND, T_BOUND, B_BOUND
```

Hints:

- Use nested for-loops
- Print `P` at player's position, `.` everywhere else
- Don't forget newlines at the end of each row

Expected output when player is at (0,0):

```
P.......
........
........
........
........
........
........
........
```

Testing: Write code in `main()` to test your implementation.

### Question 2. Game Loop

Complete the code in `game/Q2/mygame.c`. Your program should contain a game loop that processes user commands to move the player around an 8x8 world. Follow the guide below and the TODOs in the C file. 

**TODO: Setup variables and functions**

Global constants: 

- `R_BOUND`, `L_BOUND` , `T_BOUND`, `B_BOUND` for 8x8 world.

Functions:

- Place your `draw_screen` implementation under `system("clear");` in the `draw_screen` function in `mygame.c`

Variables for `main()`:

- `player_x` and `player_y` to track the player's current coordinates. Initialize them to start the player at (0,0).
- `bool running` to control the game loop. Initialize it so the loop will execute.
- `input` to store a single character command from the user.

**TODO: Implement game loop**

Create your game loop in `main()` using the variables and draw screen function you created. You can choose whether you want to use a `while` or `do while` statement. The loop should continue until the player enters `q` or `Q`. You may write code outside of the loop if appropriate. The loop should do the following (not necessarily in the order listed):

- Display current state: Call `draw_screen()` with the player's current position. Print the player's coordinates: `"Player position: (x, y)"`. Prompt for input: `"Input command (W/A/S/D to move, Q to quit) and hit enter: "`

- Get user input: Read one character using `scanf`

- Process the command: Use a `switch` statement to handle user input.
    - Player movement: Only update the Player position if the move is valid (won’t go out of bounds).
        
        ```
        w/W: Move player up
        a/A: Move player left
        s/A: Move player down
        d/D: Move player right
        ```
        
    - End game: When the player quits, print: `"Game ended."`
        
        ```
        
        q or Q: End the game
        Any other input: Ignore. 
        ```
        

**TODO: Test your game**

Run your program and test the following:

- Move in all four directions (W/A/S/D) using lowercase and uppercase commands.
- Try to move past boundaries (player should stop at edge)
- Enter invalid commands
- Quitting with 'Q' or 'q'
- Follow the steps in EXPECTED BEHAVIOUR to confirm your program operates as expected.