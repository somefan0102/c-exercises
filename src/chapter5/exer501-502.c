#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "input.h"
#include "nstring.h"

#define MAXLINE 1000

/*
    Gets the next number equivalent from `str[]` and puts it to `*n`.
    Returns if it hits `'\0'` in `str[]`, then wraps back to start of string.
*/
int getint(char str[], int *n);

// Like `getint()` but gets the next float equivalent.
int getfloat(char str[], double *n);

int main(void) {
    int number_i = 0;
    double number_f = 0;

    char line[MAXLINE] = "Hello -.135 world, th1s a-24.56 string +282e4.6 just wait and c";
    char input[MAXLINE];

    printf("[N]umber or [F]loat: ");
    getline(input, MAXLINE);

    printf("Line: ");
    getline(line, MAXLINE);

    switch (input[0]) {
        case 'N': case 'n':
            while (getint(line, &number_i) == 0) {
                printf("%i\n", number_i);
            }
            break;

        case 'F': case 'f':
            while (getfloat(line, &number_f) == 0) {
                printf("%i\n", number_f);
            }
            break;
        
        default:
            printf("Error: Invalid mode.\n");
            break;
    }

    return 0;
}

int getint(char str[], int *n) {
    static int i = 0;
    int sign;

    // I'm not using getch or pushing stuff for 501, I'd rather do this:
    while (!(isdigit(str[i]) || (issign(str[i]) && isdigit(str[i+1])) || str[i] == '\0')) {
        i++;
    }

    if (str[i] == '\0') {
        i = 0;
        return 1;
    }

    sign = (str[i] == '-') ? -1 : 1;

    if (issign(str[i])) {
        i++;
    }

    for (*n = 0; isdigit(str[i]); i++) {
        *n = (*n * 10) + (str[i] - '0');
    }
    *n *= sign;

    return 0;
}

int getfloat(char str[], double *n) {
    static int i = 0;
    int sign;

    double frac = 0.0;  // Fraction part of number
    double power = 1.0; // Used for `frac`
    int esign = 1;      // Sign of exponent number
    double e = 0;       // Exponent number

    while (!(isdigit(str[i]) || (issign(str[i]) && (isdigit(str[i+1]) || str[i+1] == '.')) || str[i] == '\0')) {
        i++;
    }

    if (str[i] == '\0') {
        i = 0;
        return 1;
    }

    sign = (str[i] == '-') ? -1 : 1;

    if (issign(str[i])) {
        i++;
    }

    for (*n = 0; isdigit(str[i]); i++) {
        *n = (*n * 10) + (str[i] - '0');
    }

    if (str[i] == '.') {
        i++;

        while (isdigit(str[i])) {
            frac = (frac * 10.0) + (str[i] - '0');
            i++;
            power *= 10.0;
        }
    }

    if (str[i] == 'e') {
        i++;

        esign = (str[i] == '-') ? -1 : 1;

        if (issign(str[i])) {
            i++;
        }

        while (isdigit(str[i])) {
            e = (e * 10.0) + (str[i] - '0');;
            i++;
        }
    }

    *n += frac / power;
    *n *= sign * pow(10, e * esign);

    return 0;
}

/*
501: As written, `getint` treats a `+` or `-` not followed by a digit as a valid
     representation of zero. Fix it to push such a character back on the input.
502: Write `getfloat`, the floating-point analog of `getint`. What type does `getfloat`
     return as its function value?
*/