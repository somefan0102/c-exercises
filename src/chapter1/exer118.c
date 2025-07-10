#include <stdio.h>
#include <ctype.h>

#define SIZE 200

int main(void) {
    int i = 0;
    int ch;
    int lastCh = 0;
    char ws[SIZE];

    while ((ch = getchar()) != EOF) {
        if (isspace(ch) && ch != '\n') {
            // Stores the whitespace for later.
            ws[i++] = ch;
            ws[i] = '\0';
        } else if (isspace(lastCh) && ch != '\n') {
            // If next character isn't a newline, print the whitespace.
            printf("%s", ws);
            putchar(ch);
            i = 0;
        } else {
            // If next character is a newline, flush whitespace.
            if (ch == '\n') {
                i = 0;
                ws[i] = '\0';
                // Rids of blank lines.
                if (lastCh == '\n') {
                    continue;
                }
            }
            putchar(ch);
        }
        lastCh = ch;
    }

    return 0;
}

/*
118: Write a program to remove trailing blanks and tabs from each line of input,
     and to delete entirely blank lines.
*/