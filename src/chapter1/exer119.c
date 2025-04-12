#include <stdio.h>

#define SIZE 100

void reverse(char[]);

int main(void) {
    int ch, i;
    char line[SIZE];

    i = 0;
    while ((ch = getchar()) != EOF) {
        if (ch == '\n') {
            line[i] = '\0';
            reverse(line);
            for (int j = 0; line[j] != '\0'; j++) {
                putchar(line[j]);
            }
            i = 0;
        } else {
            line[i] = ch;
            i++;
        }
    }
}

void reverse(char line[]) {
    int i, j;
    char tempLine[SIZE];

    for (i = 0; line[i] != '\0'; i++) {
        tempLine[i] = line[i];
    }
    tempLine[i] = '\0';

    // Subtractions here because we don't wanna screw up
    // the null character at the beginning.
    for (j = i-1; j >= 0; j--) {
        line[i-j-1] = tempLine[j];
    }
    line[i] = '\0';
}

/*
119: Write a function `reverse(s)` that reverses the character string `s`. Use it to
     write a program that reverses its input a line at a time.
*/