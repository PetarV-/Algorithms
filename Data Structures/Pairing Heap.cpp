/*
 Petar 'PetarV' Velickovic
 Data Structure: Pairing Heap
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
#define INF 987654321
using namespace std;
typedef long long lld;
typedef unsigned long long llu;

/*
 Pairing Heap data structure satisfying the heap property, with highly efficient asymptotic bounds.
 Often outperforming Fibonacci heaps, and simple to implement.
 Complexity:    O(1) for insert, first and merge
 O(log n) amortized for extractMin and delete
 O(log n) amortized for decreaseKey - not known if bound is tight; Omega(log log N).
*/

struct PNode
{
    int key;
    PNode *b, *f, *c;
    
    PNode()
    {
        this -> key = 0;
        this -> b = this -> f = this -> c = NULL;
    }
    
    PNode(int key)
    {
        this -> key = key;
        this -> b = this -> f = this -> c = NULL;
    }
};

class PHeap
{
    PNode *root;
    
public:
    PHeap();
    PHeap(PNode*);
    bool isEmpty();
    void insert(PNode*);
    void merge(PHeap*);
    PNode* first();
    PNode* extractMin();
    void decreaseKey(PNode*, int);
    void Delete(PNode*);
};

PHeap::PHeap()
{
    this -> root = NULL;
}

PHeap::PHeap(PNode *x)
{
    this -> root = x;
    x -> b = x -> f = NULL;
}

bool PHeap::isEmpty()
{
    return (this -> root == NULL);
}

void PHeap::insert(PNode *x)
{
    this -> merge(new PHeap(x));
}

void PHeap::merge(PHeap *ph)
{
    if (ph -> isEmpty()) return;
    
    if (this -> isEmpty())
    {
        this -> root = ph -> root;
        return;
    }
    
    else
    {
        if (this -> root -> key < ph -> root -> key)
        {
            PNode *fC = this -> root -> c;
            this -> root -> c = ph -> root;
            ph -> root -> b = this -> root;
            ph -> root -> f = fC;
            if (fC != NULL) fC -> b = ph -> root;
        }
        else
        {
            PNode *fC = ph -> root -> c;
            ph -> root -> c = this -> root;
            this -> root -> b = ph -> root;
            this -> root -> f = fC;
            if (fC != NULL) fC -> b = this -> root;
            this -> root = ph -> root;
        }
    }
}

PNode* PHeap::first()
{
    return this -> root;
}

PNode* PHeap::extractMin()
{
    PNode *ret = this -> first();
    
    PNode *oldList = ret -> c;
    
    if (oldList == NULL)
    {
        this -> root = NULL;
        return ret;
    }
    
    queue<PHeap*> heapFIFO;
    stack<PHeap*> heapLIFO;
    
    while (oldList != NULL)
    {
        PNode *next = oldList -> f;
        heapFIFO.push(new PHeap(oldList));
        oldList = next;
    }
    
    while (!heapFIFO.empty())
    {
        PHeap *t1 = heapFIFO.front();
        heapFIFO.pop();
        if (!heapFIFO.empty())
        {
            PHeap *t2 = heapFIFO.front();
            heapFIFO.pop();
            t1 -> merge(t2);
        }
        heapLIFO.push(t1);
    }
    
    while (heapLIFO.size() > 1)
    {
        PHeap *x = heapLIFO.top();
        heapLIFO.pop();
        PHeap *y = heapLIFO.top();
        heapLIFO.pop();
        x -> merge(y);
        heapLIFO.push(x);
    }
    
    this -> root = heapLIFO.top() -> root;
    
    return ret;
}

void PHeap::decreaseKey(PNode *x, int newKey)
{
    x -> key = newKey;
    
    if (this -> root == x) return;
    
    if (x -> b -> c == x)
    {
        x -> b -> c = x -> f;
        if (x -> f != NULL) x -> f -> b = x -> b;
    }
    else
    {
        x -> b -> f = x -> f;
        if (x -> f != NULL) x -> f -> b = x -> b;
    }
    
    this -> merge(new PHeap(x));
}

void PHeap::Delete(PNode *x)
{
    if (this -> root == x) extractMin();
    else
    {
        if (x -> b -> c == x)
        {
            x -> b -> c = x -> f;
            if (x -> f != NULL) x -> f -> b = x -> b;
        }
        else
        {
            x -> b -> f = x -> f;
            if (x -> f != NULL) x -> f -> b = x -> b;
        }
        
        PHeap *R = new PHeap(x);
        R -> extractMin();
        this -> merge(R);
    }
}

int main()
{
    PHeap *ph = new PHeap();
    
    PNode *x = new PNode(11);
    PNode *y = new PNode(5);
    
    ph -> insert(x);
    ph -> insert(y);
    ph -> insert(new PNode(3));
    ph -> insert(new PNode(8));
    ph -> insert(new PNode(4));
    
    ph -> decreaseKey(x, 2);
    ph -> Delete(y);
    
    while (!ph -> isEmpty())
    {
        printf("%d ", ph -> extractMin() -> key);
    }
    
    printf("\n");
    return 0;
}

