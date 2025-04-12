#include <stdio.h>
#include <stdbool.h>

#define SIZE 200
#define MAX 80

int main(void) {
    char line[SIZE];
    int i;

    while (true) {
        for (i = 0; (line[i] = getchar()) != '\n' && line[i] != EOF; i++);

        if (line[i-1] == EOF) {
            break;
        }

        line[i] = '\0';

        if (i > MAX) {
            for (int j = 0; line[j] != '\0'; j++) {
                putchar(line[j]);
            }
            putchar('\n');
        }
    }

    return 0;
}

/*
117: Write a program to print all input lines that are longer than 80 characters.
*/