#include <stdio.h>
#include <string.h>

int valid_word(const char *line);

int main(int argc, char **argv) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            const char *word = argv[i];
            if (valid_word(word))
                printf("%s\n", word);
        }
        return 0;
    }

    char line[64];
    int skip = 0;
    while (fgets(line, sizeof(line), stdin)) {
        // Lines longer than 64 characters will be skipped.
        if (strchr(line, 0)[-1] != '\n')
            skip = 1;
        if (skip)
            continue;
        skip = 0;
        if (valid_word(line))
            printf("%s", line);
    }
    return 0;
}
