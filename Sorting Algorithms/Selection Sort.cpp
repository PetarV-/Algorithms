/*
 Petar 'PetarV' Velickovic
 Algorithm: Selection Sort
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
#define MAX_N 5001
using namespace std;
typedef long long lld;

int n;
int niz[MAX_N];

//Selection sort algoritam za sortiranje niza
//Slozenost: O(n^2)

inline void selectionSort()
{
    for (int i=0;i<n-1;i++)
    {
        int minPos = i;
        for (int j=i+1;j<n;j++)
        {
            if (niz[j] < niz[minPos])
            {
               minPos = j;
            }
        }
        swap(niz[i], niz[minPos]);
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
    selectionSort();
    for (int i=0;i<n;i++) printf("%d ",niz[i]);
    printf("\n");
    return 0;
}
