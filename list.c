#include <stdio.h>
#include "list.h"

// creation d'une nouvelle liste vide
s_node * list_create(void) {
    return NULL;
}

// lire la donnee d'un noeud
void * list_get_data(s_node * node) {
    return node->data;
}

// ecrire la donnee d'un noeud
void list_set_data(s_node * node, void * data) {
    node->data = data;
}

// creation et insertion d'un noeud en tete de liste
// retourne la tete de liste
s_node * list_insert(s_node * head, void * data) {
    if (data != NULL) {
        s_node * inserted_node = (s_node *) malloc(sizeof(s_node));
        if (inserted_node) {
            list_set_data(inserted_node, data);
            inserted_node->next = head;
            head = inserted_node;
        } else
            printf("list.c > list_insert(s_node *, void *) > allocation failed.\n");
    } else
        printf("list.c > list_insert(s_node *, void *) > data NULL.\n");

    return head;
}

// creation et ajout d'un noeud en queue de liste
// retourne la tete de liste
s_node * list_append(s_node * head, void * data) {
    if (data != NULL && head != NULL) {
        s_node * inserted_node = (s_node *) malloc(sizeof(s_node));
        if (inserted_node) {
            list_set_data(inserted_node, data);
            s_node * cursor = head;
            while (cursor->next != NULL) {
                cursor = cursor->next;
            }
            cursor->next = inserted_node;
        } else
            printf("list.c > list_append(s_node *, void *) > allocation failed.\n");
    } else
        printf("list.c > list_append(s_node *, void *) > data NULL.\n");
    
    return head;
}

// ajout d'un noeud dans une liste ordonnee
// selon le resulat de "compare" ;
// si la donnee existe deja, elle n'est pas ajoutee
s_node * list_orderedAppend(s_node ** head, int (*compare)(s_node *, void *), void *param) {
    if (param != NULL) {
        if (*head == NULL) {
            return list_insert(*head, param);
        }
        s_node * inserted_node = (s_node *) malloc(sizeof(s_node));
        if (inserted_node) {
            int comparison = (*compare)(*head, param);
            if (comparison == -1) {
                printf("list.c > list_orderedAppend(s_node **, int (*compare)(s_node *, void *), void *) > data already exists.\n");
            } else {
                s_node * cursor = *head;
                int i = 0;

                // test if it's an insert
                if (comparison == 0) {
                    list_set_data(inserted_node, param);
                    inserted_node->next = cursor;
                    head = &inserted_node;
                } else {
                    // otherwise test if we have to append
                    i++;
                    while (cursor != NULL && i < comparison) {
                        cursor = cursor->next;
                        i++;
                    }

                    if (i == comparison) {
                        list_set_data(inserted_node, param);
                        inserted_node->next = cursor->next;
                        cursor->next = inserted_node;
                    } else {
                        printf("list.c > list_orderedAppend(s_node **, int (*compare)(s_node *, void *), void *) > fail to append.\n");
                    }
                }
            }
        } else
            printf("list.c > list_orderedAppend(s_node **, int (*compare)(s_node *, void *), void *) > allocation failed.\n");
    } else
        printf("list.c > list_orderedAppend(s_node **, int (*compare)(s_node *, void *), void *) > param NULL.\n");
    
    return *head;
}

// suppression de la premiere instance d'une
// donnee dans la liste, retourne la tete de liste
s_node * list_remove(s_node * head, void * data) {
    s_node *courant = head;
    if (head == NULL)
        return head;

    if (head->data == data){
        courant = head->next;
        free(head);
        return courant;
    }

    while (courant->next != NULL) {
        if(courant->next->data == data){
            s_node *tmp = courant->next->next;
            free(courant->next);
            courant->next = tmp;
            return head;
        }

        courant = courant->next;
    }

    return head;
}

// suppression de la tete de liste
// retourne la nouvelle tete de liste
s_node * list_headRemove(s_node * head) {
    s_node * new_head = head;
    if (head != NULL) {
        new_head = head->next;
        head = NULL;
        free(head);
    }

    return new_head;
}

// destruction d'une liste
//  (La liberation des donnees n'est pas prise en charge)
void list_destroy(s_node * head) {
    while (head != NULL) {
        head = list_headRemove(head);
    }
}

// affiche les données des nodes de la liste
void displayList(s_node * head, void (*display)(s_node *)) {
    s_node *ptr = head;

    while (ptr) {
        (*display) (ptr);
        printf(" -> ");
        ptr = ptr->next;
    }

    printf("null\n");
}