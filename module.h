// Author of the program - Justas Mileika 2021 Vilnius University, Software Engineering, Bachelor's degree, first year, group 2. E-mail: justasmileika@gmail.com
#ifndef MODULE_H_INCLUDED
#define MODULE_H_INCLUDED

typedef struct DoublyLinkedList {
    void *value;
    struct DoublyLinkedList *next;
    struct DoublyLinkedList *previous;
} List;

// function that creates an empty list of size specified by the parameter size
// NULL is returned if function unsuccessful
List *createList(int size);

// function that inserts an element with a value into a certain position which are passed as a parameter into the list passed as a parameter.
// parameter typeSize indicates the size of the value in bytes
// the value passed as a parameter is returned on success and NULL is returned if function unsuccessful
void *insertElement(List **list, void* value, int typeSize, int position);

// function that returns a pointer to a value of the list in position specified by the parameters
// NULL is returned if function unsuccessful
void *getElement(List *list, int position);

// function that deletes an element from the list in position specified by the parameters
// the removed value is returned and NULL if function unsuccessful
void *deleteElement(List **list, int position);

// function that takes in pointer to a list and the size of the data type stored in the list
// and removes two adjacent elements if they are same when compared with a function which is passed as a function parameter
// the compare function should take in two void type pointers and return 1 if the elements are the same and 0 otherwise
// if NULL is passed as a compare function, the default byteCompare function is used as the comparing function
void removeDuplicates(List **list, int typeSize, int (*compare)(void *value1, void *value2));

// function that takes in a list and prints it out on the screen based on the print function which is passed as a parameter
// the print function must be with void return type and take in a void type pointer
void printList(List *list, void (*print)(void *value));

// function that returns the size of the list passed as a parameter
// -1 is returned if function unssuccessful
int getListSize(List *list);

// function that destroys the list passed as a parameter
void destroyList(List **list);

// function that changes the value of an element in the list at a certain position to a different value of size typeSize which are passed as parameters
// returns the changed value at the position specified or NULL otherwise
void *changeValue(List *list, void *value, int typeSize, int position);

// function that compares size amount of bytes from the memory locations passed and returns 1 if they are equal and 0 otherwise
int compareBytes(void *x, void *y, int size);

#endif // MODULE_H_INCLUDED
