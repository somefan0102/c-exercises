#ifndef NSTRING_H
#define NSTRING_H

#define strlen(s)           n_strlen(s)
#define strcpy(s, t)        n_strcpy(s, t)
#define strcmp(s, t)        n_strcmp(s, t)
#define strcat(s, t, z)     n_strcat(s, t, z)
#define strncpy(s, t, n)    n_strncpy(s, t, n)
#define strncmp(s, t, n)    n_strncmp(s, t, n)
#define strncat(s, t, n, z) n_strncat(s, t, n, z)
#define atoi(s)             n_atoi(s)
#define atof(s)             n_atof(s)
#define itob(n,s,b)         n_itob(n,s,b);

// Returns a null-exclusive length of `*s`.
int n_strlen(char *s);

// Copies `*t` into `*s`.
void n_strcpy(char *s, char *t);

// Returns the difference of `*s` to `*t`.
int n_strcmp(char *s, char *t);

// Appends `*t` to `*s`, with precaution of `*s`' `size`.
void n_strcat(char *s, char *t, int size);

// Copies `n` characters of `*s` into `*t`.
void n_strncpy(char *s, char *t, int n);

// Returns the difference of `n` characters of `*s` to `*t`.
int n_strncmp(char *s, char *t, int n);

// Appends `*t` with `n` characters to `*s`, with precaution of `*s`' `size`.
void n_strncat(char *s, char *t, int size, int n);

// Returns an integer equivalent of `*s`.
int n_atoi(char *s);

// Returns `str` as double.
double n_atof(char str[]);

// Returns a string equivalent of `n` into `*s`.
void itoa(int n, char *s);

// Returns a string equivalent of `n` into `*s` with base of `b`.
void n_itob(int n, char s[], int b);

// Return whether `ch` is a sign operator.
int issign(char ch);

// Reverses `*s`.
void reverse(char *s);

// Returns the index where `ch` begins in `*s`.
int strfind(char *s, char ch);

// Returns the index where the first occurance of substring `*t` begins in `*s`.
int strend(char *s, char *t);

// Return index of substring `sub` found in `str`, starting from rightmost item.
int strindex(char str[], char sub[]);

// Writes `*t` to be `*s` sliced from indices `start` to `end`, inclusive.
void strslice(char *s, char *t, int start, int end);

// Removes any characters in `*t` from `*s`.
void squeeze(char *s, char *t);

// Converts all characters in `*s` to lowercase.
void strlower(char *s);

// Converts all characters in `*s` to uppercase.
void strupper(char *s);

#endif