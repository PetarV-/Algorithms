/*
 Petar 'PetarV' Velickovic
 Algorithm: Connected Components
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

//Algoritam za odredjivanje broja povezanih komponenti neusmerenog grafa, koristeci DFS
//Slozenost: O(V + E)

inline void DFS(int start)
{
    stack<int> dfs_stek;
    dfs_stek.push(start);
    while (!dfs_stek.empty())
    {
        int xt = dfs_stek.top();
        dfs_stek.pop();
        mark[xt] = true;
        for (int i=0;i<graf[xt].adj.size();i++)
        {
            if (!mark[graf[xt].adj[i]])
            {
                dfs_stek.push(graf[xt].adj[i]);
                mark[graf[xt].adj[i]] = true;
            }
        }
    }
}

inline int numComponents(int n)
{
    int ret = 0;
    for (int i=0;i<n;i++)
    {
        if (!mark[i])
        {
            DFS(i);
            ret++;
        }
    }
    return ret;
}

int main()
{
    n = 6;
    
    graf[0].adj.push_back(1);
    graf[1].adj.push_back(0);
    
    graf[0].adj.push_back(2);
    graf[2].adj.push_back(0);
    
    graf[4].adj.push_back(4);
    
    graf[3].adj.push_back(5);
    graf[5].adj.push_back(3);
    
    printf("%d\n",numComponents(n));
    
    return 0;
}
