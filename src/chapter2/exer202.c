#include <stdio.h>
#include <stdbool.h>

int main(void) {
    int i, ch, lim = 10;
    char s[lim];

    i = 0;
    while  (true) {
        if (i >= lim-1) {
            break;
        }
        if ((ch = getchar()) == '\n') {
            break;
        }
        if (ch == EOF) {
            break;
        }
        s[i++] = ch;
    }
    s[i] = '\0';

    printf("%s", s);

    return 0;
}

/*
202: Write a loop equivalent to the `for` loop above without using `&&` or `||`.
*/