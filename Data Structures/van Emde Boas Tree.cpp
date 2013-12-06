/*
 Petar 'PetarV' Velickovic
 Data Structure: van Emde Boas Tree (vEB)
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
 van Emde Boas Tree structure for holding a set of integers in a given universe.
 Complexity:    O(1) for min, max and first
                O(log log u) for member, insert, delete, pred, succ, extractMin and decreaseKey
*/

class vEB
{
    llu u;
    
    llu *m, *M;
    vEB *summary;   // used if u != 2
    vEB **cluster;  // used if u != 2
    
public:
    vEB(llu);
    
    bool member(llu);
    void insert(llu);
    void Delete(llu);
    llu min();
    llu max();
    llu* pred(llu);
    llu* succ(llu);
    
    llu extractMin();
    llu first();
    void decreaseKey(llu, llu);
};

vEB::vEB(llu u)
{
    this -> u = u;
    this -> m = NULL;
    this -> M = NULL;
    
    if (u == 2)
    {
        this -> summary = NULL;
        this -> cluster = NULL;
    }
    
    else
    {
        llu subSize = (llu)sqrt(u);
        this -> summary = new vEB(subSize);
        this -> cluster = new vEB*[subSize];
    }
}

bool vEB::member(llu x)
{
    if (u == 2)
    {
        if (m == NULL) return false;
        if (x == 0) return ((*m) == 0);
        else if (x == 1) return ((*M) == 1);
        return false;
    }
    else
    {
        if (m == NULL) return false;
        if (x < (*m) || x > (*M)) return false;
        else if (x == (*m) || (x == (*M))) return true;
        else
        {
            llu subSize = (llu)sqrt(u);
            llu hi = x / subSize, lo = x % subSize;
            if (cluster[hi] == NULL) return false;
            else return cluster[hi] -> member(lo);
        }

    }
}

void vEB::insert(llu x)
{
    if (u == 2)
    {
        if (x == 0)
        {
            if (m == NULL)
            {
                m = new llu;
                M = new llu;
                (*m) = (*M) = x;
            }
            else (*m) = x;
        }
        else if (x == 1)
        {
            if (M == NULL)
            {
                m = new llu;
                M = new llu;
                (*m) = (*M) = x;
            }
            else (*M) = x;
        }
    }
    else
    {
        if (m == NULL)
        {
            m = new llu;
            M = new llu;
            (*m) = (*M) = x;
        }
        else
        {
            if (x < (*m))
            {
                llu currMin = (*m);
                (*m) = x;
                this -> insert(currMin);
            }
            else
            {
                llu subSize = (llu)sqrt(u);
                llu hi = x / subSize, lo = x % subSize;
                if (cluster[hi] == NULL)
                {
                    cluster[hi] = new vEB(subSize);
                    cluster[hi] -> insert(lo);
                    summary -> insert(hi);
                }
                else cluster[hi] -> insert(lo);
                
                if (x > (*M)) (*M) = x;
            }
        }
    }
}

void vEB::Delete(llu x)
{
    if (u == 2)
    {
        if (x == 0)
        {
            if ((*M) == 0)
            {
                m = M = NULL;
            }
            else (*m) = 1;
        }
        else if (x == 1)
        {
            if ((*m) == 1)
            {
                m = M = NULL;
            }
            else (*M) = 0;
        }
    }
    else
    {
        llu subSize = (llu)sqrt(u);
        llu hi = x / subSize, lo = x % subSize;
        
        if (x == (*m))
        {
            if (x == (*M))
            {
                m = M = NULL;
            }
            else
            {
                llu nextMinHi = summary -> min();
                llu nextMinLo = cluster[summary -> min()] -> min();
                llu nextMin = nextMinHi * subSize + nextMinLo;
                this -> Delete(nextMin);
                (*m) = nextMin;
            }
        }
        else
        {
            cluster[hi] -> Delete(lo);
            if (cluster[hi] -> m == NULL)
            {
                summary -> Delete(hi);
                delete cluster[hi];
                cluster[hi] = NULL;
            }
            if (x == (*M))
            {
                if (summary -> m == NULL) (*M) = (*m);
                else
                {
                    llu nextMaxHi = summary -> max();
                    llu nextMaxLo = cluster[summary -> max()] -> max();
                    (*M) = nextMaxHi * subSize + nextMaxLo;
                }
            }
        }
    }
}

llu vEB::min()
{
    return (*m);
}

llu vEB::max()
{
    return (*M);
}

llu* vEB::pred(llu x)
{
    if (u == 2)
    {
        if (x == 0) return NULL;
        else if (x == 1)
        {
            if (m == NULL) return NULL;
            if ((*m) == 1) return NULL;
            return m;
        }
        else return NULL;
    }
    else
    {
        if (m == NULL) return NULL;
        if (x <= (*m)) return NULL;
        if (x > (*M)) return M;
        llu subSize = (llu)sqrt(u);
        llu hi = x / subSize;
        llu lo = x % subSize;
        if (cluster[hi] == NULL)
        {
            llu* prev = summary -> pred(hi);
            llu* ret = new llu;
            (*ret) = (*prev) * subSize + cluster[(*prev)] -> max();
            return ret;
        }
        else
        {
            llu *newLo, *newHi;
            newHi = new llu;
            newLo = new llu;
            (*newHi) = hi;
            llu minInCluster = cluster[hi] -> min();
            if (lo > minInCluster) newLo = cluster[hi] -> pred(lo);
            else
            {
                newHi = summary -> pred(hi);
                (*newLo) = cluster[(*newHi)] -> max();
            }
            llu *ret = new llu;
            (*ret) = (*newHi) * subSize + (*newLo);
            return ret;
        }
    }
}

llu* vEB::succ(llu x)
{
    if (u == 2)
    {
        if (x == 1) return NULL;
        else if (x == 0)
        {
            if (M == NULL) return NULL;
            if ((*M) == 0) return NULL;
            return M;
        }
        else return NULL;
    }
    else
    {
        if (m == NULL) return NULL;
        if (x >= (*M)) return NULL;
        if (x < (*m)) return m;
        llu subSize = (llu)sqrt(u);
        llu hi = x / subSize;
        llu lo = x % subSize;
        if (cluster[hi] == NULL)
        {
            llu* next = summary -> succ(hi);
            llu* ret = new llu;
            (*ret) = (*next) * subSize + cluster[(*next)] -> min();
            return ret;
        }
        else
        {
            llu *newLo, *newHi;
            newHi = new llu;
            newLo = new llu;
            (*newHi) = hi;
            llu maxInCluster = cluster[hi] -> max();
            if (lo < maxInCluster) newLo = cluster[hi] -> succ(lo);
            else
            {
                newHi = summary -> succ(hi);
                (*newLo) = cluster[(*newHi)] -> min();
            }
            llu *ret = new llu;
            (*ret) = (*newHi) * subSize + (*newLo);
            return ret;
        }
    }
}

llu vEB::extractMin()
{
    llu ret = this -> min();
    this -> Delete(ret);
    return ret;
}

llu vEB::first()
{
    return this -> min();
}

void vEB::decreaseKey(llu x, llu y)
{
    // Preconditions: y < x, x is in the tree, y is not in the tree
    
    this -> Delete(x);
    this -> insert(y);
}

int main()
{
    vEB *vEB = new class vEB(16);
    
    vEB -> insert(2);
    vEB -> insert(3);
    vEB -> insert(4);
    vEB -> insert(5);
    vEB -> insert(7);
    vEB -> insert(14);
    vEB -> insert(15);
    
    printf("%llu\n", vEB -> min());
    printf("%llu\n", vEB -> max());
    printf("%llu\n", (*vEB -> pred(9)));
    printf("%llu\n", (*vEB -> succ(9)));
    
    vEB -> Delete(7);
    vEB -> Delete(14);
    
    
    printf("%llu\n", (*vEB -> pred(9)));
    printf("%llu\n", (*vEB -> succ(9)));
    
    return 0;
}