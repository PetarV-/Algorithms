/*
 Petar 'PetarV' Velickovic
 Algorithm: Tarjan's SCC Algorithm
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
#define INF 987654321
using namespace std;
typedef long long lld;

int n, m;
struct Node
{
    vector<int> adj;
};
Node graf[MAX_N];
stack<int> Stack;
bool onStack[MAX_N];
int Indices;
int Index[MAX_N];
int LowLink[MAX_N];
int component[MAX_N];
int numComponents;

//Tarjanov algoritam za racunanje jako povezanih komponenti datog usmerenog grafa
//Slozenost: O(V + E)

void tarjanDFS(int i)
{
    Index[i] = ++Indices;
    LowLink[i] = Indices;
    Stack.push(i); onStack[i] = true;
    for (int j=0;j<graf[i].adj.size();j++)
    {
        int w = graf[i].adj[j];
        if (Index[w] == 0)
        {
            tarjanDFS(w);
            LowLink[i] = min(LowLink[i], LowLink[w]);
        }
        else if (onStack[w])
        {
            LowLink[i] = min(LowLink[i], Index[w]);
        }
    }
    if (LowLink[i] == Index[i])
    {
        int w = 0;
        do
        {
            w = Stack.top(); Stack.pop();
            component[w] = numComponents;
            onStack[w]=false;
        } while (i != w && !Stack.empty());
        numComponents++;
    }
}

void Tarjan()
{
    Indices = 0;
    while (!Stack.empty()) Stack.pop();
    for (int i=n;i>0;i--) onStack[i] = LowLink[i] = Index[i] = 0;
    numComponents = 0;
    for (int i=n;i>0;i--) if (Index[i] == 0) tarjanDFS(i);
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
    
    Tarjan();
    
    printf("%d\n",numComponents);
    
    return 0;
}
