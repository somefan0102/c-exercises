#include <stdio.h>
#include "nstring.h"

#define swap(t,x,y) t temp = y; y = x; x = temp 

void recur_itoa(int n, char s[]);
void recur_reverse(char s[]);

int main(void) {
     char str[] = "";
     char space[100] = "\0";
     int x = -242374;

     recur_reverse(str);
     printf("%s\n", str);

     recur_itoa(x, space);
     printf("%s", space);

     return 0;
}

void recur_itoa(int n, char s[]) {
     if (n < 0) {
          s[strlen(s)] = '-';
          s[strlen(s)+1] = '\0';
          n = -n;
     }

     if (n / 10) {
          recur_itoa(n / 10, s);
     }
     
     s[strlen(s)] = n % 10 + '0';
     s[strlen(s)+1] = '\0';
}

void recur_reverse(char s[]) {
     int start = 0;
     int end = strlen(s)-1;
     char t[end];

     strslice(s, t, start+1, end-1);
     t[end-1] = '\0';
     swap(char, s[start], s[end]);

     if (strlen(s) > 2) {
          recur_reverse(t);
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