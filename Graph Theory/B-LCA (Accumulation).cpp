// Implementation based on adjacency linklist.
template<typename WeTy=int>
struct graph1
{
  /* Refer to @-Graph Definition */

  /**
   * A Solution to LCA problem - Accumulation
   * Invoke lca_init(int) first, then for each query, invoke lca_query(u,v) for results.
   */

  // base-2 logarithm array
  // if there're multiple graphs, consider modifying Log to be a global array object.
  vector<int> Log;
  // anc: LCA cheatsheet
  // Assumed that N<=2^22=4194304. Might need modification in specific problems.
  const static int lca_maxd=23;
  vector<int> anc[lca_maxd],dep;int lca_inited=0;
  void lca_init(int rt)
  {
    assert((rt>=1&&rt<=n)&&"vertex out of range");
    lca_inited=1;
    
    //resize Log array to fit in
    Log.resize(n+1,0);
    for(int i=1;i<=n;++i)
      Log[i]=Log[i-1]+((1<<Log[i-1])==i);
    //initialize anc,dep
    for(int i=0;i<lca_maxd;++i) anc[i].resize(n+1,0);
    dep.resize(n+1,0);
    //dfs
    function<void(int,int)> lca_dfs=[&](int u,int fa)
    {
      anc[0][u]=fa,dep[u]=dep[fa]+1;
      for(int i=1,_i=Log[dep[u]];i<=_i;++i) anc[i][u]=anc[i-1][anc[i-1][u]];
      for(int j=head[u];~j;j=nxt[j])
        if(to[j]!=fa) lca_dfs(to[j],u);
    };
    lca_dfs(rt,0);
  }
  int lca_query(int x,int y)
  {
    assert(lca_inited&&"lca not inited");
    if(dep[x]<dep[y]) swap(x,y);
    while(dep[x]>dep[y]) x=anc[Log[dep[x]-dep[y]]-1][x];
    if(x==y) return x;
    for(int k=Log[dep[x]]-1;k>=0;--k)
      if(anc[k][x]!=anc[k][y]) x=anc[k][x],y=anc[k][y];
    return anc[0][x];
  }
};