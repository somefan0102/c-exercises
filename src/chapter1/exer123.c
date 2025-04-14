#include <stdio.h>

int main(void) {
    int ch;
    int lastCh = 0;

    while ((ch = getchar()) != EOF) {
        if (ch == '\"') {
            while ((ch = getchar()) != EOF && ch != '\"') {
                putchar(ch);
            }
        } else if (ch == '\'') {
            while ((ch = getchar()) != EOF && ch != '\'') {
                putchar(ch);
            }
        }

        if (lastCh == '/' && ch == '/') {
            while ((ch = getchar()) != EOF && ch != '\n');
            putchar('\n');
        } else if (lastCh == '/' && ch == '*') {
            lastCh = 0;
            while ((ch = getchar()) != EOF && !(lastCh == '*' && ch == '/')) {
                lastCh = ch;
            }
            ch = 0;
        } else if (ch == '/') {
            lastCh = ch;
            continue;
        } else {
            if (lastCh == '/') {
                putchar(lastCh);
            }
            putchar(ch);
        }
        
        lastCh = ch;
    }

    return 0;
}

/*
123: Write a program to remove all comments from a C program. Don't forget to
     handle quoted strings and character constants properly. C comments don't nest.
*/