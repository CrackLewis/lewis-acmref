#include<bits/stdc++.h>
using namespace std;

// Implementation based on adjacency linklist.
template<typename WeTy=int>
struct graph1
{
  vector<int> head,to,nxt;
  vector<WeTy> we;
  int n,eid;
  graph1(int _n):n(_n),head(_n+1,-1),eid(-1){}
  void addedge(int u,int v,WeTy w=WeTy())
  {
    assert((u<=n&&v<=n)&&"vertex out of range");
    to.emplace_back(v);
    nxt.emplace_back(head[u]);
    we.emplace_back(w);
    head[u]=++eid;
  }
};