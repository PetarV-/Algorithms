/*
 Petar 'PetarV' Velickovic
 Algorithm: Prim's Algorithm
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
#define MAX_N 101
using namespace std;
typedef long long lld;

int n;
struct Node
{
    vector<int> adj;
    vector<int> weight;
};
Node graf[MAX_N];
bool mark[MAX_N];

struct edge
{
    int u, v;
    double w;
    bool operator <(const edge &a) const
    {
        return (w>a.w);
    }
};

priority_queue<edge> pq_prim;

//Primov algoritam za racunanje minimalnog stabla razapinjanja datog tezinskog grafa
//Slozenost: O((V+E)log V)

inline int Prim()
{
    int xt = 0;
    int ret = 0;
    int amt = 0;
    while (amt < n-1)
    {
        mark[xt]=true;
        for (int i=0;i<graf[xt].adj.size();i++)
        {
            if (!mark[graf[xt].adj[i]])
            {
                edge E;
                E.u = xt;
                E.v = graf[xt].adj[i];
                E.w = graf[xt].weight[i];
                pq_prim.push(E);
            }
        }
        while (!pq_prim.empty())
        {
            edge X = pq_prim.top();
            pq_prim.pop();
            if (!mark[X.v])
            {
                ret += X.w;
                xt = X.v;
                amt++;
                break;
            }
        }
    }
    return ret;
}

int main()
{
    n = 7;
    
    graf[0].adj.push_back(1);
    graf[0].weight.push_back(7);
    graf[1].adj.push_back(0);
    graf[1].weight.push_back(7);
    
    graf[0].adj.push_back(3);
    graf[0].weight.push_back(5);
    graf[3].adj.push_back(0);
    graf[3].weight.push_back(5);
    
    graf[1].adj.push_back(2);
    graf[1].weight.push_back(8);
    graf[2].adj.push_back(1);
    graf[2].weight.push_back(8);
    
    graf[1].adj.push_back(3);
    graf[1].weight.push_back(9);
    graf[3].adj.push_back(1);
    graf[3].weight.push_back(9);
    
    graf[1].adj.push_back(4);
    graf[1].weight.push_back(7);
    graf[4].adj.push_back(1);
    graf[4].weight.push_back(7);
    
    graf[2].adj.push_back(4);
    graf[2].weight.push_back(5);
    graf[4].adj.push_back(2);
    graf[4].weight.push_back(5);
    
    graf[3].adj.push_back(4);
    graf[3].weight.push_back(15);
    graf[4].adj.push_back(3);
    graf[4].weight.push_back(15);
    
    graf[3].adj.push_back(5);
    graf[3].weight.push_back(6);
    graf[5].adj.push_back(3);
    graf[5].weight.push_back(6);
    
    graf[4].adj.push_back(5);
    graf[4].weight.push_back(8);
    graf[5].adj.push_back(4);
    graf[5].weight.push_back(8);
    
    graf[4].adj.push_back(6);
    graf[4].weight.push_back(9);
    graf[6].adj.push_back(4);
    graf[6].weight.push_back(9);
    
    graf[5].adj.push_back(6);
    graf[5].weight.push_back(11);
    graf[6].adj.push_back(5);
    graf[6].weight.push_back(11);
    
    printf("%d\n",Prim());
    
    return 0;
}
