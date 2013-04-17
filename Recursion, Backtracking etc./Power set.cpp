/*
 Petar 'PetarV' Velickovic
 Algorithm: Power Set
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

//Metoda koja generise partitivni skup nekog skupa
//Slozenost O(2^n)

int n;
int set[100];
vector<vector<int> > pSet;

void powerSet(int pos, vector<int> curr;)
{
     if (pos==n) pSet.push_back(curr);
     recurse(pos+1,curr);
     curr.push_back(set[pos]);
     recurse(pos+1,curr);
}
