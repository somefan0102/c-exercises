#include <ctype.h>
#include "nstring.h"

int strlen(char str[]) {
    int i;
    for (i = 0; str[i] != '\0'; i++);
    return i;
}

int strlenn(char str[]) {
    return strlen(str) + 1;
}

int strch(char str[], char ch) {
    int i;

    for (i = 0; str[i] != ch && str[i] != '\0'; i++);

    if (str[i] == '\0') {
        return -1;
    } else {
        return i;
    }
}

int strsub(char str[], char sub[]) {
    int index = -1;

    for (int i = 0, j = 0; str[i] != '\0'; i++) {
        if (str[i] != sub[j] && sub[j] != '\0') {
            j = 0;
            index = -1;
        }

        if (str[i] == sub[j]) {
            j++;
            if (index == -1) {
                index = i;
            }
        } else if (sub[j] == '\0') {
            break;
        }
    }

    return index;
}

void strreverse(char str[]) {
    int temp;

    for (int i = 0, j = strlen(str)-1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

int streq(char lstr[], char rstr[]) {
    if (strlen(lstr) != strlen(rstr)) {
        return 0;
    }

    for (int i = 0, j = 0; lstr[i] != '\0'; i++, j++) {
        if (lstr[i] != rstr[i]) {
            return 0;
        }
    }
    return 1;
}

void strslice(char str1[], char str2[], int start, int end) {
    int j = 0;
    
    for (int i = start; i <= end; i++, j++) {
        str2[j] = str1[i];
    }
    str2[j] = '\0';
}

void ltrim(char str[]) {
    int i = 0;
    int j = 0;

    while (!isspace(str[i]) && str[i] != '\0') {
        i++;
    }

    while (str[i] != '\0') {
        str[j++] = str[i++];
    }
}

void rtrim(char str[]) {
    strreverse(str);
    ltrim(str);
    strreverse(str);
}

void squeeze(char str[], char targets[]) {
    int i, j;

    for (int k = 0; targets[k] != '\0'; k++) {
        for (i = 0, j = 0; str[i] != '\0'; i++) {
            if (str[i] != targets[k]) {
                str[j++] = str[i];
            }
        }
        str[j] = '\0';
    }
}