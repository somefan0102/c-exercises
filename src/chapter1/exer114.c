#include <stdio.h>
#include <limits.h>

int main(void) {
    int frequency[SCHAR_MAX];
    int ch;
    char sortType;

    for (int i = 0; i <= SCHAR_MAX; i++) {
        frequency[i] = 0;
    }

    while ((ch = getchar()) != EOF) {
        frequency[ch]++;
    }

    printf("Sort by character [v]alue or by [c]ount: ");
    sortType = getchar();

    if (sortType == 'v' || sortType == 'V') {
        for (int i = 0; i < SCHAR_MAX; i++) {
            if (frequency[i] > 0) {
                printf("%2c (%03i): %i\n", i, i, frequency[i]);
            }
        }
    } else if (sortType == 'c' || sortType == 'C') {
        int longest = 0;
        int frequencyAlt[SCHAR_MAX];

        for (int i = 0; i <= SCHAR_MAX; i++) {
            frequencyAlt[i] = frequency[i];
        }

        for (int i = 0; i <= SCHAR_MAX; i++) {
            for (int j = 0; j < SCHAR_MAX; j++) {
                if (frequencyAlt[j] > frequencyAlt[longest]) {
                    longest = j;
                }
            }
            
            if (frequencyAlt[longest] > 0) {
                printf("%2c (%03i):%i\n", longest, longest, frequencyAlt[longest]);
                frequencyAlt[longest] = 0;
                longest = 0;
            }
        }
    } else {
        return -1;
    }

    return 0;
}

/*
114: Write a program to print a histogram of the
     frequencies of different characters in its input.
*/