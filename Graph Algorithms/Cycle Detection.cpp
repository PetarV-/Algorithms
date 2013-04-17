/*
 Petar 'PetarV' Velickovic
 Algorithm: Cycle Detection
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

//Algoritam za trazenje ciklusa u neusmerenom grafu, koristeci DFS
//Slozenost: O(V + E)

inline bool DFS(int start)
{
    stack<int> dfs_stek;
    stack<int> previous;
    dfs_stek.push(start);
    previous.push(-1);
    while (!dfs_stek.empty())
    {
        int xt = dfs_stek.top();
        int pt = previous.top();
        dfs_stek.pop();
        previous.pop();
        mark[xt] = true;
        for (int i=0;i<graf[xt].adj.size();i++)
        {
            if (!mark[graf[xt].adj[i]])
            {
                dfs_stek.push(graf[xt].adj[i]);
                previous.push(xt);
                mark[graf[xt].adj[i]] = true;
            }
            else if (graf[xt].adj[i] != pt) return true;
        }
    }
    return false;
}

inline bool hasCycle(int n)
{
    for (int i=0;i<n;i++)
    {
        if (!mark[i])
        {
            if (DFS(i)) return true;
        }
    }
    return false;
}

int main()
{
    n = 6;
    
    graf[0].adj.push_back(1);
    graf[1].adj.push_back(0);
    
    graf[0].adj.push_back(2);
    graf[2].adj.push_back(0);
    
    graf[2].adj.push_back(1);
    graf[1].adj.push_back(2);
    
    graf[3].adj.push_back(5);
    graf[5].adj.push_back(3);
    
    printf("%d\n",hasCycle(n) ? 1 : 0);
    
    return 0;
}
