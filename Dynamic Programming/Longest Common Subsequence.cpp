/*
 Petar 'PetarV' Velickovic
 Algorithm: Longest Common Subsequence
*/
/* Modified by Daniel Ward ('dwarduk') to extract subsequence */

#include <stdio.h>
#include <string>
#include <algorithm>
#include <iostream>

#define MAX_N 1001
using namespace std;

int n, m;
string A, B;
int dp[MAX_N][MAX_N];
int route[MAX_N][MAX_N];
char seq[MAX_N];

//Algoritam koji racuna najduzu zajednicku podsekvencu dva stringa
//Slozenost: O(n*m)

inline int LCS()
{
    for (int i=0;i<=n;i++) { dp[i][0] = 0; route[i][0] = 0; }
    for (int j=0;j<=m;j++) { dp[0][j] = 0; route[0][j] = 0; }
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=m;j++)
        {
            if (A[i-1] == B[j-1])
            {
                dp[i][j] = dp[i-1][j-1] + 1;
                route[i][j] = 3; // Builds on (i-1,j-1) elem in dp
            }
            else if(dp[i][j-1] > dp[i-1][j])
            {
                dp[i][j] = dp[i][j-1];
                route[i][j] = 2; // Builds on (i,j-1) elem in dp
            }
            else { // if dp[i-1][j] >= dp[i][j-1] 
                dp[i][j] = dp[i-1][j];
                route[i][j] = 1; // Builds on (i-1,j) elem in dp
            }
        }
    }
    return dp[n][m];
}

inline char *getLCS() {
    int x = n, y = m;
    int length = dp[n][m];

    while(route[x][y] > 0 && length > 0) {
        if(route[x][y] == 3) {
	    seq[length-1] = A[x-1]; //or B[y-1]
            x--;y--;length--;
        }
        else if(route[x][y] == 2) {
            y--;
        }
        else if(route[x][y] == 1) { //if route[x][y] == 1
            x--;
        }
        else {
            return ""; //invalid input
        }
    }

    return seq;
    
}

int main()
{
    n = 5, m = 6;
    A = "aleks";
    B = "abcdef";
    printf("%d\n",LCS());
    printf("%s\n",getLCS());
    return 0;
}
