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
    if (data != NULL) {
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

// compare la valeur d'un noeud dans la liste (int)
// retourne -1 si la valeur existe déjà
// retourne -2 si un il y a un problème de comparaison
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

// ajout d'un noeud dans une liste ordonnee
// selon le resulat de "compare" ;
// si la donnee existe deja, elle n'est pas ajoutee
s_node * list_orderedAppend(s_node ** head, int (*compare)(s_node *, void *), void *param) {
    if (param != NULL) {
        s_node * inserted_node = (s_node *) malloc(sizeof(s_node));
        if (inserted_node) {
            int comparison = (*compare)(*head, param);
            if (comparison == -1) {
                printf("list.c > list_orderedAppend(s_node **, int (*compare)(s_node *, void *), void *) > data already exists.\n");
            } else if (comparison == -2) {
                printf("list.c > list_orderedAppend(s_node **, int (*compare)(s_node *, void *), void *) > comparison problem in the list.\n");
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
    if (head != NULL) {
        s_node *ptr = head;
        if (ptr->data == data) {
            head = list_headRemove(head);
        } else {
            while(ptr->next != NULL && ptr->next->data != data){
                ptr = ptr->next;
            }

            if(ptr->next->data == data) {
                s_node *tmp = ptr->next;
                ptr->next = ptr->next->next;
                free(tmp);
            }
        }
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
    s_node *cursor1 = head;
    s_node *cursor2 = head;

    while (cursor1) {
        cursor2 = cursor1->next;
        cursor1->next = NULL;
        free(cursor1);
        cursor1 = cursor2;
    }

    cursor1->next = NULL;
    free(cursor1);
    cursor2->next = NULL;
    free(cursor2);
}

// affiche les données des nodes de la liste
void displayList(s_node * head, void (*display)(s_node *)) {
    s_node *ptr = head;

    while (ptr) {
        (*display) (ptr);
        printf("->");
        ptr = ptr->next;
    }

    printf("NULL\n");
}