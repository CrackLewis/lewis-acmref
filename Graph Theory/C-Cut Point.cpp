#include <bits/stdc++.h>
using namespace std;

// Implementation based on adjacency linklist.
template <typename WeTy = int>
struct graph1 {
  vector<int> head, to, nxt;
  vector<WeTy> we;
  int n, eid;
  graph1(int _n) : n(_n), head(_n + 1, -1), eid(-1) {}
  void addedge(int u, int v, WeTy w = WeTy()) {
    assert((u >= 1 && v >= 1 && u <= n && v <= n) && "vertex out of range");
    to.emplace_back(v);
    nxt.emplace_back(head[u]);
    we.emplace_back(w);
    head[u] = ++eid;
  }

  /**
   * Cutpoint Algorithm
   *
   * A cutpoint is a point in an undirected connected graph without which the
   * located connected component will fall apart.
   *
   *
   */
  vector<int> cutpoint() {
    vector<int> vis(n + 1), flag(n + 1), dfn(n + 1), low(n + 1);
    int nid = 0, res = 0;
    // we need tarjan method to get dfn and low
    function<void(int, int)> tarjan_dfs = [&](int u, int fa) {
      vis[u] = 1;
      low[u] = dfn[u] = ++nid;
      int child = 0;
      for (int j = head[u], v; ~j; j = nxt[j]) {
        v = to[j];
        if (!vis[v]) {  // unvisited
          child++;
          tarjan_dfs(v, u);
          low[u] = min(low[u], low[v]);
          if (fa != u && low[v] >= dfn[u] && !flag[u]) {
            flag[u] = 1;
            res++;
          }
        } else if (v != fa) {
          low[u] = min(low[u], dfn[v]);
        }
      }
      if (fa == u && child >= 2 && !flag[u]) {
        flag[u] = 1;
        res++;
      }
    };

    for (int i = 1; i <= n; ++i) {
      if (!vis[i]) {
        nid = 0;
        tarjan_dfs(i, i);
      }
    }
    return flag;
  }
};