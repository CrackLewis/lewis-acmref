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
   * ISAP Maxflow Algorithm
   *
   *
   */
  i64 isap(int s, int t) {
    i64 flowsum = 0;
    vector<int> vis(n + 1), dis(n + 1), cur(n + 1), p(n + 1), num(n + 1);
    vector<int> flow(cap.size(), 0);
    // BFS: ISAP uses inverse search.
    auto isap_bfs = [&]() {
      fill(vis.begin(), vis.end(), 0);
      queue<int> Q;
      Q.push(t);
      vis[t] = 1, dis[t] = 0;
      while (Q.size()) {
        int x = Q.front();
        Q.pop();
        for (int i = 0, j; i < G[x].size(); ++i) {
          j = G[x][i] ^ 1;  // inserve edge
          if (!vis[from[j]] && cap[j] > flow[j]) {
            vis[from[j]] = 1;
            dis[from[j]] = dis[x] + 1;
            Q.push(from[j]);
          }
        }
      }
      return vis[s];
    };

    auto isap_augment = [&]() {
      int x = t, a = INT_MAX;
      while (x != s) {
        a = min(a, cap[p[x]] - flow[p[x]]);
        x = from[p[x]];
      }
      x = t;
      while (x != s) {
        flow[p[x]] += a;
        flow[p[x] ^ 1] -= a;
        x = from[p[x]];
      }
      return a;
    };

    isap_bfs();
    for (int i = 1; i <= n; ++i) num[dis[i]]++;
    int x = s;
    while (dis[s] < n) {
      if (x == t) {
        flowsum += isap_augment();
        x = s;
      }
      int ok = 0;
      for (int i = cur[x], j; i < G[x].size(); ++i) {
        j = G[x][i];
        if (cap[j] > flow[j] && dis[x] == dis[to[j]] + 1) {
          ok = 1;
          p[to[j]] = j;
          cur[x] = i;
          x = to[j];
          break;
        }
      }
      if (!ok) {
        int m = n - 1;
        for (int i = 0, j; i < G[x].size(); ++i) {
          j = G[x][i];
          if (cap[j] > flow[j]) m = min(m, dis[to[j]]);
        }
        if (--num[dis[x]] == 0) break;
        num[dis[x] = m + 1]++;
        cur[x] = 0;
        if (x != s) x = from[p[x]];
      }
    }
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
  cout << G.isap(s, t) << endl;
  return 0;
}