#include <stdio.h>
#include "input.h"
#include "nstring.h"
#include "options.h"

#define CLEAR "\x1b[2J\x1b[H"
#define HELP \
"USAGE: tab OPTION...\n\
\n\
tab is a program that allows you to write lines.\n\
Each line can show its tabs, tab stopping, spaces, and\n\
configuring them to replaces tabs with spaces and vice versa.\n\
\n\
OPTIONS:\n\
\n\
-h         Display this information.\n\
-(number)  Run en/detabber every (number) columns. Default is 1.\n\
+(number)  Run en/detabber after column (number). Default is 1.\n\
=(number)  Tab size is (number). Default is 8.\n\
-r         Show tab stopper ruler.\n\
-e         Entabber: Replace all available consecutive spaces with tabs.\n\
-d         Detabber: Replace all abailable tabs with spaces.\n\
           NOTE: There can not be both -e and -d in a set of arguments or neither; there must only be one!\n\
-c         Clear screen before and after writing. For *nix terminals only.\n\
=s(char)   Represent and render all spaces as the character (char) instead.\n\
=t(char)   Represent and render all tabs as the character (char) instead.\n"

#define DEFAULT_M 1
#define DEFAULT_N 1
#define DEFAULT_TABSIZE 8
#define MAX_LINE 100

int m = DEFAULT_M;              // -(number)
int n = DEFAULT_N;              // +(number)
int tab_size = DEFAULT_TABSIZE; // =(number)

int is_help = 0;
int is_ruler = 0;
int is_entab = 0;
int is_detab = 0;
int is_clear = 0;
char space = '.';
char tab = '\t';

Flag flags[] = {
    { .name = 'h', .variable = &is_help, },
    { .name = 'r', .variable = &is_ruler, },
    { .name = 'e', .variable = &is_entab, },
    { .name = 'd', .variable = &is_detab, },
    { .name = 'c', .variable = &is_clear, },
};

Flag *p_flags[] = {
    &flags[0], &flags[1], &flags[2], &flags[3], &flags[4],
};

int changeMode(char *prefix, int number);

int main(int argc, char *argv[]) {
    int exit, length;
    char line[MAX_LINE];

    initHelp("tab -h", HELP);

    for (int i = 1; i < argc; i++) {
        if (*argv[i] != '-' && *argv[i] != '+' && *argv[i] != '=') {
            optionError(argv[i], "No option found.");
            return 1;
        }
        exit = parseOption(argv[i], p_flags, 1, changeMode);
        if (argv[i][0] == '=') {
            if (argv[i][1] == 's' && argv[i][2]) {
                space = argv[i][2];
            } else if (argv[i][1] == 't' && argv[i][2]) {
                tab = argv[i][2];
            } else {
                optionError(argv[i], "Invalid flag and parameter as non-hyphen options.");
                return 1;
            }
        }
        if (exit == 1) {
            return 1;
        } else if (exit == 2) {
            return 0;
        }
    }

    if (is_clear) {
        printf("%s", CLEAR);
    }

    if ((is_entab && is_detab) || (!is_entab && !is_detab)) {
        printf("Error: -e and -d options co-existing or non-existent are invalid; pick one.\n");
        return 1;
    }

    if (is_help) {
        printf("%s", HELP);
        return 0;
    }

    printf("-- You can now write your lines here. Exit when done.\n");
    printf("-- You are also now in \"%s\" mode%s", (is_entab) ? "entab" : "detab", (m != 1 || n != 1) ? ", which will occur " : ".");

    if (m != 1) {
        printf("every %i columns%c", m, (n != 1) ? ' ' : '.');
    }

    if (n != 1) {
        printf("after column %i.", n);
    }

    putchar('\n');

    if (is_ruler) {
        if (m > 1 && m <= 15) {
            for (int i = 0; i <= tab_size*10 && i < 100; i++) {
                printf("%x", (i%m)+1);
            }
            putchar('\n');
        }
        for (int i = 0; i <= tab_size*10 && i < 100; i++) {
            printf("%c", (i % tab_size == 0) ? 'v' : '=');
        }
        putchar('\n');
    }

    while ((length = getline(line, MAX_LINE))) {
        int left = tab_size;
        if (is_entab) {
            int space_c = 0;
            for (int i = 0, j = 1; i < length; i++) {
                if (line[i] == ' ' && j > n-1 && (j%m) == 0) {
                    space_c++;
                } else {
                    for (int k = 0; k < space_c; k++, j++) {
                        putchar(space);
                    }
                    space_c = 0;
                    putchar((line[i] == ' ') ? space : line[i]);
                    j++;
                }

                if (left == 1 && space_c) {
                    putchar(tab);
                    j += space_c;
                    space_c = 0;
                }

                if (--left <= 0) {
                    left = tab_size;
                }
            }
        } else if (is_detab) {
            for (int i = 0, j = 1; i < length; i++) {
                if (line[i] == '\t') {
                    if (j > n-1 && (j%m) == 0) {
                        for (int k = 0; k < left; k++, j++) {
                            putchar(space);
                        }
                    } else {
                        putchar(tab);
                        j += left;
                    }
                    left = tab_size+1;
                } else {
                    putchar((line[i] == ' ') ? space : line[i]);
                    j++;
                }

                if (--left <= 0) {
                    left = tab_size;
                }
            }
        }
        putchar('\n');
    }
}

int changeMode(char *prefix, int number) {
    if (*prefix == '-') {
        m = number;
    } else if (*prefix == '+') {
        n = number;
    } else if (*prefix == '=') {
        tab_size = number;
    } else {
        optionError(prefix, "Prefix can only a be a \"-\", \"+\", or \"=\".");
    }
    return 0;
}

/*
511: Modify the program `entab` and `detab` to accept a list of tab stops as arguments.
     Use the default tab settings if there are no arguments.
512: Extend `entab` and `detab` to accept the shorthand `entab -m +n`
     to mean tab stops every n columns, starting at column m. Choose convenient (for the user)
     default behavior.
*/