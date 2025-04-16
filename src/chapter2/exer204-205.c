#include <stdio.h>

void squeeze(char[], char[]);
int any(char[], char[]);

int main(void) {
    char string1[] = "Hello, world!";
    char string2[] = "C is a very cool and incredible language!";
    char string3[] = "Lorem ipsum dolor sit amet.";

    squeeze(string1, "lo");
    squeeze(string2, "Cce!");
    squeeze(string3, "aeiou");

    printf("%s\n%s\n%s\n", string1, string2, string3);
    printf("%i", any("I will forbid from using that 101st ASCII symbol in this string... hopefully.", "e"));
    
    return 0;
}

void squeeze(char string1[], char string2[]) {
    int i, j;

    for (int k = 0; string2[k] != '\0'; k++) {
        for (i = 0, j = 0; string1[i] != '\0'; i++) {
            if (string1[i] != string2[k]) {
                string1[j++] = string1[i];
            }
        }
        string1[j] = '\0';
    }
}

int any(char string1[], char string2[]) {
    for (int i = 0; string1[i] != '\0'; i++) {
        for (int j = 0; string2[j] != '\0'; j++) {
            if (string1[i] == string2[j]) {
                return i;
            }
        }
    }
    return -1;
}

/*
204: Write an alternative version of `squeeze(s1, s2)` that deletes each character
     in `s1` that matches any character in the string `s2`.
205: Write the function any(s1,s2), which returns the first location in a string s1
     where any character from the string s2 occurs, or -1 if s1 contains no characters from s2.
     (The standard library function strpbrk does the same job but returns a pointer to the location.)
*/