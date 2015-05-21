/*
 Petar 'PetarV' Velickovic
 Algorithm: Kosaraju's Algorithm
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

#define MAX_N 20001

typedef long long lld;
typedef unsigned long long llu;
using namespace std;

/*
 Kosaraju's algorithm aims to find all strongly connected components (SCCs) of
 a given input graph. It does so using two depth-first searches, and as such is
 less efficient than Tarjan's SCC algorithm, but is more intuitive.
 
 Complexity:    O(V + E)
*/

int n, m;
struct Node
{
    vector<int> adj;
    vector<int> rev_adj;
};
Node graf[MAX_N];

stack<int> S;
bool visited[MAX_N];

int component[MAX_N];
vector<int> components[MAX_N];
int numComponents;

void kosaraju_dfs_1(int x)
{
    visited[x] = true;
    for (int i=0;i<graf[x].adj.size();i++)
    {
        if (!visited[graf[x].adj[i]]) kosaraju_dfs_1(graf[x].adj[i]);
    }
    S.push(x);
}

void kosaraju_dfs_2(int x)
{
    printf("%d ", x);
    component[x] = numComponents;
    components[numComponents].push_back(x);
    visited[x] = true;
    for (int i=0;i<graf[x].rev_adj.size();i++)
    {
        if (!visited[graf[x].rev_adj[i]]) kosaraju_dfs_2(graf[x].rev_adj[i]);
    }
}

void Kosaraju()
{
    for (int i=0;i<n;i++)
    {
        if (!visited[i]) kosaraju_dfs_1(i);
    }
    
    for (int i=0;i<n;i++)
    {
        visited[i] = false;
    }
    
    while (!S.empty())
    {
        int v = S.top(); S.pop();
        if (!visited[v])
        {
            printf("Component %d: ", numComponents);
            kosaraju_dfs_2(v);
            numComponents++;
            printf("\n");
        }
    }
}

int main()
{
    n = 8, m = 14;
    graf[0].adj.push_back(1);
    graf[1].adj.push_back(2);
    graf[1].adj.push_back(4);
    graf[1].adj.push_back(5);
    graf[2].adj.push_back(3);
    graf[2].adj.push_back(6);
    graf[3].adj.push_back(2);
    graf[3].adj.push_back(7);
    graf[4].adj.push_back(5);
    graf[5].adj.push_back(6);
    graf[6].adj.push_back(5);
    graf[7].adj.push_back(3);
    graf[7].adj.push_back(6);
    
    // making the reverse graph immediately
    graf[1].rev_adj.push_back(0);
    graf[2].rev_adj.push_back(1);
    graf[4].rev_adj.push_back(1);
    graf[5].rev_adj.push_back(1);
    graf[3].rev_adj.push_back(2);
    graf[6].rev_adj.push_back(2);
    graf[2].rev_adj.push_back(3);
    graf[7].rev_adj.push_back(3);
    graf[5].rev_adj.push_back(4);
    graf[6].rev_adj.push_back(5);
    graf[5].rev_adj.push_back(6);
    graf[3].rev_adj.push_back(7);
    graf[6].rev_adj.push_back(7);
    
    Kosaraju();
    
    printf("Total number of components: %d\n", numComponents);
    
    return 0;
}
