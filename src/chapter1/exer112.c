#include <stdio.h>

int main(void) {
    int ch;
    int lastCh = 0;

    while ((ch = getchar()) != EOF) {
        if (ch == ' ' && lastCh != ' ') {
            putchar('\n');
        } else if (!(lastCh == ' ' && ch == ' ')) {
            putchar(ch);
        }
        lastCh = ch;
    }

    return 0;
}

/*
112: Write a program that prints its input one word per line.
*/