/*
 Petar 'PetarV' Velickovic
 Algorithm: First-Fit Bin Packing
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

#define MID (left+right)/2
#define MAX_N 1000001
#define MAX_TREE (MAX_N << 2)

typedef long long lld;
typedef unsigned long long llu;
using namespace std;

/*
 The bin packing problem attempts to put n items of sizes 0 < s_i < 1 into bins of capacity 1.
 The first-fit algorithm utilises a greedy approach to the problem: it works by placing each 
 item into the first bin it encounters that has enough free space (potentially creating a new
 bin if necessary). This implementation takes advantage of a segment tree data structure to
 quickly locate the first fit (assuming we know the number of items, n, in advance).

 Complexity:    O(n log n) time
                O(n)       space
 
 Approximation ratio: 2
*/

// the number of items to distribute
int n;
// the segment tree; it is an "almost complete" binary tree
// and hence may be represented by an array
double ST[MAX_TREE];

// We have inserted an item of size val into the x-th bin
// Toplevel call: Update(1, x, val, 1, n)
void Update(int idx, int x, double val, int left, int right)
{
    if (left == right)
    {
        // leaf node, left == right == x
        ST[idx] += val;
        return;
    }

    // check which subtree the x-th bin belongs to and recurse
    if (x <= MID) Update(2*idx, x, val, left, MID);
    else Update(2*idx+1, x, val, MID+1, right);
    
    // store the new minimum fill level of the current (sub)tree
    ST[idx] = min(ST[2*idx], ST[2*idx+1]);
}

// Determine the first fit bin for a given value
// Toplevel call: Query(1, val, 1, n)
int Query(int idx, double val, int left, int right)
{
    if (left == right)
    {
        // leaf node: we have found the first-fit bin!
        return left;
    }
    // check whether the left subtree contains a fitting bin
    if (ST[2*idx] <= 1.0 - val) return Query(2*idx, val, left, MID);
    else return Query(2*idx+1, val, MID+1, right);
}

// Fit an item of size val
inline void FirstFit(double val)
{
    int first_fit = Query(1, val, 1, n);
    Update(1, first_fit, val, 1, n);
    printf("Placed item of value %lf in bin ID %d!\n", val, first_fit);
}

int main()
{
    scanf("%d", &n);
    for (int i=0;i<n;i++)
    {
        double curr;
        scanf("%lf", &curr);
        FirstFit(curr);
    } 
    return 0;
}

