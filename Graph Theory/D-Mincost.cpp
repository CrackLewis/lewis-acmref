#include <bits/stdc++.h>
using namespace std;

using i64 = long long int;

struct graph3 {
  vector<int> from, to;
  vector<int> cap, cost;
  vector<vector<int>> G;
  int n, m;

  graph3(int _n) : n(_n), G(_n + 1, vector<int>()) {}

  void _addedge(int u, int v, int _cap, int _cost) {
    from.emplace_back(u);
    to.emplace_back(v);
    cap.emplace_back(_cap);
    cost.emplace_back(_cost);
    m = from.size();
    G[u].emplace_back(m - 1);
  }
  void addedge(int u, int v, int _cap, int _cost) {
    _addedge(u, v, _cap, _cost), _addedge(v, u, 0, -_cost);
  }

  // pair(maxflow, mincost)
  pair<i64, i64> mcmf(int s, int t) {
    i64 flowcost = 0, flowsum = 0;
    vector<int> pre(n + 1), vis(n + 1);
    vector<int> flow(cap.size(), 0);

    auto spfa = [&]() {
      vector<int> dis(n + 1, 0x3f3f3f3f);
      queue<int> Q;
      Q.push(s), vis[s] = 1, dis[s] = 0;
      while (Q.size()) {
        int x = Q.front();
        Q.pop(), vis[x] = 0;
        for (int i = 0, j, v; i < G[x].size(); ++i) {
          j = G[x][i], v = to[j];
          if (cap[j] > flow[j] && dis[v] > dis[x] + cost[j]) {
            dis[v] = dis[x] + cost[j];
            pre[v] = j;
            if (!vis[v]) Q.push(v), vis[v] = 1;
          }
        }
      }
      return dis[t];
    };

    int dis, f;
    while ((dis = spfa()) < 0x3f3f3f3f) {
      f = 0x3f3f3f3f;
      // calculate flow
      for (int j = t; j != s; j = from[pre[j]]) {
        f = min(f, cap[pre[j]] - flow[pre[j]]);
      }
      flowcost += dis * f;
      flowsum += f;
      // update flow value
      for (int j = t; j != s; j = from[pre[j]]) {
        flow[pre[j]] += f;
        flow[pre[j] ^ 1] -= f;
      }
    }
    return make_pair(flowsum, flowcost);
  }
};