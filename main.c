#include <stdio.h>
#include "list.h"

void displayInt(s_node * node) {
    int *ptrInt;
    if (node) {
        ptrInt = (int *) node->data;
        printf("%d", *ptrInt);
    }
}

int main(void) {
    int i = 1, j = 2;
    s_node *head = list_create();

    head = list_insert(head, (void *) &i);
    head = list_append(head, (void *) &j);

    displayList(head, &displayInt);
    
    return 0;
}