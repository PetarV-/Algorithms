/*
 Petar 'PetarV' Velickovic
 Data Structure: Suffix Array + LCP Array
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
#define MAX_N 90001
using namespace std;
typedef long long lld;

int n, t;
string s;
int SA[MAX_N], LCP[MAX_N];
int tmp[MAX_N], poz[MAX_N];

//Algoritam koji generise sufiksni niz i niz najdužeg zajedničkog prefiksa (LCP) nad datim stringom
//Slozenost: O(n log^2 n) za sufiksni niz, O(n) za LCP niz

inline bool suff_compare(int i, int j)
{
    if (poz[i] != poz[j]) return (poz[i] < poz[j]);
    i += t;
    j += t;
    if (i < n && j < n) return (poz[i] < poz[j]);
    else return (i > j);
}

inline void buildSA()
{
    for (int i=0;i<n;i++)
    {
        SA[i] = i;
        poz[i] = s[i];
    }
    for (t = 1 ; t < 2*n+1; t *= 2)
    {
        sort(SA, SA + n, suff_compare);
        for (int i=0;i<n-1;i++)
        {
            tmp[i+1] = tmp[i];
            if (suff_compare(SA[i],SA[i+1])) tmp[i+1]++;
        }
        for (int i=0;i<n;i++)
        {
            poz[SA[i]] = tmp[i];
        }
        if (tmp[n-1] == n-1) break;
    }
}

inline void buildLCP()
{
    int k = 0;
    for (int i=0;i<n;i++)
    {
        if (poz[i] != n-1)
        {
            int j = SA[poz[i]+1];
            while (s[i+k] == s[j+k]) k++;
            LCP[poz[i]] = k;
            if (k > 0) k--;
        }
    }
}

int main()
{
    n = 6;
    s = "banana";
    
    buildSA();
    buildLCP();
    
    for (int i=0;i<n;i++) printf("%d ",SA[i]);
    printf("\n");
    for (int i=0;i<n;i++) printf("%d ",LCP[i]);
    printf("\n");
    
    return 0;
}
