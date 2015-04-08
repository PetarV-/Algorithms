/*
 Petar 'PetarV' Velickovic
 Algorithm: Segmented Least Squares (Microchallenge)
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
#define MAX_N 501
using namespace std;
typedef long long lld;

/*
 Algorithm for calculating the minimal cost of approximating a set of points with segments
 
 The cost of a particular set of segments is calculated as sum(i=1 -> n) E_i + c*L,
 where E_i is the error of the i-th point WRT its segment,
 c the cost of each segment,
 and L the amount of segments used
 
 Input: Set of points (from file) + Cost of each segment (from command line)
 Returns: The minimal cost (to command line) + segments used (to file)
 Complexity: O(n^2) time, O(n^2) memory
*/

int n = 1, c;

struct Point
{
    int x, y;
    bool operator <(const Point &p) const
    {
        return (x < p.x);
    }
};
Point pts[MAX_N];

double err[MAX_N][MAX_N]; //err[i][j] - total error by approximating points [i..j] by a segment
double a[MAX_N][MAX_N]; //a[i][j] - the slope of the segment used to approximate points [i..j]
double b[MAX_N][MAX_N]; //b[i][j] - the y-intercept of the segment used to approximate points [i..j]

int xySums[MAX_N], xSums[MAX_N], ySums[MAX_N], xSqrSums[MAX_N], ySqrSums[MAX_N]; //prefix sums for x_i * y_i, x_i, y_i, x_i * x_i and y_i * y_i

double minCost[MAX_N]; //minCost[j] - optimal cost for points [1..j]
int retIndex[MAX_N]; //the last segment in the optimal case for points [1..j] is [retIndex[j], j]

struct Segment
{
    double x1, y1, x2, y2;
    Segment()
    {
        this->x1 = 0;
        this->y1 = 0;
        this->x2 = 0;
        this->y2 = 0;
    }
    Segment(double x1, double y1, double x2, double y2)
    {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }
};
vector<Segment> ret; //final solution

inline void Precalculate()
{
    sort(pts+1, pts+n+1); //can be omitted if points are guaranteed to be given in ascending X order
    
    for (int i=1;i<=n;i++)
    {
        xSums[i] = xSums[i-1] + pts[i].x;
        ySums[i] = ySums[i-1] + pts[i].y;
        xSqrSums[i] = xSqrSums[i-1] + pts[i].x * pts[i].x;
        xySums[i] = xySums[i-1] + pts[i].x * pts[i].y;
        ySqrSums[i] = ySqrSums[i-1] + pts[i].y * pts[i].y;
    }
    
    for (int i=1;i<=n;i++)
    {
        for (int j=i+1;j<=n;j++)
        {
            int nn = j - i + 1;
            int xySum = xySums[j] - xySums[i-1];
            int xSum = xSums[j] - xSums[i-1];
            int ySum = ySums[j] - ySums[i-1];
            int xSqrSum = xSqrSums[j] - xSqrSums[i-1];
            int ySqrSum = ySqrSums[j] - ySqrSums[i-1];
            
            a[i][j] = ((nn * xySum - xSum * ySum) * 1.0) / ((nn * xSqrSum - xSum * xSum) * 1.0);
            b[i][j] = ((ySum - a[i][j] * xSum) * 1.0) / (nn * 1.0);
            
            err[i][j] = a[i][j] * a[i][j] * xSqrSum + 2.0 * a[i][j] * b[i][j] * xSum - 2.0 * a[i][j] * xySum + nn * b[i][j] * b[i][j] - 2.0 * b[i][j] * ySum + ySqrSum;
        }
    }
}

inline double SegmentedLeastSquares()
{
    for (int j=1;j<=n;j++)
    {
        minCost[j] = err[1][j] + c;
        retIndex[j] = 1;
        
        for (int i=2;i<=j;i++)
        {
            if (minCost[i-1] + err[i][j] + c < minCost[j])
            {
                minCost[j] = minCost[i-1] + err[i][j] + c;
                retIndex[j] = i;
            }
        }
    }
    
    return minCost[n];
}

inline void getSegments()
{
    stack<Segment> S;
    int currInd = n;
    while (currInd > 1)
    {
        int nextInd = retIndex[currInd];
        if (nextInd == currInd)
        {
            S.push(Segment(pts[currInd-1].x, pts[currInd-1].y, pts[currInd].x, pts[currInd].y));
        }
        else
        {
            double x1 = pts[nextInd].x;
            double y1 = x1 * a[nextInd][currInd] + b[nextInd][currInd];
            double x2 = pts[currInd].x;
            double y2 = x2 * a[nextInd][currInd] + b[nextInd][currInd];
            S.push(Segment(x1, y1, x2, y2));
        }
        currInd = nextInd - 1;
    }
    while (!S.empty())
    {
        ret.push_back(S.top());
        S.pop();
    }
}

int main(int argc, char **argv)
{
    sscanf(argv[1],"%d",&c);
    freopen("/Users/PetarV/.makedots","r",stdin);
    while (scanf("%d%d",&pts[n].x,&pts[n].y) == 2) n++;
    n--;
    Precalculate();
    printf("%.10lf\n",SegmentedLeastSquares());
    freopen("/Users/PetarV/.makedots-segments","w",stdout);
    getSegments();
    for (int i=0;i<ret.size();i++)
    {
        printf("%d %d %d %d\n",(int)ret[i].x1, (int)ret[i].y1, (int)ret[i].x2, (int)ret[i].y2);
    }
    return 0;
}
