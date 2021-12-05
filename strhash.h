#include "list.h"
#include <limits.h>

#ifndef _STRHASH_H_
#define _STRHASH_H_

#define MAX_ENTREES 10

// struct liste
struct _liste {
    s_node *liste[MAX_ENTREES];
    int nbEntrees;
};

// création du type tab_hash
typedef struct _liste tab_hash;

// création d'une table de hashage
tab_hash * tab_hash_create(void);

// destruction d'une table de hashage
void tab_hash_destroy(tab_hash * t);

// libération des données d'une table de hashage
void tab_hash_freedata(tab_hash * t);

// ajout d'un mot dans la table de hashage
void tab_hash_ajout(tab_hash * t, const char *mot, int (*compare)(s_node *, void *));

// suppression d'un mot dans la table de hashage
void tab_hash_suppression(tab_hash * t, char *mot);

// affichage de données statistiques sur la table de hashage
void display_tab_hash(tab_hash * t);

#endif