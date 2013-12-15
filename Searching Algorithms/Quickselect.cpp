/*
 Petar 'PetarV' Velickovic
 Algorithm: Quickselect
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

int n, k;
int niz[MAX_N];

//Quickselect algoritam za nalazenje k-tog elementa u nizu
//Slozenost: O(n)

int qselect(int left, int right, int k)
{
    if (left < right)
    {
        int pivotIndex = left;
        int pivot = niz[(left+right)/2];
        swap(niz[(left+right)/2], niz[right]);
        for (int i=left;i<right;i++)
        {
            if (niz[i] < pivot)
            {
                swap(niz[pivotIndex], niz[i]);
                pivotIndex++;
            }
        }
        swap(niz[pivotIndex], niz[right]);
        if (pivotIndex == k) return niz[pivotIndex];
        else if (k < pivotIndex) return qselect(left, pivotIndex-1, k);
        else return qselect(pivotIndex+1, right, k);
    }
    else return niz[left];
}

int main()
{
    n = 5, k = 3;
    niz[0] = 4;
    niz[1] = 2;
    niz[2] = 5;
    niz[3] = 1;
    niz[4] = 3;
    printf("%d\n",qselect(0, n-1, k));
    return 0;
}
