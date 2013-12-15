/*
 Petar 'PetarV' Velickovic
 Algorithm: Z Algorithm
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
#define MAX_N 1000001
using namespace std;
typedef long long lld;

int n, m;
string needle, haystack;
int Z[MAX_N];
vector<int> matches;

//Z Algoritam koji racuna Z-funkciju nad datim stringom; moze se koristiti za efikasan string matching
//Slozenost: O(N + M)

inline void Z_Algorithm(string s)
{
    int len = s.length();
    int L = 0, R = 0;
    for (int i=1;i<len;i++)
    {
        if (i > R)
        {
            L = R = i;
            while (R < len && s[R-L] == s[R]) R++;
            Z[i] = R-L;
            R--;
        }
        else
        {
            int k = i - L;
            if (Z[k] < R-i+1) Z[i] = Z[k];
            else
            {
                L = i;
                while (R < len && s[R-L] == s[R]) R++;
                Z[i] = R - L;
                R--;
            }
        }
        if (Z[i] == m) matches.push_back(i - m - 1);
    }
}

int main()
{
    n = 6, m = 2;
    haystack = "abcabc";
    needle = "bc";
    Z_Algorithm(needle + "#" + haystack);
    for (int i=0;i<matches.size();i++) printf("%d ",matches[i]);
    printf("\n");
    return 0;
}
