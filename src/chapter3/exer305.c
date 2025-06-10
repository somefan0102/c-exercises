#include <stdio.h>

#define MIN 0
#define MAX 127

int ipow(int m, int n);
void itob(int n, char s[], int b);

int main(void) {
    char result[20];

    printf("\tBASE2\t\tBASE3\tBASE4\tBASE5\tBASE6\tBASE7\tBASE8\tBASE9\tBASE10\tBASE11\tBASE12\tBASE13\tBASE14\tBASE15\tBASE16\n");
    printf("\tBIN\t\t\t\t\t\t\t\t\tOCT\t\tDEC\t\t\t\tHEX\n");

    for (int i = MIN; i <= MAX; i++) {
        printf("%3i =\t", i);

        itob(i, result, 2);
        printf("%s\t\t", result);

        for (int j = 3; j <= 16; j++) {
            itob(i, result, j);
            printf("%s\t", result);
        }

        putchar('\n');
    }

    return 0;
}

int ipow(int m, int n) {
    int result = 1;

    for (int i = 0; i < n; i++) {
        result *= m;
    }
    
    return result;
}

void itob(int n, char s[], int b) {
    const char SYMBOLS[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    int e, f, t, i;
    
    if (b < 2) {
        printf("Error: Negative bases, base-0 and base-1 not supported.");
        return;
    }

    for (e = 0; (t = ipow(b, e)) <= n; e++);
    e--;

    i = 0;
    while (e >= 0) {
        t = ipow(b, e);

        for (f = 0; f * t <= n; f++);
        f--;

        s[i++] = SYMBOLS[f];
        n -= f * t;
        e--;
    }

    if (i == 0) {
        s[i++] = '0';
    }

    s[i] = '\0';
}

/*
305: Write the function `itob(n,s,b)` that converts the integer `n` into a base `b`
     character representation in the string `s`. In particular, `itob(n,s,16)` formats `s` as a
     hexadecimal integer in `s`.
*/