/*
 Petar 'PetarV' Velickovic
 Data Structure: Circular Doubly Linked List (Microchallenge)
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <complex>
using namespace std;
typedef long long lld;

/*
 An implementation of a Circular Doubly Linked List data structure.
 Used as an underlying data structure in the Fibonacci Heap implementation.
 Complexity:    O(1) for: isEmpty, insert, getMinimum, decreaseKey and merge.
                O(N) for: extractMinimum and Delete (if we're deleting the minimum).
*/

class Node
{
public:
    int key;
    
    Node *left;
    Node *right;
    
    Node();
    Node(int key);
};

class CircularDoublyLinkedList
{
public:
    Node *first;
    Node *minimum;
    
    CircularDoublyLinkedList();
    
    bool isEmpty();
    void insert(Node *x);
    Node *getMinimum();
    Node *extractMinimum();
    void decreaseKey(Node *x, int newKey);
    void Delete(Node *x);
    void merge(CircularDoublyLinkedList *cdll);
    
    void print();
};

Node::Node()
{
    this -> key = 0;
    this -> left = NULL;
    this -> right = NULL;
}

Node::Node(int key)
{
    this -> key = key;
    this -> left = NULL;
    this -> right = NULL;
}

CircularDoublyLinkedList::CircularDoublyLinkedList()
{
    this -> first = NULL;
    this -> minimum = NULL;
}

bool CircularDoublyLinkedList::isEmpty()
{
    return (this -> first == NULL);
}

void CircularDoublyLinkedList::insert(Node *x)
{
    if (isEmpty())
    {
        this -> first = x;
        this -> minimum = x;
        x -> left = x;
        x -> right = x;
    }
    else
    {
        Node *last = this -> first -> left;
        last -> right = x;
        x -> left = last;
        this -> first -> left = x;
        x -> right = this -> first;
        if (x -> key < this -> minimum -> key) this -> minimum = x;
    }
}

Node* CircularDoublyLinkedList::getMinimum()
{
    return this -> minimum;
}

Node* CircularDoublyLinkedList::extractMinimum()
{
    if (isEmpty()) return NULL;
    Node *ret = this -> minimum;
    if (ret -> right == ret)
    {
        this -> first = NULL;
        this -> minimum = NULL;
    }
    else
    {
        Node *prev = ret -> left;
        Node *next = ret -> right;
        prev -> right = next;
        next -> left = prev;
        if (ret == this -> first)
        {
            this -> first = next;
        }
        this -> minimum = this -> first;
        Node *curr = this -> first -> right;
        while (curr != this -> first)
        {
            if (curr -> key < this -> minimum -> key) this -> minimum = curr;
            curr = curr -> right;
        }
    }
    return ret;
}

void CircularDoublyLinkedList::decreaseKey(Node *x, int newKey)
{
    x -> key = newKey;
    if (x -> key < this -> minimum -> key) this -> minimum = x;
}

void CircularDoublyLinkedList::Delete(Node *x)
{
    if (this -> minimum == x) extractMinimum();
    else
    {
        Node *prev = x -> left;
        Node *next = x -> right;
        prev -> right = next;
        next -> left = prev;
        if (x == this -> first)
        {
            this -> first = next;
        }
    }
}

void CircularDoublyLinkedList::merge(CircularDoublyLinkedList *cdll)
{
    /*
     Merging works by "clipping" the list to be merged before the first pointer
     and then inserting that entire list before the first pointer in the original list.
     
     For example, if our lists were A <-> B <-> C <-> A and D <-> E <-> D
     The merged list would look something like A <-> B <-> C <-> D <-> E <-> A
    */
    
    if (cdll -> isEmpty()) return;
    if (this -> isEmpty())
    {
        this -> first = cdll -> first;
        this -> minimum = cdll -> minimum;
        return;
    }
    Node *first1 = this -> first;
    Node *last1 = this -> first -> left;
    Node *first2 = cdll -> first;
    Node *last2 = cdll -> first -> left;
    first1 -> left = last2;
    last1 -> right = first2;
    first2 -> left = last1;
    last2 -> right = first1;
    if (cdll -> minimum -> key < this -> minimum -> key) this -> minimum = cdll -> minimum;
}

void CircularDoublyLinkedList::print()
{
    if (isEmpty()) { printf("\n"); return; }
    else
    {
        if (this -> first == this -> minimum) printf("*%d*", this -> first -> key);
        else printf("%d", this -> first -> key);
        Node *curr = this -> first;
        do
        {
            curr = curr -> right;
            if (this -> minimum == curr) printf(" <-> *%d*", curr -> key);
            else printf(" <-> %d", curr -> key);
        } while (curr != this -> first);
        printf("\n");
    }
}

int main()
{
    char response[55];
    
    printf("Do you want to write the results to file? (Y/N)\n");
    while (true)
    {
        scanf("%s", response);
        if (response[0] == 'Y' || response[0] == 'y') break;
        else if (response[0] == 'N' || response[0] == 'n') break;
        printf("Incorrect character! You must input 'Y' or 'N'. Retry: \n");
    }
    
    if (response[0] == 'Y' || response[0] == 'y')
    {
        freopen("/Users/PetarV/TestLogs/CDLL-Test.txt","w",stdout);
    }
    
    time_t t = time(0);
    struct tm *now = localtime(&t);
    
    printf("CDLL Microchallenge testing protocol started.\n");
    printf("Testing carried out on %d-%d-%d, by Petar Velickovic.", now -> tm_year + 1900, now -> tm_mon + 1, now -> tm_mday);
    printf("\n---------------------------------------------------------------\n");
    
    printf("Creating an empty CDLL.\n");
    CircularDoublyLinkedList *CDLL = new CircularDoublyLinkedList();
    printf("CDLL Contains:\n");
    CDLL -> print();
    printf("---------------------------------------------------------------\n");
    
    printf("Creating two nodes, X(7) and Y(4).\n");
    Node *X = new Node(7);
    Node *Y = new Node(4);
    
    printf("Inserting an anonymous node, with key 3.\n");
    CDLL -> insert(new Node(3));
    printf("CDLL Contains:\n");
    CDLL -> print();
    printf("---------------------------------------------------------------\n");
    
    printf("Inserting X(7).\n");
    CDLL -> insert(X);
    printf("CDLL Contains:\n");
    CDLL -> print();
    printf("---------------------------------------------------------------\n");

    printf("Inserting an anonymous node, with key 2.\n");
    CDLL -> insert(new Node(2));
    printf("CDLL Contains:\n");
    CDLL -> print();
    printf("---------------------------------------------------------------\n");
    
    printf("Inserting Y(4).\n");
    CDLL -> insert(Y);
    printf("CDLL Contains:\n");
    CDLL -> print();
    printf("---------------------------------------------------------------\n");
    
    printf("Decreasing the key of X(7) to -1.\n");
    CDLL -> decreaseKey(X, -1);
    printf("CDLL Contains:\n");
    CDLL -> print();
    printf("---------------------------------------------------------------\n");
    
    printf("Extracting the minimum.\n");
    Node *M = CDLL -> extractMinimum();
    printf("The minimum key is: %d.\n", M -> key);
    printf("CDLL Contains:\n");
    CDLL -> print();
    printf("---------------------------------------------------------------\n");
    
    printf("Deleting Y(4).\n");
    CDLL -> Delete(Y);
    printf("CDLL Contains:\n");
    CDLL -> print();
    printf("---------------------------------------------------------------\n");
    
    printf("Merging with a CDLL containing 1 <-> 2 <-> 3 <-> 4 <-> 1.\n");
    CircularDoublyLinkedList *toMerge = new CircularDoublyLinkedList();
    toMerge -> insert(new Node(1));
    toMerge -> insert(new Node(2));
    toMerge -> insert(new Node(3));
    toMerge -> insert(new Node(4));
    CDLL -> merge(toMerge);
    printf("CDLL Contains:\n");
    CDLL -> print();
    printf("---------------------------------------------------------------\n");
    
    printf("Testing completed.\n");
    return 0;
}
