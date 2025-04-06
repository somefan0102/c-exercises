#include <stdio.h>

int main(void) {
    int ch;
    int lastCh = 0;
    
    while ((ch = getchar()) != EOF) {
        if (lastCh != ' ' || lastCh == ' ' && ch != ' ') {
            putchar(ch);
        }
        lastCh = ch;
    }

    return 0;
}

/*
109: Write a program to copy its input to its output,
     replacing each string of one or more blanks by a single blank.
*/