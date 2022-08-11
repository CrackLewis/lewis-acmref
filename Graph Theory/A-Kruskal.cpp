// Implementation based on adjacency linklist.
template<typename WeTy=int>
struct graph1
{
  /* Refer to @-Graph Definition */

  // Minimum spanning tree - Kruskal Algorithm
  // Tell if an MST exists by checking if krus_ans==n-1.
  WeTy krus_wesum; int krus_ans;
  using KEDGE=tuple<int,int,WeTy>;
  graph1<WeTy> mst_kruskal()
  {
    //union-find set
    vector<int> fa(n+1);
    for(int i=1;i<=n;++i) fa[i]=i;
    function<int(int)> find=[&](int x){return fa[x]==x?x:(fa[x]=find(fa[x]));};
    auto merge=[&](int x,int y){x=find(x),y=find(y);if(x!=y)fa[x]=y;};
    
    auto edgecomp=[](const KEDGE& lhs,const KEDGE& rhs){return get<2>(lhs)<get<2>(rhs); };
    vector<KEDGE> krue;
    //convert edges to sortable edges
    for(int i=1;i<=n;++i)
      for(int j=head[i];~j;j=nxt[j]) krue.emplace_back(make_tuple(i,to[j],we[j]));
    sort(krue.begin(),krue.end(),edgecomp);

    graph1<WeTy> ans(n); int u,v; WeTy w;
    krus_wesum=WeTy(),krus_ans=0;
    for(auto& e:krue)
    {
      u=get<0>(e),v=get<1>(e),w=get<2>(e);
      if(find(u)==find(v)) continue;
      merge(u,v);
      krus_ans++,krus_wesum+=w;
      // It's assumed that exporting graph is undirected.
      // Might need modification in specific problems.
      ans.addedge(u,v,w),ans.addedge(v,u,w);
    }
    return ans;
  }
};