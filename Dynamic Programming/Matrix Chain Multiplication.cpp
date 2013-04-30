/*
 Petar 'PetarV' Velickovic
 Algorithm: Matrix Chain Multipication
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
#define MAX_N 305
#define INF 987654321
using namespace std;
typedef long long lld;

int n;
int p[MAX_N];
int m[MAX_N][MAX_N];
int memo[MAX_N][MAX_N];

//Algoritam koji odredjuje optimalan redosled mnozenja N matrica
//Dimenzije i-te matrice su: p[i-1] x p[i]
//Slozenost: O(N^3)

inline int MatrixChainMultiplication(int i, int j)
{
    if (i == j) return 0;
    if (memo[i][j] > 0) return memo[i][j];
    int ret = INF;
    for (int k=i;k<j;k++)
    {
        int curr = MatrixChainMultiplication(i, k) + MatrixChainMultiplication(k+1, j) + p[i-1] * p[k] * p[j];
        ret = min(ret, curr);
    }
    memo[i][j] = ret;
    return ret;
}

int main()
{
    n = 6;
    p[0] = 30, p[1] = 35, p[2] = 15, p[3] = 5, p[4] = 10, p[5] = 20, p[6] = 25;
    printf("%d\n",MatrixChainMultiplication(1, 6));
    return 0;
}
