.POSIX:

CC = c99
cppflags = -D_POSIX_C_SOURCE=200809L
cflags = -Wall -Wextra -Werror
all_cflags = $(cppflags) $(CPPFLAGS) $(cflags) $(CFLAGS)

.PHONY: all clean
all: bin/names bin/test patp.txt
clean:
	rm -f $(targets) src/*.o bin/* patp.txt

.SUFFIXES: .c .o
.c.o:
	$(CC) $(all_cflags) -c $< -o $@

bin/names: src/main.o src/match.o
	mkdir -p bin
	$(CC) src/main.o src/match.o -o $@

bin/test: src/test.o src/match.o
	mkdir -p bin
	$(CC) src/test.o src/match.o -o $@

patp.txt: bin/names
	bin/names < /usr/share/dict/words | \
		awk '{print(length, $$0)}' | sort -k 1nr | \
		sed 's/^[0-9]* //' > $@
