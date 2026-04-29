CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=c99

EX01 := ex01_cmd_line_unit_test
EX02 := ex02_my_cmd

.PHONY: all test clean

all: test_cmd_line test_my_cmd

test: all
	./test_cmd_line
	./test_my_cmd

test_cmd_line: $(EX01)/cmd_line.c $(EX01)/test_cmd_line.c
	$(CC) $(CFLAGS) $^ -o $@

test_my_cmd: $(EX02)/my_cmd.c $(EX02)/test_my_cmd.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f test_cmd_line test_my_cmd
