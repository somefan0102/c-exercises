#include <stdio.h>
#include <ctype.h>

#define IN  1
#define OUT 0

/*  Additions:

    1. You can now check for other symbols, and the state is turned
       on if we find an actual alphabetic character. This will prevent
       strings like "hello!world" and "?" to be counted as one.
    2. More whitespace characters are to be accounted for.
*/

int main(void) {
    int ch, state;
    int nlines = 0;
    int nwords = 0;
    int nchars = 0;

    state = OUT;
    while ((ch = getchar()) != EOF) {
        nchars++;

        if (ch == '\n') {
            nlines++;
        }

        if (isspace(ch) || !isalpha(ch)) {
            state = OUT;
        } else if (state == OUT) {
            state = IN;
            nwords++;
        }
    }

    printf("Number of newlines:   %i\n", nlines);
    printf("Number of words:      %i\n", nwords);
    printf("Number of characters: %i\n", nchars);

    return 0;
}


// Old version.
// #include <stdio.h>
//
// int main(void) {
//     int ch, state;
//     int nlines = 0;
//     int nwords = 0;
//     int nchars = 0;
//
//     state = OUT;
//     while ((ch = getchar()) != EOF) {
//         nchars++;
//         if (ch == '\n') {
//             nlines++;
//         } else if (ch == ' ' || ch == '\n' || ch == '\t') {
//             state = OUT;
//         } else if (state == OUT) {
//             state = IN;
//             nwords++;
//         }
//     }
//  
//     printf("Number of newlines:   %i\n", nlines);
//     printf("Number of words:      %i\n", nwords);
//     printf("Number of characters: %i\n", nchars);
//
//     return 0;
// }



/*
111: How would you test the word count program?
     What kinds of input are most likely to uncover bugs if there are any?
*/