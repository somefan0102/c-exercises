#include <stdio.h>
#include <stdbool.h>

int main(void) {
    int ch;
    int nLines = 0;
    int nWords = 0;
    int nChs = 0;
    bool isStateIn = false;

    while ((ch = getchar()) != EOF) {
        nChs++;

        if (ch == '\n') {
            nLines++;
        }
        
        if (ch == ' ' || ch == '\n' || ch == '\t') {
            isStateIn = false;
        } else if (isStateIn == false) {
            isStateIn = true;
            nWords++;
        }
    }
    
    printf("Number of newlines:   %i\n", nLines);
    printf("Number of words:      %i\n", nWords);
    printf("Number of characters: %i\n", nChs);

    return 0;
}

/*
111: How would you test the word count program?
     What kinds of input are most likely to uncover bugs if there are any?
*/