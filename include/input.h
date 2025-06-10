#ifndef INPUT_H
#define INPUT_H

// Gets input until `delimiter` from user into `str`, but limited to `max` characters (including null). Returns null-included length or 0 if EOF.
int getinput(char str[], int max, char delimiter);

// Like `getinput()`, but `delimiter` is always newline (`\n`).
int getline(char str[], int max);

#endif