/*
 Petar 'PetarV' Velickovic
 Algorithm: Bitonic Sorter
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>
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

typedef long long lld;
typedef unsigned long long llu;
using namespace std;

/*
 The Bitonic Sorter is an algorithm for sorting an array of keys.
 
 While not very efficient in serial form, it can be used to construct
 an efficient parallel sorting algorithm (asymptotically slower than
 the AKS algorithm, but in practice faster due to constant factors).
 
 Complexity:    O(n log^2 n) serial
                O(log^2 n)   parallel
*/

// Comparator between values a and b
void compare(int &a, int &b)
{
    if (a > b) swap(a, b);
}

// Sorts a bitonic sequence A[lo..hi]
void BitonicSorter(int *A, int lo, int hi)
{
    if (lo == hi) return;
    int len = (hi - lo + 1) >> 1;
    int mid = (hi + lo) >> 1;
    // first pass: half-cleaner
    for (int i=0;i<len;i++) compare(A[lo+i], A[lo+len+i]);
    // second pass: recursively sort
    BitonicSorter(A, lo, mid);
    BitonicSorter(A, mid+1, hi);
}

// Merges two sorted sequences, A[lo..mid], A[mid+1..hi]
void Merger(int *A, int lo, int mid, int hi)
{
    int len = (hi - lo + 1) >> 1;
    // first half of merger: give two bitonic sequences
    for (int i=0;i<len;i++) compare(A[lo+i], A[hi-i]);
    // second half of merger: bitonically sort the two halves
    BitonicSorter(A, lo, mid);
    BitonicSorter(A, mid+1, hi);
}

// Precondition: |A| must be a power of 2
void Sorter(int *A, int lo, int hi)
{
    if (lo == hi) return;
    int mid = (lo + hi) >> 1;
    Sorter(A, lo, mid);
    Sorter(A, mid+1, hi);
    Merger(A, lo, mid, hi);
}

int main()
{
    int *x = new int[8];
    x[0] = 10; x[1] = 30; x[2] = 11; x[3] = 20;
    x[4] = 4; x[5] = 330; x[6] = 21; x[7] = 110;
    
    Sorter(x, 0, 7);
    
    for (int i=0;i<8;i++) printf("%d ", x[i]);
    printf("\n");
    
    return 0;
}
