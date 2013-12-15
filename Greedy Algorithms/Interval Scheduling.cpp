/*
 Petar 'PetarV' Velickovic
 Algorithm: Interval Scheduling
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
#define MAX_N 100001
using namespace std;
typedef long long lld;

int n;

struct Interval
{
    int L, R;
    bool operator <(const Interval &a) const
    {
        if (R != a.R) return (R < a.R);
        return (L < a.L);
    }
};
Interval I[MAX_N];

//Algoritam koji odredjuje maksimalan broj disjunktnih intervala iz nekog skupa
//Slozenost: O(n log n)

inline int ScheduleIntervals()
{
    sort(I, I+n);
    
    int ret = 1;
    int currentEnd = I[0].R;
    
    for (int i=1;i<n;i++)
    {
        if (I[i].L >= currentEnd)
        {
            currentEnd = I[i].R;
            ret++;
        }
    }
    
    return ret;
}

int main()
{
    n = 4;
    
    I[0].L = -1, I[0].R = 1;
    I[1].L = 0, I[1].R = 5;
    I[2].L = 2, I[2].R = 3;
    I[3].L = 5, I[3].R = 9;
    
    printf("%d\n",ScheduleIntervals());
    return 0;
}
