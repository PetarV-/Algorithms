/*
 Petar 'PetarV' Velickovic
 Data Structure: Link/cut Tree
*/

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <time.h>
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
#include <chrono>
#include <random>
#include <unordered_map>

#define MAX_N 100001

typedef long long lld;
typedef unsigned long long llu;
using namespace std;

/*
 The link/cut tree data structure enables us to efficiently handle a dynamic forest of trees.
 It does so by storing a decomposition of the forest into "preferred paths", where a path is
 preferred to another when it has been more recently accessed.
 Each preferred path is stored in a splay tree which is keyed by depth.
 
 The tree supports the following operations:
     - make_tree(v): create a singleton tree containing the node v
     - find_root(v): find the root of the tree containing v
     - link(v, w):   connect v to w
                     (precondition: v is root of its own tree,
                     and v and w are not in the same tree!)
     - cut(v):       cut v off from its parent
     - path(v):      access the path from the root of v's tree to v 
                     (in order to e.g. perform an aggregate query on that path)
 
 More complex operations and queries are possible that require the data structure 
 to be augmented with additional data. Here I will demonstrate the LCA(p, q)
 (lowest common ancestor of p and q) operation.
 
 Complexity:    O(1) for make_tree
                O(log n) amortized for all other operations
*/

int n, m;
char cmd[101];
int p, q;

struct Node
{
    int L, R, P;
    int PP;
};

Node LCT[MAX_N];

inline void make_tree(int v)
{
    if (v == -1) return;
    LCT[v].L = LCT[v].R = LCT[v].P = LCT[v].PP = -1;
}

inline void rotate(int v)
{
    if (v == -1) return;
    if (LCT[v].P == -1) return;
    int p = LCT[v].P;
    int g = LCT[p].P;
    if (LCT[p].L == v)
    {
        LCT[p].L = LCT[v].R;
        if (LCT[v].R != -1)
        {
            LCT[LCT[v].R].P = p;
        }
        LCT[v].R = p;
        LCT[p].P = v;
    }
    else
    {
        LCT[p].R = LCT[v].L;
        if (LCT[v].L != -1)
        {
            LCT[LCT[v].L].P = p;
        }
        LCT[v].L = p;
        LCT[p].P = v;
    }
    LCT[v].P = g;
    if (g != -1)
    {
        if (LCT[g].L == p)
        {
            LCT[g].L = v;
        }
        else
        {
            LCT[g].R = v;
        }
    }
    // must preserve path-pointer!
    // (this only has an effect when g is -1)
    LCT[v].PP = LCT[p].PP;
    LCT[p].PP = -1;
}

inline void splay(int v)
{
    if (v == -1) return;
    while (LCT[v].P != -1)
    {
        int p = LCT[v].P;
        int g = LCT[p].P;
        if (g == -1) // zig
        {
            rotate(v);
        }
        else if ((LCT[p].L == v) == (LCT[g].L == p)) // zig-zig
        {
            rotate(p);
            rotate(v);
        }
        else // zig-zag
        {
            rotate(v);
            rotate(v);
        }
    }
}

inline void expose(int v)
{
    if (v == -1) return;
    splay(v); // now v is root of its aux. tree
    if (LCT[v].R != -1)
    {
        LCT[LCT[v].R].PP = v;
        LCT[LCT[v].R].P = -1;
        LCT[v].R = -1;
    }
    while (LCT[v].PP != -1)
    {
        int w = LCT[v].PP;
        splay(w);
        if (LCT[w].R != -1)
        {
            LCT[LCT[w].R].PP = w;
            LCT[LCT[w].R].P = -1;
        }
        LCT[w].R = v;
        LCT[v].P = w;
        splay(v);
    }
}

inline int find_root(int v)
{
    if (v == -1) return -1;
    expose(v);
    int ret = v;
    while (LCT[ret].L != -1) ret = LCT[ret].L;
    expose(ret);
    return ret;
}

inline void link(int v, int w) // attach v's root to w
{
    if (v == -1 || w == -1) return;
    expose(w);
    LCT[v].L = w; // the root can only have right children in its splay tree, so no need to check
    LCT[w].P = v;
    LCT[w].PP = -1;
}

inline void cut(int v)
{
    if (v == -1) return;
    expose(v);
    if (LCT[v].L != -1)
    {
        LCT[LCT[v].L].P = -1;
        LCT[LCT[v].L].PP = -1;
        LCT[v].L = -1;
    }
}

inline int LCA(int p, int q)
{
    expose(p);
    splay(q);
    if (LCT[q].R != -1)
    {
        LCT[LCT[q].R].PP = q;
        LCT[LCT[q].R].P = -1;
        LCT[q].R = -1;
    }
    
    int ret = q, t = q;
    while (LCT[t].PP != -1)
    {
        int w = LCT[t].PP;
        splay(w);
        if (LCT[w].PP == -1) ret = w;
        if (LCT[w].R != -1)
        {
            LCT[LCT[w].R].PP = w;
            LCT[LCT[w].R].P = -1;
        }
        LCT[w].R = t;
        LCT[t].P = w;
        LCT[t].PP = -1;
        t = w;
    }
    splay(q);
    
    return ret;
}

int main()
{
    // This is the code I used for the problem Dynamic LCA (DYNALCA)
    // on Sphere Online Judge (SPOJ)
    scanf("%d%d", &n, &m);
    
    for (int i=1;i<=n;i++) make_tree(i);
    
    while (m--)
    {
        scanf("%s", cmd);
        if (strcmp(cmd, "link") == 0)
        {
            scanf("%d%d", &p, &q);
            link(p, q);
        }
        else if (strcmp(cmd, "cut") == 0)
        {
            scanf("%d", &p);
            cut(p);
        }
        else if (strcmp(cmd, "lca") == 0)
        {
            scanf("%d%d", &p, &q);
            printf("%d\n", LCA(p, q));
        }
    }
    
    return 0;
}
