/*
 Petar 'PetarV' Velickovic
 Algorithm: 0/1 Knapsack
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
//Mozemo uzeti tacno jedan komad od svake vrste predmeta
//Slozenost O(n*K)

inline int Knapsack01()
{
    for (int i=0;i<=capacity;i++) Sol[i] = 0;
    for (int i=0;i<n;i++)
    {
        for (int j=capacity;j>=1;j--)
        {
            if (Weight[i] <= j)
            {
                int x = Sol[j];
                int y = Sol[j-Weight[i]]+Value[i];
                Sol[j] = max(x,y);
            }
        }
    }
    return Sol[capacity];
}

int main()
{
    n = 4, capacity = 6;
    Weight[0] = 1, Value[0] = 4;
    Weight[1] = 2, Value[1] = 6;
    Weight[2] = 3, Value[2] = 12;
    Weight[3] = 2, Value[3] = 7;
    printf("%d\n",Knapsack01());
    return 0;
}
