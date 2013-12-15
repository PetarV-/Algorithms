/*
 Petar 'PetarV' Velickovic
 Algorithm: Pascal's Triangle
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
#define MAX_N 5001
#define MAX_K 5001
using namespace std;
typedef long long lld;

lld binom[MAX_N][MAX_K];

int lasti = 0, lastj = 0;
bool init = false;

//Algoritam za racunanje binomnih koeficijenata preko rekurentne veze (Paskalovog trougla)
//Slozenost: O(n*k)

inline lld BinomialCoefficient(int n, int k)
{
    if (lasti >= n && lastj >= k) return binom[n][k];
    if (!init)
    {
        for (int i=0;i<=n;i++) binom[i][0] = 1;
        for (int j=1;j<=k;j++) binom[0][j] = 0;
        for (int i=1;i<=n;i++)
        {
            for (int j=1;j<=k;j++)
            {
                binom[i][j] = binom[i-1][j-1] + binom[i-1][j];
            }
        }
        init = true;
        lasti = n;
        lastj = k;
        return binom[n][k];
    }
    else
    {
        if (lastj < k)
        {
            for (int i=1;i<=lasti;i++)
            {
                for (int j=lastj+1;j<=k;j++)
                {
                    binom[i][j] = binom[i-1][j-1] + binom[i-1][j];
                }
            }
            lastj = k;
        }
        if (lasti >= n) return binom[n][k];
        else
        {
            for (int i=lasti+1;i<=n;i++)
            {
                binom[i][0] = 1;
                for (int j=1;j<=lastj;j++)
                {
                    binom[i][j] = binom[i-1][j-1] + binom[i-1][j];
                }
            }
            lasti = n;
            return binom[n][k];
        }
    }
}

int main()
{
    printf("%lld\n",BinomialCoefficient(5, 2));
    printf("%lld\n",BinomialCoefficient(7, 1));
    printf("%lld\n",BinomialCoefficient(7, 3));
    printf("%lld\n",BinomialCoefficient(15, 7));
    printf("%lld\n",BinomialCoefficient(10, 4));
    return 0;
}
