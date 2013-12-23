/*
 Petar 'PetarV' Velickovic
 Data Structure: Fibonacci Heap
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
 Fibonacci Heap data structure satisfying the heap property, with highly efficient asymptotic bounds.
 Useful for a priority queue implementation in Dijkstra's and Prim's algorithms.
 Complexity:    O(1) for insert, first and merge
                O(1) amortized for decreaseKey
                O(log N) amortized for extractMin and delete
*/

struct FibNode
{
    int key;
    bool marked;
    int degree;
    FibNode *b, *f, *p, *c;
    
    FibNode()
    {
        this -> key = 0;
        this -> marked = false;
        this -> degree = 0;
        this -> b = this -> f = this -> p = this -> c = NULL;
    }
    
    FibNode(int key)
    {
        this -> key = key;
        this -> marked = false;
        this -> degree = 0;
        this -> b = this -> f = this -> p = this -> c = NULL;
    }
};

class FibHeap
{
    FibNode *min;
    int N;
    
public:
    FibHeap();
    FibHeap(FibNode*);
    bool isEmpty();
    void insert(FibNode*);
    void merge(FibHeap*);
    FibNode* first();
    FibNode* extractMin();
    void decreaseKey(FibNode*, int);
    void Delete(FibNode*);
};

FibHeap::FibHeap()
{
    this -> min = NULL;
    this -> N = 0;
}

FibHeap::FibHeap(FibNode *n)
{
    this -> min = n;
    n -> b = n -> f = n;
    n -> p = n -> c = NULL;
    
    this -> N = 1;
}

bool FibHeap::isEmpty()
{
    return (this -> min == NULL);
}

void FibHeap::insert(FibNode *n)
{
    this -> merge(new FibHeap(n));
}

void FibHeap::merge(FibHeap *h)
{
    this -> N += h -> N;
    if (h -> isEmpty()) return;
    if (this -> isEmpty())
    {
        this -> min = h -> min;
        return;
    }
    FibNode *first1 = this -> min;
    FibNode *last1 = this -> min -> b;
    FibNode *first2 = h -> min;
    FibNode *last2 = h -> min -> b;
    first1 -> b = last2;
    last1 -> f = first2;
    first2 -> b = last1;
    last2 -> f = first1;
    if (h -> min -> key < this -> min -> key) this -> min = h -> min;
}

FibNode* FibHeap::first()
{
    return this -> min;
}

FibNode* FibHeap::extractMin()
{
    FibNode *ret = this -> min;
    this -> N = this -> N - 1;
    
    if (ret -> f == ret)
    {
        this -> min = NULL;
    }
    else
    {
        FibNode *prev = ret -> b;
        FibNode *next = ret -> f;
        prev -> f = next;
        next -> b = prev;
        this -> min = next; // Not necessarily a minimum. This is for assisting with the merge w/ min's children.
    }
    
    if (ret -> c != NULL)
    {
        FibNode *firstChd = ret -> c;
        FibNode *currChd = firstChd;
        
        do
        {
            currChd -> p = NULL;
            currChd = currChd -> f;
        } while (currChd != firstChd);
        
        if (this -> isEmpty())
        {
            this -> min = firstChd;
        }
        else
        {
            FibNode *first1 = this -> min;
            FibNode *last1 = this -> min -> b;
            FibNode *first2 = firstChd;
            FibNode *last2 = firstChd -> b;
            first1 -> b = last2;
            last1 -> f = first2;
            first2 -> b = last1;
            last2 -> f = first1;
        }
    }
    
    if (this -> min != NULL)
    {
        int maxAuxSize = 5 * (((int)log2(this -> N + 1)) + 1);
        FibNode *aux[maxAuxSize + 1];
        for (int i=0;i<=maxAuxSize;i++) aux[i] = NULL;
        int maxDegree = 0;
        
        FibNode *curr = this -> min;
        
        do
        {
            FibNode *next = curr -> f;
            int deg = curr -> degree;
            FibNode *P = curr;
            while (aux[deg] != NULL)
            {
                FibNode *Q = aux[deg];
                aux[deg] = NULL;
                
                if (P -> key > Q -> key)
                {
                    FibNode *tmp = P;
                    P = Q;
                    Q = tmp;
                }
                
                Q -> p = P;
                if (P -> c == NULL)
                {
                    P -> c = Q;
                    Q -> b = Q -> f = Q;
                }
                else
                {
                    FibNode *last = P -> c -> b;
                    last -> f = Q;
                    Q -> b = last;
                    P -> c -> b = Q;
                    Q -> f = P -> c;
                }
                
                deg++;
                P -> degree = deg;
            }
            aux[deg] = P;
            if (deg > maxDegree) maxDegree = deg;
            curr = next;
        } while (curr != this -> min);
        
        
        FibNode *previous = aux[maxDegree];
        this -> min = previous;
        for (int i=0;i<=maxDegree;i++)
        {
            if (aux[i] != NULL)
            {
                previous -> f = aux[i];
                aux[i] -> b = previous;
                if (aux[i] -> key < this -> min -> key) this -> min = aux[i];
                previous = aux[i];
            }
        }
        
    }
    
    return ret;
}

void FibHeap::decreaseKey(FibNode *n, int newKey)
{
    // Precondition: newKey < n -> key
    n -> key = newKey;
    
    FibNode *curr = n;
    if (curr -> p != NULL)
    {
        if (curr -> key < curr -> p -> key)
        {
            FibNode *parent = curr -> p;
            curr -> marked = false;
            
            curr -> p = NULL;
            if (curr -> f == curr) parent -> c = NULL;
            else
            {
                FibNode *prev = curr -> b;
                FibNode *next = curr -> f;
                prev -> f = next;
                next -> b = prev;
                if (parent -> c == curr) parent -> c = prev;
            }
            parent -> degree = parent -> degree - 1;
            
            FibNode *last = this -> min -> b;
            last -> f = curr;
            curr -> b = last;
            this -> min -> b = curr;
            curr -> f = this -> min;
            
            if (curr -> key < this -> min -> key) this -> min = curr;
            
            while (parent -> p != NULL && parent -> marked)
            {
                curr = parent;
                parent = curr -> p;
                curr -> marked = false;
                
                curr -> p = NULL;
                if (curr -> f == curr) parent -> c = NULL;
                else
                {
                    FibNode *prev = curr -> b;
                    FibNode *next = curr -> f;
                    prev -> f = next;
                    next -> b = prev;
                    if (parent -> c == curr) parent -> c = prev;
                }
                parent -> degree = parent -> degree - 1;
                
                FibNode *last = this -> min -> b;
                last -> f = curr;
                curr -> b = last;
                this -> min -> b = curr;
                curr -> f = this -> min;
                
            }
            if (parent -> p != NULL) parent -> marked = true;
        }
    }
    else if (n -> key < this -> min -> key) this -> min = n;
}

void FibHeap::Delete(FibNode *n)
{
    this -> decreaseKey(n, -INF);
    this -> extractMin();
}

int main()
{
    FibHeap *fh = new FibHeap();
    
    FibNode *x = new FibNode(11);
    FibNode *y = new FibNode(5);
    
    fh -> insert(x);
    fh -> insert(y);
    fh -> insert(new FibNode(3));
    fh -> insert(new FibNode(8));
    fh -> insert(new FibNode(4));
    
    fh -> decreaseKey(x, 2);
    fh -> Delete(y);
    
    while (!fh -> isEmpty())
    {
        printf("%d ", fh -> extractMin() -> key);
    }
    printf("\n");
    return 0;
}

