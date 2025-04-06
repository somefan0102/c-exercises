#include <stdio.h>

int main(void) {
    printf("getchar() != EOF  --> %2i\n", getchar() != EOF);
    printf("EOF (End of file) --> %2i\n", EOF);
    return 0;
}

/*
106: Verify that the expression `getchar() != EOF` is `0` or `1`.
107: Write a program to print the value of `EOF`.
*/