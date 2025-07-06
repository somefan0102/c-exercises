#include <stdio.h>

#define TABSIZE 8

// int printGuide(int);

int main(void) {
    int ch;
    int spacesLeft = TABSIZE;

    while ((ch = getchar()) != EOF) {
        if (ch == '\t') {
            while (spacesLeft >= 1) {
                putchar(' ');
                spacesLeft--;
            }
        } else {
            putchar(ch);
            spacesLeft--;
        }
    
        if ((ch == '\t' && spacesLeft < 1) || (ch != '\t' && ch != '\n') && spacesLeft < 1 || ch == '\n') {
            spacesLeft = TABSIZE;
        }
    }

    return 0;
}

// int printGuide(int size) {
//     for (int i = 0; i <= size; i++) {
//         putchar('|');
//         for (int i = 0; i < TAB_SIZE; i++) {
//             putchar(' ');
//         }
//     }
//     putchar('\n');
//     for (int i = 0; i <= size; i++) {
//         for (int i = TAB_SIZE; i >= 0; i--) {
//             putchar(i+48);
//         }
//     }
//     putchar('\n');
// }

/*
120: Write a program `detab` that replaces tabs in the input with the proper number
     of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every `n` columns.
     Should `n` be a variable or a symbolic parameter?
*/

