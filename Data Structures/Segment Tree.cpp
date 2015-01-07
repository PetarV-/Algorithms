/*
 Petar 'PetarV' Velickovic
 Data Structure: Segment Tree
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
#define MID (left+right)/2
#define MAX_N 1000001
#define MAX_TREE (MAX_N << 2)
#define INF 987654321
using namespace std;
typedef long long lld;

int n;
int niz[MAX_N];
int ST[MAX_TREE];

//Segmentno stablo nad datim nizom - u datom primeru cuva se minimum nad svakim segmentom
//Slozenost: InitTree O(N), Update O(log N), Query O(log N)

void InitTree(int idx, int left, int right)
{
    if (left == right)
    {
        ST[idx] = niz[left];
        return;
    }
    InitTree(2*idx, left, MID);
    InitTree(2*idx+1, MID+1, right);
    ST[idx] = min(ST[2*idx], ST[2*idx+1]);
}

void Update(int idx, int x, int val, int left, int right)
{
    if (left == right)
    {
        ST[idx] = val;
        return;
    }
    if (x <= MID) Update(2*idx, x, val, left, MID);
    else Update(2*idx+1, x, val, MID+1, right);
    ST[idx] = min(ST[2*idx], ST[2*idx+1]);
}

int Query(int idx, int l, int r, int left, int right)
{
    if (l <= left && right <= r) return ST[idx];
    int ret = INF;
    if (l <= MID) ret = min(ret, Query(2*idx, l, r, left, MID));
    if (r > MID) ret = min(ret, Query(2*idx+1, l, r, MID+1, right));
    return ret;
}

int main()
{
    n = 6;
    niz[1] = 4;
    niz[2] = 2;
    niz[3] = 5;
    niz[4] = 1;
    niz[5] = 6;
    niz[6] = 3;
    
    InitTree(1, 1, n);
    printf("%d\n",Query(1, 1, 3, 1, n));
    
    Update(1, 4, 10, 1, n);
    Update(1, 5, 0, 1, n);
    printf("%d\n",Query(1, 4, 6, 1, n));
    
    return 0;
}
