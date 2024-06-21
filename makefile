.POSIX:

CC = c99
cppflags = -D_POSIX_C_SOURCE
cflags = -g -Wall -Wextra -Werror
all_cflags = $(cppflags) $(CPPFLAGS) $(cflags) $(CFLAGS)

.PHONY: all clean
all: bin/names bin/test
clean:
	rm -f $(targets) src/*.o bin/*

.SUFFIXES: .c .o
.c.o:
	$(CC) $(all_cflags) -c $< -o $@

bin/names: src/main.o src/match.o
	mkdir -p bin
	$(CC) src/main.o src/match.o -o $@

bin/test: src/test.o src/match.o
	mkdir -p bin
	$(CC) src/test.o src/match.o -o $@
