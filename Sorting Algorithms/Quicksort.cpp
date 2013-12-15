/*
 Petar 'PetarV' Velickovic
 Algorithm: Quicksort
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

//Quicksort algoritam za sortiranje niza
//Slozenost: O(n log n)

void qsort(int left, int right)
{
    if (left < right)
    {
        int i = left;
        int j = right;
        int pivot = niz[(i+j)/2];
        while (i<=j)
        {
            while (niz[i]<pivot) i++;
            while (niz[j]>pivot) j--;
            if (i<=j)
            {
                swap(niz[i], niz[j]);
                i++;
                j--;
            }
        }
        qsort(left,j);
        qsort(i,right);
    }
}

int main()
{
    n = 5;
    niz[0] = 4;
    niz[1] = 2;
    niz[2] = 5;
    niz[3] = 1;
    niz[4] = 3;
    qsort(0, n-1);
    for (int i=0;i<n;i++) printf("%d ",niz[i]);
    printf("\n");
    return 0;
}
