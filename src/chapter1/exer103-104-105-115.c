#include <stdio.h>

const char tableType = 'c';
const int range[] = {300, 0, 20};
int i, result;

void iteration(void);

int main(void) {
    if (tableType == 'c') {
        printf("Cels\tFahr\n");
    } else if (tableType == 'f') {
        printf("Fahr\tCels\n");
    } else {
        return -1;
    }

    printf("----\t----\n");

    if (range[0] > range[1]) {
        for (i = range[0]; i >= range[1]; i -= range[2]) {
            iteration();
        }
    } else {
        for (i = range[0]; i <= range[1]; i += range[2]) {
            iteration();
        }
    }
    return 0;
}

void iteration(void) {
    if (tableType == 'c') {
        result = 9 * i / 5 + 32;
    } else if (tableType == 'f') {
        result = 5 * (i - 32) / 9;
    }

    printf("%i\t%i\n", i, result);
}

/*
103: Modify the temperature conversion program to print a heading above the table.
104: Write a program to print the corresponding Celsius to Fahrenheit table.
105: Modify the temperature conversion program to print the table in reverse order, that is, from 300 degrees to 0.
115: Rewrite the temperature conversion program of Section 1.2 to use a function for conversion.
*/