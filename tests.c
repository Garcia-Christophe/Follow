#include <stdio.h>
#include "list.h"
#include "testListHelpers.h"

void displayInt(s_node * node) {
    int *ptrInt;
    if (node) {
        ptrInt = (int *) node->data;
        printf("%d", *ptrInt);
    }
}

int main() {
    printf("\nTESTS DU PROJET FOLLOW\n");
    printf("======================\n");

    // Tests 
    // printf("\nAffichage de la liste (normale) :\n");

    int i = 1, j = 2, k = 3;
    s_node *head = list_create(); // NULL
    printf("Création\nRésultat attendu : NULL : %d\n", check_list_state(head, &node_int_to_string, "null"));
    displayList(head, &displayInt);
    printf("\n");

    head = list_insert(head, (void *) &i); // 1->NULL
    printf("Insert 1\nRésultat attendu : 1->NULL : %d\n", check_list_state(head, &node_int_to_string, "1 -> null"));
    displayList(head, &displayInt);
    printf("\n");

    head = list_append(head, (void *) &j); // 1->2->NULL
    printf("Append 2\nRésultat attendu : 1->2->NULL : %d\n", check_list_state(head, &node_int_to_string, "1 -> 2 -> null"));
    displayList(head, &displayInt);
    printf("\n");

    head = list_insert(head, (void *) &k); // 3->1->2->NULL
    printf("Insert 3\nRésultat attendu : 3->1->2->NULL : %d\n", check_list_state(head, &node_int_to_string, "3 -> 1 -> 2 -> null"));
    displayList(head, &displayInt);
    printf("\n");

    head = list_remove(head, (void *) &j); // 3->1->NULL
    printf("Remove 2\nRésultat attendu : 3->1->NULL : %d\n", check_list_state(head, &node_int_to_string, "3 -> 1 -> null"));
    displayList(head, &displayInt);
    printf("\n");

    head = list_headRemove(head); // 1->NULL
    printf("Remove head\nRésultat attendu : 1->NULL : %d\n", check_list_state(head, &node_int_to_string, "1 -> null"));
    displayList(head, &displayInt);
    printf("\n");

    head = list_remove(head, (void *) &i); // NULL
    printf("Remove 1\nRésultat attendu : NULL : %d\n", check_list_state(head, &node_int_to_string, "null"));
    displayList(head, &displayInt);
    printf("\n");

    head = list_remove(head, (void *) &i); // NULL
    printf("Remove 1\nRésultat attendu : NULL : %d\n", check_list_state(head, &node_int_to_string, "null"));
    displayList(head, &displayInt);
    printf("\n");

    int l = 1, m = 2, n = 4, o = 3, p = 5, q = 0;
    s_node *ordered_head = list_create(); // NULL
    printf("\tliste créée : ");
    displayList(ordered_head, &displayInt);

    ordered_head = list_insert(ordered_head, (void *) &l); // 1->NULL
    printf("\tliste (insert 1) : ");
    displayList(ordered_head, &displayInt);

    ordered_head = list_append(ordered_head, (void *) &m); // 1->2->NULL
    printf("\tliste (append 2) : ");
    displayList(ordered_head, &displayInt);

    ordered_head = list_append(ordered_head, (void *) &n); // 1->2->4->NULL
    printf("\tliste (append 4) : ");
    displayList(ordered_head, &displayInt);

    ordered_head = list_orderedAppend(&ordered_head, compareInt, (void *) &o); // 1->2->3->4->NULL
    printf("\tliste (ordered append 3) : ");
    displayList(ordered_head, &displayInt);

    ordered_head = list_orderedAppend(&ordered_head, compareInt, (void *) &m); // 1->2->3->4->NULL
    printf("\tliste (ordered append 2, déjà existant) : ");
    displayList(ordered_head, &displayInt);

    ordered_head = list_orderedAppend(&ordered_head, compareInt, (void *) &p); // 1->2->3->4->5->NULL
    printf("\tliste (ordered append 5) : ");
    displayList(ordered_head, &displayInt);

    ordered_head = list_orderedAppend(&ordered_head, compareInt, (void *) &q); // 0->1->2->3->4->5->NULL
    printf("\tliste (ordered append 0) : ");
    displayList(ordered_head, &displayInt);

    return 0;
}