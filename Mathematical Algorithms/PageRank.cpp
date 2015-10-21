/*
 Petar 'PetarV' Velickovic
 Algorithm: PageRank
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
#include <iomanip>
#include <numeric>

#define DPRINTC(C) printf(#C " = %c\n", (C))
#define DPRINTS(S) printf(#S " = %s\n", (S))
#define DPRINTD(D) printf(#D " = %d\n", (D))
#define DPRINTLLD(LLD) printf(#LLD " = %lld\n", (LLD))
#define DPRINTLF(LF) printf(#LF " = %.5lf\n", (LF))

using namespace std;
typedef long long lld;
typedef unsigned long long llu;

int n;
vector<vector<int> > edges;

/*
 The PageRank algorithm computes a relevance metric for nodes in a graph,
 by computing a stationary distribution of its corresponding ergodic
 Markov Chain (using the ``easily bored random web surfer'' model).
 
 Complexity: O(V + E) time (per iteration), O(V + E) memory
*/

double sum(double x, double y)
{
    return x + y;
}

double sq_diff(double x, double y)
{
    return (x - y) * (x - y);
}

vector<double> pagerank(double alpha, double epsilon)
{
    // initialise
    vector<double> old_pi(n), pi(n);
    for (int i=0;i<n;i++) pi[i] = 1.0 / n;
    
    int num_iterations = 0;
    
    do
    {
        vector<double> H(n), A(n), I(n);
        for (int i=0;i<n;i++)
        {
            old_pi[i] = pi[i];
            H[i] = A[i] = I[i] = 0.0;
        }
        
        // Compute the separate components of pi
        for (int i=0;i<n;i++)
        {
            for (int j=0;j<edges[i].size();j++)
            {
                H[edges[i][j]] += (1.0 - alpha) * pi[i] / edges[i].size();
            }
            if (edges[i].empty()) A[i] += (1.0 - alpha) / n;
            I[i] += alpha / n;
        }
        
        // Add them up, normalise and print
        double sum = 0.0;
        for (int i=0;i<n;i++)
        {
            pi[i] = H[i] + A[i] + I[i];
            sum += pi[i];
        }
        cout << "Iteration " << ++num_iterations << ": {";
        for (int i=0;i<n;i++)
        {
            pi[i] /= sum;
            cout << pi[i];
            if (i < n - 1) cout << ", ";
            else cout << "}" << endl;
        }
        
        // Stop iterating if the computation has converged enough
    } while (inner_product(pi.begin(), pi.end(), old_pi.begin(), 0.0, sum, sq_diff) > epsilon);
    
    return pi;
}

int main()
{
    n = 7;
    edges.resize(7);
    
    edges[0].push_back(2);
    
    edges[1].push_back(1);
    edges[1].push_back(2);
    
    edges[2].push_back(0);
    edges[2].push_back(2);
    edges[2].push_back(3);
    
    edges[3].push_back(3);
    edges[3].push_back(4);
    
    edges[4].push_back(6);
    
    edges[5].push_back(5);
    edges[5].push_back(6);
    
    edges[6].push_back(3);
    edges[6].push_back(4);
    edges[6].push_back(6);
    
    pagerank(0.1, 1e-6);
    
    return 0;
}
