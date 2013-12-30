/*
 Petar 'PetarV' Velickovic
 Algorithm: Matrix Multiplication
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
 Naive algorithm for matrix multiplication of two matrices, A (of size n*l) and B (of size l*m).
 Complexity:    O(nlm)
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

int main()
{
    lld **matA;
    matA = new lld*[2];
    for (int i=0;i<2;i++) matA[i] = new lld[3];
    matA[0][0] = 1;
    matA[0][1] = 2;
    matA[0][2] = 3;
    matA[1][0] = 4;
    matA[1][1] = 5;
    matA[1][2] = 6;
    
    lld **matB;
    matB = new lld*[3];
    for (int i=0;i<3;i++) matB[i] = new lld[2];
    matB[0][0] = 7;
    matB[0][1] = 8;
    matB[1][0] = 9;
    matB[1][1] = 10;
    matB[2][0] = 11;
    matB[2][1] = 12;
    
    lld **matC = MatrixMultiply(matA, matB, 2, 3, 2);
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