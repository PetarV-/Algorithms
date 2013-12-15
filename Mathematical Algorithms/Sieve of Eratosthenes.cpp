/*
 Petar 'PetarV' Velickovic
 Algorithm: Sieve of Eratosthenes
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

vector<int> primes;
bool mark[MAX_N];

//Algoritam koji izdvaja sve proste brojeve do broja B
//Slozenost: O(N log log N)

inline void sieve(int B)
{
    if (B > 1) primes.push_back(2);
    for (int i=3;i<=B;i+=2)
    {
        if (!mark[i])
        {
            mark[i]=true;
            primes.push_back(i);
            if (i<=sqrt(B)+1)  for (int j=i*i;j<=B;j+=i) mark[j]=true;
        }
    }
}

int main()
{
    sieve(30);
    for (int i=0;i<primes.size();i++) printf("%d\n",primes[i]);
    return 0;
}
