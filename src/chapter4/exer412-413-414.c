#include <stdio.h>
#include "nstring.h"

#define swap(t,x,y) t temp = y; y = x; x = temp 

void itoa(int n, char s[]);
void reverse(char s[]);

int main(void) {
     char str[] = "Hello, world!";
     char space[100] = "\0";
     int x = -242374;

     reverse(str);
     printf("%s\n", str);

     itoa(x, space);
     printf("%s", space);
}

void itoa(int n, char s[]) {
     if (n < 0) {
          s[strlen(s)] = '-';
          s[strlen(s)+1] = '\0';
          n = -n;
     }

     if (n / 10) {
          itoa(n / 10, s);
     }
     
     s[strlen(s)] = n % 10 + '0';
     s[strlen(s)+1] = '\0';
}

void reverse(char s[]) {
     int start = 0;
     int end = strlen(s)-1;
     char t[end+1];

     strslice(s, t, start+1, end-1);
     swap(char, s[start], s[end]);

     if (strlen(s) > 2) {
          reverse(t);
          for (int i = 1; i <= strlen(t); i++) {
               s[i] = t[i-1];
          }
     }
}

/*
412: Adapt the ideas of printd to write a recursive version of `itoa`; that is, convert
     an integer into a string by calling a recursive routine.
413: Write a recursive version of the function `reverse(s)`, which reverses the string `s` in place.
414: Define a macro `swap(t,x,y)` that interchanges two arguments of type `t`. (Block structure will help.)
*/