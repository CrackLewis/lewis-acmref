#include <bits/stdc++.h>
using namespace std;

using i64 = long long int;

struct graph3 {
  vector<int> from, to;
  vector<int> cap;
  vector<vector<int>> G;
  int n, m;

  graph3(int _n) : n(_n), G(_n + 1, vector<int>()) {}
  // ATTENTION: this function add two directed edges into the network
  void addedge(int u, int v, int _cap = 0) {
    from.emplace_back(u), from.emplace_back(v);
    to.emplace_back(v), to.emplace_back(u);
    cap.emplace_back(_cap), cap.emplace_back(0);
    m = from.size();
    G[u].emplace_back(m - 2);
    G[v].emplace_back(m - 1);
  }

  /**
   * Dinic Maxflow Algorithm
   *
   *
   */
  i64 dinic(int s, int t) {
    vector<int> dis(n + 1), cur(n + 1), vis(n + 1);
    vector<int> flow(cap.size(), 0);
    i64 flowsum = 0;
    // BFS: check if t can be reached from s in the residue network
    auto dinic_bfs = [&]() {
      fill(vis.begin(), vis.end(), 0);
      queue<int> Q;
      Q.push(s);
      vis[s] = 1, dis[s] = 0;
      int x;
      while (Q.size()) {
        x = Q.front();
        Q.pop();
        for (auto j : G[x]) {
          if (!vis[to[j]] && cap[j] > flow[j]) {
            vis[to[j]] = 1;
            dis[to[j]] = dis[x] + 1;
            Q.push(to[j]);
          }
        }
      }
      return vis[t];
    };

    function<int(int, int)> dinic_dfs = [&](int x, int a) {
      if (x == t || a == 0) return a;
      int flowdiff = 0, f, j;
      for (int& i = cur[x]; i < G[x].size(); ++i) {
        j = G[x][i];
        if (dis[x] + 1 == dis[to[j]] &&
            (f = dinic_dfs(to[j], min(a, cap[j] - flow[j]))) > 0) {
          flow[j] += f;
          flow[j ^ 1] -= f;
          flowdiff += f;
          a -= f;
          if (a == 0) break;
        }
      }
      return flowdiff;
    };

    // we will repeatedly augment until there is no path to node t
    while (dinic_bfs()) {
      fill(cur.begin(), cur.end(), 0);
      flowsum += dinic_dfs(s, 0x3f3f3f3f);
    }
    /**
     * If you need min-cut, then do dfs to find every nodes connected to s in
     * residue network.
     */
    return flowsum;
  }
};

int main() {
  int n, m, s, t;
  cin >> n >> m >> s >> t;
  graph3 G(n);
  for (int i = 1, u, v, cap; i <= m; ++i) {
    cin >> u >> v >> cap;
    G.addedge(u, v, cap);
  }
  cout << G.dinic(s, t) << endl;
  return 0;
}