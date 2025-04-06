#include <stdio.h>

int main(void) {
    int ch;
    int nBlanks = 0;
    int nTabs = 0;
    int nLines = 0;
    
    while ((ch = getchar()) != EOF) {
        switch (ch)
        {
            case ' ':
                nBlanks++;
                break;
            
            case '\t':
                nTabs++;
                break;
            
            case '\n':
                nLines++;
                break;
            
            default:
                break;
        }
    }

    printf("Number of blanks:   %i\n", nBlanks);
    printf("Number of tabs:     %i\n", nTabs);
    printf("Number of newlines: %i\n", nLines);

    return 0;
}

/*
108: Write a program to count blanks, tabs, and newlines.
*/