#include <stdio.h>
#include <string.h>

int best_score(const char *line);

int main(int argc, char **argv) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            const char *word = argv[i];
            if (best_score(word) == 0)
                printf("%s\n", word);
        }
        return 0;
    }

    char line[64];
    int skip = 0;
    while (fgets(line, sizeof(line), stdin)) {
        // Lines longer than 64 characters will be skipped.
        int prev_skip = skip;
        skip = strchr(line, 0)[-1] != '\n';
        if (skip || prev_skip)
            continue;
        if (best_score(line) == 0)
            printf("%s", line);
    }
    return 0;
}
