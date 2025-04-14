#include <stdio.h>

#define COLUMNSIZE 10

int main(void) {
    int ch;
    int columnsLeft = COLUMNSIZE;

    while ((ch = getchar()) != EOF) {
        putchar(ch);
        columnsLeft--;

        if (ch == '\n') {
            columnsLeft = COLUMNSIZE;
        } else if (columnsLeft < 1) {
            if (ch == ' ' || ch == '\t') {
                putchar('\n');
            } else {
                while ((ch = getchar()) != EOF && ch != ' ' && ch != '\t' && ch != '\n') {
                    putchar(ch);
                }
                putchar('\n');
            }
            columnsLeft = COLUMNSIZE;
        }
    }
    return 0;
}

/*
122: Write a program to `fold` long input lines into two or more shorter lines after
     the last non-blank character that occurs before the `n`-th column of input. Make sure your
     program does something intelligent with very long lines, and if there are no blanks or tabs
     before the specified column.
*/