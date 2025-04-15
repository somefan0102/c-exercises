#include <stdio.h>
#include <stdbool.h>

int main(void) {
    int ch, lim = 10, string[lim];

    int i = 0;
    while (true) {
        if (i >= lim-1) {
            break;
        }
        if ((ch = getchar()) == '\n') {
            break;
        }
        if (ch == EOF) {
            break;
        }
        string[i] = ch;
        i++;
    }

    return 0;
}

/*
202: Write a loop equivalent to the `for` loop above without using `&&` or `||`.
*/