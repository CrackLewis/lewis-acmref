// Implementation based on adjacency linklist.
template<typename WeTy=int>
struct graph1
{
  /* Refer to @-Graph Definition */

  // Toposort Algorithm
  // This algorithm relies topo_res as an appendice output.
  // Check the return value of toposort(), if it's true, refer to topo_res.
  vector<int> topo_res;
  bool toposort()
  {
    vector<int> flag(n+1,0);
    topo_res.clear();
    function<bool(int)> topo_dfs=[&](int u)
    {
      flag[u]=-1;
      for(int j=head[u],v;~j;j=nxt[j])
      {
        v=to[j];
        if(flag[v]<0) return false;
        else if(!flag[v]) if(!topo_dfs(v)) return false;
      }
      flag[u]=1;
      topo_res.emplace_back(u);
      return true;
    };
    for(int i=1;i<=n;++i)
      if(!flag[i]) if(!topo_dfs(i)) return false;
    reverse(topo_res.begin(),topo_res.end());
    return true;
  }
};