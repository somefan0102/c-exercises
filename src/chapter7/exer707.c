#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include "nstring.h"

#define MAX_BUFFER 0xfff
#define MAX_MATCHES 200
// #define DEBUG

typedef struct {
    int line;
    int column;
} Match;

// Writes the `n`th line of `stream` to the `buffer`, with precaution of its `buffer_size`.
void fetchLine(FILE *stream, int n, char *buffer, size_t buffer_size);

// Returns the amount of matches of `pattern` in `*input` file and pastes each match
// to a `matches_array[]` of `matches_size` elements, with the utility of `buffer` and its `buffer_size`.
int find(char *pattern, FILE *input, Match *matches[], size_t matches_size, char *buffer, size_t buffer_size);

int main(int argc, char **argv) {
    FILE *stream;
    char buffer[MAX_BUFFER];
    Match *matches[MAX_MATCHES];
    char *pattern, *filename;
    int found, is_stdin = 0;

    if (argc <= 1) {
        printf("Error: No pattern argument.\n");
        printf("Usage: find [pattern] files...");
        return 1;
    } else if (argc == 2) {
        int ch = 0;
        is_stdin = 1;
        stream = fopen("temp", "w+");

        if (stream == NULL) {
            perror("temp");
            return 1;
        }

        while (ch != EOF) {
            fputc((ch = getchar()), stream);
        }
    }

    pattern = argv[1];

    for (int arg = 2; arg < argc || is_stdin; arg++) {
        if (is_stdin == 0) {
            filename = argv[arg];
            stream = fopen(filename, "r");

            if (stream == NULL) {
                perror(filename);
                return 1;
            }
        }

        found = find(pattern, stream, matches, MAX_MATCHES, buffer, MAX_BUFFER);

        printf("[File %i: %s] (%i matches)\n", arg-1, (is_stdin) ? "stdin" : filename, found);
        for (int i = 0; matches[i]; i++) {
            fetchLine(stream, matches[i]->line, buffer, MAX_BUFFER);
            printf("%3i. (Line %2i) ", i+1, matches[i]->line);
            for (int j = 0; buffer[j]; j++) {
                if (j >= matches[i]->column-1 && j < matches[i]->column+strlen(pattern)-1) {
                    printf("\x1b[0;44m");
                }
                putchar(buffer[j]);
                if (j >= matches[i]->column-1 && j < matches[i]->column+ strlen(pattern)-1) {
                    printf("\x1b[0m");
                }
            }
            putchar('\n');
        }

        if (is_stdin) {
            if (fclose(stream) == EOF) {
                perror("stdin");
                return 1;
            }
            remove("temp");
        } else {
            if (fclose(stream) == EOF && is_stdin) {
                perror(filename);
                return 1;
            }
            putchar('\n');
        }
        is_stdin = 0;
    }

    return 0;
}

int find(char *pattern, FILE *input, Match *matches[], size_t matches_size, char *buffer, size_t buffer_size) {
    int line = 1, column = 1;
    int found = 0;
    int ch;

    // Reset the stream position.
    if (fseek(input, 0L, SEEK_SET) != 0) {
        perror("find failed");
        return 0;
    }

    while (feof(input) == 0) {
        int i = 0;
        int position = 0;

        // Get next line ready.
        if (ch == '\n') {
            line++;
            column = 1;
        }

        // Copy next word to buffer.
        while (!isspace(ch = fgetc(input)) && !feof(input)) {
            if (buffer_size-1 > i) {
                buffer[i++] = ch;
            }
            column++;
        }
        buffer[i] = '\0';
        column++;

        // If word matches, allocate a slot and add to match array.
        strlower(buffer);
        if ((position = strend(buffer, pattern)) != -1 && matches_size-1 > found) {
            matches[found] = (Match *)malloc(sizeof(Match));
            if (matches[found]) {
                matches[found]->line = line;
                matches[found]->column = column-strlen(buffer)-1+position;
            }
            found++;
        }
    }

    matches[found] = NULL;

    return found;
}

void fetchLine(FILE *stream, int n, char *buffer, size_t buffer_size) {
    int i, ch;
    int line = 1;

    assert(n > 0);

    // Reset the stream position.
    if (fseek(stream, 0L, SEEK_SET) != 0) {
        perror("fetchLine failed");
        return;
    }

    // Get to the line position.
    while (!feof(stream) && n > line) {
        if (fgetc(stream) == '\n') {
            line++;
        }
    }

    // Copy line to buffer.
    i = 0;
    if (!feof(stream)) {
        while (i < buffer_size-1 && (ch = fgetc(stream)) != '\n' && !feof(stream)) {
            buffer[i++] = ch;
        }
    }
    buffer[i] = '\0';
}

/*
707: Modify the pattern finding program of Chapter 6 to take its input from a set of
     named files or, if no files are named as arguments, from the standard input.
     Should the file name be printed when a matching line is found?
*/