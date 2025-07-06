#include <stdio.h>
#include "input.h"
#include "nstring.h"
#include "options.h"

#define CLEAR "\x1b[2J\x1b[H"
#define HELP \
"USAGE: tail OPTION...\n\
\n\
tail is a program that allows you to write lines.\n\
After exiting, it will print the last lines of input you wrote.\n\
\n\
OPTIONS:\n\
\n\
-h         Display this information.\n\
-(number)  Prints the last (number) lines of input. Default is 10.\n\
           Should be a standalone option.\n\
-c         Clear screen before and after writing. For *nix terminals only.\n\
-n         Number list of last lines.\n\
-s         Safe mode.\n"

#define DEFAULT_LAST 10
#define MAX_LINES 200
#define MAX_BUFFER 5000

int is_help = 0;
int is_clear = 0;
int is_numbered = 0;
int is_safe = 0;
int last_lines = DEFAULT_LAST;

char *lines[MAX_LINES];
char buffer[MAX_BUFFER];

Flag flags[] = {
    { .name = 'h', .variable = &is_help, },
    { .name = 'c', .variable = &is_clear, },
    { .name = 'n', .variable = &is_numbered, },
    { .name = 's', .variable = &is_safe, },
};

Flag *p_flags[] = {
    &flags[0], &flags[1], &flags[2], &flags[3],
};

int getNumber(char *prefix, int number);

int main(int argc, char *argv[]) {
    int exit;        // Stores return code from `parseOption`.
    int length;      // Stores length from `getline`.
    int lc;          // Stores next index of `*lines`.
    char *p;         // Stores a pointer to a string for `buffer`.
    
    for (int i = 1; i < argc; i++) {
        if (*argv[i] != '-') {
            optionError(argv[i], "No option found.");
            return 1;
        }
        exit = parseOption(argv[i], p_flags, 0, getNumber);
        if (exit == 1) {
            return 1;
        } else if (exit == 2) {
            return 0;
        }
    }

    if (is_clear) {
        printf("%s", CLEAR);
    }

    printf("-- You can now write your lines here. Exit when done.\n");

    /*
       `MAX_BUFFER-(p-buffer)` is the amount of elements left to hold some part of the inputs.
       `getline` returns a null-included length of string or 0 if EOF.
    */
    p = buffer;
    lc = 0;
    while (lc < MAX_LINES && (length = getline(p, MAX_BUFFER-(p-buffer))) != 0 && length < MAX_BUFFER-(p-buffer)) {
        lines[lc++] = p;
        p += length;
    }
    lines[lc] = p;

    if (is_clear) {
        printf("%s", CLEAR);
    }

    for (int i = last_lines-1; i >= 0; i--) {
        if (lc-i-1 < 0 && is_safe) {
           continue;
        }

        if (is_numbered) {
            printf("%2i (%03i): ", lc-i, last_lines-i);
        }

        printf("%s\n", lines[lc-i-1]);
    }

    return 0;
}

int getNumber(char *prefix, int number) {
    if (*prefix == '-') {
        last_lines = number;
    } else {
        optionError(prefix, "Prefix can only a be a \"-\".");
    }
    return 0;
}

/*
513: Write the program `tail`, which prints the last `n` lines of its input. By default, `n`
    is set to 10, let us say, but it can be changed by an optional argument so that ``tail -n``
    prints the last n lines.
    
    The program should behave rationally no matter how unreasonable the input or the value of `n`.
    Write the program so it makes the best use of available storage; line should be stored as in
    the sorting program of Section 5.6, not in a two-dimensional array of fixed size. 
*/