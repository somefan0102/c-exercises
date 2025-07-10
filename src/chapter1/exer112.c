#include <stdio.h>
#include <ctype.h>

int main(void) {
    int ch;
    int lastCh = 0;

    while ((ch = getchar()) != EOF) {
        if (isspace(ch) && !isspace(lastCh)) {
            putchar('\n');
        } else if (isalpha(ch)) {
            putchar(ch);
        }
        lastCh = ch;
    }

    return 0;
}

/*
112: Write a program that prints its input one word per line.
*/