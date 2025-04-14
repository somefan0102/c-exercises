#include <stdio.h>

#define SIZE 200

int main(void) {
    char whitespaceChars[SIZE];
    int ch;
    int lastCh = 0;
    int i = 0;

    while ((ch = getchar()) != EOF) {
        if (ch == ' ' || ch == '\t') {
            whitespaceChars[i++] = ch;
        } else if ((lastCh == ' ' || lastCh == '\t') && ch != '\n') {
            whitespaceChars[i] = '\0';
            puts(whitespaceChars);
            i = 0;
            whitespaceChars[i] = '\0';
            putchar(ch);
        } else {
           if (ch == '\n') {
                // Blank lines only exist if both ch and lastCh are \n.
                if (lastCh == '\n') {
                    continue;
                }

                i = 0;
                lastCh = 0;
                whitespaceChars[i] = '\0';
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