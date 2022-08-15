// Implementation based on adjacency linklist.
template<typename WeTy=int>
struct graph1
{
  /* Refer to @-Graph Definition */

  /**
   * A Solution to LCA problem - Tarjan (LCA)
   * 
   * This is an *** OFF-LINE *** algorithm which constructs all queries into
   * a graph and relies on union-find set to solve LCA problem.
   * 
   * Refer to returning value for answer.
   */

  vector<int> lca_tarjan(int rt,const vector<pair<int,int>>& queries)
  {
    //construct a "query graph" connecting each query pairs of nodes
    graph1<int> QG(n);
    for(const auto& q:queries) 
      QG.addedge(q.first,q.second),QG.addedge(q.second,q.first);
    //union-find set
    vector<int> fa(n+1,0),vis(n+1,0),lca(queries.size(),0);
    for(int i=1;i<=n;++i) fa[i]=i;
    function<int(int)> find=[&](int x){ return fa[x]==x?x:(fa[x]=find(fa[x])); };

    function<void(int)> tarjan_dfs=[&](int u)
    {
      fa[u]=u,vis[u]=1;
      //DFS on all edges
      for(int j=head[u],v;~j;j=nxt[j])
      {
        if(!vis[v=to[j]])
          tarjan_dfs(v),fa[v]=u;
      }
      //calc ans to adjacent queries
      for(int j=QG.head[u],v;~j;j=QG.nxt[j])
      {
        if(vis[v=QG.to[j]])
          lca[j>>1]=find(v);
      }
    };
    tarjan_dfs(rt);
    return lca;
  }
};