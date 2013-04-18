/*
 Petar 'PetarV' Velickovic
 Data Structure: Priority Queue (Binary Heap)
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

int PQ[MAX_N];
int heap_size = 0;

//Prioritetni red implementiran kao min-heap
//Slozenost: O(log N) za Push/Pop, O(1) za Empty/GetMinimum

inline bool Empty()
{
    return (heap_size == 0);
}

inline int GetMinimum()
{
    if (Empty()) return -1;
    return PQ[1];
}

inline void Push(int x)
{
    PQ[++heap_size] = x;
    int pos = heap_size;
    while (pos > 1 && PQ[pos/2] > PQ[pos])
    {
        swap(PQ[pos/2], PQ[pos]);
        pos /= 2;
    }
}

inline void Pop()
{
    if (Empty()) return;
    int pos = 1;
    swap(PQ[pos], PQ[heap_size--]);
    while (pos <= heap_size)
    {
        int ret = pos;
        int left = pos*2;
        int right = pos*2+1;
        if (left <= heap_size && PQ[left] < PQ[ret]) ret = left;
        if (right <= heap_size && PQ[right] < PQ[ret]) ret = right;
        if (ret != pos)
        {
            swap(PQ[pos], PQ[ret]);
            pos = ret;
        }
        else break;
    }
}

int main()
{
    Push(5);
    Push(3);
    Push(8);
    Push(4);
    Push(11);
    while (!Empty())
    {
        printf("%d ",GetMinimum());
        Pop();
    }
    printf("\n");
    return 0;
}
