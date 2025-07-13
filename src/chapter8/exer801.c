#include <fcntl.h>

#define BUFFER_SIZE 0x1000

enum Streams {
    stdin, stdout, stderr,
};

int strlen(char s[]);
void print(char s[], int error);

int main(int argc, char *argv[]) {
    /* This is faster, I assume? It uses rawer calls to the system
     than stdio.h and doesn't use file pointers and structures. */

    int fd, nbytes;
    char buffer[BUFFER_SIZE];

    if (argc == 1) {
        print("Usage: cat [file]...\n", 1);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        fd = open(argv[i], O_RDONLY, 0);
        
        if (fd == -1) {
            print("Error: Can't open \"", 1);
            print(argv[i], 1);
            print("\"; permission denied or file not found.\n", 1);
            return 1;
        }

        while ((nbytes = read(fd, buffer, BUFFER_SIZE)) > 0) {
            if (write(stdout, buffer, nbytes) != nbytes) {
                print("Error: While writing bytes to output.\n", 1);
            }
        }

        close(fd);
    }

    return 0;
}

int strlen(char s[]) {
    int i;
    for (i = 0; s[i]; i++);
    return i;
}

void print(char s[], int error) {
    write((error) ? stderr : stdout, s, strlen(s));
}

/*
#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *file;
    int ch;

    if (argc == 1) {
        printf("Usage: cat [file]...\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        file = fopen(argv[i], "r");

        if (file == NULL) {
            fprintf(stderr, "Error: Can't open %s.", argv[i]);
        }

        while ((ch = getc(file)) != EOF) {
            putchar(ch);
        }

        fclose(file);
    }

    return 0;
}
*/

/*
801: Rewrite the program cat from Chapter 7 using `read`, `write`, `open`,
     and `close` instead of their standard library equivalents.
     Perform experiments to determine the relative speeds of the two versions.
*/