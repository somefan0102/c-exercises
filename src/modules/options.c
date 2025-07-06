#include <stdio.h>
#include <ctype.h>
#include "nstring.h"
#include "options.h"

static char *help_command;
static char *help;
static int isint(char *s, int *n);

int isint(char *s, int *n) {
    return ((*n = atoi(s)) != 0 || (*n == 0 && *s == '0') || (*n == 0 && issign(*s) && s[1] == '0'));
}

void optionError(char *option, char *reason) {
    printf("Error: %s (%s)\n", (reason[0]) ? reason : "No reason provided.", option);\
    printf("Type \"%s\" for help information.\n", help_command);
}

void initHelp(char *hc, char *h) {
    help_command = hc;
    help = h;
}

void showHelp(void) {
    printf("%s", help);
}

int parseOption(char *option, Flag *p_flags[], int nonhyphen_options, int (*number_func)(char *option, int number)) {
    int number, found;
    char *prefix = option;

    if (strlen(option) <= 1) {
        optionError(prefix, "Empty option.");
        return 1;
    }

    option++;
    if (isint(option, &number)) {
        if ((*number_func)(prefix, number) == 1) {
            return 1;
        }
        while (option && isdigit(*option)) {
            option++;
        }
    }

    if (*prefix == '-') {
        while (*option) {
            found = 0;

            for (int i = 0; p_flags[i]; i++) {
                if (*option == p_flags[i]->name) {
                    *(p_flags[i]->variable) = 1;
                    found = 1;
                    break;
                }
            }

            if (found == 0) {
                optionError(prefix, "Invalid option flag.");
                return 1;
            }

            option++;
        }
    } else if (!isdigit(*option) && !nonhyphen_options) {
        optionError(prefix, "Flags aren't allowed as non-hyphen options.");
        return 1;
    }

    return 0;
}