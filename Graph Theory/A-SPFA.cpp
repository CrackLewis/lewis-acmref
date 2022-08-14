// Implementation based on adjacency linklist.
template<typename WeTy=int>
struct graph1
{
  /* Refer to @-Graph Definition */

  // Negative loop flag.
  // If this is set to true, then rt-th node is connected to a negative-sum
  // loop in the graph.
  bool sig_spfa_negflag;
  vector<WeTy> spfa(int rt)
  {
    assert((rt>=1&&rt<=n)&&"vertex out of range");
    //Its assumed here that the maximum distance doesnt exceed INT_MAX.
    //Might need to be modified in specific problems.
    vector<WeTy> dis(n+1,WeTy(INT_MAX));
    vector<bool> vis(n+1,false);
    vector<int> cnt(n+1,0);
    queue<int> Q;
    sig_spfa_negflag=false;

    dis[rt]=WeTy(),vis[rt]=true;
    Q.push(rt);

    int v,now; WeTy w;
    while(Q.size())
    {
      now=Q.front();Q.pop();
      vis[now]=false;
      for(int j=head[now];~j;j=nxt[j])
      {
        v=to[j],w=we[j];
        if(dis[v]>dis[now]+w)
        {
          dis[v]=dis[now]+w;
          cnt[v]++;
          if(cnt[v]>=n) {sig_spfa_negflag=true; return dis;}
          if(!vis[v]){ Q.push(v);vis[v]=true; }
        }
      }
    }
    return dis;
  }
};