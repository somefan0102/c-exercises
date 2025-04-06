#include <stdio.h>

void render(int[], int, char, char);
void copy(int, int[], int[]);

int main(void) {
    const int MAX = 100;
    int histogram[MAX];
    int ch;
    int lastCh = 0;
    int i = 0;
    int j = 0;
    char renderType, symbol;

    while ((ch = getchar()) != EOF) {
        if (ch == '\n' || ch == ' ') {
            if (lastCh != ' '  || lastCh == ' '  && ch != ' '
             || lastCh != '\t' || lastCh == '\t' && ch != '\t') {
                histogram[j++] = i;
                i = 0;
            }
        } else {
            i++;
        }
        lastCh = ch;
    }

    printf("Render horizontally or vertically [h/v] with [any] second character: ");

    renderType = getchar();
    if (renderType != 'h' && renderType != 'H' && renderType != 'v' && renderType != 'V') {
        printf("Not a valid render type.\n");
        return -1;
    }

    symbol = getchar();
    if (symbol == '\n' || symbol == '\t' || symbol == ' ') {
        printf("Such whitespace characters are not allowed.\n");
        return -1;
    }

    render(histogram, j, renderType, symbol);
    return 0;
}

void copy(int size, int from[], int to[]) {
    for (int m = 0; m < size; m++) {
        to[m] = from[m];
    }
}

void render(int histogram[], int size, char type, char symbol) {
    if (type == 'h' || type == 'H') {
        for (int k = 0; k < size; k++) {
            printf("%02i (%02i): ", k, histogram[k]);
            for (int l = 0; l < histogram[k]; l++) {
                putchar(symbol);
            }
            putchar('\n');
        }
    } else if (type == 'v' || type == 'V') {
        int verticalHistogram[size];
        int longest = -1;

        copy(size, histogram, verticalHistogram);

        for (int k = 0; k < size; k++) {
            if (verticalHistogram[k] > longest) {
                longest = verticalHistogram[k];
            }
        }

        for (int k = 0; k < size; k++) {
            printf("%02i\t", k);
        }
        putchar('\n');

        for (int k = 0; k < size; k++) {
            printf("(%02i)\t", verticalHistogram[k]);
        }
        putchar('\n');

        for (int k = 0; k < longest; k++) {
            for (int l = 0; l < size; l++) {
                if (verticalHistogram[l] > 0) {
                    putchar(symbol);
                    verticalHistogram[l]--;
                }
                putchar('\t');
            }
            putchar('\n');
        }
    }
}

/*
113: Write a program to print a histogram of the lengths of words in its input.
     It is easy to draw the histogram with the bars horizontal;
     a vertical orientation is more challenging.
*/