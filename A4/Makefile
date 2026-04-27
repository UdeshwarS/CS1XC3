CC     = gcc
CFLAGS = -Wall -Wextra

OBJS = main.o board.o player.o enemy.o scores.o input.o

# Default — build and run the game.
terminal_run: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o terminal_run

run: terminal_run
	./terminal_run

# Object file rules with header dependencies.
main.o:   main.c   config.h types.h board.h player.h enemy.h scores.h input.h
	$(CC) $(CFLAGS) -c main.c -o main.o

board.o:  board.c  board.h config.h types.h
	$(CC) $(CFLAGS) -c board.c -o board.o

player.o: player.c player.h board.h config.h types.h
	$(CC) $(CFLAGS) -c player.c -o player.o

enemy.o:  enemy.c  enemy.h board.h config.h types.h
	$(CC) $(CFLAGS) -c enemy.c -o enemy.o

scores.o: scores.c scores.h config.h
	$(CC) $(CFLAGS) -c scores.c -o scores.o

input.o:  input.c  input.h config.h
	$(CC) $(CFLAGS) -c input.c -o input.o

# Test targets.
test_board: board.c board.h config.h types.h
	$(CC) $(CFLAGS) -DBOARD_TEST board.c -o test_board

test_player: player.c board.c player.h board.h config.h types.h
	$(CC) $(CFLAGS) -DPLAYER_TEST player.c board.c -o test_player

test_enemy: enemy.c board.c enemy.h board.h config.h types.h
	$(CC) $(CFLAGS) -DENEMY_TEST enemy.c board.c -o test_enemy

test_scores: scores.c scores.h config.h
	$(CC) $(CFLAGS) -DSCORES_TEST scores.c -o test_scores

test_input: input.c input.h config.h
	$(CC) $(CFLAGS) -DINPUT_TEST input.c -o test_input

test_all: test_board test_player test_enemy test_scores
	@echo "--- test_board ---"  && ./test_board
	@echo ""
	@echo "--- test_player ---" && ./test_player
	@echo ""
	@echo "--- test_enemy ---"  && ./test_enemy
	@echo ""
	@echo "--- test_scores ---" && ./test_scores
	@echo ""
	@echo "All automated tests passed."

# Extra credit build via -DEXTRA_CREDIT.
# Compiles directly (no separate .o files) to avoid conflicting with
# the default object files which were compiled without the flag.
extra_credit: main.c board.c player.c enemy.c scores.c input.c
	$(CC) $(CFLAGS) -DEXTRA_CREDIT main.c board.c player.c enemy.c scores.c input.c -o terminal_run_ec
	./terminal_run_ec


clean:
	rm -f terminal_run $(OBJS) \
	      test_board test_player test_enemy test_scores test_input \
	      scores.csv

.PHONY: run test_all clean