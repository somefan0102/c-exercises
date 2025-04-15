#include <stdio.h>
#include <math.h>
#include <string.h>

#define SIZE 200

int htoi(char[]);

int main(void) {
    char line[SIZE];
    int i = 0;

    while (i < SIZE && ((line[i++] = getchar()) != '\n'));
    line[i-1] = '\0';

    printf("%i", htoi(line));
    
    return 0;
}

int htoi(char string[]) {
    int power = 0;
    int value = 0;

    for (int i = strlen(string)-1; i >= 0; i--) {
        if (string[i] >= '0' && string[i] <= '9') {
            value += (string[i] - 48) * pow(16, power);
        } else if (string[i] >= 'A' && string[i] <= 'F') {
            value += (string[i] - 55) * pow(16, power);
        } else if (string[i] >= 'a' && string[i] <= 'f') {
            value += (string[i] - 87) * pow(16, power);
        } else if ((i == 1 && (string[i] == 'x' || string[i] == 'X')) && (string[i-1] == '0')) {
            break;
        } else {
            return -1;
        }
        power++;
    }

    return value;
}

/*
203: Write a function `htoi(s)`, which converts a string of hexadecimal digits
     (including an optional `0x` or `0X`) into its equivalent integer value.
     The allowable digits are `0` through `9`, `a` through `f`, and `A` through `F`.
*/