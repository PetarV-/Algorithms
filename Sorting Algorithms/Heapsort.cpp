/*
 Petar 'PetarV' Velickovic
 Algorithm: Heapsort
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
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
#define MAX_N 1000001
using namespace std;
typedef long long lld;

int n;
int niz[MAX_N];

int heap_size;

//Heapsort algoritam za sortiranje niza
//Slozenost: O(n log n)

inline void Heapify(int pos)
{
    if (pos > heap_size) return;
    int ret = pos;
    int left = pos*2;
    int right = pos*2+1;
    if (left <= heap_size && niz[left] > niz[ret]) ret = left;
    if (right <= heap_size && niz[right] > niz[ret]) ret = right;
    if (ret != pos)
    {
        swap(niz[pos], niz[ret]);
        Heapify(ret);
    }
}

inline void Pop()
{
    int pos = 1;
    swap(niz[pos], niz[heap_size--]);
    while (pos <= heap_size)
    {
        int ret = pos;
        int left = pos*2;
        int right = pos*2+1;
        if (left <= heap_size && niz[left] > niz[ret]) ret = left;
        if (right <= heap_size && niz[right] > niz[ret]) ret = right;
        if (ret != pos)
        {
            swap(niz[pos], niz[ret]);
            pos = ret;
        }
        else break;
    }
}

int main()
{
    n = 5;
    niz[1] = 4;
    niz[2] = 2;
    niz[3] = 5;
    niz[4] = 1;
    niz[5] = 3;
    
    heap_size = n;
    
    for (int i=n/2;i>=1;i--) Heapify(i);
    while (heap_size > 1) Pop();
    
    for (int i=1;i<=n;i++) printf("%d ",niz[i]);
    printf("\n");
    
    return 0;
}
