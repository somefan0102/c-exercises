#include <stdio.h>
#include <ctype.h>
#include "input.h"

int getinput(char str[], int max, char delimiter) {
    int i = 0;
    int ch;

    while (i < max-1 && (ch = getchar()) != EOF && ch != delimiter) {
        str[i++] = ch;
    }
    str[i++] = '\0';

    if (ch == EOF) {
        return 0;
    }

    return i;
}

int getline(char str[], int max) {
    return getinput(str, max, '\n');
}