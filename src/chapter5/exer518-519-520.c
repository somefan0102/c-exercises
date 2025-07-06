#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "input.h"
#include "nstring.h"

// This also combines `dcl` and `undcl` functionality.
// I'll be more wary of writing more readable programs, but this is an obligatory exception.

#define MAX_TOKENS 200
#define MAX_TYPES 500
#define MAX_LINE 900
#define error(reason) printf("Error: %s\n", reason); exit(1);
#define append(appendee, string) strcat(appendee, string, MAX_LINE);
#define NONE 0

// For "ttype"
enum Type {
    TYPE_NONE, CHAR, INT, SHORT, LONG, DOUBLE, FLOAT, VOID,
};

// For "token" and "gettoken()".
enum Tokens {
    TOKEN_NONE, CONST, TYPE, NAME, POINTER, NUMBER, PARENS, BRACK, COMMA, NAME_IMPLIED,
};

// Stores the user input.
char line[MAX_LINE];
// Scanner for the user input.
int scan = 0;
// Saves the last point after the scan, useful for ungettoken().
int last_scan = 0;
// Stores the main name of declaration.
char name[MAX_LINE];
// Stores the output.
char output[MAX_LINE];
// Writes each type here as each type in types[] is processed.
char typename[MAX_LINE];
// Stack for storing each type in an integer code.
int types[MAX_TYPES];
// Stack "pointer" for the type stack.
int types_i = 0;
// Stores the token, synonymous with the return of gettoken().
int token;
// Like `last_scan`, but `token`.
int last_token = NONE;
int get_ready = 0;
// Stores the metadata or "type" of the token.
int ttype;
// Stores whether the "name" should be processed or not.
// Useful for not overwriting the main name when processing other names in function parameters.
int disallow_name = 0;

#define HELP \
"USAGE: dcl [OPTION]...\n\
\n\
dcl is a program that parses and converts complicated C declarations into English text and vice versa.\n\
It is more than rudimentary yet less than complete.\n\
\n\
OPTIONS:\n\
\n\
-h   Display help information.\n\
-u   undcl mode: Convert English text back to C declarations.\n\
\n\
ARGS:\n\
\n\
Once the program is run, you can type a C declaration, however with some caveats:\n\
\n\
* ONLY ONE data type must always be explicitly defined. (No \"const int x\" or \"const long int x\")\n\
* A declaration must always have a name, even ones in function parameters, and even ones whose type is \"void\".\n\
    * However names in function parameters won't be saved or processed into text.\n\
* There are no \"signed\", \"unsigned\", \"static\", and other modifiers, only const and the data types shown in the syntax ref.\n\
* Limitations of declaring with arrays and functions are limited; you can have arrays of functions and functions of arrays.\n\
\n\
SYNTAX:\n\
\n\
t:       ('const '|) ('char' | 'short' | 'int' | 'long' | 'float' | 'double' | 'void')\n\
d:       [t] [pd]\n\
p:       '*' ([p]|)\n\
pd:      [p] [ed]\n\
ed:      [name] | '(' [pd] ')' | [ed] ([b] | [f])\n\
b:       '[' [number] ']'\n\
f:       '(' [arg] ')'\n\
arg:     [t] [ad] {',' [arg]|}\n\
pad:     [p] [ad]                            // Like [pd]\n\
ad:      '(' [pad] ')' | [ad] ([b] | [f])    // Like [ad]\n\
name:    // A series of letters, digits, and underscres. But should NOT begin with a number.\n\
number:  // A series of digits from 0-9.\n\
\n\
SYNTAX KEYS:\n\
\n\
'xyz'\tVerbatim text.\n\
()\tGroup to retain its intended priority.\n\
{}\tOptional, can be treated the same when skipped.\n\
\\\\\tComments.\n\
[x]\tSymbol, defined in another line, except for [name] and [number].\n"

// "Ungets" the previous token and clears every variable used for parsing.
void ungettoken(void);
// Gets the next token.
int gettoken(void);
int getuntoken(void);
// Pushes the next data type to the stack.
char *getdt(void);
// Pops the top data type from the stack.
void putdt(int dt);

// Function used to parse each symvol respectively.
void parse_t(void);
void parse_d(void);
void parse_pd(void); // Covers "p" and "pd" itself.
void parse_ed(void);
void parse_b(void);
void parse_f(void);
void parse_arg(void);
void parse_pad(void);
void parse_ad(void);

// Turns text back to declarations.
char *undcl(int length, int is_in);

void parse_arg(void) {
    append(output, "`");
    parse_t();
    parse_pad();
    append(output, getdt());
    append(output, "\"");

    if (gettoken() == COMMA) {
        append(output, ", and a ");
        parse_arg();
    } else {
        ungettoken();
    }
}

void putdt(int dt) {
    if (types_i >= MAX_TYPES) {
        error("Can't push another data type; stack full.");
    }
    types[types_i++] = dt;
}

char *getdt(void) {
    int dt_code;
    typename[0] = '\0';

    if (types_i <= 0) {
        error("Can't fetch another data type; stack empty.");
    }
    
    dt_code = types[--types_i];

    if (dt_code < 0) {
        dt_code *= -1;
        append(typename, "const ");
    }

    if (dt_code == CHAR) {
        append(typename, "char");
    } else if (dt_code == INT) {
        append(typename, "int");
    } else if (dt_code == SHORT) {
        append(typename, "short");
    } else if (dt_code == LONG) {
        append(typename, "long");
    } else if (dt_code == DOUBLE) {
        append(typename, "double");
    } else if (dt_code == FLOAT) {
        append(typename, "float");
    } else if (dt_code == VOID) {
        append(typename, "void");
    }
    return typename;
}

void parse_d(void) {
    parse_t();
    parse_pd();
}

void parse_pd(void) {
    int count;

    for (count = 0; gettoken() == POINTER; count++);
    ungettoken();

    parse_ed();

    while (count-- > 0) {
        append(output, "pointer to a ")
    }
}

void parse_pad(void) {
    int count;

    for (count = 0; gettoken() == POINTER; count++);
    ungettoken();

    parse_ad();

    while (count-- > 0) {
        append(output, "pointer to a ")
    }
}

void parse_t(void) {
    int my_token = gettoken();
    int sign = 1;

    if (my_token == CONST) {
        my_token = gettoken();
        sign = -1;
    }

    if (my_token == TYPE) {
        putdt(sign * ttype);
    } else {
        error("Can't parse; a type was missing.");
    }
}

void parse_ed(void) {
    int my_token = gettoken();
    int next_token;

    if (my_token != NAME) {
        if (my_token == PARENS && ttype == '(') {
            parse_pd();
            if (gettoken() == PARENS && ttype != ')') {
                error("Can't parse; A parenthesis was missing.");
            }
        } else {
            error("Can't parse; A name or parenthesis was missing.");
        }
    }

    while (((next_token = gettoken()) == PARENS && ttype == '(') || (next_token == BRACK && ttype == '[')) {
        ungettoken();
        if (next_token == BRACK) {
            parse_b();
        } else {
            parse_f();
        }
    }
    ungettoken();
}

void parse_ad(void) {
    int my_token = gettoken();
    int next_token;

    if (my_token != NAME_IMPLIED) {
        if (my_token == PARENS && ttype == '(') {
            parse_pad();
            if (gettoken() == PARENS && ttype != ')') {
                error("Can't parse; (arg) A parenthesis was missing.");
            }
        } else {
            error("Can't parse; you may have forgotten to name a function parameter.");
        }
    }

    while (((next_token = gettoken()) == PARENS && ttype == '(') || (next_token == BRACK && ttype == '[')) {
        ungettoken();
        if (next_token == BRACK) {
            parse_b();
        } else {
            parse_f();
        }
    }
    ungettoken();
}

void parse_b(void) {
    int my_token, number;
    char str[MAX_LINE];

    if ((my_token = gettoken()) == BRACK && ttype == '[') {
        if ((my_token = gettoken()) == NUMBER) {
            number = ttype;
            if ((my_token = gettoken()) == BRACK && ttype == ']') {
                append(output, "array[");
                itoa(number, str);
                append(output, str);
                append(output, "] of ");
            } else {
                error("Can't parse; a bracket was missing.");
            }
        } else if (my_token == BRACK && ttype == ']') {
            append(output, "array[] of ");
        } else {
            error("Can't parse; a number was missing.");
        }
    } else {
        error("Can't parse; a bracket was missing.");
    }
}

void parse_f(void) {
    int my_token;
    int was_zero = (disallow_name == 0);

    if ((my_token = gettoken()) == PARENS && ttype == '(') {
        append(output, "function ");
        disallow_name = 1;
        if ((my_token = gettoken()) == PARENS && ttype == ')') {
            append(output, "that returns a ");
        } else if (my_token == TYPE || my_token == CONST) {
            ungettoken();
            append(output, "that takes a (");
            parse_arg();
            append(output, ") ");
            if ((my_token = gettoken()) == PARENS && ttype == ')') {
                append(output, "that returns a ");
            } else {
                error("Can't parse; a missing function parenthesis was missing.");
            }
        } else {
            error("Can't parse; a missing function parenthesis or parameter was missing.");
        }
    } else {
        error("Can't parse; a missing function parenthesis was missing.");
    }

    if (was_zero) {
        disallow_name = 0;
    }
}

void ungettoken(void) {
    scan = last_scan;
    token = NONE;
    ttype = 0;
}

enum UnToken {
    WORD_NONE, WORD_CONST, WORD_CHAR, WORD_INT, WORD_LONG,
    WORD_SHORT, WORD_DOUBLE, WORD_FLOAT, WORD_VOID, WORD_ARRAY,
    WORD_FUNCTION, WORD_TAKES, WORD_POINTER, WORD_RETURNS, WORD_SQUOTE,
    WORD_EQUOTE, WORD_COMMA, WORD_SPAR, WORD_EPAR, WORD_AND, WORD_A,
    WORD_TO, WORD_OF, WORD_THAT, WORD_IS,
};

int getuntoken(void) {
    char token_str[MAX_LINE];
    int i;
    token = NONE;
    ttype = 0;
    last_scan = scan;

    if (get_ready) {
        last_token = 0;
        get_ready = 0;
    }

    while (isspace(line[scan])) {
        scan++;
    };

    switch (line[scan]) {
        case '(':
            token = WORD_SPAR;
            get_ready = 1;
            scan++;
            break;

        case ')':
            token = WORD_EPAR;
            get_ready = 1;
            scan++;
            break;

        case ',':
            token = WORD_COMMA;
            get_ready = 1;
            scan++;
            break;

        case '`':
            token = WORD_SQUOTE;
            get_ready = 1;
            scan++;
            break;

        case '\"':
            token = WORD_EQUOTE;
            get_ready = 1;
            scan++;
            break;

        default:
            if (isalpha(line[scan])) {
                for (i = 0; isalnum(line[scan]) || line[scan] == '[' || line[scan] == ']'; i++, scan++) {
                    token_str[i] = line[scan];
                }
            } else {
                return NONE;
            }
            token_str[i] = '\0';

            if (!strcmp("const", token_str)) {
                token = WORD_CONST;
                get_ready = 1;
            } else if (!strcmp("char", token_str)) {
                token = WORD_CHAR;
                get_ready = 1;
            } else if (!strcmp("int", token_str)) {
                token = WORD_INT;
                get_ready = 1;
            } else if (!strcmp("long", token_str)) {
                token = WORD_LONG;
                get_ready = 1;
            } else if (!strcmp("double", token_str)) {
                token = WORD_DOUBLE;
                get_ready = 1;
            } else if (!strcmp("float", token_str)) {
                token = WORD_FLOAT;
                get_ready = 1;
            } else if (!strcmp("void", token_str)) {
                token = WORD_VOID;
                get_ready = 1;
            } else if (!strcmp("function", token_str)) {
                token = WORD_FUNCTION;
                get_ready = 1;
            } else if (!strcmp("takes", token_str)) {
                token = WORD_TAKES;
            } else if (!strcmp("returns", token_str)) {
                token = WORD_RETURNS;
            } else if (!strcmp("pointer", token_str)) {
                token = WORD_POINTER;
                last_token = 1;
            } else if (!strcmp("and", token_str)) {
                token = WORD_AND;
            } else if (!strcmp("is", token_str)) {
                token = WORD_IS;
            } else if (!strcmp("a", token_str)) {
                token = WORD_A;
            } else if (!strcmp("to", token_str)) {
                token = WORD_TO;
            } else if (!strcmp("of", token_str)) {
                token = WORD_OF;
            } else if (!strcmp("that", token_str)) {
                token = WORD_THAT;
            } else if (!strncmp("array", token_str, 5)) {
                token = WORD_ARRAY;
                last_token = 0;
                while (token_str[i] != '[' && token_str[i] >= 0) {
                    i--;
                }
                if (i < 0) {
                    return NONE;
                }
                if (token_str[i+1] == ']') {
                    ttype = -1;
                    return token;
                }
                i++;
                ttype = atoi(token_str+i);
                if (ttype < 0) {
                    return NONE;
                }
            }
            break;
    }

    // printf("TK: %i\tTP: %i\tP:%i\n", token, ttype, last_token);
    return token;
}

int gettoken(void) {
    token = NONE;
    ttype = 0;
    last_scan = scan;

    while (isspace(line[scan])) {
        scan++;
    };

    switch (line[scan]) {
        case '(': case ')':
            ttype = line[scan];
            token = PARENS;
            scan++;
            break;

        case '[': case ']':
            ttype = line[scan];
            token = BRACK;
            scan++;
            break;
        
        case '*':
            ttype = 0;
            token = POINTER;
            scan++;
            break;
        
        case ',':
            ttype = 0;
            token = COMMA;
            scan++;
            break;

        default:
            if (isdigit(line[scan])) {
                token = NUMBER;
                ttype = atoi(line+scan);
                while (isdigit(line[scan])) {
                    scan++;
                };
            } else if (isalpha(line[scan]) || line[scan] == '_') {
                int i;
                char token_str[MAX_LINE];
                for (i = 0; isalnum(line[scan]) || line[scan] == '_'; i++, scan++) {
                    token_str[i] = line[scan];
                }
                token_str[i] = '\0';

                if (!strcmp("char", token_str)) {
                    token = TYPE;
                    ttype = CHAR;
                } else if (!strcmp("short", token_str)) {
                    token = TYPE;
                    ttype = SHORT;
                } else if (!strcmp("int", token_str)) {
                    token = TYPE;
                    ttype = INT;
                } else if (!strcmp("long", token_str)) {
                    token = TYPE;
                    ttype = LONG;
                } else if (!strcmp("float", token_str)) {
                    token = TYPE;
                    ttype = FLOAT;
                } else if (!strcmp("double", token_str)) {
                    token = TYPE;
                    ttype = DOUBLE;
                } else if (!strcmp("void", token_str)) {
                    token = TYPE;
                    ttype = VOID;
                } else if (!strcmp("const", token_str)) {
                    token = CONST;
                } else {
                    if (disallow_name) {
                        token = NAME_IMPLIED;
                    } else {
                        token = NAME;
                        if (!*name) {
                            for (int i = 0; i < MAX_LINE && token_str[i]; i++) {
                                name[i] = token_str[i];
                            }
                        }
                    }
                }
            }
            break;
    }

    return token;
}

char *undcl(int length, int is_in) {
    int my_token, next_token;
    char *temp = (char *)malloc(MAX_LINE*sizeof(char));
    char temp2[MAX_LINE];

    if (is_in == 1) {
        temp[0] = '_';
        temp[1] = '\0';
    } else {
        int i;
        for (i = 0; isalnum(line[scan]) || line[scan] == '_'; i++, scan++) {
            temp[i] = line[scan];
        }
        
        temp[i] = '\0';
    }

    if (is_in == 0) {
        while (isalnum(line[scan]) || line[scan] == '_') {
            scan++;
        }
        while (isspace(line[scan])) {
            scan++;
        }

        if (getuntoken() == WORD_IS) {
            if (getuntoken() == WORD_A) {
                // Pass.
            } else {
                error("Token of \"a\" expected before \"is\".");
            }
        } else {
            error("Token of name expected before \"is\".");
        }
    }

    if (is_in == 1) {
        if (getuntoken() == WORD_SQUOTE) {
            // Pass.
        } else {
            error("Token of \"`\" expected in function parameter.");
        }
    }

    do {
        strcpy(temp2, temp);
        my_token = getuntoken();
        if (my_token == WORD_FUNCTION) {
            if (last_token) {
                sprintf(temp, "(%s)", temp2);
            } else {
                sprintf(temp, "%s", temp2);
            }
            if (getuntoken() == WORD_THAT) {
                if ((next_token = getuntoken()) == WORD_TAKES) {
                    if (getuntoken() == WORD_A) {
                        if (getuntoken() == WORD_SPAR) {
                            append(temp, "(");
                            char *a = undcl(0, 1);
                            append(temp, a);
                            free(a);
                            if (getuntoken() == WORD_EPAR) {
                                append(temp, ")");
                                if (getuntoken() == WORD_THAT) {
                                    if (getuntoken() == WORD_RETURNS) {
                                        if (getuntoken() == WORD_A) {
                                            // Pass.
                                        } else {
                                            error("Token of \"a\" expected after \"returns\".");
                                        }
                                    } else {
                                        error("Token of \"takes\" or \"returns\" after \"that\".");
                                    }
                                } else {
                                    error("Token of \"that\" expected after \")\"."); 
                                }
                            } else {
                                error("Token of \")\" expected in function parameter."); 
                            }
                        } else {
                            error("Token of \"(\" expected after \"a\"."); 
                        }
                    } else {
                        error("Token of \"a\" expected after \"takes\".");
                    }
                } else if (next_token == WORD_RETURNS) {
                    append(temp, "()");
                    if (getuntoken() == WORD_A) {
                        // Pass.
                    } else {
                        error("Token of \"a\" expected after \"returns\".");
                    }
                } else {
                    error("Token of \"takes\" or \"returns\" after \"that\".");
                }
            } else {
                error("Token of \"that\" expected after \"function\".");
            }
        } else if (my_token == WORD_POINTER) {
            sprintf(temp, "*%s", temp2);
            if (getuntoken() == WORD_TO) {
                if (getuntoken() == WORD_A) {
                    // Pass.
                } else {
                    error("Token of \"a\" expected after \"to\".");
                }
            } else {
                error("Token of \"to\" expected after \"pointer\".");
            }
        } else if (my_token == WORD_ARRAY) {
            if (last_token) {
                sprintf(temp, "(%s)", temp2);
            } else {
                sprintf(temp, "%s", temp2);
            }
            if (ttype == -1) {
                append(temp, "[]");
            } else {
                char str[MAX_LINE];
                append(temp, "[");
                itoa(ttype, str);
                append(temp, str);
                append(temp, "]");
            }
            if (getuntoken() == WORD_OF) {
                // Pass.
            } else {
                error("Token of \"of\" expected after \"array\"."); 
            }
        } else if (my_token == WORD_CHAR) {
            sprintf(temp, "char %s", temp2);
        } else if (my_token == WORD_INT) {
            sprintf(temp, "int %s", temp2);
        } else if (my_token == WORD_LONG) {
            sprintf(temp, "long %s", temp2);
        } else if (my_token == WORD_DOUBLE) {
            sprintf(temp, "double %s", temp2);
        } else if (my_token == WORD_SHORT) {
            sprintf(temp, "short %s", temp2);
        } else if (my_token == WORD_FLOAT) {
            sprintf(temp, "float %s", temp2);
        } else if (my_token == WORD_VOID) {
            sprintf(temp, "void %s", temp2);
        } else if (my_token == WORD_CONST) {
            if ((next_token = getuntoken()) == WORD_CHAR) {
                sprintf(temp, "char %s", temp2);
            } else if (next_token == WORD_INT) {
                sprintf(temp, "int %s", temp2);
            } else if (next_token == WORD_LONG) {
                sprintf(temp, "long %s", temp2);
            } else if (next_token == WORD_DOUBLE) {
                sprintf(temp, "double %s", temp2);
            } else if (next_token == WORD_SHORT) {
                sprintf(temp, "short %s", temp2);
            } else if (next_token == WORD_FLOAT) {
                sprintf(temp, "float %s", temp2);
            } else if (next_token == WORD_VOID) {
                sprintf(temp, "void %s", temp2);
            } else {
                error("Type expected, got something else.");
            }
            strcpy(temp2, temp);
            sprintf(temp, "const %s", temp2);
        } else if (my_token == WORD_A) { // From pointer.
            
        }
    } while ((is_in) ? my_token != WORD_EQUOTE : my_token);

    if (is_in == 1) {
        if (getuntoken() == WORD_COMMA) {
            append(temp, ", ");
            if (getuntoken() == WORD_AND) {
                if (getuntoken() == WORD_A) {
                    char *a = undcl(0, 1);
                    append(temp, a);
                    free(a);
                } else {
                    error("Token of \"a\" expected after \"and\".");
                }
            } else {
                error("Token of \"and\" expected after \",\".");
            }
        } else {
            ungettoken();
        }
    }
    return temp;
}

int main(int argc, char *argv[]) {
    int is_undcl = 0;
    int length;
    char *unoutput;
    output[0] = '\0';

    if (argc > 2) {
        error("Only one option is neccessary.");
    }

    if (argc == 2) {
        if (!strcmp("-h", argv[1])) {
            printf("%s", HELP);
            return 0;
        } else if (!strcmp("-u", argv[1])) {
            is_undcl = 1;
        } else {
            error("Option not recognized.");
        }
    }

    printf(is_undcl ? "Text: " : "Declaration: ");
    length = getline(line, MAX_LINE);

    if (length) {
        if (is_undcl) {
            unoutput = undcl(length, 0);
            printf("%s", unoutput);
            free(unoutput);
        } else {
            parse_d();
            printf("%s is a %s%s\n", name, output, getdt());
        }
    }

    return 0;

    // do {
    //     gettoken();
    //     printf("TK: %i\tTP: %i\n", token, ttype);
    // } while (token != NONE);
}

/*
518: Make `dcl` recover from input errors.
519: Modify `undcl` so that it does not add redundant parentheses to declarations.
520: Expand `dcl` to handle declarations with function argument types, qualifiers like
     const, and so on. 
*/