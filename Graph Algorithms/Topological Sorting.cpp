/*
 Petar 'PetarV' Velickovic
 Algorithm: Topological Sorting
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

struct Node
{
    vector<int> adj;
};
Node graf[MAX_N];
bool mark[MAX_N];

int indegree[MAX_N];
int toposort[MAX_N];

//Algoritam za topolosko sortiranje usmerenog grafa; moze se koristiti i za otkrivanje ciklusa
//Slozenost: O(V + E)

inline int TopoSort()
{
    queue<int> S;
    for (int i=0;i<n;i++) if (indegree[i] == 0) S.push(i);
    int idx = 0;
    while (!S.empty())
    {
        int idd = S.front();
        S.pop();
        toposort[idx++] = idd;
        for (int i=0;i<graf[idd].adj.size();i++)
        {
            if (--indegree[graf[idd].adj[i]] == 0) S.push(graf[idd].adj[i]);
        }
    }
    if (idx < n) return -1; // Cycle detected!
    else return 0;
}

int main()
{
    n = 8;
    
    graf[7].adj.push_back(0);
    graf[7].adj.push_back(5);
    graf[7].adj.push_back(6);
    graf[4].adj.push_back(5);
    graf[3].adj.push_back(7);
    graf[3].adj.push_back(4);
    graf[2].adj.push_back(7);
    graf[1].adj.push_back(4);
    graf[1].adj.push_back(6);
    
    indegree[0] = 1;
    indegree[1] = 0;
    indegree[2] = 0;
    indegree[3] = 0;
    indegree[4] = 2;
    indegree[5] = 2;
    indegree[6] = 2;
    indegree[7] = 2;
    
    TopoSort();
    for (int i=0;i<n;i++) printf("%d ",toposort[i]);
    printf("\n");
    
    return 0;
}
