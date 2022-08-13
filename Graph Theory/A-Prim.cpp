// Implementation based on adjacency linklist.
template<typename WeTy=int>
struct graph1
{
  /* Refer to @-Graph Definition */

  // Minimum spanning tree - Prim Algorithm
  // Tell if an MST exists by checking if prim_ans==n-1.
  WeTy prim_sum; int prim_ans;
  graph1<WeTy> mst_prim()
  {
    //It's assumed here that the distance doesn't exceed INT_MAX.
    //Might need modification in specific problems.
    vector<WeTy> dis(n+1,WeTy(INT_MAX));
    vector<bool> vis(n+1,false);
    priority_queue<pair<int,int>> Q;
    map<int,int> pred;
    graph1<WeTy> res(n);

    prim_sum=WeTy(),prim_ans=0;
    dis[1]=WeTy(),Q.push(make_pair(-WeTy(),1));
    while(Q.size())
    {
      auto now=Q.top().second; Q.pop();
      if(vis[now]) continue;

      vis[now]=true;
      
      if(pred.count(now)) 
      {
        prim_ans++,prim_sum+=dis[now];
        // It's assumed that exporting graph is undirected.
        // Might need modification in specific problems.
        res.addedge(pred[now],now,dis[now]),res.addedge(now,pred[now],dis[now]);
      }

      for(int j=head[now];~j;j=nxt[j])
      {
        if(dis[to[j]]>we[j]&&!vis[to[j]])
        {
          dis[to[j]]=we[j],pred[to[j]]=now;
          Q.push(make_pair(-dis[to[j]],to[j]));
        }
      }
    }

    return res;
  }
};