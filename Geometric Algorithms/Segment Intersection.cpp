/*
 Task: Tetris AI
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
#define LIMIT 1000000
using namespace std;
typedef long long lld;
char buffer[LIMIT], * pos = buffer + LIMIT;

inline char getnext(){
    if (pos == buffer + LIMIT){
        pos = buffer;
        fread(buffer, 1, LIMIT, stdin);
    }
    return *pos++;
}

inline int getint()
{
    int num = 0;
    char cc;
    while (!isdigit(cc = getnext()));
    do { num = num * 10 + cc - '0'; } while (isdigit(cc = getnext()));
    return num;
}

int skorr[5] = {1, 4, 10, 15};

int tet[22][12], H[100];
int mat[22][12]/*indeksirana tako da je najdonji red 0 jer mi je bilo puno lakse razmisljati o tetrisu na taj nacin*/,n,k,m,o,a[100],h,x;
int movesX[50001], movesO[50001];
bool phail;

int tetrominos[50001];
bool holeZ[22][12];

clock_t timeZ;
bool tiime = false;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int totalHeight;
int linesCleared;
int holes;
int blockades;
int edgesOnWall;
int edgesOnOtherBlock;
int edgesOnFloor;

bool stored;
double currFunctionVal;
double optFunctionVal;
int storeX, storeO;
int currScore, optScore;

int heightMultiplier;
int lineMultiplier;
int holeMultiplier;
int onFloorMultiplier;
int onEdgeMultiplier;
int onHoleMultiplier;
int onTetMultiplier;

int totalScore = 0;

int t, br;

inline void ispis (void)
{
    cout<<endl<<"+++++++++++++++++++++++"<<endl;
    for (int i=19; i>=0; i--)
    {
        for (int j=0; j<10; j++)
            cout<<mat[i][j];
        cout<<endl;
    }
    cout<<endl;
    for (int i=0; i<10; i++) cout<<a[i]<<" ";
    cout<<endl;
    cout<<endl<<"+++++++++++++++++++++++"<<endl;
    return;
}

inline void clear_row(int id)
{
    for (int j=0;j<10;j++) mat[id][j] = 0;
    for (int i=id+1;i<20;i++)
    {
        for (int j=0;j<10;j++)
        {
            mat[i-1][j] = mat[i][j];
        }
    }
}

inline int delete_rows()
{
    bool ok;
    int ret = 0;
    
    int add = 0;
    
    for (int i=0;i<20;i++)
    {
        ok = true;
        while (ok)
        {
            for (int j=0;j<10;j++)
            {
                if (mat[i][j] == 0)
                {
                    ok = false;
                    break;
                }
            }
            if (ok)
            {
                clear_row(i);
                ret+=skorr[add];
                if (add < 3) add++;
            }
            else add = 0;
        }
    }
    return ret;
}

inline void recalculateHeights()
{
    for (int j=0;j<10;j++)
    {
        int ii = 19;
        while (ii >= 0 && mat[ii][j] == 0) ii--;
        a[j] = ++ii;
    }
}

inline int padni (int x, int n, int o, bool test)
{
    for (int i=0;i<20;i++)
    {
        for (int j=0;j<10;j++)
        {
            mat[i][j] = tet[i][j];
        }
    }
    
    for (int i=0;i<10;i++) a[i] = H[i];
    
    vector<pair<int, int> > prom;
    
    if (n == 1)
    {
        if (o > 1) return -1;
        if (o == 0)
        {
            if (x < 0 || x > 6) return -1;
            h = 0;
            for (int i=x; i<x+4; i++)
            {
                h = max(h, a[i]);
            }
            if (h > 10) return -1;
            for (int i=x; i<x+4; i++)
            {
                mat[h][i] = 1;
                prom.push_back(make_pair(h,i));
            }
        }
        else if (o == 1)
        {
            if (x < 0 || x > 9) return -1;
            h = a[x];
            if (h > 10) return -1;
            for (int i=h; i<h+4; i++)
            {
                mat[i][x] = 1;
                prom.push_back(make_pair(i,x));
            }
        }
    }
    
    else if (n == 2)
    {
        if (o == 0)
        {
            if (x < 0 || x > 7) return -1;
            h = 0;
            for (int i=x; i<x+3; i++)
            {
                h = max(h,a[i]);
            }
            if (h > 10) return -1;
            for (int i=x; i<x+3; i++)
            {
                mat[h][i] = 1;
                prom.push_back(make_pair(h,i));
            }
            mat[h+1][x+2] = 1;
            prom.push_back(make_pair(h+1,x+2));
        }
        else if (o == 1)
        {
            if (x < 0 || x > 8) return -1;
            h = max(a[x],a[x+1]);
            if (h > 10) return -1;
            for (int i=h; i<h+3; i++)
            {
                mat[i][x] = 1;
                prom.push_back(make_pair(i,x));
            }
            mat[h][x+1] = 1;
            prom.push_back(make_pair(h,x+1));
        }
        else if (o == 2)
        {
            if (x < 0 || x > 7) return -1;
            h = max(a[x+1]-1,a[x+2]-1);
            h = max(h,a[x]);
            if (h > 10) return -1;
            for (int i=x; i<x+3; i++)
            {
                mat[h+1][i] = 1;
                prom.push_back(make_pair(h+1,i));
            }
            mat[h][x] = 1;
            prom.push_back(make_pair(h,x));
        }
        else if (o == 3)
        {
            if (x < 0 || x > 8) return -1;
            h = max(a[x]-2,a[x+1]);
            if (h > 10) return -1;
            for (int i=h; i<h+3; i++)
            {
                mat[i][x+1] = 1;
                prom.push_back(make_pair(i,x+1));
            }
            mat[h+2][x] = 1;
            prom.push_back(make_pair(h+2,x));
        }
    }
    
    else if (n == 3)
    {
        if (o == 0)
        {
            if (x < 0 || x > 7) return -1;
            h = 0;
            for (int i=x; i<x+3; i++)
            {
                h = max(h,a[i]);
            }
            if (h > 10) return -1;
            for (int i=x; i<x+3; i++)
            {
                mat[h][i] = 1;
                prom.push_back(make_pair(h,i));
            }
            mat[h+1][x] = 1;
            prom.push_back(make_pair(h+1,x));
        }
        else if (o == 1)
        {
            if (x < 0 || x > 8) return -1;
            h = max(a[x],a[x+1]-2);
            if (h > 10) return -1;
            for (int i=h; i<h+3; i++)
            {
                mat[i][x] = 1;
                prom.push_back(make_pair(i,x));
            }
            mat[h+2][x+1] = 1;
            prom.push_back(make_pair(h+2,x+1));
        }
        else if (o == 2)
        {
            if (x < 0 || x > 7) return -1;
            h = max(a[x]-1,a[x+1]-1);
            h = max(h,a[x+2]);
            if (h > 10) return -1;
            for (int i=x; i<x+3; i++)
            {
                mat[h+1][i] = 1;
                prom.push_back(make_pair(h+1,i));
            }
            mat[h][x+2] = 1;
            prom.push_back(make_pair(h,x+2));
        }
        else if (o == 3)
        {
            if (x < 0 || x > 8) return -1;
            h = max(a[x],a[x+1]);
            if (h > 10) return -1;
            for (int i=h; i<h+3; i++)
            {
                mat[i][x+1] = 1;
                prom.push_back(make_pair(i,x+1));
            }
            mat[h][x] = 1;
            prom.push_back(make_pair(h,x));
        }
    }
    
    else if (n == 4)
    {
        if (o > 1) return -1;
        if (o == 0)
        {
            if (x < 0 || x > 7) return -1;
            h = max(max(a[x+2],a[x+1]),a[x]-1);
            if (h > 10) return -1;
            mat[h][x+1] = 1;
            mat[h][x+2] = 1;
            mat[h+1][x] = 1;
            mat[h+1][x+1] = 1;
            prom.push_back(make_pair(h,x+1));
            prom.push_back(make_pair(h,x+2));
            prom.push_back(make_pair(h+1,x));
            prom.push_back(make_pair(h+1,x+1));
        }
        else if (o == 1)
        {
            if (x < 0 || x > 8) return -1;
            h = max(a[x],a[x+1]-1);
            if (h > 10) return -1;
            mat[h][x] = 1;
            mat[h+1][x] = 1;
            mat[h+1][x+1] = 1;
            mat[h+2][x+1] = 1;
            prom.push_back(make_pair(h,x));
            prom.push_back(make_pair(h+1,x));
            prom.push_back(make_pair(h+1,x+1));
            prom.push_back(make_pair(h+2,x+1));
        }
    }
    
    else if (n == 5)
    {
        if (o > 1) return -1;
        if (o == 0)
        {
            if (x < 0 || x > 7) return -1;
            h = max(max(a[x+2]-1,a[x+1]),a[x]);
            if (h > 10) return -1;
            mat[h][x] = 1;
            mat[h][x+1] = 1;
            mat[h+1][x+1] = 1;
            mat[h+1][x+2] = 1;
            prom.push_back(make_pair(h,x));
            prom.push_back(make_pair(h,x+1));
            prom.push_back(make_pair(h+1,x+1));
            prom.push_back(make_pair(h+1,x+2));
        }
        else if (o == 1)
        {
            if (x < 0 || x > 8) return -1;
            h = max(a[x]-1,a[x+1]);
            if (h > 10) return -1;
            mat[h][x+1] = 1;
            mat[h+1][x] = 1;
            mat[h+1][x+1] = 1;
            mat[h+2][x] = 1;
            prom.push_back(make_pair(h,x+1));
            prom.push_back(make_pair(h+1,x));
            prom.push_back(make_pair(h+1,x+1));
            prom.push_back(make_pair(h+2,x));
        }
    }
    
    else if (n == 6)
    {
        if (o > 0) return -1;
        if (x < 0 || x > 8) return -1;
        h = max(a[x],a[x+1]);
        if (h > 17) return -1;
        mat[h][x] = 1;
        mat[h][x+1] = 1;
        mat[h+1][x] = 1;
        mat[h+1][x+1] = 1;
        prom.push_back(make_pair(h,x));
        prom.push_back(make_pair(h,x+1));
        prom.push_back(make_pair(h+1,x));
        prom.push_back(make_pair(h+1,x+1));
    }
    
    linesCleared = delete_rows();
    recalculateHeights();
    
    if (!test)
    {
        for (int i=0;i<20;i++)
        {
            for (int j=0;j<10;j++)
            {
                tet[i][j] = mat[i][j];
            }
        }
        for (int i=0;i<10;i++) H[i] = a[i];
        totalScore += linesCleared;
    }
    
    else
    {
        totalHeight = 0;
        for (int i=0;i<10;i++) totalHeight = max(totalHeight, a[i]);
        //currScore = totalHeight * (-prom.size());
        //currScore += linesCleared*10;
        currScore = totalHeight * heightMultiplier;
        currScore += linesCleared * lineMultiplier;
        
        holes = 0;
        for (int i=0;i<19;i++)
        {
            for (int j=0;j<10;j++)
            {
                holeZ[i][j] = false;
                if (mat[i][j] == 0 && mat[i+1][j] == 1)
                {
                    if (j == 0 || j == 9)
                    {
                        holeZ[i][j] = true;
                        holes++;
                    }
                    else if (mat[i+1][j-1] == 1 || mat[i+1][j+1] == 1)
                    {
                        holeZ[i][j] = true;
                        holes++;
                    }
                }
            }
        }
        
        //currScore -= 15*holes;
        currScore += holes * holeMultiplier;
        
        for (int i=0;i<prom.size();i++)
        {
            int xx = prom[i].first, yy = prom[i].second;
            if (xx == 0) currScore += onFloorMultiplier; //currScore += 2;
            else if (tet[xx-1][yy] == 1) currScore += onTetMultiplier; //currScore += 2;
            else if (mat[xx-1][yy] == 0) currScore += onHoleMultiplier; //currScore -= 10;
            if (yy == 0 || yy == 9) currScore += onEdgeMultiplier; //currScore += 2;
            else
            {
                if (tet[xx][yy-1] == 1) currScore += onTetMultiplier; //currScore += 2;
                if (tet[xx][yy+1] == 1) currScore += onTetMultiplier; //currScore += 2;
            }
        }
        
        if (stored == false || currScore > optScore)
        {
            optScore = currScore;
            storeO = o;
            storeX = x;
            stored = true;
        }
    }
    
    //ispis();
    return 0;
}

inline void debug()
{
    while (1)
    {
        cin>>n>>o>>x;
        cout<<padni(x,n,o,false)<<endl;
    }
}

inline void resetAll()
{
    for (int i=0;i<20;i++)
    {
        for (int j=0;j<10;j++)
        {
            tet[i][j] = 0;
        }
    }
    for (int j=0;j<10;j++) H[j] = 0;
    totalScore = 0;
}

inline int rjesi(int par1, int par2, int par3, int par4, int par5, int par6, int par7)
{
    resetAll();
    heightMultiplier = par1;
    lineMultiplier = par2;
    holeMultiplier = par3;
    onEdgeMultiplier = par4;
    onFloorMultiplier = par5;
    onTetMultiplier = par6;
    onHoleMultiplier = par7;
    
    totalScore = 0;
    
    for (int ii=0;ii<br;ii++)
    {
        stored = false;
        if (phail) break;
        for (int i=0;i<10;i++)
        {
            for (int j=0;j<4;j++)
            {
                padni(i, tetrominos[ii], j, true);
            }
        }
        if (!stored)
        {
            phail = true;
            continue;
        }
        padni(storeX, tetrominos[ii], storeO, false);
        movesO[ii] = storeO;
        movesX[ii] = storeX + 1;
    }
    if (phail)
    {
        printf("case 1 N\n");
        return -1;
    }
    else
    {
        printf("case 1 Y\n");
        for (int i=0;i<br;i++)
        {
            printf("%d %d\n",movesO[i], movesX[i]);
        }
        return totalScore;
    }
}

int main()
{
    //debug();
    //timeZ = clock();
    //scanf("%d",&t);
    t = getint();
    while (t--)
    {
        resetAll();
        //scanf("%d",&br);
        br = getint();
        phail = false;
        for (int i=0;i<br;i++)
        {
            //scanf("%d",&tetrominos[i]);
            tetrominos[i] = getint();
        }
        rjesi(-5, 10, -15, 2, 2, 2, -10);
    }
    return 0;
}