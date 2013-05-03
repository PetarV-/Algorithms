/*
 Petar 'PetarV' Velickovic
 Algorithm: Longest Common Subsequence
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
#define MAX_N 1001
using namespace std;
typedef long long lld;

int n, m;
string A, B;
int dp[MAX_N][MAX_N];

//Algoritam koji racuna najduzu zajednicku podsekvencu dva stringa
//Slozenost: O(n*m)

inline int LCS()
{
    for (int i=0;i<=n;i++) dp[i][0] = 0;
    for (int j=0;j<=m;j++) dp[0][j] = 0;
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=m;j++)
        {
            if (A[i-1] == B[j-1])
            {
                dp[i][j] = dp[i-1][j-1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
            }
        }
    }
    return dp[n][m];
}

int main()
{
    n = 5, m = 6;
    A = "aleks";
    B = "abcdef";
    printf("%d\n",LCS());
    return 0;
}
