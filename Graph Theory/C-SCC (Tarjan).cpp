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
    assert((u>=1&&v>=1&&u<=n&&v<=n)&&"vertex out of range");
    to.emplace_back(v);
    nxt.emplace_back(head[u]);
    we.emplace_back(w);
    head[u]=++eid;
  }

  vector<int> tarjan()
  {
    int dfn_cnt=0,scc_cnt=0,top=0;
    vector<int> dfn(n+1),low(n+1),stk(n+1),in_stk(n+1);
    vector<int> scc_no(n+1),sz(n+1);

    function<void(int)> tarjan_dfs=[&](int u)
    {
      low[u]=dfn[u]=++dfn_cnt;
      stk[++top]=u,in_stk[u]=1;
      for(int i=head[u],v;~i;i=nxt[i])
      {
        v=to[i];
        if(!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
        else if(in_stk[v]) low[u]=min(low[u],dfn[v]);
      }
      //take all nodes from stack and build SCC
      if(dfn[u]==low[u])
      {
        ++scc_cnt;
        while(stk[top]!=u)
        {
          scc_no[stk[top]]=scc_cnt;
          sz[scc_cnt]++;
          in_stk[stk[top]]=0;
          --top;
        }
        scc_no[stk[top]]=scc_cnt;
        sz[scc_cnt]++;
        in_stk[stk[top]]=0;
        --top;
      }
    };

    for(int i=1;i<=n;++i)
      if(!dfn[i]) tarjan_dfs(i);
    return scc_no;
  }
};