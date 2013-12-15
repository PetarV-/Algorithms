/*
 Petar 'PetarV' Velickovic
 Algorithm: Merge Sort
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
int niz[MAX_N], tmp[MAX_N];

//Merge sort algoritam za sortiranje niza
//Slozenost: O(n log n)

inline void merge(int left, int mid, int right)
{
    int h,i,j,k;
    h = left;
    i = left;
    j = mid+1;
    while (h <= mid && j <= right)
    {
        if (niz[h] <= niz[j])
        {
            tmp[i] = niz[h];
            h++;
        }
        else
        {
            tmp[i] = niz[j];
            j++;
        }
        i++;
    }
    if (h > mid)
    {
        for(k=j;k<=right;k++)
        {
            tmp[i] = niz[k];
            i++;
        }    
    }
    else
    {
        for(k=h;k<=mid;k++)
        {
            tmp[i] = niz[k];
            i++;
        }
    }
    for(k=left;k<=right;k++) niz[k] = tmp[k];
}

void mergeSort(int left, int right)
{
    if (left == right) return;
    int MID = (left+right)/2;
    mergeSort(left, MID);
    mergeSort(MID+1, right);
    merge(left, MID, right);
}

int main()
{
    n = 5;
    niz[0] = 4;
    niz[1] = 2;
    niz[2] = 5;
    niz[3] = 1;
    niz[4] = 3;
    mergeSort(0, n-1);
    for (int i=0;i<n;i++) printf("%d ",niz[i]);
    printf("\n");
    return 0;
}
