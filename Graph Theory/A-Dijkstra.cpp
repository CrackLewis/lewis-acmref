// Implementation based on adjacency linklist.
template<typename WeTy=int>
struct graph1
{
  /* Refer to @-Graph Definition */

  //You should always ignore dis[0] and start from dis[1].
  vector<WeTy> dijkstra(int rt)
  {
    assert(rt<=n&&"vertex out of range");
    vector<bool> vis(n+1,false);
    //Its assumed here that the maximum distance doesnt exceed INT_MAX.
    //Might need to be modified in specific problems.
    vector<WeTy> dis(n+1,WeTy(INT_MAX));
    dis[rt]=WeTy();
    priority_queue<pair<WeTy,int>> Q;
    Q.push(make_pair(-dis[rt],rt));
    while(Q.size())
    {
      auto now=Q.top().second; int v;
      Q.pop();
      if(vis[now]) continue;
      vis[now]=true;
      for(int j=head[now];~j;j=nxt[j])
      {
        v=to[j];
        if(dis[v]>dis[now]+we[j])
        {
          dis[v]=dis[now]+we[j];
          Q.push(make_pair(-dis[v],v));
        }
      }
    }
    return dis;
  }
};