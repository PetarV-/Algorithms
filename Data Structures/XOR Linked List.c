/*
 Petar 'PetarV' Velickovic
 Data Structure: XOR Linked List
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct XORNode
{
    int data;
    struct XORNode *XOR;
} XNode;

typedef struct XORLinkedList
{
    XNode *first;
    XNode *last;
} XLL;

void initialize(XLL *l)
{
    l -> first = l -> last = NULL;
}

XNode* addAfter(XLL *l, XNode *n, int data)
{
    // PRECONDITION: l is empty, or n is in l

    if (l -> first == NULL)
    {
        XNode *new = (XNode*)malloc(sizeof(XNode));
        new -> data = data;
        new -> XOR = NULL;
        l -> first = new;
        l -> last = new;
        
        return new;
    }
    else
    {
        XNode *prevPtr = NULL;
        XNode *currPtr = l -> first;
        XNode *nextPtr = l -> first -> XOR;
        while (currPtr != n)
        {
            prevPtr = currPtr;
            currPtr = nextPtr;
            nextPtr = (XNode*)((uintptr_t)prevPtr ^ (uintptr_t)(currPtr -> XOR));
        }
        XNode *new = (XNode*)malloc(sizeof(XNode));
        new -> data = data;
        new -> XOR = (XNode*)((uintptr_t)currPtr ^ (uintptr_t)nextPtr);
        
        currPtr -> XOR = (XNode*)((uintptr_t)(currPtr -> XOR) ^ (uintptr_t)nextPtr ^ (uintptr_t)new);
        if (nextPtr != NULL) nextPtr -> XOR = (XNode*)((uintptr_t)(nextPtr -> XOR) ^ (uintptr_t)currPtr ^ (uintptr_t)new);
        else l -> last = new;
        
        return new;
    }
}

XNode* addBefore(XLL *l, XNode *n, int data)
{
    // PRECONDITION: l is empty, or n is in l
    
    if (l -> last == NULL)
    {
        XNode *new = (XNode*)malloc(sizeof(XNode));
        new -> data = data;
        new -> XOR = NULL;
        l -> first = new;
        l -> last = new;
        
        return new;
    }
    else
    {
        XNode *prevPtr = NULL;
        XNode *currPtr = l -> last;
        XNode *nextPtr = l -> last -> XOR;
        while (currPtr != n)
        {
            prevPtr = currPtr;
            currPtr = nextPtr;
            nextPtr = (XNode*)((uintptr_t)prevPtr ^ (uintptr_t)(currPtr -> XOR));
        }
        XNode *new = (XNode*)malloc(sizeof(XNode));
        new -> data = data;
        new -> XOR = (XNode*)((uintptr_t)currPtr ^ (uintptr_t)nextPtr);
        
        currPtr -> XOR = (XNode*)((uintptr_t)(currPtr -> XOR) ^ (uintptr_t)nextPtr ^ (uintptr_t)new);
        if (nextPtr != NULL) nextPtr -> XOR = (XNode*)((uintptr_t)(nextPtr -> XOR) ^ (uintptr_t)currPtr ^ (uintptr_t)new);
        else l -> first = new;
        
        return new;
    }
}

void delete(XLL *l, XNode *n)
{
    // PRECONDITION: n is in l
    
    if (l -> first == l -> last)
    {
        free(l -> first);
        l -> first = l -> last = NULL;
    }
    
    else
    {
    
        XNode *prevPtr = NULL;
        XNode *currPtr = l -> first;
        XNode *nextPtr = l -> first -> XOR;
    
        while (currPtr != n)
        {
            prevPtr = currPtr;
            currPtr = nextPtr;
            nextPtr = (XNode*)((uintptr_t)prevPtr ^ (uintptr_t)(currPtr -> XOR));
        }
        
        if (prevPtr != NULL) prevPtr -> XOR = (XNode*)((uintptr_t)(prevPtr -> XOR) ^ (uintptr_t)currPtr ^ (uintptr_t)nextPtr);
        else l -> first = nextPtr;
        
        if (nextPtr != NULL) nextPtr -> XOR = (XNode*)((uintptr_t)(nextPtr -> XOR) ^ (uintptr_t)currPtr ^ (uintptr_t)prevPtr);
        else l -> last = prevPtr;
        
    }
}

void traverseForward(XLL *l)
{
    if (l -> first == NULL) return;
    
    XNode *prevPtr = NULL;
    XNode *currPtr = l -> first;
    XNode *nextPtr = l -> first -> XOR;
    
    while (currPtr != NULL)
    {
        printf("%d ", currPtr -> data);
        prevPtr = currPtr;
        currPtr = nextPtr;
        if (currPtr != NULL) nextPtr = (XNode*)((uintptr_t)prevPtr ^ (uintptr_t)(currPtr -> XOR));
    }
    
    printf("\n");
}

void traverseBackward(XLL *l)
{
    if (l -> last == NULL) return;
    
    XNode *prevPtr = NULL;
    XNode *currPtr = l -> last;
    XNode *nextPtr = l -> last -> XOR;
    
    while (currPtr != NULL)
    {
        printf("%d ", currPtr -> data);
        prevPtr = currPtr;
        currPtr = nextPtr;
        if (currPtr != NULL) nextPtr = (XNode*)((uintptr_t)prevPtr ^ (uintptr_t)(currPtr -> XOR));
    }
    
    printf("\n");
}


int main()
{
    XLL *xlist = (XLL*)malloc(sizeof(XLL));
    
    initialize(xlist);
    
    XNode *A = addAfter(xlist, NULL, 1);
    
    traverseForward(xlist);
    
    XNode *B = addAfter(xlist, A, 5);
    
    traverseForward(xlist);
    
    XNode *C = addBefore(xlist, A, 3);
    
    traverseForward(xlist);
    traverseBackward(xlist);
    
    delete(xlist, A);
    
    traverseForward(xlist);
    traverseBackward(xlist);
    
    return 0;
}
