#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *stream;
    char *filename, ch;
    int line_n;

    if (argc == 1) {
        printf("Error: No filepaths given.\n");
    }

    for (int i = 1; i < argc; i++) {
        filename = argv[i];
        stream = fopen(filename, "r");

        if (stream == NULL) {
            perror(filename);
            return 1;
        }

        printf("[Page %i: %s]\n", i, filename);
        line_n = 1;
        while (ch != EOF) {
            printf("%3i |", line_n);
            while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
                putchar(ch);
            }
            line_n++;
            putchar('\n');
        }
        ch = 0;
        printf("\n\f");

        fclose(stream);
    }
    printf("(END)");

    return 0;
}

/*
708: Write a program to print a set of files, starting each new one on a new page,
     with a title and a running page count for each file.
*/