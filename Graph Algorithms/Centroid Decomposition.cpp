#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 1;
const int K = 20;

int n,m;
vector<int> adj[N];
int sz[N],pa[N];
bool blocked[N];
int res[N],dp[K][N],lv[N];

void dfs(int u,int p)
{
    sz[u] = 1;
    for(int v : adj[u]) if(v!=p and !blocked[v]) dfs(v,u),sz[u]+=sz[v];
}
 
void build(int u,int cp)
{
    dfs(u,0);
    int c = u,prev = 0;
    while(true)
    {
        int mx = -1,id;
        for(int v : adj[c]) if(!blocked[v] and v!=prev) if(sz[v]>mx) mx = sz[v],id = v;
        if(mx*2>sz[u]) prev = c,c = id;
        else break;
    }
    pa[c] = cp;
    blocked[c] = true;
    for(int v : adj[c]) if(!blocked[v]) build(v,c);
}

void update_and_query(int x){ for(int u = x;u;u = pa[u]); } // go up on parent in centroid tree for update and query
