/*
 Petar 'PetarV' Velickovic
 Algorithm: Nussinov Algorithm
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

#define MAX_N 1001

#define DPRINTC(C) printf(#C " = %c\n", (C))
#define DPRINTS(S) printf(#S " = %s\n", (S))
#define DPRINTD(D) printf(#D " = %d\n", (D))
#define DPRINTLLD(LLD) printf(#LLD " = %lld\n", (LLD))
#define DPRINTLF(LF) printf(#LF " = %.5lf\n", (LF))

using namespace std;
typedef long long lld;
typedef unsigned long long llu;

int n;
string A;
int dp[MAX_N][MAX_N];

/*
 The Nussinov algorithm attepts to predict RNA secondary structure,
 under the assumption that RNA will form as many loops as possible.
 
 Complexity: O(n^3) time, O(n^2) memory
*/

bool complementary(char X, char Y)
{
    return ((X == 'A' && Y == 'U') || (X == 'U' && Y == 'A') || (X == 'C' && Y == 'G') || (X == 'G' && Y == 'C'));
}

int nussinov(int i, int j)
{
    if (dp[i][j] != -1) return dp[i][j];
    
    if (i >= j - 1)
    {
        dp[i][j] = 0;
        return 0;
    }
    
    int ret = 0;
    ret = max(ret, nussinov(i + 1, j));
    ret = max(ret, nussinov(i, j - 1));
    if (complementary(A[i], A[j])) ret = max(ret, nussinov(i + 1, j - 1) + 1);
    for (int k=i+1;k<j;k++)
    {
        ret = max(ret, nussinov(i, k) + nussinov(k + 1, j));
    }
    
    dp[i][j] = ret;
    return ret;
}

inline int nussinov()
{
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            dp[i][j] = -1;
        }
    }
    
    return nussinov(0, n - 1);
}

string get_bracketing(int i, int j)
{
    if (i == j) return A.substr(i, 1);
    if (i > j) return "";
    
    if (nussinov(i, j) == nussinov(i + 1, j))
    {
        string left = A.substr(i, 1);
        return left + get_bracketing(i + 1, j);
    }
    
    if (nussinov(i, j) == nussinov(i, j - 1))
    {
        string right = A.substr(j, 1);
        return get_bracketing(i, j - 1) + right;
    }
    
    if (complementary(A[i], A[j]) && nussinov(i, j) == nussinov(i+1, j-1) + 1)
    {
        string left = A.substr(i, 1);
        string right = A.substr(j, 1);
        return "(" + left + get_bracketing(i+1, j-1) + right + ")";
    }
    
    for (int k=i+1;k<j;k++)
    {
        if (nussinov(i, j) == nussinov(i, k) + nussinov(k + 1, j))
        {
            return get_bracketing(i, k) + get_bracketing(k + 1, j);
        }
    }
    
    return "FAIL"; // should never happen!
}

int main()
{
    n = 8;
    A = "GCACGACG";
    // A = "GGGAAAUCC"
    
    printf("%d\n", nussinov());
    cout << get_bracketing(0, n - 1) << endl;
    
    return 0;
}
