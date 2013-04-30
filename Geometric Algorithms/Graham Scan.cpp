/*
 Petar 'PetarV' Velickovic
 Algorithm: Graham Scan
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
#define INF 987654321
using namespace std;
typedef long long lld;

struct Point
{
    double X, Y;
    Point()
    {
        this->X = this->Y = 0;
    }
    Point(double x, double y)
    {
        this->X = x;
        this->Y = y;
    }
};

int n;
Point P[MAX_N];
Point R;

//Grahamov algoritam za nalazenje konveksnog omotaca datog skupa 2D tacaka
//Slozenost: O(N log N)

inline bool cmp(Point A, Point B)
{
    return atan2(A.Y-R.Y,A.X-R.X) < atan2(B.Y-R.Y,B.X-R.X);
}

inline double CCW(Point a, Point b, Point c)
{
    return ((b.X - a.X) * (c.Y - a.Y) - (b.Y - a.Y) * (c.X - a.X));
}

inline int GrahamScan(vector<Point> &cH)
{
    int min_id = 1;
    for (int i=2;i<=n;i++)
    {
        if (P[i].Y < P[min_id].Y || (P[i].Y == P[min_id].Y && P[i].X < P[min_id].X))
        {
            min_id = i;
        }
    }
    swap(P[1], P[min_id]);
    R = P[1];
    sort(P+2, P+n+1, cmp);
    
    P[0] = P[n];
    int HullSize = 1;
    
    for (int i=2;i<=n;i++)
    {
        while (CCW(P[HullSize-1], P[HullSize], P[i]) <= 0)
        {
            if (HullSize > 1) HullSize--;
            else if (i == n) break;
            else i++;
        }
        swap(P[++HullSize], P[i]);
    }
    
    for (int i=1;i<=HullSize;i++) cH.push_back(P[i]);
    return HullSize;
}

int main()
{
    n = 4;
    
    P[1] = Point(4, 8);
    P[2] = Point(4, 12);
    P[3] = Point(5, 9.3);
    P[4] = Point(7, 8);
    
    vector<Point> cH;
    int m = GrahamScan(cH);
    
    printf("Hull size: %d\n",m);
    for (int i=0;i<m;i++)
    {
        printf("%lf %lf\n",cH[i].X, cH[i].Y);
    }
    
    return 0;
}
