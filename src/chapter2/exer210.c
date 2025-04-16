#include <stdio.h>

char lower(char);
void lowerString(char[]);

int main(void) {
    char message[] = "IT WORKS!";
    lowerString(message);
    printf(message);
    return 0;
}

void lowerString(char string[]) {
    for (int i = 0; string[i] != '\0'; i++) {
        string[i] = lower(string[i]);
    }
}

char lower(char ch) {
    return (ch >= 'A' && ch <= 'Z') ? (ch + 'a' - 'A') : ch;
}

/*
210: Rewrite the function `lower`, which converts upper case letters to lower case,
     with a conditional expression instead of `if-else`.
*/