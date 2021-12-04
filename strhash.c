#include <stdio.h>
#include <string.h>
#include <math.h>
#include "strhash.h"
#include "list.h"

// création d'une table de hashage
tab_hash * tab_hash_create(void) {
    tab_hash * t = (tab_hash *) malloc(sizeof(tab_hash));
    
    if (t) {
        t->nbEntrees = MAX_ENTREES;

        for (int i = 0; i < MAX_ENTREES; i++) {
            t->liste[i] = list_create();
        }
    }

    return t;
}

// destruction d'une table de hashage
void tab_hash_destroy(tab_hash * t) {
    if (t) {
        for (int i = 0; i < t->nbEntrees; i++) {
            list_destroy(t->liste[i]);
        }
    }
}

// libération des données d'une table de hashage
void tab_hash_freedata(tab_hash * t) {
    for (int i = 0; i < t->nbEntrees; i++) {
        t->liste[i] = NULL;
    }
}

// ajout d'un mot dans la table de hashage
void tab_hash_ajout(tab_hash * t, const char *mot, int (*compare)(s_node *, void *)) {
    if (t && mot) {
        int cle = clef(mot, t->nbEntrees);
        char * copieMot = strdup(mot);
        t->liste[cle] = list_orderedAppend(&t->liste[cle], compare, copieMot);
    }
}

// suppression d'un mot dans la table de hashage
void tab_hash_suppression(tab_hash * t, char *mot, int (*compare)(s_node *, void *)) {
    if (t && mot) {
        int cle = clef(mot, t->nbEntrees);
        s_node *courant = t->liste[cle];

        if (t->liste[cle] != NULL) {
            int cmp = strcmp(t->liste[cle]->data, mot);
            if (strcmp(t->liste[cle]->data, mot) == 0) {
                //courant = t->liste[cle]->next;
                free(t->liste[cle]);
                t->liste[cle] = t->liste[cle]->next;
            } else {
                while (courant->next != NULL && cmp < 0) {
                    cmp = strcmp(courant->next->data, mot);
                    if (cmp == 0) {
                        s_node *tmp = courant->next->next;
                        free(courant->next);
                        courant->next = tmp;
                    } else {
                        courant = courant->next;
                    }
                }
            }
        }
    }
}

void displayMot(s_node * node) {
    if (node) {
        char *mot = (char *) node->data;
        printf("%s", mot);
    }
}

// affichage de données statistiques sur la table de hashage
void display_tab_hash(tab_hash * t) {
    if (t) {
        printf("Table de hashage (%d entrées) :\n", t->nbEntrees);
        float nbElemTot = 0;
        int sousTotal = 0;
        int nbMax = 0;
        int nbMin = 0;
        float sousTotaux[t->nbEntrees];
        float ecartsTypes[t->nbEntrees];
        float moyenne = 0;
        float ecartType = 0;
        s_node* curseur;
        // Parcours des sous-listes (calculs)
        for (int i = 0; i < t->nbEntrees; i++) {
            sousTotal = 0;
            curseur = t->liste[i];
            while (curseur != NULL) {
                sousTotal++;
                curseur = curseur->next;
            }

            nbMax = sousTotal > nbMax ? sousTotal : nbMax;
            nbMin = sousTotal < nbMin ? sousTotal : nbMin;
            nbElemTot += sousTotal;
            sousTotaux[i] = sousTotal;

        }
        moyenne = nbElemTot / t->nbEntrees;

        // Parcours de la liste principale (affichage + calcul écart type)
        for (int i = 0; i < t->nbEntrees; i++) {
            ecartType = (moyenne - sousTotaux[i]) * (moyenne - sousTotaux[i]);
            ecartType /= t->nbEntrees;
            ecartType = sqrt(ecartType);
            
            printf("\t%d.\tNbElem : %.0f, écart type : %.2f\t\tListe : ", i, sousTotaux[i], ecartType);
            displayList(t->liste[i], &displayMot);
        }

        printf("Nb total éléments : %.0f\n", nbElemTot);
        printf("Nb maximum éléments : %d\n", nbMax);
        printf("Nb minimum éléments : %d\n", nbMin);
        printf("Moyenne : %.2f\n", moyenne);
    } else {
        printf("NULL");
    }
}

// calcul de la clef de hashage
int clef(char *mot, int nbEntrees) {
    int clef = 0;
    char * curseur;
    for (curseur = mot; *curseur != '\0'; curseur++) {
        clef *= 2;
        clef += (int) *curseur;
    }
    clef = clef % nbEntrees;

    return clef;
}