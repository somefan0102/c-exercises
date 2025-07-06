#ifndef OPTIONS_H
#define OPTIONS_H

// Stores the flag's `name` and its access to a `variable`.
typedef struct {
    char name;
    int *variable;
} Flag;

// Sets up the help tools.
void initHelp(char *hc, char *h);

// Show help using `*help`.
void showHelp(void);

// Show error from options with `reason` and last `option` used.
void optionError(char *option, char *reason);

/*
    Used to parse and execute each `*option` in `*argv[]`, and returns an exit code.
    with context of `*flags[]` for handling flags and `*(number_func)()` for handling numbers,
    Note that the only checking of a prefix symbol is a flag's hyphen for a character.
*/
int parseOption(char *option, Flag *p_flags[], int nonhyphen_options, int (*number_func)(char *option, int number));

#endif