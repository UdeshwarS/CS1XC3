# Terminal Run Documentations

**Name:** Udeshwar Singh Sandhu

**Email:** sandhu3@mcmaster.ca



---

## Build and Run the Game

Build the main game:

```bash
make
```

Run the main game:
```bash
./terminal_run
```
You can also build and run it in one command with:

```bash
make run
```
The default build uses gcc with the flags -Wall -Wextra, which enable extra compiler warnings.
---

## Modules

main.c:
This file controls the overall game loop and game states. It handles the start screen, pause screen, level transitions, win/game over screens, rendering, achievement checking, and the main gameplay loop.

board.c / board.h:
This module loads level files into a dynamically allocated Board struct, stores static tiles, records the player spawn, exit, and enemy spawn positions, and provides helper functions such as get_tile() and is_walkable(). The board only stores static map data and never stores moving entities.

player.c / player.h:
This module manages the player’s position, lives, invincibility timer, respawning, and movement. It returns a MoveResult so main.c can react differently to normal movement, blocked movement, and reaching the exit.

enemy.c / enemy.h:
This module creates enemies from the enemy spawn points on the board and moves them around the map. Enemies choose random directions and step counts, avoid obstacles and boundaries, and do not move through each other.

scores.c / scores.h:
This module saves finished runs to scores.csv, loads score history, sorts entries best-first, frees scoreboard memory, and prints the scoreboard for the start screen.

input.c / input.h:
This module is provided code for handling raw terminal input. It allows the game to read single keypresses without waiting for Enter and supports both blocking menu input and non-blocking gameplay input.

types.h:
This header stores shared types used across multiple modules, such as Position and Direction.

config.h:
This header stores game configuration constants such as tick speed, invincibility duration, starting lives, score file names, and the clear-screen ANSI escape sequence.

Makefile:
The Makefile builds the game, builds test versions of each module, runs all automated tests, and supports an extra credit build target.

/levels:
This folder contains the level text files used by the game. Each level is loaded based on the current value of g_level.
---

## Custom Builds for Testing
### MAIN GAME

```bash
#Build the game
make
```

```bash
#Run the Game
./terminal_run
```

### INDIVIDUAL TEST MODULES

```bash
#Build board.c tests
make test_board
./test_board
```

```bash
#Build player.c tests
make test_player
./test_player
```

```bash
#Build enemy.c tests
make test_enemy
./test_enemy
```

```bash
#Build score.c tests
make test_scores
./test_scores
```

```bash
#Build input.c tests
make test_input
./test_input
```

```bash
# Run all automated tests
make test_all
```

```bash
# Extra credit build
make extra_credit
#This compiles the game with -DEXTRA_CREDIT and produces terminal_run_ec
```
```bash
# Cleaning Build files
make clean
#This removes the compiled game, object files, test executables, and scores.csv
```
---
### Testing main.c

`main.c` cannot be unit tested the way the other modules can. To test it, try:

1. Start the game from the start screen with 1 .
2. Quit from the start screen with 2 .
3. Move with W, A, S, and D.
4. Pause during gameplay with Q.
5. Resume from the pause menu.
6. Return to the main menu from the pause menu.
7. Reach the exit X and confirm the next level loads.
8. Get hit by an enemy and confirm the hit screen, respawn, and invincibility work.
9. Lose all lives and confirm the game over screen appears.
10. Complete all levels and confirm the win screen appears.
11. Check that scores appear on the start screen after completed runs or game over runs.


---

## Known issues and limitations

1. main.c is tested manually through gameplay rather than through automated unit tests.
2. The scoreboard file can contain older runs from earlier versions unless scores.csv is deleted.
3. Enemy movement is random, so gameplay is not deterministic between runs.


---

## Extra credit and customizations

I added two extra levels, `level06.txt` and `level07.txt`.

To keep the standard version unchanged, I used conditional compilation in `main.c`:
- normal build stops after level 5
- extra credit build allows levels 6 and 7

Run the standard version with:

```bash
make
./terminal_run
```
Run the extra credit version with:
```bash
make extra_credit
```
make extra_credit builds and runs terminal_run_ec.
---

## Reflections
### 1. Storage classes

Find one example of each storage class used in the codebase (`auto`, `static` local, `static` file-scope, `extern`) and explain in your own words what it does at that specific location. Why does that storage class apply there, or, why is it not the best choice?

**`auto`:**
In main.c, the line auto GameState state = STATE_START; is an example of auto. This is the normal storage class for a local variable inside a function. The variable is created when main() begins and exists only during that function call. In this case, state belongs only to main(), so local automatic storage makes sense. Writing auto is not necessary because local variables are automatic by default, but it is included here to demonstrate the keyword.

**`static` (local):**
In enemy.c, static int seeded = 0; inside init_enemies() is a local static variable. It keeps its value between function calls, unlike a normal local variable. That is useful here because the random number generator should only be seeded once. If seeded were automatic instead, it would reset to 0 every time the function was called and srand() would run again each time.

**`static` (file-scope):**
In enemy.c, static const int row_delta[] = { -1, 1, 0, 0 }; is a file-scope static object. It can only be used inside enemy.c. That is a good choice because the movement delta table is only needed in that file, so static helps with information hiding and prevents name collisions with other files.

**`extern`:**
In enemy.c, the line extern int g_level; refers to the variable that is actually defined in main.c. This lets enemy.c read the current level number without creating a second copy of the variable. It works here because the enemy module needs the current level to scale difficulty. However, it also creates coupling between enemy.c and main.c, so passing the level as a parameter would be a cleaner alternative.
---

### 2. File I/O

`load_board()` reads the board file in two passes, calling `rewind()` between them. Why are two passes necessary? Could you redesign `load_board()` to use only one pass? What tradeoffs would that involve?

Two passes are useful because the program does not know the board dimensions or the number of enemy spawns until it reads the file. In the first pass, it can count the number of rows, find the maximum row length, count the enemies, and validate the characters. After that, it knows exactly how much memory to allocate for the board and enemy spawn array. In the second pass, it actually fills the arrays.

Yes, it could be redesigned to use one pass, but then the code would need to allocate memory gradually while reading. For example, it could use realloc() to grow the rows array and possibly grow the enemy spawn array whenever another enemy is found. That would avoid rereading the file, but it would make the code more complicated and less predictable. The two-pass design is simpler, easier to reason about, and fits this assignment well.

---

### 3. Choose one:

#### Something unfamiliar

Find one thing in the provided code (e.g. `input.c`, `config.h`, anywhere in `main.c`) that you didn't recognise or fully understand. Research it, then describe: what it is, what role it plays in this implementation, and whether you can think of an alternative approach.

**What I looked up:**
nanosleep() and struct timespec
**What it is:**
nanosleep() is a POSIX function that pauses the program for a specified amount of time. struct timespec stores that time using seconds and nanoseconds.
**Its role in this implementation:**
This game uses nanosleep() for short pauses such as the hit screen and the level clear screen. That makes the screens visible for a brief moment before the game continues. It helps the game feel more polished because transitions are noticeable instead of instant.
**Alternative approach (if any):**
An alternative would be to use a loop based on current_time() and keep checking until enough time has passed. Another alternative on some systems would be usleep(), but nanosleep() is more standard and gives clearer control over timing.
#### Profiling with gprof 

Explore the game with gprof, e.g.,

```bash
gcc -pg -Wall -Wextra main.c board.c player.c enemy.c scores.c input.c -o terminal_run_prof
./terminal_run_prof
gprof terminal_run_prof gmon.out > profile.txt
```

Which function was called most often? Does that make sense? Was anything surprising?

Not chosen. I answered the "Something unfamiliar" option instead.
---
### 4. Information hiding

The `Board` struct is never modified by `player.c` or `enemy.c`, they only read from it. How does the design enforce this? What would break, and where, if `enemy.c` directly modified `board->tiles` instead of just reading positions?

The design enforces this mainly by responsibility and by API usage. The board module owns the static map data, while the player and enemy modules only move their own positions. Functions like get_tile() and is_walkable() let other modules read board information without needing to change it. Also, rendering is centralized in main.c, which layers the player and enemies on top of the static board instead of storing them inside the board.

If enemy.c directly modified board->tiles, several things could break. First, enemies could leave behind incorrect characters when they move away, creating “ghost” enemies on the map. Second, an enemy moving onto X could overwrite the exit tile, which would break level completion. Third, collision logic in main.c depends on comparing positions, not reading enemy characters from the board, so the board state and actual enemy state could become inconsistent. Overall, it would violate the separation between static world data and moving entities and make the code much harder to maintain.
---
## Extra Credit and Customizations

I added two extra levels, `level06.txt` and `level07.txt`.

To keep the standard version unchanged, I used conditional compilation in `main.c`:
- normal build stops after level 5
- extra credit build allows levels 6 and 7

Run the standard version with:

```bash
make
./terminal_run
```
Run the extra credit version with:
```bash
make extra_credit
```
make extra_credit builds and runs terminal_run_ec.