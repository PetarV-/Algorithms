/*
 Petar 'PetarV' Velickovic
 Algorithm: Exponentiation by Squaring
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

//Algoritam za stepenovanje kvadriranjem po datom modulu i za racunanje modularnog inverza (pod uslovom da je modul prost)
//Slozenost O(log N)

inline lld mod_pow(lld num, lld pow, lld mod)
{
    lld ret = 1;
    while (pow)
    {  
        if (pow&1)
        {
            ret = (ret*num)%mod;
        }
        pow>>=1;
        num = (num*num)%mod;
    }
    return ret;
}

inline lld mod_inv(lld num, lld mod)
{
    return mod_pow(num, mod-2, mod);
}

int main()
{
    printf("%lld\n",mod_pow(5,2,10));
    printf("%lld\n",mod_inv(1423,13));
    return 0;
}
