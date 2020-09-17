/*
 Petar 'PetarV' Velickovic
 Algorithm: K-Combinations
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
using namespace std;
typedef long long lld;

int n, k;
int skup[100];
bool inSet[100];

//Program koji generise sve kombinacije od po K elemenata datog skupa
//Slozenost: O((n choose k))

void kCombinations(int pos, int amt)
{
    if (n-pos<k-amt) return;
    if (amt==k)
    {
        for (int i=0;i<n;i++) if (inSet[i]) printf("%d ",skup[i]);
        printf("\n");
        return;
    }
    inSet[pos] = true;
    kCombinations(pos+1,amt+1);
    inSet[pos] = false;
    kCombinations(pos+1,amt);
}

int main()
{
    n = 5, k = 2;
    skup[0] = 1;
    skup[1] = 2;
    skup[2] = 3;
    skup[3] = 4;
    skup[4] = 5;
    kCombinations(0, 0);
    return 0;
}
