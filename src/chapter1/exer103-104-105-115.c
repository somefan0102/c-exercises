#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void iteration(int temp, char symbol);
void getString(char[], int);

int main(void) {
    int i, tableType;
    int range[3];
    char messages[3][MAX] = {"Minimum range: ", "Maximum range: ", "Count by: "};
    char string[MAX];

    printf("[C/c]elsius or [F/f]ahrenheit: ");
    tableType = getchar();
    while (getchar() != '\n');

    if (tableType != 'c' && tableType != 'C' && tableType != 'f' && tableType != 'F') {
        printf("%c is not a valid table type.\n", tableType);
        return -1;
    }

    for (int j = 0; j <= 2; j++) {
        printf(messages[j]);
        getString(string, MAX);
        range[j] = atoi(string);
    }

    if (tableType == 'c' || tableType == 'C') {
        printf("Cels\tFahr\n");
    } else if (tableType == 'f' || tableType == 'F') {
        printf("Fahr\tCels\n");
    }

    printf("----\t----\n");

    if (range[2] == 0) {
        printf("Third integer of range cannot be %i.\n", range[2]);
        return -1;
    }

    if (range[0] > range[1]) {
        for (i = range[0]; i >= range[1]; i -= range[2]) {
            iteration(i, tableType);
        }
    } else {
        for (i = range[0]; i <= range[1]; i += range[2]) {
            iteration(i, tableType);
        }
    }
    return 0;
}

void iteration(int temp, char symbol) {
    int result;

    if (symbol == 'c' || symbol == 'C') {
        result = 9 * temp / 5 + 32;
    } else if (symbol == 'f' || symbol == 'F') {
        result = 5 * (temp - 32) / 9;
    }

    printf("%i\t%i\n", temp, result);
}

void getString(char string[], int size) {
    int ch, k;

    k = 0;
    while ((ch = getchar()) != '\n' || k >= size) {
        string[k] = ch;
        k++;
    }
    string[k] = '\0';
}

/*
103: Modify the temperature conversion program to print a heading above the table.
104: Write a program to print the corresponding Celsius to Fahrenheit table.
105: Modify the temperature conversion program to print the table in reverse order, that is, from 300 degrees to 0.
115: Rewrite the temperature conversion program of Section 1.2 to use a function for conversion.
*/