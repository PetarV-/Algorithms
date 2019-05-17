#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> g;
vector<bool> v;
void addEdge(int a, int b)
{
 g[a].push_back(b);
 //add g[b].push_back(a); for undirected graph
}
void bfs(int u)
{
 queue<int> q;
 q.push(u);
 v[u]=true;
 
 while(!q.empty())
 {
  int f=q.front();
  q.pop();
  cout << f << endl;
  
  for(auto i=g[f].begin() ; i!=g[f].end() ;i++ )
      {
   if(!v[*i])
   {
    q.push(*i);
    v[*i]=true;
   }
      }
       
 }
 
}
int main()
{
 int n=5;
 v.assign(n,false); // initializing vaiables
 g.assign(n,vector<int> ());
 
 addEdge(0,1);// adding edges
 addEdge(1,2);
 addEdge(1,3);
 addEdge(1,4);
 addEdge(0,4);
 
 for(int i=0 ;i<n; i++)// iterating over all vertices
 {
   if(!v[i])
   {
       bfs(i);
   }
 }
 
}
