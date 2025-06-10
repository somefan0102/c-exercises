#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "input.h"

#define MAXLINE 1000

// Returns `str` as double.
double atof(char str[]);

int main(void) {
    char x[MAXLINE];
    getline(x, MAXLINE);

    printf("%lf\n", atof(x));

    return 0;
}

double atof(char str[]) {
    double value, power;
    int esign, sign, i, ex;

    for (i = 0; isspace(str[i]); i++);

    sign = (str[i] == '-') ? -1 : 1;

    if (str[i] == '+' || str[i] == '-') {
        i++;
    }

    for (value = 0.0; isdigit(str[i]); i++) {
        value = 10.0 * value + (str[i] - '0');
    }

    if (str[i] == '.') {
        i++;
    }

    for (power = 1.0; isdigit(str[i]); i++) {
        value = 10.0 * value + (str[i] - '0');
        power *= 10;
    }

    if (str[i] == 'e' || str[i] == 'E') {
        i++;
    }

    esign = (str[i] == '-') ? -1 : 1;

    if (str[i] == '+' || str[i] == '-') {
        i++;
    }

    for (ex = 0; isdigit(str[i]); i++) {
        ex = 10.0 * ex + (str[i] - '0');
    }

    return (sign * value / power) * pow((double)10, (double)esign * ex);
}

/*
402: Extend `atof` to handle scientific notation of the form, `123.45e-6`,
     where a floating-point number may be followed by `e` or `E` and an optionally signed exponent.
*/