#include <stdio.h>

#define MAXLINE 1000
#define MAX 80

int main(void) {
    char line[MAXLINE];
    int ch;
    int i = 0;

    while ((ch = getchar()) != EOF) {
        line[i++] = ch;

        if (ch == '\n') {
            line[i++] = '\0';
            if (i > MAX) {
                printf("%s", line);
            }
            i = 0;
        }
    }
}

/*
117: Write a program to print all input lines that are longer than 80 characters.
*/