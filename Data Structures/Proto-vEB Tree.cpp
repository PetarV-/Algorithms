/*
 Petar 'PetarV' Velickovic
 Data Structure: Proto-vEB Tree
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
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
typedef unsigned long long llu;

/*
 Proto-vEB Tree structure for holding a set of integers in a given universe.
 Complexity:    O(log log u) for member
                O(log u) for insert, delete, min, max, extractMin, first and decreaseKey
                O(log u log log u) for pred, succ
*/

class Proto_vEBTree
{
    llu u;
    Proto_vEBTree *summary; // used if u != 2
    Proto_vEBTree **cluster; // used if u != 2
    
    bool low, high; // used only when u == 2
    int n; // alternative for speeding up proto-vEB-Delete
public:
    Proto_vEBTree(llu);
    
    bool member(llu);
    bool insert(llu);
    bool Delete(llu);
    llu min();
    llu max();
    llu pred(llu);
    llu succ(llu);
    
    llu extractMin();
    llu first();
    void decreaseKey(llu, llu);
};

Proto_vEBTree::Proto_vEBTree(llu u)
{
    this -> u = u;
    this -> n = 0;
    if (u == 2)
    {
        this -> low = this -> high = false;
        this -> summary = NULL;
        this -> cluster = NULL;
    }
    else
    {
        llu subSize = (llu)sqrt(u);
        this -> summary = new Proto_vEBTree(subSize);
        this -> cluster = new Proto_vEBTree*[subSize];
    }
}

bool Proto_vEBTree::member(llu x)
{
    if (u == 2)
    {
        if (x == 0) return low;
        else if (x == 1) return high;
        return false;
    }
    else
    {
        llu subSize = (llu)sqrt(u);
        llu hi = x / subSize, lo = x % subSize;
        if (cluster[hi] == NULL) return false;
        else return cluster[hi] -> member(lo);
    }
}

bool Proto_vEBTree::insert(llu x)
{
    if (u == 2)
    {
        if (x == 0)
        {
            if (low) return false;
            low = true;
            n++;
            return true;
        }
        else if (x == 1)
        {
            if (high) return false;
            high = true;
            n++;
            return true;
        }
        else throw -1;
    }
    else
    {
        llu subSize = (llu)sqrt(u);
        llu hi = x / subSize, lo = x % subSize;
        if (cluster[hi] == NULL)
        {
            cluster[hi] = new Proto_vEBTree(subSize);
            cluster[hi] -> insert(lo);
            n++;
            summary -> insert(hi);
            return true;
        }
        else return cluster[hi] -> insert(lo);
    }
}

bool Proto_vEBTree::Delete(llu x)
{
    if (u == 2)
    {
        if (x == 0)
        {
            low = false;
            n--;
            return !high;
        }
        else if (x == 1)
        {
            high = false;
            n--;
            return !low;
        }
        else throw -1;
    }
    else
    {
        llu subSize = (llu)sqrt(u);
        llu hi = x / subSize, lo = x % subSize;
        if (cluster[hi] -> Delete(lo))
        {
            delete cluster[hi];
            cluster[hi] = NULL;
            n--;
            if (n == 0)
            {
                summary -> Delete(hi);
                return true;
            }
            return false;
        }
        return false;
    }
}

llu Proto_vEBTree::min()
{
    if (u == 2)
    {
        if (low) return 0;
        else if (high) return 1;
        else throw -1; // Proto-vEB is empty
    }
    else
    {
        llu subSize = (llu)sqrt(u);
        llu hi = summary -> min();
        llu lo = cluster[hi] -> min();
        return hi * subSize + lo;
    }
}

llu Proto_vEBTree::max()
{
    if (u == 2)
    {
        if (high) return 1;
        else if (low) return 0;
        else throw -1; // Proto-vEB is empty
    }
    else
    {
        llu subSize = (llu)sqrt(u);
        llu hi = summary -> max();
        llu lo = cluster[hi] -> max();
        return hi * subSize + lo;
    }
}

llu Proto_vEBTree::pred(llu x)
{
    if (u == 2)
    {
        if (x == 1 && low) return 0;
        else throw -1; // Predecessor does not exist
    }
    else
    {
        llu subSize = (llu)sqrt(u);
        llu hi = x / subSize;
        llu lo = x % subSize;
        if (cluster[hi] == NULL)
        {
            llu prev = summary -> pred(hi);
            return prev * subSize + cluster[prev] -> max();
        }
        else
        {
            llu newLo, newHi = hi;
            try
            {
                newLo = cluster[hi] -> pred(lo);
            }
            catch (int e)
            {
                newHi = summary -> pred(hi);
                newLo = cluster[newHi] -> max();
            }
            return newHi * subSize + newLo;
        }
    }
}

llu Proto_vEBTree::succ(llu x)
{
    if (u == 2)
    {
        if (x == 0 && high) return 1;
        else throw -1; // Successor does not exist
    }
    else
    {
        llu subSize = (llu)sqrt(u);
        llu hi = x / subSize;
        llu lo = x % subSize;
        if (cluster[hi] == NULL)
        {
            llu next = summary -> succ(hi);
            return next * subSize + cluster[next] -> min();
        }
        else
        {
            llu newLo, newHi = hi;
            try
            {
                newLo = cluster[hi] -> succ(lo);
            }
            catch (int e)
            {
                newHi = summary -> succ(hi);
                newLo = cluster[newHi] -> min();
            }
            return newHi * subSize + newLo;
        }
    }
}

llu Proto_vEBTree::extractMin()
{
    llu ret = this -> min();
    this -> Delete(ret);
    return ret;
}

llu Proto_vEBTree::first()
{
    return this -> min();
}

void Proto_vEBTree::decreaseKey(llu x, llu y)
{
    // Preconditions: y < x, x is in the tree, y is not in the tree
    
    this -> Delete(x);
    this -> insert(y);
}

int main()
{
    Proto_vEBTree *vEB = new Proto_vEBTree(16);
    vEB -> insert(2);
    vEB -> insert(3);
    vEB -> insert(4);
    vEB -> insert(5);
    vEB -> insert(7);
    vEB -> insert(14);
    vEB -> insert(15);
    printf("%llu\n", vEB -> min());
    printf("%llu\n", vEB -> max());
    printf("%llu\n", vEB -> pred(9));
    printf("%llu\n", vEB -> succ(9));
    return 0;
}

