/*
 Petar 'PetarV' Velickovic
 Algorithm: Binary Search
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

int n, x;
int niz[MAX_N];

//Binarna pretraga elementa u sortiranom nizu
//Slozenost: O(log n)

inline int b_search(int left, int right, int x)
{
    int i = left;
    int j = right;
    while (i < j)
    {
        int mid = (i+j)/2;
        if (niz[mid] == x) return mid;
        if (niz[mid] < x) i = mid+1;
        else j = mid-1;
    }
    if (niz[i] == x) return i;
    return -1;
}

int main()
{
    n = 5, x = 4;
    niz[0] = 1;
    niz[1] = 2;
    niz[2] = 3;
    niz[3] = 4;
    niz[4] = 5;
    printf("%d\n",b_search(0, n-1, x));
    return 0;
}
