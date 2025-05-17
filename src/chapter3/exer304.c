#include <stdio.h>
#include <limits.h>

int strlen(char s[]);
void reverse(char s[]);
void itoa(int n, char s[]);
void betteritoa(int n, char s[]);

int main(void) {
    char x[30];

    itoa(INT_MIN, x);
    printf("Original function with %i:\t%s\n", INT_MIN, x);

    betteritoa(INT_MIN, x);
    printf("Better function with %i:\t%s\n", INT_MIN, x);

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

void itoa(int n, char s[]) {
    int i = 0;
    int sign = 0;

    /*
        The following statement won't support INT_MIN, -2147483648.
        Once inverted the correct number would be 2147483648,
        but due to limitations with the maximum capacity the number can hold (2147483647),
        it will overflow back to -2147483648.
    */

    if (n < 0) {
        n = -n;
        sign = 1;
    }

    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign) {
        s[i++] = '-';
    }

    s[i] = '\0';
    reverse(s);
}

void betteritoa(int n, char s[]) {
    /*
        For portability and considering the absolute value of minimum of type n is bigger than the max,
        using arithmetic with negative numbers instead of positive numbers may solve this,
        which solves both for two's complement and one's complement, but this may be a rather unique approach...
    */

    int i = 0;
    int sign = 1;

    if (n >= 0) {
        n = -n;
        sign = 0;
    }

    do {
        s[i++] = -1*(n % 10) + '0';
    } while ((n /= 10) < 0);

    if (sign) {
        s[i++] = '-';
    }

    s[i] = '\0';
    reverse(s);
}

/*
304: In a two's complement number representation, our version of `itoa` does not
     handle the largest negative number, that is, the value of n equal to `-(2^wordsize-1)`.
     Explain why not. Modify it to print that value correctly, regardless of the machine on which it runs.
*/