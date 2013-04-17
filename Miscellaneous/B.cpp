/*
 Petar 'PetarV' Velickovic
 Task: TheGraf
 */

#include <stdio.h>
#include <vector>
#include <stack>
#include <set>
#define INF 987654321
#define MAX_N 20001
using namespace std;

int n, m, t;
int x, y;
vector<int> adj[MAX_N];
stack<int> Stack;
bool onStack[MAX_N];
int Indices;
int Index[MAX_N];
int LowLink[MAX_N];
int component[MAX_N];
int in[MAX_N], out[MAX_N];
int numComponents;

int max1(int x, int y)
{
    if (x>y) return x;
    return y;
}

void tarjanDFS(int i)
{
    Index[i] = ++Indices;
    LowLink[i] = Indices;
    Stack.push(i); onStack[i] = true;
    for (int j = 0; j < adj[i].size(); ++j)
    {
        int w = adj[i][j];
        if(Index[w] == 0)
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
            w = Stack.top(); Stack.pop(); onStack[w] = false;
            component[w] = numComponents;
        } while (i != w && !Stack.empty());
        numComponents++;
    }
}

void Tarjan()
{
    Indices = 0;
    while (!Stack.empty()) Stack.pop();
    for (int i = n; i ; --i) onStack[i] = LowLink[i] = Index[i] = 0;
    numComponents = 0;
    for (int i = n; i; --i) if (Index[i] == 0) tarjanDFS(i);
}

vector < set<int> > Cadj;

void MakeComponentGraph()
{
    Cadj.resize(numComponents);
    for (int i = n; i; --i)
    {
        int ic = component[i];
        for (int j = 0; j < adj[i].size(); ++j)
        {
            int jc = component[adj[i][j]];
            if (ic != jc)
            {
                Cadj[ic].insert(jc);
                in[ic]++;
                out[jc]++;
            }
        }
    }
}

inline void reset1()
{
    x = 0, y = 0;
    Indices = 0;
    numComponents = 0;

    for (int i=0;i<n;i++)
    {
        onStack[i] = false;
        Index[i] = 0;
        LowLink[i] = 0;
        component[i] = 0;
        in[i] = 0;
        out[i] = 0;
        adj[i].clear();
    }
}

int main()
{
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d%d",&n,&m);
        for (int i=0;i<m;i++)
        {
            scanf("%d%d",&x,&y);
            adj[x].push_back(y);
        }
        Tarjan();
        MakeComponentGraph();
    
        if (numComponents == 1) { printf("0\n"); return 0; }
    
        else
        {
            int sol = INF;
            int cnt1 = 0, cnt2 = 0;
            for (int i=0;i<numComponents;i++)
            {
                if (in[i] == 0) cnt1++;
                if (out[i] == 0) cnt2++;
            }
            printf("%d\n",max1(cnt1,cnt2));
        }
        
        if (t != 0) reset1();
    }
    return 0;
}