#include<iostream>
#include<vector>
#include<functional>
#include<utility>
#include<cassert>
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
    assert((u>=1&&v>=1&&u<=n&&v<=n)&&"vertex out of range");
    to.emplace_back(v);
    nxt.emplace_back(head[u]);
    we.emplace_back(w);
    head[u]=++eid;
  }

  /**
   * Tree Centroid Algorithm
   * 
   * The centroid of a tree is the node with the minimum value of its maximum subtree size.
   * A tree could have up to 2 centroids.
   * 
   * if the second element is 0, then only the first element is the valid centroid.
   * 
   * Test: POJ1655
   */
  pair<int,int> centroid()
  {
    //sz(x): size of the subtree of x-th node
    //weight(x): the biggest value of all subtrees
    vector<int> sz(n+1,0),weight(n+1,0);
    int centroid[2]={0,0};

    function<void(int,int)> centroid_dfs=[&](int u,int fa)
    {
      sz[u]=1,weight[u]=0;
      for(int j=head[u],v;~j;j=nxt[j])
      {
        if((v=to[j])==fa) continue;
        centroid_dfs(v,u);
        sz[u]+=sz[v],weight[u]=max(weight[u],sz[v]);
      }
      //the subtree up-above also counts
      weight[u]=max(weight[u],n-sz[u]);
      if(weight[u]<=n/2) 
        centroid[!!(centroid[0]!=0)]=u;
    };
    centroid_dfs(1,0);
    return make_pair(centroid[0],centroid[1]);
  }
};