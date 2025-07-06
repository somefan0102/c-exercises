#include <stdio.h>
#include <ctype.h>
#include "nstring.h"

#define MAX_LINE 100

int main(void) {
    int ch;
    int column = 0;
    char string[MAX_LINE];

    while ((ch = getchar()) != EOF) {
        if (ch >= 0 && ch < 127) {
            putchar(ch);
            column++;
        } else {
            itob(ch, string, 16)
            printf("[0x%s]", string);
            column += strlen(string)+4;
        }
        if (ch == '\n') {
            column = 0;
        }
        if (column > MAX_LINE) {
            if (!isspace(ch) && isalnum(ch)) {
                putchar('-');
            }
            putchar('\n');
            column = 0;
        }
    }

    return 0;
}

/*
702: Write a program that will print arbitrary input in a sensible way.
     As a minimum, it should print non-graphic characters in octal or hexadecimal
     according to local custom, and break long text lines.
*/