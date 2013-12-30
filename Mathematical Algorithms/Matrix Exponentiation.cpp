/*
 Petar 'PetarV' Velickovic
 Algorithm: Matrix Exponentiation
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
using namespace std;
typedef long long lld;

/*
 Fast algorithm for exponentiation of an n*n matrix that utilizes exponentiation by squaring.
 Complexity:    O(n^3 log pow)
*/

inline lld** MatrixMultiply(lld** a, lld** b, int n, int l, int m)
{
    lld **c = new lld*[n];
    for (int i=0;i<n;i++) c[i] = new lld[m];
    
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            c[i][j]=0;
            for(int k=0;k<l;k++)
            {
                c[i][j] += a[i][k]*b[k][j];
            }
        }
    }
    return c;
}

inline lld** MatrixPower(lld** a, int n, lld pow)
{
    lld** ret = new lld*[n];
    for (int i=0;i<n;i++)
    {
        ret[i] = new lld[n];
        for (int j=0;j<n;j++)
        {
            if (i == j) ret[i][j] = 1;
            else ret[i][j] = 0;
        }
    }
    
    while (pow)
    {
        if (pow&1) ret = MatrixMultiply(ret, a, n, n, n);
        pow>>=1;
        a = MatrixMultiply(a, a, n, n, n);
    }
    
    return ret;
}

int main()
{
    lld **matA;
    matA = new lld*[2];
    for (int i=0;i<2;i++) matA[i] = new lld[2];
    matA[0][0] = 4;
    matA[0][1] = 2;
    matA[1][0] = -1;
    matA[1][1] = 1;
    
    lld **matC = MatrixPower(matA, 2, 5);
    
    for (int i=0;i<2;i++)
    {
        for (int j=0;j<2;j++)
        {
            printf("%lld ", matC[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}