#ifndef INPUT_H
#define INPUT_H

// Gets input until newline from user into `str`, but limited to `max` characters (including null).
// Returns null-included length or 0 if EOF.
int getline(char str[], int max);

// Gets input until a `delimiter` from user into `str`, but limited to `max` characters (including null).
// Returns null-included length or 0 if EOF.
int getinput(char str[], int max, char delimiter);

#endif