/*
 Petar 'PetarV' Velickovic
 Algorithm: Kruskal's Algorithm
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
#define MAX_N 100001
using namespace std;
typedef long long lld;

int n, m;
int numComponents, ret;

struct Edge
{
    int a, b;
    int weight;
    bool operator <(const Edge &e) const
    {
        return (weight < e.weight);
    }
};
Edge E[MAX_N];

struct Node
{
    int parent;
    int rank;
};
Node DSU[MAX_N];

//Kruskalov algoritam za racunanje minimalnog stabla razapinjanja datog tezinskog grafa
//Slozenost: O(E log V)

inline void MakeSet(int x)
{
    DSU[x].parent = x;
    DSU[x].rank = 0;
}

inline int Find(int x)
{
    if (DSU[x].parent == x) return x;
    DSU[x].parent = Find(DSU[x].parent);
    return DSU[x].parent;
}

inline void Union(int x, int y)
{
    int xRoot = Find(x);
    int yRoot = Find(y);
    if (xRoot == yRoot) return;
    if (DSU[xRoot].rank < DSU[yRoot].rank)
    {
        DSU[xRoot].parent = yRoot;
    }
    else if (DSU[xRoot].rank > DSU[yRoot].rank)
    {
        DSU[yRoot].parent = xRoot;
    }
    else
    {
        DSU[yRoot].parent = xRoot;
        DSU[xRoot].rank++;
    }
}

inline int Kruskal()
{
    int ret = 0, numComponents = n;
    for (int i=0;i<n;i++) MakeSet(i);
    sort(E, E+m);
    for (int i=0;i < m && numComponents > 1;i++)
    {
        if (Find(E[i].a) != Find(E[i].b))
        {
            Union(E[i].a, E[i].b);
            ret += E[i].weight;
            numComponents--;
        }
    }
    if (numComponents > 1) return -1;
    return ret;
}

int main()
{
    n = 7, m = 11;
    
    E[0].a = 0, E[0].b = 1, E[0].weight = 7;
    E[1].a = 0, E[1].b = 3, E[1].weight = 5;
    E[2].a = 1, E[2].b = 2, E[2].weight = 8;
    E[3].a = 1, E[3].b = 3, E[3].weight = 9;
    E[4].a = 1, E[4].b = 4, E[4].weight = 7;
    E[5].a = 2, E[5].b = 4, E[5].weight = 5;
    E[6].a = 3, E[6].b = 4, E[6].weight = 15;
    E[7].a = 3, E[7].b = 5, E[7].weight = 6;
    E[8].a = 4, E[8].b = 5, E[8].weight = 8;
    E[9].a = 4, E[9].b = 6, E[9].weight = 9;
    E[10].a = 5, E[10].b = 6, E[10].weight = 11;
    
    printf("%d\n",Kruskal());
    
    return 0;
}
