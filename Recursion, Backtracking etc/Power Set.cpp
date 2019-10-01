/*
 Petar 'PetarV' Velickovic
 Algorithm: Power Set
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

//Metoda koja generise partitivni skup nekog skupa
//Slozenost: O(2^n)

int n;
int skup[100];
bool inSet[100];

void powerSet(int pos)
{
    if (pos==n)
    {
        for (int i=0;i<n;i++) if (inSet[i]) printf("%d ",skup[i]);
        printf("\n");
        return;
    }
    inSet[pos] = false;
    powerSet(pos+1);
    inSet[pos] = true;
    powerSet(pos+1);
}

int main()
{
    n = 3;
    skup[0] = 1;
    skup[1] = 2;
    skup[2] = 3;
    powerSet(0);
    return 0;
}
