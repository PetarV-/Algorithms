/*
 Petar 'PetarV' Velickovic
 Algorithm: Extended Euclidean Algorithm
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>
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

typedef long long lld;
typedef unsigned long long llu;
using namespace std;

/*
 The Extended Euclidean Algorithm, similarly to its basic variant,
 calculates the Greatest Common Divisor (GCD) of two integers, a and b.
 However, it also computes two integers, x and y, such that a*x + b*y = gcd(a, b).
 
 This is the preferred method for calculating the modular inverse of a number,
 as well as partitioning an integer into subgroups (as per the Chinese Remainder Theorem).
 
 Complexity:    O(log N)
*/

inline pair<lld, pair<lld, lld> > egcd(lld a, lld b)
{
    lld aa = 1, ab = 0, ba = 0, bb = 1;
    while (true)
    {
        lld q = a / b;
        if (a == b * q) return make_pair(b, make_pair(ba, bb));
        lld tmp_a = a;
        lld tmp_aa = aa;
        lld tmp_ab = ab;
        a = b;
        b = tmp_a - b * q;
        aa = ba;
        ab = bb;
        ba = tmp_aa - ba * q;
        bb = tmp_ab - bb * q;
    }
}

inline lld modinv(lld a, lld b)
{
    lld b0 = b;
    lld aa = 1, ba = 0;
    while (true)
    {
        lld q = a / b;
        if (a == b * q)
        {
            if (b != 1)
            {
                // Modular inverse does not exist!
                return -1;
            }
            while (ba < 0) ba += b0;
            return ba;
        }
        lld tmp_a = a;
        lld tmp_aa = aa;
        a = b;
        b = tmp_a - b * q;
        aa = ba;
        ba = tmp_aa - ba * q;
    }
}

int main()
{
    lld a = 2250, b = 360;
    pair<lld, pair<lld, lld> > ret = egcd(a, b);
    printf("gcd(%lld, %lld) = %lld = %lld * %lld + %lld * %lld\n", a, b, ret.first, a, ret.second.first, b, ret.second.second);
    
    a = 806515533049393LL, b = 1304969544928657LL;
    lld inv = modinv(a, b);
    printf("modinv(%lld, %lld) = %lld\n", a, b, inv);
    
    a = 4505490, b = 7290036;
    inv = modinv(a, b);
    printf("modinv(%lld, %lld) = %lld\n", a, b, inv);
    
    return 0;
}
