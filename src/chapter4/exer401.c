#include <stdio.h>
#include "input.h"
#include "nstring.h"

#define MAXLINE 1000

// Return index of substring `sub` found in `str`, starting from rightmost item.
int strindex(char str[], char sub[]);

int main(void) {
    char line[MAXLINE];
    char pattern[MAXLINE];
    char locations[MAXLINE];
    char mode[2];
    
    int result = -1;
    int found = 0;

    printf("Mode (Search [l]eft or [r]ight): ");
    getline(mode, MAXLINE);

    if (mode[0] != 'l' && mode[0] != 'r') {
        printf("Error: Not a valid mode.\n");
        return -1;
    }

    printf("Pattern: ");
    getline(pattern, MAXLINE);

    while (getline(line, MAXLINE) > 0) {
        if (mode[0] == 'l') {
            result = strsub(line, pattern);
        } else if (mode[0] == 'r') {
            result = strindex(line, pattern);
        }

        if (result >= 0) {
            printf("%s\n", line);
            locations[found++] = result;
        }
    }

    printf("Locations: ");
    for (int i = 0; i < found; i++) {
        printf("\n\t- Line %i (Character %i)", i, locations[i]);
    }
    putchar('\n');

    printf("Lines found: %i\n", found);

    return found;
}

int strindex(char str[], char sub[]) {
    int index = -1;

    for (int i = strlen(str)-1, j = i; i >= 0; i--) {
        if (str[i] != sub[j] && j >= 0) {
            j = strlen(sub)-1;
            index = -1;
        }

        if (str[i] == sub[j]) {
            j--;
        } else if (j < 0) {
            index = i+1;
            break;
        }
    }

    return index;
}

/*
401: Write the function `strindex(s,t)` which returns the position of the rightmost
     occurrence of `t` in `s`, or -1 if there is none.
*/