#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include "input.h"
#include "nstring.h"

#define MAX_LINE 500

// Minimal version of `printf(...)`.
int minprintf(char *format, ...);

// Minimal version of `minscanf(...)`.
// Errors on minscanf are features; scanf is already a mess anyway.
int minscanf(char *format, ...);

void ltoa(long n, char *s);
void ftoa(double n, char *s, char *s2, int precision);

int main(void) {
    char *fruit, *name, *verb;
    minprintf("Hello, %s on %s %d, %d and counting.\n", "world", "July", 1, 2025);
    minscanf("Type a fruit: %15s", &fruit);
    minscanf("Type a name: %15s", &name);
    minscanf("Type a gerund verb: %15s", &verb);
    minprintf("%s was %s until they found a delicious %s!", name, verb, fruit);

    return 0;
}

int minprintf(char *format, ...) {
    va_list ap;
    char conversion[MAX_LINE];
    char fractional[MAX_LINE];
    int number;

    union {
        int i_value;
        double f_value;
        long l_value;
        unsigned int u_value;
        char *s_value;
    } specifier;

    va_start(ap, format);

    for (char *p = format; *p; p++) {
        if (*p != '%') {
            putchar(*p);
        } else {
            p++;
            if (isdigit(*p)) {
                number = atoi(p);
                while (isdigit(*p)) {
                    p++;
                }
            }

            switch (*p) {
                case 'i': case 'd':
                    specifier.i_value = va_arg(ap, int);
                    itoa(specifier.i_value, conversion);
                    fputs(conversion, stdout);
                    break;

                case 'c':
                    specifier.i_value = va_arg(ap, int);
                    putchar(specifier.i_value);
                    break;

                case 'l':
                    specifier.l_value = va_arg(ap, long);
                    ltoa(specifier.l_value, conversion);
                    fputs(conversion, stdout);
                    break;

                case 'x': case 'p': case 'u':
                    specifier.u_value = va_arg(ap, unsigned int);
                    itob(specifier.u_value, conversion, (*p == 'u') ? 10 : 16);
                    if (specifier.u_value == 0 && *p == 'p') {
                        fputs("(null)", stdout);
                    } else {
                        fputs(conversion, stdout);
                    }
                    break;

                case 'o':
                    specifier.u_value = va_arg(ap, unsigned int);
                    itob(specifier.u_value, conversion, 8);
                    fputs(conversion, stdout);
                    break;

                case 'f':
                    specifier.f_value = va_arg(ap, double);
                    ftoa(specifier.f_value, conversion, fractional, number+1);
                    minprintf("%s.%s", conversion, fractional);
                    break;

                case '%':
                    putchar('%');
                    break;
                
                case 's':
                    for (specifier.s_value = va_arg(ap, char *); *specifier.s_value; specifier.s_value++) {
                        putchar(*specifier.s_value);
                    }
                    break;

                default:
                    minprintf("Error: Invalid format specifier (%c).\n", *p);
                    return 1;
            }
        }
    }

    va_end(ap);
    return 0;
}

int minscanf(char *format, ...) {
    va_list ap;
    char *line;
    int max;

    union {
        int **i_pp;
        char **c_pp;
        char **s_pp;
    } specifier_pp;
    
    va_start(ap, format);
    for (char *p = format; *p; p++) {
        if (*p != '%') {
            putchar(*p);
        } else {
            p++;
            if (isdigit(*p)) {
                max = atoi(p)+1;
                while (isdigit(*p)) {
                    p++;
                }
            }

            switch (*p) {
                case 'd':
                    specifier_pp.i_pp = va_arg(ap, int **);
                    line = (char *)malloc(max*sizeof(char));
                    getinput(line, max, '\n');
                    *specifier_pp.i_pp = (int *)malloc(sizeof(int));
                    **specifier_pp.i_pp = atoi(line);
                    free(line);
                    break;

                case 'c': case 's':
                    specifier_pp.c_pp = va_arg(ap, char **);
                    if (*p == 'c') {
                        *specifier_pp.c_pp = (char *)malloc(sizeof(char));
                        **specifier_pp.c_pp = getchar();
                    } else if (*p == 's') {
                        line = (char *)malloc(max*sizeof(char));
                        getinput(line, max, '\n');
                        *specifier_pp.s_pp = line;
                    }

                    break;

                case '%':
                    putchar('%');
                    break;

                default:
                    minprintf("Error: Invalid format specifier.\n");
                    return 1;
            }
        }
    }

    va_end(ap);
    return 0;                   
}

void ltoa(long n, char *s) {
    char *a = s;
    int sign = (n < 0);
    n = (sign) ? -n : n;

    do {
        *s++ = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign) {
        *s++ = '-';
    }

    *s = '\0';
    reverse(a);
}

void ftoa(double f, char *s, char *s2, int precision) {
    char *a = s;
    char *b = s2;
    int sign = (f < 0);
    int n = (sign) ? -f : f;

    do {
        *s++ = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign) {
        *s++ = '-';
    }

    *s = '\0';
    reverse(a);

    float r = (f - (double)atoi(a));
    r = (r > 0) ? r : -r;

    for (int i = 0; i < precision; i++) {
        r *= 10;
    }

    while ((int)(r /= 10) > 0) {
        *s2++ = (int)r % 10 + '0';
    }

    *s2 = '\0';
    reverse(b);
}

/*
703: Revise `minprintf` to handle more of the other facilities of `printf`.
704: Write a private version of `scanf` analogous to `minprintf` from the previous section.
*/