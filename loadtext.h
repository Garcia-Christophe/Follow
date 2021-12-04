#include "list.h"
#include "strhash.h"
#include <limits.h>

#ifndef _LOADTEXT_H_
#define _LOADTEXT_H_

// struct token
struct _token {
    enum { WORD, SHORT_SPACE, SPACE, ERASE, INSERT, REPLACE, EMPTY } type;
    int textOffset; // décalage par rapport au début du texte
    union {
        char * word;
        char space[4];
    } data;
};

// création du type token
typedef struct _token token;

// charge un texte et le stock dans un tableau
void text_load();

// affichage du tableau de tokens du texte
void text_display();

#endif