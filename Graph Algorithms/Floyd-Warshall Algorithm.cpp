/*
 Petar 'PetarV' Velickovic 
 Algorithm: Floyd-Warshall Algorithm
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
#define MAX_N 300
#define INF 987654321
using namespace std;
typedef long long lld;

int n;

int dist[MAX_N][MAX_N];
int flojd[MAX_N][MAX_N];

//Floyd-Warshallov algoritam za trazenje duzina najkracih puteva svih parova cvorova u grafu
//Slozenost: O(V^3)

inline void FloydWarshall()
{
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=n;j++)
        {
            flojd[i][j] = dist[i][j];
        }
        flojd[i][i] = 0;
    }
    for (int k=1;k<=n;k++)
    {
        for (int i=1;i<=n;i++)
        {
            for (int j=1;j<=n;j++)
            {
                if (flojd[i][k] + flojd[k][j] < flojd[i][j])
                {
                    flojd[i][j] = flojd[i][k] + flojd[k][j];
                }
            }
        }
    }
}

int main()
{
    n = 3;
    dist[1][1] = 0, dist[1][2] = 3, dist[1][3] = INF;
    dist[2][1] = INF, dist[2][2] = 0, dist[2][3] = 4;
    dist[3][1] = INF, dist[3][2] = 1, dist[3][3] = 0;
    FloydWarshall();
    printf("%d\n",flojd[1][3]);
    return 0;
}
