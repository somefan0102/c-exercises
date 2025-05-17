#include <stdio.h>

int strlen(char s[]);
void escape(char s1[], char s2[]);
void descape(char s1[], char s2[]);

int main(void) {
    char string1[] = "A tab can be represented as \t, while a new line can be represented as \n.";
    char string2[] = "Newline: \n, Tab: \t, Alert: \a, Backspace: \b, Form feed: \f, Vertical tab: \v";

    char string1_result[strlen(string1)+1];
    char string2_result[strlen(string2)+1];

    escape(string1, string1_result);
    printf("String 1 with escape:\t%s\n", string1_result);

    descape(string2, string2_result);
    printf("String 2 with descape:\t%s\n", string2_result);

    putchar('\n');
    return 0;
}

int strlen(char s[]) {
    int i;
    for (i = 0; s[i] != '\0'; i++);
    return i;
}

void escape(char s1[], char s2[]) {
    int j = 0;
    char ch;

    for (int i = 0; (ch = s1[i]) != '\0'; i++) {
        if (ch == '\n' || ch == '\t' || ch == '\a' || ch == '\b' || ch == '\f' || ch == '\v') {
            s2[j++] = '\\';
        }

        switch (ch) {
            case '\n':
                s2[j++] = 'n';
                break;
            case '\t':
                s2[j++] = 't';
                break;
            case '\a':
                s2[j++] = 'a';
                break;
            case '\b':
                s2[j++] = 'b';
                break;
            case '\f':
                s2[j++] = 'f';
                break;
            case '\v':
                s2[j++] = 'v';
                break;
            case '\r':
                s2[j++] = 'r';
                break;
            default:
                s2[j++] = ch;
                break;
        }
    }

    s2[j] = '\0';
}

void descape(char s1[], char s2[]) {
    int j = 0;

    for (int i = 0; s1[i] != '\0'; i++) {
        if (s1[i] == '\\') {
            switch (s1[i+1]) {
                case 'n':
                    s2[j++] = '\n';
                    break;
                case 't':
                    s2[j++] = '\t';
                    break;
                case 'a':
                    s2[j++] = '\a';
                    break;
                case 'b':
                    s2[j++] = '\b';
                    break;
                case 'f':
                    s2[j++] = '\f';
                    break;
                case 'v':
                    s2[j++] = '\v';
                    break;
                case 'r':
                    s2[j++] = '\r';
                    break;
                default:
                    printf("Error at character %d: Invalid escape-letter character.", i);
                    return;
            }
            i++;
        } else {
            s2[j++] = s1[i];
        }
    }

    s2[j] = '\0';
}

/*
302: Write a function `escape(s,t)` that converts characters like newline and tab into
     visible escape sequences like `\n` and `\t` as it copies the string t to s. Use a switch.
     Write a function for the other direction as well, converting escape sequences into the real characters.
*/