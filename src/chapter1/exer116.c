#include <stdio.h>

int main(void) {
    int ch;
    int longest = 0;
    int i = 0;

    while ((ch = getchar()) != EOF) {
        i++;

        if (ch == '\n') {
            if (i > longest) {
                longest = i;
            }
            i = 0;
        }
    }

    printf("The longest line you typed in was %i characters long, newline-inclusive.", longest);
}

/*
116: Revise the main routine of the longest-line program so it will correctly print the
     `i` of arbitrary long input lines, and as much as possible of the text.
*/