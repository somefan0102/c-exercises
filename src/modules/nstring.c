#include <assert.h>
#include <ctype.h>
#include <math.h>
#include "nstring.h"

int n_strlen(char *s) {
    char *a = s;
    while (*s++);
    return s-a-1;
}

void n_strcpy(char *s, char *t) {
    while ((*s++ = *t++));
}

int n_strcmp(char *s, char *t) {
    while (*s == *t) {
        if (*s == '\0') {
            return 0;
        }
        s++; t++;
    }

    return *s - *t;
}

void n_strcat(char *s, char *t, int size) {
    assert(n_strlen(t) < size-n_strlen(s));
    while (*s++);
    s--;
    n_strcpy(s, t);
}

void n_strncpy(char *s, char *t, int n) {
    char *a = t;
    while ((*s++ = *t++) && t-a < n);
}

int n_strncmp(char *s, char *t, int n) {
    char *a = t;
    while (*s++ == *t++ && t-a < n) {
        if ((*s)-1 == '\0') {
            return 0;
        }
    }
    return *--s - *--t;
}

void n_strncat(char *s, char *t, int size, int n) {
    assert(n_strlen(t) < size-n_strlen(s));
    while (*s++);
    s--;
    n_strncpy(s, t, n);
}

int n_atoi(char *s) {
    int n = 0;
    int sign = (*s == '-') ? -1 : 1;

    if (*s == '-' || *s == '+') {
        s++;
    }

    while (isdigit(*s)) {
        n = n * 10 + (*s++ - '0');
    }

    return n * sign;
}

double n_atof(char str[]) {
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

void itoa(int n, char *s) {
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

static int ipow(int m, int n);

static int ipow(int m, int n) {
    int result = 1;

    for (int i = 0; i < n; i++) {
        result *= m;
    }
    
    return result;
}

void n_itob(int n, char s[], int b) {
    const char SYMBOLS[] = "0123456789abcdef";
    int e, f, t, i;
    
    if (b < 2) {
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

int issign(char ch) {
    return (ch == '+' || ch == '-');
}

void reverse(char *s) {
    char *t = s;
    char temp;

    while (*t) {
        t++;
    }
    t--;

    while (s < t) {
        temp = *s;
        *s = *t;
        *t = temp;
        s++, t--;
    }
}

int strfind(char *s, char ch) {
    char *a = s;

    while (*s) {
        if (*s == ch) {
            return s-a;
        }
        s++;
    }

    return -1;
}

int strend(char *s, char *t) {
    char *a = s;

    while (*s) {
        if (*s == *t && !n_strncmp(s, t, n_strlen(t))) {
            return s-a;
        }
        s++;
    }

    return -1;
}

int strindex(char str[], char sub[]) {
    int index = -1;

    for (int i = strlen(str)-1, j = i; i >= 0; i--) {
        if (str[i] != sub[j] && j >= 0) {
            j = strlen(sub)-1;
            index = -1;
        }

        if (str[i] == sub[j]) {
            j--;
        } else if (j < 0) {
            index = i+1;
            break;
        }
    }

    return index;
}

void strslice(char *s, char *t, int start, int end) {
    char *a = s;

    assert(start >= 0 && end < n_strlen(s));

    while (s-a < start) {
        s++;
    }

    n_strncpy(t, s, end-start+1);
}

void squeeze(char *s, char *t) {
    int i, j;

    while (*t) {
        i = 0;
        j = 0;
        
        while (s[i]) {
            if (s[i] != *t) {
                s[j++] = s[i];
            }
            i++;
        }
        t++;
    }
}

void strlower(char *s) {
    while (*s) {
        *s = tolower(*s);
        s++;
    }
}

void strupper(char *s) {
    while (*s) {
        *s = toupper(*s);
        s++;
    }
}