/*
 Petar 'PetarV' Velickovic
 Algorithm: Heavy-Light Decomposition
*/

#include <stdio.h>
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
#define MAX_N 1000001
#define INF 987654321
using namespace std;
typedef long long lld;
typedef unsigned long long llu;

/*
 Heavy-Light Decomposition algorithm for partitioning the edges of a tree into two groups - heavy and light.
 Can be used for efficient traversal from any node to the root of the tree, since there are at most log n light edges
 along that path; hence, we can skip entire chains of heavy edges.
 Complexity: O(n)
*/

struct Node
{
     vector<int> adj;
};
Node graf[MAX_N];

struct TreeNode
{
     int parent;
     int depth;
     int chainTop;
     int subTreeSize;
};
TreeNode T[MAX_N];

int DFS(int root, int parent, int depth)
{
     T[root].parent = parent;
     T[root].depth = depth;
     T[root].subTreeSize = 1;
     for (int i=0;i<graf[root].adj.size();i++)
     {
          int xt = graf[root].adj[i];
          if (xt == parent) continue;
          T[root].subTreeSize += DFS(xt, root, depth+1);
     }
     return T[root].subTreeSize;
}

void HLD(int root, int parent, int chainTop)
{
     T[root].chainTop = chainTop;
     
     for (int i=0;i<graf[root].adj.size();i++)
     {
          int xt = graf[root].adj[i];
          if (xt == parent) continue;
          if (T[xt].subTreeSize*1.0 > T[root].subTreeSize*0.5) HLD(xt, root, chainTop);
          else HLD(xt, root, xt);
     }
}

inline int LCA(int u, int v)
{
     while (T[u].chainTop != T[v].chainTop)
     {
          if (T[T[u].chainTop].depth < T[T[v].chainTop].depth) v = T[T[v].chainTop].parent;
          else u = T[T[u].chainTop].parent;
     }
     
     if (T[u].depth < T[v].depth) return u;
     else return v;
}

int n;

int main()
{
     n = 7;
     
     graf[1].adj.push_back(2);
     graf[2].adj.push_back(1);
     
     graf[1].adj.push_back(3);
     graf[3].adj.push_back(1);
     
     graf[1].adj.push_back(4);
     graf[4].adj.push_back(1);
     
     graf[3].adj.push_back(5);
     graf[5].adj.push_back(3);
     
     graf[3].adj.push_back(6);
     graf[6].adj.push_back(3);
     
     graf[3].adj.push_back(7);
     graf[7].adj.push_back(3);
     
     DFS(1, 1, 0);
     HLD(1, 1, 1);
     
     printf("%d\n", LCA(5, 7));
     printf("%d\n", LCA(2, 7));
     
     return 0;
}