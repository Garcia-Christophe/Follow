#include <stdio.h>
#include <string.h>
#include "list.h"
#include "testListHelpers.h"
#include "strhash.h"
#include "loadtext.h"

void displayInt(s_node * node) {
    int *ptrInt;
    if (node) {
        ptrInt = (int *) node->data;
        printf("%d", *ptrInt);
    }
}

// compare la valeur d'un noeud dans la liste (int)
// retourne -1 si la valeur existe déjà
// sinon retourne "l'indice" de la place du noeud dans la liste
int compareInt(s_node * head, void * data) {
    int res = 0;
    s_node * cursor = head;
    
    while (cursor != NULL && *(int *) cursor->data < *(int *) data) {
        cursor = cursor->next;
        res++;
    }

    if (cursor != NULL && *(int *) data == *(int *) cursor->data) {
        res = -1;
    }

    return res;
}

// compare la valeur d'un noeud dans la liste (pointeur de char)
// retourne -1 si la valeur existe déjà
// sinon retourne "l'indice" de la place du noeud dans la liste
int compareMot(s_node * head, void * data) {
    int res = 0;
    int cmp = 0;
    s_node * cursor = head;
    
    // Cherche la place du mot tant que le curseur n'est pas null (fin de chaîne)
    // tant que la valeur n'existe pas
    // tant que la valeur suivante est plus petite (ou égale mais dans ce cas s'arrête aussi par la cond. préc.)
    while (cursor != NULL && res != -1 && cmp <= 0) {
        cmp = strcmp(cursor->data, data);
        if (cmp < 0) {
            cursor = cursor->next;
            res++;
        } else if (cmp == 0) {
            res = -1;
        }
    }

    return res;
}

void testList() {
    // Tests liste normale
    printf("\n=== Tests de la liste (normale) ===\n");

    int i = 1, j = 2, k = 3;
    s_node *head = list_create(); // NULL
    printf("Création\nRésultat attendu : null : %d\n", check_list_state(head, &node_int_to_string, "null"));
    displayList(head, &displayInt);
    list_to_string(head, &displayInt);
    printf("\n\n");

    head = list_insert(head, (void *) &i); // 1->NULL
    printf("Insert 1\nRésultat attendu : 1 -> null : %d\n", check_list_state(head, &node_int_to_string, "1 -> null"));
    displayList(head, &displayInt);
    list_to_string(head, &displayInt);
    printf("\n\n");

    head = list_append(head, (void *) &j); // 1->2->NULL
    printf("Append 2\nRésultat attendu : 1 -> 2 -> null : %d\n", check_list_state(head, &node_int_to_string, "1 -> 2 -> null"));
    displayList(head, &displayInt);
    list_to_string(head, &displayInt);
    printf("\n\n");

    head = list_insert(head, (void *) &k); // 3->1->2->NULL
    printf("Insert 3\nRésultat attendu : 3 -> 1 -> 2 -> null : %d\n", check_list_state(head, &node_int_to_string, "3 -> 1 -> 2 -> null"));
    displayList(head, &displayInt);
    list_to_string(head, &displayInt);
    printf("\n\n");

    head = list_remove(head, (void *) &j); // 3->1->NULL
    printf("Remove 2\nRésultat attendu : 3 -> 1 -> null : %d\n", check_list_state(head, &node_int_to_string, "3 -> 1 -> null"));
    displayList(head, &displayInt);
    list_to_string(head, &displayInt);
    printf("\n\n");

    head = list_append(head, (void *) &j); // 3->1->2->NULL
    printf("Append 2\nRésultat attendu : 3 -> 1 -> 2 -> null : %d\n", check_list_state(head, &node_int_to_string, "3 -> 1 -> 2 -> null"));
    displayList(head, &displayInt);
    list_to_string(head, &displayInt);
    printf("\n\n");

    head = list_remove(head, (void *) &j); // 3->1->NULL
    printf("Remove 2\nRésultat attendu : 3 -> 1 -> null : %d\n", check_list_state(head, &node_int_to_string, "3 -> 1 -> null"));
    displayList(head, &displayInt);
    list_to_string(head, &displayInt);
    printf("\n\n");

    head = list_append(head, (void *) &j); // 3->1->2->NULL
    printf("Append 2\nRésultat attendu : 3 -> 1 -> 2 -> null : %d\n", check_list_state(head, &node_int_to_string, "3 -> 1 -> 2 -> null"));
    displayList(head, &displayInt);
    list_to_string(head, &displayInt);
    printf("\n\n");

    head = list_headRemove(head); // 1->2->NULL
    printf("Remove head\nRésultat attendu : 1 -> 2 -> null : %d\n", check_list_state(head, &node_int_to_string, "1 -> 2 -> null"));
    displayList(head, &displayInt);
    list_to_string(head, &displayInt);
    printf("\n\n");

    head = list_remove(head, (void *) &i); // 2->NULL
    printf("Remove 1\nRésultat attendu : 2 -> null : %d\n", check_list_state(head, &node_int_to_string, "2 -> null"));
    displayList(head, &displayInt);
    list_to_string(head, &displayInt);
    printf("\n\n");

    head = list_remove(head, (void *) &i); // 2->NULL (remove nothing, &i already removed)
    printf("Remove 1\nRésultat attendu : 2 -> null : %d\n", check_list_state(head, &node_int_to_string, "2 -> null"));
    displayList(head, &displayInt);
    list_to_string(head, &displayInt);
    printf("\n\n");

    // Tests liste ordonée
    printf("\n=== Tests de la liste ordonée ===\n");

    int l = 1, m = 2, n = 4, o = 3, p = 5, q = 0;
    s_node *ordered_head = list_create(); // NULL
    printf("Création\nRésultat attendu : null : %d\n", check_list_state(ordered_head, &node_int_to_string, "null"));
    displayList(ordered_head, &displayInt);
    list_to_string(ordered_head, &displayInt);
    printf("\n\n");

    ordered_head = list_insert(ordered_head, (void *) &l); // 1->NULL
    printf("Insert 1\nRésultat attendu : 1 -> null : %d\n", check_list_state(ordered_head, &node_int_to_string, "1 -> null"));
    displayList(ordered_head, &displayInt);
    list_to_string(ordered_head, &displayInt);
    printf("\n\n");

    ordered_head = list_append(ordered_head, (void *) &m); // 1->2->NULL
    printf("Append 2\nRésultat attendu : 1 -> 2 -> null : %d\n", check_list_state(ordered_head, &node_int_to_string, "1 -> 2 -> null"));
    displayList(ordered_head, &displayInt);
    list_to_string(ordered_head, &displayInt);
    printf("\n\n");

    ordered_head = list_append(ordered_head, (void *) &n); // 1->2->4->NULL
    printf("Append 4\nRésultat attendu : 1 -> 2 -> 4 -> null : %d\n", check_list_state(ordered_head, &node_int_to_string, "1 -> 2 -> 4 -> null"));
    displayList(ordered_head, &displayInt);
    list_to_string(ordered_head, &displayInt);
    printf("\n\n");

    ordered_head = list_orderedAppend(&ordered_head, &compareInt, (void *) &o); // 1->2->3->4->NULL
    printf("Ordered append 3\nRésultat attendu : 1 -> 2 -> 3 -> 4 -> null : %d\n", check_list_state(ordered_head, &node_int_to_string, "1 -> 2 -> 3 -> 4 -> null"));
    displayList(ordered_head, &displayInt);
    list_to_string(ordered_head, &displayInt);
    printf("\n\n");

    ordered_head = list_orderedAppend(&ordered_head, &compareInt, (void *) &m); // 1->2->3->4->NULL
    printf("Ordered append 2 (déjà existant)\nRésultat attendu : 1 -> 2 -> 3 -> 4 -> null : %d\n", check_list_state(ordered_head, &node_int_to_string, "1 -> 2 -> 3 -> 4 -> null"));
    displayList(ordered_head, &displayInt);
    list_to_string(ordered_head, &displayInt);
    printf("\n\n");

    ordered_head = list_orderedAppend(&ordered_head, &compareInt, (void *) &p); // 1->2->3->4->5->NULL
    printf("Ordered append 5\nRésultat attendu : 1 -> 2 -> 3 -> 4 -> 5 -> null : %d\n", check_list_state(ordered_head, &node_int_to_string, "1 -> 2 -> 3 -> 4 -> 5 -> null"));
    displayList(ordered_head, &displayInt);
    list_to_string(ordered_head, &displayInt);
    printf("\n\n");

    ordered_head = list_orderedAppend(&ordered_head, &compareInt, (void *) &q); // 0->1->2->3->4->5->NULL
    printf("Ordered append 0\nRésultat attendu : 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> null : %d\n", check_list_state(ordered_head, &node_int_to_string, "0 -> 1 -> 2 -> 3 -> 4 -> 5 -> null"));
    displayList(ordered_head, &displayInt);
    list_to_string(ordered_head, &displayInt);
    printf("\n\n");

    ordered_head = list_remove(ordered_head, (void *) &n); // 0->1->2->3->5->NULL
    printf("Remove 4\nRésultat attendu : 0 -> 1 -> 2 -> 3 -> 5 -> null : %d\n", check_list_state(ordered_head, &node_int_to_string, "0 -> 1 -> 2 -> 3 -> 5 -> null"));
    displayList(ordered_head, &displayInt);
    list_to_string(ordered_head, &displayInt);
    printf("\n\n");

    ordered_head = list_orderedAppend(&ordered_head, &compareInt, (void *) &n); // 0->1->2->3->4->5->NULL
    printf("Ordered append 4\nRésultat attendu : 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> null : %d\n", check_list_state(ordered_head, &node_int_to_string, "0 -> 1 -> 2 -> 3 -> 4 -> 5 -> null"));
    displayList(ordered_head, &displayInt);
    list_to_string(ordered_head, &displayInt);
    printf("\n\n");

    ordered_head = list_remove(ordered_head, (void *) &n); // 0->1->2->3->5->NULL
    printf("Remove 4\nRésultat attendu : 0 -> 1 -> 2 -> 3 -> 5 -> null : %d\n", check_list_state(ordered_head, &node_int_to_string, "0 -> 1 -> 2 -> 3 -> 5 -> null"));
    displayList(ordered_head, &displayInt);
    list_to_string(ordered_head, &displayInt);
    printf("\n\n");

    ordered_head = list_orderedAppend(&ordered_head, &compareInt, (void *) &n); // 0->1->2->3->4->5->NULL
    printf("Ordered append 4\nRésultat attendu : 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> null : %d\n", check_list_state(ordered_head, &node_int_to_string, "0 -> 1 -> 2 -> 3 -> 4 -> 5 -> null"));
    displayList(ordered_head, &displayInt);
    list_to_string(ordered_head, &displayInt);
    printf("\n\n");

    list_destroy(ordered_head); // 0->1->2->3->4->5->NULL
    printf("Destroy\nRésultat attendu : 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> null : %d\n", check_list_state(ordered_head, &node_int_to_string, "0 -> 1 -> 2 -> 3 -> 4 -> 5 -> null"));
    displayList(ordered_head, &displayInt);
    list_to_string(ordered_head, &displayInt);
    printf("\n\n");
}

void testStrhash() {
    // Tests strhash
    printf("\n=== Tests de strhash ===\n");
    printf("\n");

    // création de la table de hashage
    tab_hash *t = NULL;
    display_tab_hash(t); // NULL
    printf("\n");
    t = tab_hash_create();
    t->nbEntrees = 10;
    printf("-> Création de la table\n");
    display_tab_hash(t); // vide
    printf("\n");

    // suppression "zozm"
    char* mot1 = "zozm";
    printf("-> Suppression de '%s'\n", mot1);
    tab_hash_suppression(t, mot1);
    display_tab_hash(t);
    printf("\n");

    // ajout (t = NULL)
    printf("-> Ajout (t == NULL)\n");
    tab_hash_ajout(NULL, mot1, &compareMot);
    display_tab_hash(t);
    printf("\n");

    // ajout (mot = NULL)
    printf("-> Ajout (mot == NULL)\n");
    tab_hash_ajout(t, NULL, &compareMot);
    display_tab_hash(t);
    printf("\n");

    // suppression (t = NULL)
    printf("-> Suppression (t == NULL)\n");
    tab_hash_suppression(NULL, mot1);
    display_tab_hash(t);
    printf("\n");

    // suppression (mot = NULL)
    printf("-> Suppression (mot == NULL)\n");
    tab_hash_suppression(t, NULL);
    display_tab_hash(t);
    printf("\n");

    // ajout "zozm"
    printf("-> Ajout de '%s'\n", mot1);
    tab_hash_ajout(t, mot1, &compareMot);
    display_tab_hash(t);
    printf("\n");

    // ajout "voiture"
    char* mot2 = "voiture";
    printf("-> Ajout de '%s'\n", mot2);
    tab_hash_ajout(t, mot2, &compareMot);
    display_tab_hash(t);
    printf("\n");

    // ajout "abc"
    char* mot3 = "abc";
    printf("-> Ajout de '%s'\n", mot3);
    tab_hash_ajout(t, mot3, &compareMot);
    display_tab_hash(t);
    printf("\n");

    // ajout "mozzm"
    char* mot7 = "mozzm";
    printf("-> Ajout de '%s'\n", mot7);
    tab_hash_ajout(t, mot7, &compareMot);
    display_tab_hash(t);
    printf("\n");

    // suppression "voiture"
    printf("-> Suppression de '%s'\n", mot2);
    tab_hash_suppression(t, mot2);
    display_tab_hash(t);
    printf("\n");

    // ajout " "
    char* mot4 = " ";
    printf("-> Ajout de '%s'\n", mot4);
    tab_hash_ajout(t, mot4, &compareMot);
    display_tab_hash(t);
    printf("\n");

    // ajout ""
    char* mot5 = "";
    printf("-> Ajout de '%s'\n", mot5);
    tab_hash_ajout(t, mot5, &compareMot);
    display_tab_hash(t);
    printf("\n");

    // ajout "voiture" (réajout)
    printf("-> Ajout de '%s'\n", mot2);
    tab_hash_ajout(t, mot2, &compareMot);
    display_tab_hash(t);
    printf("\n");

    // ajout " " (doublon)
    printf("-> Ajout de '%s'\n", mot4);
    tab_hash_ajout(t, mot4, &compareMot);
    display_tab_hash(t);
    printf("\n");

    // ajout "" (doublon)
    printf("-> Ajout de '%s'\n", mot5);
    tab_hash_ajout(t, mot5, &compareMot);
    display_tab_hash(t);
    printf("\n");

    // suppression ""
    printf("-> Suppression de '%s'\n", mot5);
    tab_hash_suppression(t, mot5);
    display_tab_hash(t);
    printf("\n");

    // suppression "test" (n'existe pas")
    char* mot6 = "test";
    printf("-> Suppresion de '%s'\n", mot6);
    tab_hash_suppression(t, mot6);
    display_tab_hash(t);
    printf("\n");

    // suppression "abc"
    printf("-> Suppresion de '%s'\n", mot3);
    tab_hash_suppression(t, mot3);
    display_tab_hash(t);
    printf("\n");

    // suppression "zozm"
    printf("-> Suppresion de '%s'\n", mot1);
    tab_hash_suppression(t, mot1);
    display_tab_hash(t);
    printf("\n");

    // suppression "mozzm"
    printf("-> Suppresion de '%s'\n", mot7);
    tab_hash_suppression(t, mot7);
    display_tab_hash(t);
    printf("\n");

    // free data
    printf("-> Free data\n");
    tab_hash_freedata(t);
    display_tab_hash(t);
    printf("\n");

    // destroy
    printf("-> Destroy\n");
    tab_hash_destroy(t);
    display_tab_hash(t);
    printf("\n");
}

int main() {
    printf("\nTESTS DU PROJET FOLLOW\n");
    printf("======================\n");

    // testList();
    testStrhash();

    return 0;
}