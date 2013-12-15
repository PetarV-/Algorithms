/*
 Petar 'PetarV' Velickovic
 Algorithm: Knuth-Morris-Pratt
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

int n, m;
string needle, haystack;
int P[MAX_N];
vector<int> matches;

//Knuth-Morris-Pratt algoritam za string matching
//Slozenost: O(N + M)

inline void KMP()
{
    for (int i=0;i<m;i++) P[i] = -1;
    for (int i=0, j=-1;i<m;)
    {
        while (j > -1 && needle[i] != needle[j]) j = P[j];
        i++;
        j++;
        P[i] = j;
    }
    for (int i=0, j=0;i<n;)
    {
        while (j > -1 && haystack[i] != needle[j]) j = P[j];
        i++;
        j++;
        if (j == m)
        {
            matches.push_back(i - m);
            j = P[j];
        }
    }
}

int main()
{
    n = 6, m = 2;
    haystack = "abcabc";
    needle = "bc";
    KMP();
    for (int i=0;i<matches.size();i++) printf("%d ",matches[i]);
    printf("\n");
    return 0;
}
