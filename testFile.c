// Author of the program - Justas Mileika 2021 Vilnius University, Software Engineering, Bachelor's degree, first year, group 2. E-mail: justasmileika@gmail.com

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "module.h"

void printInt(void *value);
int compare(void *x, void *y);

int main()
{
    // List currently : None

    List *head = createList(-1); // List currently : None
    assert(head == NULL); // List currently : None

    head = createList(1); // List after the change : [NULL]
    assert(head != NULL); // List currently : [NULL]
    assert(head->value == NULL); // List currently : [NULL]
    assert(getListSize(head) == 1); // List currently : [NULL]

    int x = 16;
    assert(changeValue(head, &x, sizeof(int), 0) != NULL); // List after the change : [16]
    assert(changeValue(NULL, &x, sizeof(int), 0) == NULL); // List currently : [16]
    assert(changeValue(head, &x, sizeof(int), 1) == NULL); // List currently : [16]
    assert(changeValue(head, &x, sizeof(int), -1) == NULL); // List currently : [16]

    assert(*(int*)getElement(head, 0) == 16); // List after the change : [16]
    assert(getElement(NULL, 0) == NULL); // List currently : [16]
    assert(getElement(head, -1) == NULL); // List currently : [16]
    assert(getElement(head, 1) == NULL); // List currently : [16]

    int y = 25;

    assert(insertElement(&head, &y, sizeof(int), 1) != NULL); // List after the change : [16, 25]
    assert(insertElement(NULL, &y, sizeof(int), 1) == NULL); // List currently : [16, 25]
    assert(insertElement(&head, &y, sizeof(int), -1) == NULL); // List currently : [16, 25]

    assert(getListSize(head) == 2); // List currently : [16, 25]

    assert(*(int*)getElement(head, 1) == 25); // List currently : [16, 25]

    int z = 36;

    assert(insertElement(&head, &z, sizeof(int), 2) != NULL); // List after the change : [16, 25, 36]

    assert(*(int*)getElement(head, 2) == 36); // List currently : [16, 25, 36]

    assert(deleteElement(&head, 0) != NULL); // List after the change : [25, 36]
    assert(deleteElement(NULL, 0) == NULL); // List currently : [25, 36]
    assert(deleteElement(&head, 3) == NULL); // List currently : [25, 36]
    assert(deleteElement(&head, -1) == NULL); // List currently : [25, 36]

    assert(*(int*)getElement(head, 0) == 25); // List currently : [25, 36]

    int i = 25;
    insertElement(&head, &i, sizeof(int), 1); // List after the change : [25, 25, 36]

    assert(getListSize(head) == 3); // List currently : [25, 25, 36]

    removeDuplicates(&head, sizeof(int), NULL); // List after the change : [25, 36]

    assert(*(int*)getElement(head, 0) == 25); // List currently : [25, 36]
    assert(*(int*)getElement(head, 1) == 36); // List currently : [25, 36]

    assert(getListSize(head) == 2); // List currently : [25, 36]

    insertElement(&head, &i, sizeof(int), 1); // List after the change : [25, 25, 36]

    removeDuplicates(&head, sizeof(int), compare); // List after the change : [25, 36]

    assert(*(int*)getElement(head, 0) == 25); // List currently : [25, 36]
    assert(*(int*)getElement(head, 1) == 36); // List currently : [25, 36]

    assert(getListSize(head) == 2); // List currently : [25, 36]

    printList(NULL, printInt); // List currently : [25, 36]
    printList(head, NULL); // List currently : [25, 36]
    printf("Final list before destruction:\n");
    printList(head, printInt); // List currently : [25, 36]

    destroyList(&head); // List currently : [25, 36]

    assert(getListSize(head) == 0); // List currently : None

    free(head);

    return 0;
}

int compare(void *x, void *y)
{
    if(x == NULL || x == NULL)
    {
        return 0;
    }
    if(*(int*)x == *(int*)y)
    {
        return 1;
    }
    return 0;
}

void printInt(void *value)
{
    if(value == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        printf("%d\n", *(int*)value);
    }
}
