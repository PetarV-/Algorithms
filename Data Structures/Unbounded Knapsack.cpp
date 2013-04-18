/*
 Petar 'PetarV' Velickovic
 Algorithm: Unbounded Knapsack
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

int n, capacity;
int Weight[101], Value[101], Sol[1001];

//Algoritam za odredjivanje maksimalne vrednosti koja moze stati u ranac datog kapaciteta
//Mozemo uzimati beskonacno od svake vrste predmeta
//Slozenost O(n*K)

inline int Knapsack()
{
    Sol[0] = 0;
    for (int i=1;i<=capacity;i++)
    {
        int maks = 0;
        int tek;
        for (int j=0;j<n;j++)
        {
            if (Weight[j] <= i)
            {
                tek = Value[j] + Sol[i-Weight[j]];
                if (tek > maks) maks = tek;
            }
        }
        Sol[i] = maks;
    }
    return Sol[capacity];
}

int main()
{
    n = 5, capacity = 17;
    Weight[0] = 3, Value[0] = 4;
    Weight[1] = 4, Value[1] = 5;
    Weight[2] = 7, Value[2] = 10;
    Weight[3] = 8, Value[3] = 11;
    Weight[4] = 9, Value[4] = 13;
    printf("%d\n",Knapsack());
    return 0;
}
