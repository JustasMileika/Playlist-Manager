// Author of the program - Justas Mileika 2021 Vilnius University, Software Engineering, Bachelor's degree, first year, group 2. E-mail: justasmileika@gmail.com
#include "module.h"
#include <stdlib.h>
#include <stdio.h>

void destroyList(List **list)
{
    if(list == NULL || *list == NULL)
    {
        return;
    }
    List *previous = (*list);
    *list = (*list)->next;
    while(*list != NULL)
    {
        previous = *list;
        free((*list)->previous);
        *list = (*list)->next;
    }

    free(previous);
}

List *createList(int size)
{
    if(size <= 0)
    {
        return NULL;
    }
    List *head = NULL;
    head = malloc(sizeof(List));
    if(head == NULL)
    {
        return NULL;
    }
    head->next = NULL;
    head->previous = NULL;
    head->value = NULL;

    int counter = 1;
    List *current = head;
    while(counter < size)
    {
        List *node = NULL;
        node = malloc(sizeof(List));
        if(node == NULL)
        {
            return NULL;
        }
        node->value = NULL;
        current->next = node;
        node->previous = current;
        node->next = NULL;
        current = node;
        ++counter;
    }
    return head;
}

void printList(List *list, void (*print)(void *value))
{
    if(list == NULL || print == NULL)
    {
        return;
    }

    List *current = list;
    int counter = 1;
    while(current != NULL)
    {
        if(counter > 0)
        {
            printf("%d. ", counter);
        }
        else
        {
            printf("NaN. ");
        }

        print(current->value);
        current = current->next;
        if(counter > 0)
        {
            ++counter;
        }
        if(counter == INT_MAX)
        {
            counter = -1;
        }
    }
}

void removeDuplicates(List **list, int typeSize, int (*compare)(void *value1, void *value2))
{
    if(list == NULL || *list == NULL || getListSize(*list) == 1)
    {
        return;
    }
    List *current = (*list)->next;
    List *previous = (*list);
    int counter = 1;
    while(current != NULL)
    {
        if(current->value != NULL)
        {
            if(compare == NULL)
            {
                if(compareBytes(current->value, previous->value, typeSize))
                {
                    current = current->next;
                    deleteElement(list, counter);
                }
                else
                {
                    previous = previous->next;
                    current = current->next;
                     ++counter;
                }
            }
            else
            {
                if(compare(current->value, previous->value))
                {
                    current = current->next;
                    deleteElement(list, counter);
                }
                else
                {
                    previous = previous->next;
                    current = current->next;
                     ++counter;
                }
            }
        }
        else
        {
            current = current->next;
        }
    }
}

int compareBytes(void *value1, void *value2, int size)
{
    if(value1 == NULL || value2 == NULL)
    {
        return 0;
    }
    for(int i = 0; i < size; ++i)
    {
        if(*(char*)(value1 + i) != *(char*)(value2 + i))
        {
            return 0;
        }
    }
    return 1;
}

void *deleteElement(List **list, int position)
{
    if(list == NULL || *list == NULL || getListSize(*list) <= position || position < 0)
    {
        return NULL;
    }

    void *removedValue = NULL;

    if(position == 0)
    {
        removedValue = (*list)->value;
        *list = (*list)->next;
        free((*list)->previous);
        (*list)->previous = NULL;
    }
    else
    {
        int counter = 0;
        List *current = *list;
        while(current->next != NULL && counter < position)
        {
            current = current->next;
            ++counter;
        }
        removedValue = (current)->value;
        current->previous->next = current->next;

        if(current->next != NULL)
            current->next->previous = current->previous;

        free(current);
    }
    return removedValue;
}

void *getElement(List *list, int position)
{
    if(list == NULL || getListSize(list) <= position || position < 0)
    {
        return NULL;
    }
    int counter = 0;
    List *current = list;
    while(current->next != NULL && counter < position)
    {
        current = current->next;
        ++counter;
    }
    return current->value;
}

void *changeValue(List *list, void *value, int typeSize, int position)
{
    if(list == NULL || getListSize(list) <= position || position < 0)
    {
        return NULL;
    }
    int counter = 0;
    List *current = list;
    while(current->next != NULL && counter < position)
    {
        current = current->next;
        ++counter;
    }

    if(value != NULL)
    {
        current->value = NULL;
        current->value = malloc(typeSize);
        if(current->value == NULL)
        {
            return NULL;
        }
        for(int j = 0; j < typeSize; j++)
        {
            *(char *)(current->value + j) = *(char *)(value + j);
        }
    }
    else
    {
        current->value = NULL;
    }
    return current->value;
}

void *insertElement(List **list, void* value, int typeSize, int position)
{
    if(list == NULL || *list == NULL || getListSize(*list) < position || position < 0)
    {
        return NULL;
    }

    List *node = (List*) malloc(sizeof(List));
    if(node == NULL)
    {
        return NULL;
    }
    node->value = NULL;

    if(value != NULL && typeSize > 0)
    {
        node->value = malloc(typeSize);
        if(node->value == NULL)
        {
            return NULL;
        }

        for(int i = 0; i < typeSize; i++)
        {
            *(char *)(node->value + i) = *(char *)(value + i);
        }
    }

    if(position == 0)
    {
        node->next = *list;
        node->previous = NULL;
        (*list)->previous = node;
        *list = node;
    }
    else
    {
        int counter = 0;
        List *current = *list;
        while(current->next != NULL && counter < position - 1)
        {
            current = current->next;
            ++counter;
        }
        node->next = current->next;
        if(node->next != NULL)
        {
            (node->next)->previous = node;
        }
        node->previous = current;
        current->next = node;

    }
    return value;
}

int getListSize(List *list)
{
    if(list == NULL)
    {
        return 0;
    }
    if((*list).next == NULL)
    {
        return 1;
    }
    int size = 0;
    while(list != NULL)
    {
        list = list->next;
        ++size;
        if(size == INT_MAX)
        {
            return -1;
        }
    }
    return size;
}
