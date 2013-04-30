/*
 Petar 'PetarV' Velickovic
 Algorithm: Segment Intersection
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

struct Point
{
    double X, Y;
    Point(double x, double y)
    {
        this->X = x;
        this->Y = y;
    }
};

//Algoritam koji odredjuje da li postoji presek izmedju dve 2D duzi (AB i CD)
//Slozenost: O(1)

inline double crossProduct(Point a, Point b, Point c)
{
    return ((b.X - a.X) * (c.Y - a.Y) - (b.Y - a.Y) * (c.X - a.X));
}

inline bool isLeft(Point a, Point b, Point c)
{
    return (crossProduct(a, b, c) > 0);
}

inline bool isCollinear(Point a, Point b, Point c)
{
    return (crossProduct(a, b, c) == 0);
}

inline bool oppositeSides(Point a, Point b, Point c, Point d)
{
    return (isLeft(a, b, c) != isLeft(a, b, d));
}

inline bool isBetween(Point a, Point b, Point c)
{
    return (min(a.X, b.X) <= c.X && c.X <= max(a.X, b.X) && min(a.Y, b.Y) <= c.Y && c.Y <= max(a.Y,b.Y));
}

inline bool intersect(Point a, Point b, Point c, Point d)
{
    if (isCollinear(a, b, c) && isBetween(a, b, c)) return true;
    if (isCollinear(a, b, d) && isBetween(a, b, d)) return true;
    if (isCollinear(c, d, a) && isBetween(c, d, a)) return true;
    if (isCollinear(c, d, b) && isBetween(c, d, b)) return true;
    return (oppositeSides(a, b, c, d) && oppositeSides(c, d, a, b));
}

int main()
{
    Point A(0.0, 0.0), B(0.0, 2.0), C(-1.0, 2.0), D(1.0, 2.0);
    printf(intersect(A,B,C,D) ? "YES" : "NO");
    printf("\n");
    return 0;
}
