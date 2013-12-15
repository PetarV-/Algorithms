/*
 Petar 'PetarV' Velickovic
 Algorithm: Dijkstra's Algorithm
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
#define INF 987654321
using namespace std;
typedef long long lld;

int n;

struct Node
{
    int dist;
    vector<int> adj;
    vector<int> weight;
};
Node graf[MAX_N];
bool mark[MAX_N];

struct pq_entry
{
    int node, dist;
    bool operator <(const pq_entry &a) const
    {
        if (dist != a.dist) return (dist > a.dist);
        return (node > a.node);
    }
};

//Dijkstrin algoritam za nalazenje duzina najkracih puteva iz jednog izvora u grafu
//Slozenost: O((V+E)log V)

inline void Dijkstra(int source)
{
    priority_queue<pq_entry> pq;
    pq_entry P;
    for (int i=0;i<n;i++)
    {
        if (i == source)
        {
            graf[i].dist = 0;
            P.node = i;
            P.dist = 0;
            pq.push(P);
        }
        else graf[i].dist = INF;
    }
    while (!pq.empty())
    {
        pq_entry curr = pq.top();
        pq.pop();
        int nod = curr.node;
        int dis = curr.dist;
        for (int i=0;i<graf[nod].adj.size();i++)
        {
            if (!mark[graf[nod].adj[i]])
            {
                int nextNode = graf[nod].adj[i];
                if (dis + graf[nod].weight[i] < graf[nextNode].dist)
                {
                    graf[nextNode].dist = dis + graf[nod].weight[i];
                    P.node = nextNode;
                    P.dist = graf[nextNode].dist;
                    pq.push(P);
                }
            }
        }
        mark[nod] = true;
    }
}

int main()
{
    n = 4;
    
    graf[0].adj.push_back(1);
    graf[0].weight.push_back(5);
    graf[1].adj.push_back(0);
    graf[1].weight.push_back(5);
    
    graf[1].adj.push_back(2);
    graf[1].weight.push_back(5);
    graf[2].adj.push_back(1);
    graf[2].weight.push_back(5);
    
    graf[2].adj.push_back(3);
    graf[2].weight.push_back(5);
    graf[3].adj.push_back(2);
    graf[3].weight.push_back(5);
    
    graf[3].adj.push_back(1);
    graf[3].weight.push_back(6);
    graf[1].adj.push_back(3);
    graf[1].weight.push_back(6);
    
    Dijkstra(0);
    
    printf("%d\n",graf[3].dist);
    return 0;
}
