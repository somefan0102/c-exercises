#include <stdio.h>
#include <stdlib.h>
#include "nstring.h"

#define min(x,y) ((x > y) ? y : x)

int main(int argc, char *argv[]) {
    FILE *stream1, *stream2;
    long last_pos1 = 0, last_pos2 = 0;
    int line_no1 = 0, line_no2 = 0;
    int differ, ch1, ch2, pos = 0;
    int is_same = 0;

    if (argc < 3) {
        printf("Error: Need only 2 argument for filepaths.\n");
        return 1;
    }

    stream1 = fopen(argv[1], "r");
    stream2 = fopen(argv[2], "r");

    if (stream1 == NULL) {
        perror(argv[1]);
        return 1;
    } else if (stream2 == NULL) {
        perror(argv[2]);
        return 1;
    }

    while ((ch1 = fgetc(stream1)) == (ch2 = fgetc(stream2))) {
        if (ch1 == EOF || ch2 == EOF) {
            is_same = 1;
            break;
        }
        if (ch1 == '\n') {
            last_pos1 = ftell(stream1);
            line_no1++;
        }
        if (ch2 == '\n') {
            last_pos2 = ftell(stream2);
            line_no2++;
        }
        pos++;
    }
    
    if (is_same) {
        printf("Both files have the same contents. :)");
        return 0;
    }

    ungetc(ch1, stream1);
    ungetc(ch2, stream2);
    differ = min(line_no1, line_no2) + 1;

    fseek(stream1, last_pos1, SEEK_SET);
    fseek(stream2, last_pos2, SEEK_SET);

    printf("Both files differs at line %i.\n", differ);
    printf("[Filename 1] %s\n", argv[1]);
    printf("[Filename 2] %s\n", argv[2]);

    printf("[File 1] (Line %i) ", differ);
    for (int i = 0; (ch1 = fgetc(stream1)) != '\n' && ch1 != EOF; i++) {
        putchar(ch1);
    }
    putchar('\n');
    printf("[File 2] (Line %i) ", differ);
    for (int i = 0; (ch2 = fgetc(stream2)) != '\n' && ch2 != EOF; i++) {
        putchar(ch2);
    }
    putchar('\n');

    fclose(stream1);
    fclose(stream2);
    
    return 0;
}

/*
706: Write a program to compare two files, printing the first line where they differ.
*/