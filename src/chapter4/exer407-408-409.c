#include <stdio.h>

#define BUFFER_SIZE 10

// For 409: Change buffer to store an int or signed char array rather!
signed char buf[BUFFER_SIZE];
signed char bufp = 0;

// For single pushback.
int single_buffer = 0;
int single_taken = 0;

// Gets the last input from buffer, else from user.
int getch(void);

// Stores `ch` to buffer, if not full.
void ungetch(int ch);

// Like `ungetch`, but stores a string.
void ungets(char str[]);

// Like `getch`, but for one character of pushback.
int getchs(void);

// Like `ungetch`, but for one character of pushback.
void ungetchs(int ch);

int getch(void) {
     if (bufp > 0) {
          return buf[--bufp];
     } else {
          return getchar();
     }
}

void ungetch(int ch) {
     if (bufp >= BUFFER_SIZE) {
          printf("Error: Too many characters.\n");
     } else {
          buf[bufp++] = ch;
     }
}

void ungets(char str[]) {
     for (int i = 0; str[i] != '\0'; i++) {
          ungetch(str[i]);
     }
}

int getchs(void) {
     if (single_taken) {
          single_taken = 0;
          return single_buffer;
     } else {
          return getchar();
     }
}

void ungetchs(int ch) {
     if (single_taken) {
          printf("Error: Too many characters.\n");
     } else {
          single_buffer = ch;
          single_taken = 1;
     }
}

/*
407: Write a routine `ungets(s)` that will push back an entire string onto the input.
     Should ungets know about buf and `bufp`, or should it just use `ungetch`?
408: Suppose that there will never be more than one character of pushback. Modify
     `getch` and `ungetch` accordingly.
409: Our `getch` and `ungetch` do not handle a pushed-back `EOF` correctly.
     Decide what their properties ought to be if an `EOF` is pushed back, then implement your design.
*/