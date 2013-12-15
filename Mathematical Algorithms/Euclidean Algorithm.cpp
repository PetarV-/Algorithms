/*
 Petar 'PetarV' Velickovic
 Algorithm: Euclidean Algorithm
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

//Euklidov algoritam za racunanje najveceg zajednickog delioca (NZD) dva broja
//Slozenost: O(log^2 N)

int gcd(int a, int b)
{
    if (a%b == 0) return b;
    return gcd(b,a%b);
}

int main()
{
    printf("%d\n",gcd(6,15));
    return 0;
}
