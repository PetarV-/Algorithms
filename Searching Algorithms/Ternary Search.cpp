/*
 Petar 'PetarV' Velickovic
 Algorithm: Ternary Search
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
#define EPS 1e-12
using namespace std;
typedef long long lld;

//Ternarna pretraga maksimuma/minimuma funkcije koja menja monotonost najviše jednom
//Slozenost: O(log n)

inline double f(double x)
{
    return x*x + x - 1;
}

inline double ter_search(double left, double right)
{
    if (right - left < EPS) return (left+right)/2.0;
    double leftThird = (2.0*left + right)/3.0;
    double rightThird = (left + 2.0*right)/3.0;
    if (f(leftThird) > f(rightThird)) return ter_search(leftThird, right);
    else return ter_search(left, rightThird);
}

int main()
{
    printf("%.6lf\n",ter_search(-5.0, 1.0));
    return 0;
}
