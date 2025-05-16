<<<<<<< HEAD
CC = gcc
CFLAGS = -Wall -Wextra -g -I.
LDFLAGS = -lpthread -lSDL2 -ljson-c

SRCS = src/list.c src/drone.c src/survivor.c src/ai.c src/map.c src/view.c src/globals.c
OBJS = $(SRCS:.c=.o)

TEST_SRCS = tests/stress_test.c tests/disconnect_test.c tests/multi_survivor_test.c
TEST_BINS = $(TEST_SRCS:.c=)

all: drone_simulator $(TEST_BINS)

drone_simulator: $(OBJS) src/controller.o
	$(CC) $(OBJS) src/controller.o -o $@ $(LDFLAGS)

tests/stress_test: tests/stress_test.o $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

tests/disconnect_test: tests/disconnect_test.o $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

tests/multi_survivor_test: tests/multi_survivor_test.o $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_BINS)
	@echo "Running all tests..."
	@for test in $(TEST_BINS); do \
		echo "Running $$test..."; \
		./$$test; \
	done

clean:
	rm -f $(OBJS) src/controller.o $(TEST_BINS) drone_simulator

.PHONY: all test clean
=======
#TODO
>>>>>>> 21daf67f026eb1dc7dd2fa47e2d384885b6f0ea5
