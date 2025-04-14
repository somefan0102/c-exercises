#include <stdio.h>

#define TABSIZE 8
#define SIZE 200

void render(int[]);

int main(void) {
    int line[SIZE];
    int i;

    i = 0;
    while ((line[i] = getchar()) != EOF) {
        if (line[i] == '\n') {
            line[i++] = '\n';
            line[i++] = '\0';
            render(line);
            i = 0;
            line[i] = '\0';
        } else {
            i++;
        }
    }

    return 0;
}

void render(int line[]) {
    int spacesLeft = TABSIZE;
    int spacesRemaining = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        spacesLeft--;

        if (line[i] == ' ') {
            spacesRemaining++;
            if (spacesLeft < 1) {
                putchar('\t');
                spacesRemaining = 0;
            }
        } else {
            if (spacesRemaining >= 1) {
                for (int j = 0; j < spacesRemaining; j++) {
                    putchar(' ');
                }
                spacesRemaining = 0;
            }
            putchar(line[i]);
        }

        if (spacesLeft < 1) {
            spacesLeft = TABSIZE;
        }
    }
}

/*
121: Write a program `entab` that replaces strings of blanks by the minimum
     number of tabs and blanks to achieve the same spacing. Use the same tab stops as for `detab`.
     When either a tab or a single blank would suffice to reach a tab stop, which should be given
     preference?
*/