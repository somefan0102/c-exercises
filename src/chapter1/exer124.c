#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

enum {
    NONE, O_PARENS, C_PARENS, O_BRACK,
    C_BRACK, O_CURLY, C_CURLY,
};

typedef struct NToken NToken;
typedef struct Marker Marker;

struct NToken {
    int token;
    int pos;
    NToken *next;
};

struct Marker {
    NToken *markee;
    Marker *next;
};

// Translate all the tokens in `stream` to a returned linked list of tokens.
NToken *getTokens(FILE *stream);

// Prints all errors to `stream`, with tokens starting at `head`.
void lintTokens(FILE *stream, NToken *head);

// Writes all tokens to `stream`, starting at `head` (for debugging).
void writeTokens(FILE *stream, NToken *head);

// Frees all tokens, starting at `h`.
void freeNTokens(NToken *head);
void freeMarkers(Marker *head);


int main(void) {
    NToken *head = getTokens(stdin);
    writeTokens(stdout, head);
    lintTokens(stdout, head);
    freeNTokens(head);
}

void freeNTokens(NToken *head) {
    for (NToken *p = head, *q = head; q; p = q) {
        q = p->next;
        free(p);
    }
}

void freeMarkers(Marker *head) {
    for (Marker *p = head, *q = head; q; p = q) {
        q = p->next;
        free(p);
    }
}

void writeTokens(FILE *stream, NToken *head) {
    for (NToken *p = head; p; p = p->next) {
        printf("[Token] %2i (%2i)\n", p->token, p->pos);
    }
}

NToken *getTokens(FILE *stream) {
    NToken *head = NULL;
    NToken *last;

    for (int i = 0, ch, nextch, token, sq=0, dq=0, iseof = 0; !iseof;) {
        if ((ch = getc(stream)) == EOF) {
            iseof = 1;
            continue;
        }
        i++;

        token = NONE;

        nextch = getc(stream); i++;
        if (ch == '/' && nextch == '*') {
            while (!iseof) {
                ch = getc(stream); i++;
                if (ch == '*') {
                    ch = getc(stream); i++;
                    if (ch == '/') {
                        break;
                    } else if (ch == EOF) {
                        iseof = 1;
                    } else {
                        ungetc(ch, stream); i--;
                    }
                } else if (ch == EOF) {
                    iseof = 1;
                }
            }
        } else if (ch == '/' && nextch == '/') {
            while (!iseof) {
                ch = getc(stream); i++;
                if (ch == '\n') {
                    break;
                } else if (ch == EOF) {
                    iseof = 1;
                }
            }
        } else if ((sq || dq) && ch == '\\') {
            if (nextch == EOF) {
                iseof = 1;
            }
            i++;
        } else {
            if (nextch == EOF) {
                iseof = 1;
            } else {
                ungetc(nextch, stream);
                i--;
            }
            switch (ch) {
                case '(': token = O_PARENS; break;
                case ')': token = C_PARENS; break;
                case '[': token = O_BRACK; break;
                case ']': token = C_BRACK; break;
                case '{': token = O_CURLY; break;
                case '}': token = C_CURLY; break;
                case '\"': if (!sq) { dq = !dq; } break;
                case '\'': if (!dq) { sq = !sq; } break;
            }
            if (sq || dq) {
                token = NONE;
            }
        }
        printf("%i %i\n", sq, dq);

        if (token) {
            if (head == NULL) {
                head = (NToken *)malloc(sizeof(NToken));
                assert(head);
                last = head;
            } else {
                last->next = (NToken *)malloc(sizeof(NToken));
                assert(last->next);
                last = last->next;
            }
            last->token = token;
            last->pos = i;
            last->next = NULL;
        }
    }

    return head;
}

void lintTokens(FILE *stream, NToken *head) {
    Marker *getPen(Marker *head);
    Marker *m_head = NULL;
    Marker *m_last = m_head;

    /*
     O_PARENS, C_PARENS, O_BRACK,
    C_BRACK, O_CURLY, C_CURLY,
    */

    for (NToken *p = head; p; p = p->next) {
        if (p->token == O_PARENS || p->token == O_BRACK || p->token == O_CURLY) {
            if (m_head == NULL) {
                m_head = (Marker *)malloc(sizeof(Marker));
                assert(m_head);
                m_last = m_head;
            } else {
                m_last->next = (Marker *)malloc(sizeof(Marker));
                assert(m_last->next);
                m_last = m_last->next;
            }
            m_last->markee = p;
            m_last->next = NULL;
        } else {
            Marker *q;
            q = getPen(head);
            if (q->markee->token == O_PARENS && p->token == C_PARENS) {
            } else if (q->markee->token == O_BRACK && p->token == C_BRACK) {
            } else if (q->markee->token == O_CURLY && p->token == C_CURLY) {
            } else {
                // error
            }
            free(q->next);
            q->next = NULL;
        }
    }

    // check if any still exist
    
    freeMarkers(m_head);
}

Marker *getPen(Marker* head) {

}

/*
124: Write a program to check a C program for rudimentary syntax errors like
     unmatched parentheses, brackets and braces. Don't forget about quotes,
     both single and double, escape sequences, and comments.
     (This program is hard if you do it in full generality.)
*/