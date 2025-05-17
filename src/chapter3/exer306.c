#include <stdio.h>

int strlen(char s[]);
void reverse(char s[]);
void itoa(int n, char s[], int w);

int main(void) {
    char x[100];
    itoa(42, x, 5);
    printf("%s", x);
    return 0;
}

int strlen(char s[]) {
    int i;
    for (i = 0; s[i] != '\0'; i++);
    return i;
}

void reverse(char s[]) {
    int temp;

    for (int i = 0, j = strlen(s)-1; i < j; i++, j--) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}

// Better version used in exer304.c
void itoa(int n, char s[], int w) {
    int i = 0;
    int sign = 1;
    int spacesleft = 0;

    if (n >= 0) {
        n = -n;
        sign = 0;
    }

    do {
        s[i++] = -1*(n % 10) + '0';
    } while ((n /= 10) < 0);

    spacesleft = w - i;

    if (sign) {
        s[i++] = '-';
    }

    for (int j = 0; j < spacesleft; j++) {
        s[i++] = ' ';
    }

    s[i] = '\0';
    reverse(s);
}
/*
306: Write a version of itoa that accepts three arguments instead of two. The third
     argument is a minimum field width; the converted number must be padded with blanks on the
     left if necessary to make it wide enough.
*/