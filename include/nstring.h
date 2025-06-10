#ifndef NSTRING_H
#define NSTRING_H

// Returns length of `str`, null-exclusive.
int strlen(char str[]);

// Returns length of `str`, null-inclusive.
int strlenn(char str[]);

// Return index of character `ch` found in `str`, else -1.
int strch(char str[], char ch);

// Return index of substring `sub` found in `str`, else -1.
int strsub(char str[], char sub[]);

// Reverses `str`.
void strreverse(char str[]);

// Returns whether `str1` with `str2` are equal.
int streq(char lstr[], char rstr[]);

// Slices `str1` and puts it to `str2` from index `start` to `end`, inclusive.
void strslice(char str1[], char str2[], int start, int end);

// Trims whitespace from left of `str`.
void ltrim(char str[]);

// Trims whitespace from right of `str`.
void rtrim(char str[]);

// Remove all characters in `targets` from `str`.
void squeeze(char str[], char targets[]);

#endif