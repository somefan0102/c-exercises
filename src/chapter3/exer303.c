#include <stdio.h>
#include <limits.h>

#define SIZE 200

int strlen(char s[]);
void expand(char s1[], char s2[]);

int main(void) {
    char result[CHAR_MAX];
    char line[SIZE];
    int i = 0;

    while (i < SIZE && ((line[i++] = getchar()) != '\n') && line[i] != EOF);
    line[i-1] = '\0';

    expand(line, result);
    printf("%s\n", result);

    return 0;
}

int strlen(char s[]) {
    int i;
    for (i = 0; s[i] != '\0'; i++);
    return i;
}

/*
  ASCII-compatible for ANY character expansion range because it's much more fun. Example: "(-1" -> "()*+,-./01"

  Leading or trailing hypens are supported, which imply default values for ASCII 0 and ASCII 127, respectively.
  However and thus, using leading hyphens is worthless because of null-terminating strings.

  Only the first two or three characters are significant.
*/
void expand(char s1[], char s2[]) {
    int j = 0;
    char start = '\0';
    char end = CHAR_MAX;

    if (s1[1] == '-') { // Assuming prefix "x-"
        start = s1[0];
        if (s1[2] != '\0') { // Assuming "x-y"
            end = s1[2];
        }
    } else if (s1[0] == '-') { // Assuming "-x"
        end = s1[1];
    } else {
        printf("Error expanding \"%s\"\n", s1);
        return;
    }

    if (end < start) {
        printf("Error for character's value of end range is greater than one of start range in \"%s\"\n", s1);
        return;
    }

    for (char ch = start; ch >= 0 && ch <= SCHAR_MAX && ch <= end; ch++) {
        s2[j++] = ch;
    }

    s2[j] = '\0';
}

/*
303: Write a function `expand(s1,s2)` that expands shorthand notations like `a-z` in
     the string `s1` into the equivalent complete list `abc...xyz` in `s2`. Allow for letters of either
     case and digits, and be prepared to handle cases like `a-b-c` and `a-z0-9` and `-a-z`.
     Arrange that a leading or trailing `-` is taken literally.
*/