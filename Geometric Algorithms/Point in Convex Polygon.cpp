/*
 Petar 'PetarV' Velickovic
 Algorithm: Point in Convex Polygon
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

struct Point
{
    double X, Y;
    Point()
    {
        this->X = 0;
        this->Y = 0;
    }
    Point(double x, double y)
    {
        this->X = x;
        this->Y = y;
    }
};

int n;
Point Polygon[MAX_N];

//Algoritam koji odredjuje da li je tacka Q unutar datog konveksnog mnogougla 
//Podrazumeva se da su temena mnogougla data u obrnotum smeru kazaljke na satu
//Moze se lako prosiriti u test preseka dva konveksna mnogougla
//Slozenost: O(log N)

inline int crossProduct(Point a, Point b, Point c)
{
    return ((b.X - a.X) * (c.Y - a.Y) - (b.Y - a.Y) * (c.X - a.X));
}

inline bool isLeft(Point a, Point b, Point c)
{
    return (crossProduct(a, b, c) >= 0);
}

inline bool inTriangle(Point a, Point b, Point c, Point x)
{
    return (isLeft(x,a,b) == isLeft(x,b,c) && isLeft(x,b,c) == isLeft(x,c,a));
}

inline int b_search(int left, int right, Point Q)
{
    int i = left;
    int j = right;
    while (i < j-1)
    {
        int mid = (i+j)/2;
        if (isLeft(Polygon[0], Polygon[mid], Q)) i = mid;
        else j = mid;
    }
    return i;
}

bool inPolygon(Point Q)
{
    int poz = b_search(1, n-1, Q);
    return inTriangle(Polygon[0], Polygon[poz], Polygon[poz+1], Q);
}

int main()
{
    n = 5;
    
    Polygon[0] = Point(150, 108);
    Polygon[1] = Point(250, 103);
    Polygon[2] = Point(289, 169);
    Polygon[3] = Point(240, 237);
    Polygon[4] = Point(120, 195);
    
    printf(inPolygon(Point(179, 185)) ? "YES\n" : "NO\n");
    printf(inPolygon(Point(216, 90)) ? "YES\n" : "NO\n");
    printf(inPolygon(Point(129, 174)) ? "YES\n" : "NO\n");
    
    return 0;
}
